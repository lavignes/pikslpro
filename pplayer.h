#ifndef PP_LAYER_H
#define PP_LAYER_H

#include <cairo.h>
#include <glib.h>

typedef struct ppLayer {

  int width;
  int height;
  
  double alpha;
  
  cairo_surface_t* surface;
  gint* data;

} ppLayer;

ppLayer* pp_layer_new(int width, int height);

void pp_layer_free(ppLayer* layer);

#endif /* PP_LAYER_H */
