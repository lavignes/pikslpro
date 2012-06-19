/**
 * @file pputil.c
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
 * Helpful utility functions
 *
 */
 
#include "pputil.h"
#include "ppapp.h"

guint rgba2argb(guint color) {

  guint alpha = color << 24;
  guint argb = color >> 8;
  argb |= alpha;
  
  return argb;
}

guint argb2rgba(guint color) {

  guint alpha = color >> 24;
  guint rgba = color << 8;
  rgba |= alpha;
  
  return rgba;
}

ppColor pp_color_premultiply(ppColor color) {
 
  ppColor new;
 
  gdouble mult = (gdouble)color.argb.a / 255;
  
  new.argb.r = color.argb.r * mult;
  new.argb.g = color.argb.g * mult;
  new.argb.b = color.argb.b * mult;
  new.argb.a = color.argb.a;
  
  return new;
}

void pp_color_pixbuf(GdkPixbuf* pb, guint color) {

  gint width = gdk_pixbuf_get_width(pb);
  gint height = gdk_pixbuf_get_height(pb);
  
  cairo_surface_t* surface = 
  cairo_image_surface_create_for_data(gdk_pixbuf_get_pixels(pb),
                                      CAIRO_FORMAT_ARGB32,
                                      width,
                                      height,
                                      gdk_pixbuf_get_rowstride(pb));
                                          
  cairo_t* cr = cairo_create(surface);
  
  cairo_set_source(cr, PP_APP->checker);
  
  pp_cairo_roundrect(cr, 1, 1, width-2, height-2, 10);
  cairo_fill(cr);
  
  // TODO: The color representations are off a bit for transparents
  
  ppColor c = (ppColor)color;
 
  cairo_set_source_rgba(cr, (gdouble)c.argb.b/255,
                            (gdouble)c.argb.g/255,
                            (gdouble)c.argb.r/255,
                            (gdouble)c.argb.a/255);
    
  pp_cairo_roundrect(cr, 1, 1, width-2, height-2, 10);
  cairo_fill(cr);
  
  cairo_set_source_rgb(cr, 0, 0, 0);
  
  pp_cairo_roundrect(cr, 1, 1, width-2, height-2, 10);
  
  cairo_stroke(cr);
  
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

// From cairographics.org cookbook
void pp_cairo_roundrect(cairo_t* cr, gint x, gint y, gint w, gint h, gint r) {
    
    cairo_move_to(cr, x + r, y);
    cairo_line_to(cr, x + w - r, y);
    cairo_curve_to(cr, x + w, y, x + w, y, x + w, y + r);
    cairo_line_to(cr, x + w, y + h - r);
    cairo_curve_to(cr, x + w, y + h, x + w, y + h, x + w - r, y + h);
    cairo_line_to(cr, x + r, y + h);
    cairo_curve_to(cr, x, y + h, x, y + h, x, y + h - r);
    cairo_line_to(cr, x, y + r);
    cairo_curve_to(cr, x, y, x, y, x + r, y);
}

cairo_pattern_t* pp_cairo_checkerboard() {

  cairo_t* context;
  cairo_surface_t* surface;
  cairo_pattern_t* pattern;
  
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 32, 32);
  
  context = cairo_create(surface);
  
  cairo_set_source_rgb(context, 0.6, 0.6, 0.6);
  cairo_rectangle(context, 0, 0, 16, 16);
  cairo_rectangle(context, 16, 16, 16, 16);
  cairo_fill(context);
  
  cairo_set_source_rgb(context, 0.4, 0.4, 0.4);
  cairo_rectangle(context, 16, 0, 16, 16);
  cairo_rectangle(context, 0, 16, 16, 16);
  cairo_fill(context);
  
  cairo_destroy(context);
  
  pattern = cairo_pattern_create_for_surface(surface);
  cairo_pattern_set_extend(pattern, CAIRO_EXTEND_REPEAT);
  
  cairo_surface_destroy(surface);
  
  return pattern;
}
