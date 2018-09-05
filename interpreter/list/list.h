#pragma once

#include <bytebuffer/bytebuffer.h>
#include "../YASL_Object/YASL_Object.h"
#include "../../hashtable/hashtable.h"

typedef struct List_s {
    int size;
    int count;
    YASL_Object* items;
    RefCount *rc;
} List_t;

YASL_Object YASL_List(List_t *ls);
int isvalueinarray(int64_t val, int64_t *arr, int size);
List_t *ls_new(void);
List_t* ls_new_sized(const int base_size);
void ls_del_data(List_t *ls);
void ls_del_rc(List_t *ls);
void ls_insert(List_t* ls, int64_t index, YASL_Object value);
void ls_append(List_t* ls, YASL_Object value);
YASL_Object ls_search(List_t *ls, int64_t index);
void ls_reverse(List_t *ls);
void ls_print(List_t* ls);
void ls_print_h(List_t* ls, ByteBuffer *seen);