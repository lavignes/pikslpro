/**
 * @file pppiksl.h
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

#ifndef PP_PIKSL_H
#define PP_PIKSL_H

#include <gtk/gtk.h>

#define PP_TYPE_PIKSL             (pp_piksl_get_type())
#define PP_PIKSL(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), PP_TYPE_PIKSL, ppPiksl))
#define PP_PIKSL_CLASS(obj)       (G_TYPE_CHECK_CLASS_CAST ((obj), PP_PIKSL, ppPikslClass))
#define PP_IS_PIKSL(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PP_TYPE_PIKSL))
#define PP_IS_PIKSL_CLASS(obj)    (G_TYPE_CHECK_CLASS_TYPE ((obj), PP_TYPE_PIKSL))
#define PP_PIKSL_GET_CLASS        (G_TYPE_INSTANCE_GET_CLASS ((obj), PP_TYPE_PIKSL, ppPikslClass))

typedef struct ppPiksl {

  GtkDrawingAreaClass parent;
  
  int img_width;
  int img_height;
  
  gint lastx;
  gint lasty;
  
  gdouble zoom;
  
  guint color;
  // TODO: Maybe change the bg color to a pattern (eg. checkerboards)
  guint alpha_color; // "transparent" bg color
  
  gint tool_id;
  
  // The surface where tools are drawn to
  cairo_surface_t* tool_surface;
 
  GPtrArray* layers;
  guint active_layer;
  
} ppPiksl;

typedef struct ppPikslClass  {

  GtkDrawingAreaClass parent_class;
  
} ppPikslClass;

GtkWidget* pp_piksl_new();

#endif /* PP_PIKSL_H */
