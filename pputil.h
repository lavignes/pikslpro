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

guint rgba2argb(guint color);

guint argb2rgba(guint color);

void pp_color_pixbuf(GdkPixbuf* pb, guint color);

#endif /* PP_UTILITY */
