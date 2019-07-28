#include "int_methods.h"

#include "yasl_state.h"

int int_toint(struct YASL_State *S) {
	ASSERT_TYPE((struct VM *) S, Y_INT, "int64.toint");
	return 0;
}

int int_tofloat(struct YASL_State *S) {
	ASSERT_TYPE((struct VM *) S, Y_INT, "int64.tofloat");
	vm_pushfloat((struct VM *) S, (yasl_float) YASL_GETINT(vm_pop((struct VM *) S)));
	return 0;
}

int int_tostr(struct YASL_State *S) {
	ASSERT_TYPE((struct VM *) S, Y_INT, "int64.tostr");
	yasl_int val = YASL_GETINT(vm_pop((struct VM *) S));
	char *ptr = (char *)malloc(snprintf(NULL, 0, "%" PRId64 "", val) + 1);
	sprintf(ptr, "%" PRId64 "", val);
	struct YASL_String *string = YASL_String_new_sized_heap(0, snprintf(NULL, 0, "%" PRId64 "", val), ptr);
	VM_PUSH((struct VM *) S, YASL_STR(string));
	return 0;
}
