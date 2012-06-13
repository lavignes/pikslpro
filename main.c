#include <gtk/gtk.h>

#include "pptree.h"

void func(char* key, void* value) {

  printf("\t[\"%s\"] => %d\n", key, *(int*)value);
}

int main(int argc, char* argv[]) {

  GtkWidget* window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show(window);

  gtk_main();

  ppTree* tree = pp_tree_new();

  int num = 42;

  printf("test1:\n");
  pp_tree_insert(tree, "hello", &num);
  pp_tree_insert(tree, "test", &num);
  pp_tree_insert(tree, "piksl", &num);
  pp_tree_insert(tree, "hellos", &num);
  pp_tree_traverse(tree, func);

  printf("test2:\n");
  pp_tree_remove(tree, "hellos");
  pp_tree_traverse(tree, func);

  pp_tree_free(tree);

  return 0;
}
