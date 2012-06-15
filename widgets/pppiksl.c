/**
 * @file pppiksl.c
 * @author  Scott LaVigne <scott.lavigne@linux.com>
 * @version 0.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Widget that manages an open piksl project.
 *
 */
 
#include <stdlib.h>

#include <cairo.h>

#include "pppiksl.h"
#include "../pplayer.h"
#include "../ppapp.h"

G_DEFINE_TYPE(ppPiksl, pp_piksl, GTK_TYPE_DRAWING_AREA);

static gboolean pp_piksl_draw(GtkWidget* widget, cairo_t* cr) {

  ppPiksl* piksl = PP_PIKSL(widget);

  // Draw the background color
  cairo_set_source_rgb(cr, 
                       piksl->alpha_color & 0x00FF0000,                        
                       piksl->alpha_color & 0x0000FF00,
                       piksl->alpha_color & 0x000000FF);

  
  cairo_rectangle(cr, 0, 0,
                  piksl->img_width*piksl->zoom,
                  piksl->img_height*piksl->zoom);
  cairo_fill(cr);

  // Render the graphics data...
  // Zoom the surface

  cairo_scale(cr, piksl->zoom, piksl->zoom);


  
  // Render each layer
  guint i;
  ppLayer* layer = NULL;
  for (i = 0; i < piksl->layers->len; ++i) {
  
    layer = g_ptr_array_index(piksl->layers, i);
    cairo_set_source_surface(cr, layer->surface, layer->x, layer->y);
    
    cairo_paint(cr);
  }
  
  return FALSE;
}

static gboolean pp_piksl_mouse_motion(GtkWidget* widget,
                                      GdkEventMotion* event) {
                                        
  ppPiksl* piksl = PP_PIKSL(widget);                                      
  
  if (piksl->lastx != -1 || piksl->lasty != -1) {
  
    ppLayer* layer = g_ptr_array_index(piksl->layers, piksl->active_layer);
    
    // Draw a line
    int dx = abs((int)event->x - piksl->lastx);
    int dy = abs((int)event->y - piksl->lasty);
    
    int sx = (piksl->lastx < (int)event->x)? 1 : -1;
    int sy = (piksl->lasty < (int)event->y)? 1 : -1;
    
    int err = dx-dy;
    int e2 = 2*err;
    
    while (TRUE) {
    
      // Write the color to the raster array
      //*(layer->data + cairo_image_surface_get_width(layer->surface)
      //* (int)(piksl->lasty/piksl->zoom)
      //+ (int)(piksl->lastx/piksl->zoom)) = PP_APP->color1;

      *pp_layer_pixel(layer, (int)(piksl->lastx/piksl->zoom),
                             (int)(piksl->lasty/piksl->zoom)) = PP_APP->color1;
      
      if (piksl->lastx == (int)event->x && piksl->lasty == (int)event->y) break;
      
      e2 = 2*err;
      if (e2 > -dy) {
      
        err -= dy;
        piksl->lastx += sx;
      }
      
      if (e2 < dx) {
      
        err += dx;
        piksl->lasty += sy;
      }
    }
    
    cairo_surface_mark_dirty(layer->surface);
    
    // Ask the widget to redraw itself
    gtk_widget_queue_draw(widget);
  
  }

  piksl->lastx = (int)event->x;
  piksl->lasty = (int)event->y;

  return FALSE;
}

static gboolean
pp_piksl_mouse_release(GtkWidget* widget, GdkEventButton* event) {

  ppPiksl* piksl = PP_PIKSL(widget);
  
  piksl->lastx = -1;
  piksl->lasty = -1;
  
  if (event->button == 3) {
  
    gdouble zoom = PP_PIKSL(widget)->zoom;
    
    zoom = (zoom > 10)? 1 : zoom+1;
    
    pp_piksl_set_zoom(PP_PIKSL(widget), zoom);
  }
  
  return FALSE;
}

static void pp_piksl_class_init(ppPikslClass* class) {

  GtkWidgetClass* widget_class;

  widget_class = GTK_WIDGET_CLASS(class);

  widget_class->draw = pp_piksl_draw;
  widget_class->motion_notify_event = pp_piksl_mouse_motion;
  widget_class->button_release_event = pp_piksl_mouse_release;
}

static void pp_piksl_init(ppPiksl* piksl) {

  gtk_widget_add_events(GTK_WIDGET(piksl), GDK_BUTTON_MOTION_MASK
                                           | GDK_BUTTON_PRESS_MASK
                                           | GDK_BUTTON_RELEASE_MASK);
                   
  piksl->img_width = 800;
  piksl->img_height = 600;   
                                           
  piksl->lastx = -1;
  piksl->lasty = -1;
  
  piksl->zoom = 1;
  
  piksl->alpha_color = 0xFFFFFFFF;
  
  piksl->layers = g_ptr_array_new();
  piksl->active_layer = 0;
  
  g_ptr_array_add(piksl->layers, pp_layer_new(piksl->img_width, piksl->img_height));
  
  gtk_widget_set_size_request(GTK_WIDGET(piksl),
                              piksl->img_width*piksl->zoom,
                              piksl->img_height*piksl->zoom);
}

GtkWidget* pp_piksl_new() {

  return g_object_new(PP_TYPE_PIKSL, NULL);
}

void pp_piksl_set_zoom(ppPiksl* piksl, gdouble zoom) {

  if (zoom <= 0)
    zoom = 1;

  piksl->zoom = zoom;
  
  // Resize the widget after zoom requests
  gtk_widget_set_size_request(GTK_WIDGET(piksl),
                              piksl->img_width*piksl->zoom,
                              piksl->img_height*piksl->zoom);
                            
  // Ask the widget to redraw itself
  gtk_widget_queue_draw(GTK_WIDGET(piksl));
}

