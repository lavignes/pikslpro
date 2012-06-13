#ifndef PP_LIST_H
#define PP_LIST_H

typedef struct ppList ppList;

ppList* pp_list_new();

void pp_list_free(ppList* list);

void pp_list_pushfront(ppList* list, void* value);

void pp_list_pushback(ppList* list, void* value);

void* pp_list_popfront(ppList* list);

void* pp_list_popback(ppList* list);

void* pp_list_peekfront(ppList* list);

void* pp_list_peekback(ppList* list);

void pp_list_insertbefore(ppList* list, void* pos, void* value);

void pp_list_insertafter(ppList* list, void* pos, void* value);

void pp_list_remove(ppList* list, void* value);

void pp_list_removebefore(ppList* list, void* pos);

void pp_list_removeafter(ppList* list, void* pos);

#endif /* PP_LIST_H */
