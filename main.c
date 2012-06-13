#include "ppapp.h"

#include "structs/pplist.h"

void dothis(void* text, void* data) {

  data = data;
  printf("%s\n", (char*)text);
}

int main(int argc, char* argv[]) {

  pp_app_init(argc, argv);
  
  return 0;
}
