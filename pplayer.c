/**
 * @file pplayer.c
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

#include <jemalloc/jemalloc.h>

#include "pplayer.h"

ppLayer* pp_layer_new(int width, int height) {

  ppLayer* layer = malloc(sizeof(ppLayer));
  
  layer->width = width;
  layer->height = height;
  
  layer->alpha = 1.0;
  
  layer->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
                                                        
  layer->data = (gint*)cairo_image_surface_get_data(layer->surface);
  
  return layer;
}

void pp_layer_free(ppLayer* layer) {

  if (layer != NULL) {
  
    cairo_surface_destroy(layer->surface);
    free(layer);
  }
}
