#include <cairo.h>

#include <jemalloc/jemalloc.h>

#include "ppdualpicker.h"

G_DEFINE_TYPE(ppDualPicker, pp_dualpicker, GTK_TYPE_DRAWING_AREA);

static gboolean pp_dualpicker_draw(GtkWidget* widget, cairo_t* cr) {

  /*g_return_val_if_fail(widget != NULL, FALSE);
  g_return_val_if_fail(PP_IS_DUALPICKER(widget), FALSE);
  g_return_val_if_fail(cr != NULL, FALSE);*/
  
  /*GtkAllocation allocation;
  gtk_widget_get_allocation(picker, &allocation);
  
  double x, y;
  x = allocation.x + allocation.width / 2;
  y = allocation.y + allocation.height / 2;
  
  double radius;
  radius = MIN (allocation.width / 2,
                allocation.height / 2) - 5;
                
  cairo_arc (cr, x, y, radius, 0, 2 * 3.1415926);
  
  cairo_set_source_rgb(cr, 0, 0, 1);
  cairo_fill_preserve(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_stroke(cr);*/
  
  cairo_scale(cr, 8, 8);
  
  cairo_set_source_surface(cr, PP_DUALPICKER(widget)->surface, 0, 0);
  
  cairo_paint(cr);

  return FALSE;
}

static gboolean pp_dualpicker_mouse_motion(GtkWidget* widget,
                                           GdkEventMotion* event) {

  ppDualPicker* picker = PP_DUALPICKER(widget);
  
  int position = cairo_image_surface_get_width(picker->surface) * (int)(event->y/8) + (int)(event->x/8);
  
  gint* pixel = picker->data + position;

  *pixel = 0xFF000000;
  
  cairo_surface_mark_dirty(picker->surface);
  
  gtk_widget_queue_draw(widget);

  return FALSE;
}

static void pp_dualpicker_class_init(ppDualPickerClass* class) {

  GtkWidgetClass* widget_class;

  widget_class = GTK_WIDGET_CLASS(class);

  widget_class->draw = pp_dualpicker_draw;
  widget_class->motion_notify_event = pp_dualpicker_mouse_motion;
}

static void pp_dualpicker_init(ppDualPicker* picker) {

  gtk_widget_add_events(GTK_WIDGET(picker), GDK_BUTTON_MOTION_MASK
                                            | GDK_BUTTON_PRESS_MASK);


  picker->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 800, 600);
                                                        
  picker->data = (gint*)cairo_image_surface_get_data(picker->surface);
}

GtkWidget* pp_dualpicker_new() {

  return g_object_new(PP_TYPE_DUALPICKER, NULL);
}

