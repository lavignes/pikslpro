/**
 * @file pppicker.h
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
 * A color square widget
 *
 */

#ifndef PP_SQUARE_H
#define PP_SQUARE_H

#include <gtk/gtk.h>

#define PP_TYPE_SQUARE             (pp_picker_get_type())
#define PP_SQUARE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), PP_TYPE_SQUARE, ppSquare))
#define PP_SQUARE_CLASS(obj)       (G_TYPE_CHECK_CLASS_CAST ((obj), PP_SQUARE, ppSquareClass))
#define PP_IS_SQUARE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PP_TYPE_SQUARE))
#define PP_IS_SQUARE_CLASS(obj)    (G_TYPE_CHECK_CLASS_TYPE ((obj), PP_TYPE_SQUARE))
#define PP_SQUARE_GET_CLASS        (G_TYPE_INSTANCE_GET_CLASS ((obj), PP_TYPE_SQUARE, ppSquareClass))

typedef struct ppSquare {

  GdkPixbuf parent;
  
} ppSquare;

typedef struct ppPickerClass  {

  GtkIconViewClass parent_class;
  
} ppPickerClass;

GtkWidget* pp_picker_new();

#endif /* PP_PICKER_H */
