#include <stdio.h>
#include <stdlib.h>
#include "VM.h"

VM* newVM(char* code,    // pointer to bytecode
    int pc,              // address of instruction to be executed first -- entrypoint
    int datasize) {      // total locals size required to perform a program operations
    VM* vm = malloc(sizeof(VM));
    vm->code = code;
    vm->pc = pc;
    vm->fp = 0;
    vm->sp = -1;
    vm->globals = malloc(sizeof(Constant) * datasize);
    vm->stack = malloc(sizeof(Constant) * STACK_SIZE);
    vm->builtins_vtable = malloc(sizeof(VTable_t*) * 5);
    vm->builtins_vtable[0] = float64_builtins();
    vm->builtins_vtable[1] = int64_builtins();
    vm->builtins_vtable[2] = str8_builtins();
    vm->builtins_vtable[3] = list_builtins();
    vm->builtins_vtable[4] = hash_builtins();
    return vm;
}

void delVM(VM* vm){
        free(vm->globals);                   // TODO: free these properly
        free(vm->stack);                     // TODO: free these properly
        del_vtable(vm->builtins_vtable[0]);
        del_vtable(vm->builtins_vtable[1]);
        del_vtable(vm->builtins_vtable[2]);
        del_vtable(vm->builtins_vtable[3]);
        del_vtable(vm->builtins_vtable[4]);
        free(vm->builtins_vtable);
        free(vm);
}
