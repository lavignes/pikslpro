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
 * A widget for smart color picking
 *
 */

#ifndef PP_PIKSL_H
#define PP_PIKSL_H

#include <gtk/gtk.h>

#define PP_TYPE_PICKER             (pp_picker_get_type())
#define PP_PICKER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), PP_TYPE_PICKER, ppPicker))
#define PP_PICKER_CLASS(obj)       (G_TYPE_CHECK_CLASS_CAST ((obj), PP_PICKER, ppPickerClass))
#define PP_IS_PICKER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PP_TYPE_PICKER))
#define PP_IS_PICKER_CLASS(obj)    (G_TYPE_CHECK_CLASS_TYPE ((obj), PP_TYPE_PICKER))
#define PP_PICKER_GET_CLASS        (G_TYPE_INSTANCE_GET_CLASS ((obj), PP_TYPE_PICKER, ppPickerClass))

typedef struct ppPicker {

  GtkDrawingAreaClass parent;
  
} ppPicker;

typedef struct ppPickerClass  {

  GtkDrawingAreaClass parent_class;
  
} ppPickerClass;

GtkWidget* pp_picker_new();

#endif /* PP_PICKER_H */
