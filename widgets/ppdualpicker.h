#ifndef PP_DUALPICKER_H
#define PP_DUALPICKER_H

#include <gtk/gtk.h>

#define PP_TYPE_DUALPICKER              (pp_dualpicker_get_type())
#define PP_DUALPICKER(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), PP_TYPE_DUALPICKER, ppDualPicker))
#define PP_DUALPICKER_CLASS(obj)        (G_TYPE_CHECK_CLASS_CAST ((obj), PP_DUALPICKER,  ppDualPickerClass))
#define PP_IS_DUALPICKER(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PP_TYPE_DUALPICKER))
#define PP_IS_DUALPICKER_CLASS(obj)     (G_TYPE_CHECK_CLASS_TYPE ((obj), PP_TYPE_DUALPICKER))
#define PP_DUALPICKER_GET_CLASS        (G_TYPE_INSTANCE_GET_CLASS ((obj), PP_TYPE_DUALPICKER, ppDualPickerClass))

typedef struct ppDualPicker {

  GtkDrawingAreaClass parent;
 
  cairo_surface_t* surface;
  gint* data;
  int width;
  
} ppDualPicker;

typedef struct ppDualPickerClass  {

  GtkDrawingAreaClass parent_class;
  
} ppDualPickerClass;

GtkWidget* pp_dualpicker_new();

#endif /* PP_DUALPICKER_H */
