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
 * A widget for smart color picking
 *
 */

#include "pppicker.h"
#include "../ppapp.h"

enum {

  COL_IMG,
  COL_COLOR,
  NUM_COLUMNS
};

G_DEFINE_TYPE(ppPicker, pp_picker, GTK_TYPE_ICON_VIEW);

static void pp_picker_class_init(ppPickerClass* class) {

  //GtkWidgetClass* widget_class;

  //widget_class = GTK_WIDGET_CLASS(class);
}

static void pp_picker_init(ppPicker* picker) {

  picker->color_list = gtk_list_store_new(NUM_COLUMNS, GDK_TYPE_PIXBUF, G_TYPE_UINT);
  
  //GtkTreeIter iter;
  //gtk_list_store_append(picker->color_list, &iter);
  
  gtk_icon_view_set_model(GTK_ICON_VIEW(picker), GTK_TREE_MODEL(picker->color_list));
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(picker), COL_IMG);

}

GtkWidget* pp_picker_new() {

  return g_object_new(PP_TYPE_PICKER, NULL);
}
