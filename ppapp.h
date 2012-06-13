#ifndef PP_APP_H
#define PP_APP_H

#include <gtk/gtk.h>

#include "pppiksl.h"

typedef struct ppApp {

  GtkWidget* window;

} ppApp;

extern ppApp* PP_APP;

void pp_app_init(int argc, char* argv[]);

#endif /* PP_APP_H */
