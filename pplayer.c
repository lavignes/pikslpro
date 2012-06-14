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
