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

#include <cairo.h>

#include "pppicker.h"
#include "../ppapp.h"

G_DEFINE_TYPE(ppPicker, pp_picker, GTK_TYPE_DRAWING_AREA);

static gboolean pp_picker_draw(GtkWidget* widget, cairo_t* cr) {

  return FALSE;
}

static void pp_picker_class_init(ppPickerClass* class) {

  GtkWidgetClass* widget_class;

  widget_class = GTK_WIDGET_CLASS(class);

  widget_class->draw = pp_picker_draw;
}

static void pp_picker_init(ppPicker* picker) {

  gtk_widget_add_events(GTK_WIDGET(picker), GDK_BUTTON_PRESS_MASK);
}

GtkWidget* pp_picker_new() {

  return g_object_new(PP_TYPE_PICKER, NULL);
}
