/**
 * @file pputil.h
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

#ifndef PP_UTILITY
#define PP_UTILITY

#include <gtk/gtk.h>

typedef union ppColor {

  guint color;
  
  struct {
  
    guchar b;
    guchar g;
    guchar r;
    guchar a;
    
  } argb;
  
} ppColor;

guint rgba2argb(guint color);

guint argb2rgba(guint color);

ppColor pp_color_premultiply(ppColor color);
ppColor pp_color_unmultiply(ppColor color);

void pp_color_pixbuf(GdkPixbuf* pb, guint color);
void pp_cairo_roundrect(cairo_t* cr, gint x, gint y, gint width, gint height, gint radius);
cairo_pattern_t* pp_cairo_checkerboard();

#endif /* PP_UTILITY */
