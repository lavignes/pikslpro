/**
 * @file pplayer.h
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
 * Structure for managing pixel data.
 *
 */

#ifndef PP_LAYER_H
#define PP_LAYER_H

#include <cairo.h>
#include <glib.h>

typedef struct ppLayer {

  int width;
  int height;
  
  double alpha;
  gboolean visible;
  
  cairo_surface_t* surface;
  gint* data;

} ppLayer;

ppLayer* pp_layer_new(int width, int height);

void pp_layer_free(ppLayer* layer);

#endif /* PP_LAYER_H */
