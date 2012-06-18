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
  
  // Pixbufs have a weird format.
  // I flipped red and blue
  cairo_set_source_rgba(cr, 
                        color & 0x000000FF,                        
                        color & 0x0000FF00,
                        color & 0x00FF0000,
                        color & 0xFF000000);
    
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);
  
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_stroke(cr);
  
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}
