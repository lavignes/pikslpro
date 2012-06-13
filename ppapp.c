#include <jemalloc/jemalloc.h>

#include "ppapp.h"

ppApp* PP_APP = NULL;

void pp_app_init(int argc, char* argv[]) {

  // Create appdata instance
  PP_APP = malloc(sizeof(ppApp));

  // Initialize gtk and create the main window
  gtk_init(&argc, &argv);
  PP_APP->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(PP_APP->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show(PP_APP->window);

  // Start gtk main thread
  gtk_main();
}
