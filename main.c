/*
 ============================================================================
 Name        : VM
 Author      : Thiabaud Engelbrecht
 Version     : 0.0
 Copyright   :
 Description : Bytecode VM. Must be compiled with GCC
 ============================================================================
 */
#include <inttypes.h>
#include "VM.c"
#include "opcode.c"
#include "types.c"
//#include "constant.c"
#define BUFFER_SIZE 256
#define PUSH(vm, v)  (vm->stack[++vm->sp] = v) // push value on top of the stack
#define POP(vm)      (vm->stack[vm->sp--])    // pop value from top of the stack as integer
#define NCODE(vm)    (vm->code[vm->pc++])     // get next bytecode
#define IPUSH(vm, v) (PUSH(vm, ((Constant) {INT64, v})))  //push integer v onto stack
#define DPUSH(vm, v) (((FloatConstant*)vm->stack)[++vm->sp] = (FloatConstant) {FLOAT64, v}) // push double v onto stack
#define DPOP(vm)     (((double*)vm->stack)[vm->sp--])

void run(VM* vm){
    for (;;) {
        unsigned char opcode = NCODE(vm);        // fetch
        int addr, offset, argc, rval;
        Constant a, b, v;
        int64_t c;
        double d;
        //double c, d;
        unsigned char bytes[8];
        printf("opcode = %x\n", opcode);
        switch (opcode) {   // decode
        case HALT: return;  // stop the program
        case JMP:
        	vm->pc = NCODE(vm);
        	break;
        case ICONST_M1:
            IPUSH(vm, -1);
            break;
        case ICONST_0:
            IPUSH(vm, 0);
            break;
        case ICONST_1:
            IPUSH(vm, 1);
            break;
        case ICONST_2:
            IPUSH(vm, 2);
            break;
        case ICONST_3:
            IPUSH(vm, 3);
            break;
        case ICONST_4:
            IPUSH(vm, 4);
            break;
        case ICONST_5:
            IPUSH(vm, 5);
            break;
        case DCONST_0:
            DPUSH(vm, 0.0);
            break;
        case DCONST_1:
            DPUSH(vm, 1.0);
            break;
        case DCONST_2:
            DPUSH(vm, 2.0);
            break;
        case ADD:
            b = POP(vm);
            a = POP(vm);
            if (a.type == INT64 && b.type == INT64) {
                a.value += b.value;
                PUSH(vm, a);
                break;
            }
            else if (a.type == FLOAT64 && b.type == INT64) {
                d = *((double*)&a.value) + (double)b.value;
            }
            else if (a.type == INT64 && b.type == FLOAT64) {
                d = (double)a.value + *((double*)&b.value);
            }
            else if (a.type == FLOAT64 && b.type == FLOAT64) {
                d = *((double*)&a.value) + *((double*)&b.value);
            }
            else {
                printf("ERROR: + not supported for operands of types %x and %x.\n", a.type, b.type);
                return;
            }
            DPUSH(vm, d);
            break;
        case MUL:
            b = POP(vm);
            a = POP(vm);
            if (a.type == INT64 && b.type == INT64) {
                a.value *= b.value;
                PUSH(vm, a);
                break;
            }
            else if (a.type == FLOAT64 && b.type == INT64) {
                d = *((double*)&a.value) * (double)b.value;
            }
            else if (a.type == INT64 && b.type == FLOAT64) {
                d = (double)a.value * *((double*)&b.value);
            }
            else if (a.type == FLOAT64 && b.type == FLOAT64) {
                d = *((double*)&a.value) * *((double*)&b.value);
            }
            else {
                printf("ERROR: * not supported for operands of types %x and %x.\n", a.type, b.type);
                return;
            }
            DPUSH(vm, d);
            break;
        case SUB:
            b = POP(vm);
            a = POP(vm);
            if (a.type == INT64 && b.type == INT64) {
                a.value -= b.value;
                PUSH(vm, a);
                break;
            }
            else if (a.type == FLOAT64 && b.type == INT64) {
                d = *((double*)&a.value) - (double)b.value;
            }
            else if (a.type == INT64 && b.type == FLOAT64) {
                d = (double)a.value - *((double*)&b.value);
            }
            else if (a.type == FLOAT64 && b.type == FLOAT64) {
                d = *((double*)&a.value) - *((double*)&b.value);
            }
            else {
                printf("ERROR: - not supported for operands of types %x and %x.\n", a.type, b.type);
                return;
            }
            DPUSH(vm, d);
            break;
        case DIV:
            b = POP(vm);
            a = POP(vm);
            if (a.type == INT64 && b.type == INT64) {
                d = (double)a.value / (double)b.value;
            }
            else if (a.type == FLOAT64 && b.type == INT64) {
                d = *((double*)&a.value) / (double)b.value;
            }
            else if (a.type == INT64 && b.type == FLOAT64) {
                d = (double)a.value / *((double*)&b.value);
            }
            else if (a.type == FLOAT64 && b.type == FLOAT64) {
                d = *((double*)&a.value) / *((double*)&b.value);
            }
            else {
                printf("ERROR: / not supported for operands of types %x and %x.\n", a.type, b.type);
                return;
            }
            DPUSH(vm, d);
            break;
        //case I2D: TODO: implement
        //case D2I: TODO: implement
        //case NEG: TODO: implement
        //case DCONST: TODO: implement
        //case ICONST: TODO: implement
        /*
        case DCONST:
        case ICONST: // constants are BIG endian
            b = 0;
            for (a = 56; a >= 0; a -= 8) {
              unsigned char next = NCODE(vm);
              b += ((int64_t)next) << a;
            }
            PUSH(vm, b);
            break;
        case GLOAD:
            addr = NCODE(vm);             // get pointer address from code ...
            v = vm->locals[addr];         // ... load value from memory of the provided addres ...
            PUSH(vm, v);                // ... and put that value on top of the stack
            break;
        case GSTORE:
            v = POP(vm);                // get value from top of the stack ...
            addr = NCODE(vm);           // ... get pointer address from code ...
            vm->locals[addr] = v;         // ... and store value at address received
            break; //
        case GDLOAD:
            addr = NCODE(vm);             // get pointer address from code ...
            v = ((double*)vm->locals)[addr];         // ... load value from memory of the provided addres ...
            DPUSH(vm, v);                // ... and put that value on top of the stack
            break;
        case GDSTORE:
            v = DPOP(vm);                // get value from top of the stack ...
            addr = NCODE(vm);           // ... get pointer address from code ...
            ((double*)vm->locals)[addr] = v;         // ... and store value at address received
            break; //*/
        case POP:
            --vm->sp;      // throw away value at top of the stack
            break;
        case PRINT:
            v = POP(vm);        // pop value from top of the stack ...
            //printf("%x\n", v.type); // print value
            switch (v.type) {
            case INT64:
                printf("\tint64: %" PRId64 "\n", v.value);
                break;
            case FLOAT64:
                printf("\tfloat64: %f\n", *((double*)&v.value));
                break;
            default:
                printf("ERROR UNKNOWN TYPE: %x\n", v.type);
                break;
            }
            break;
        default:
            printf("ERROR UNKNOWN OPCODE: %x\n", opcode);
            break;
        }

    }
}

char *buffer;
FILE *file_ptr;
long file_len;

int main(void) {
    file_ptr = fopen("source.bc", "rb");
    fseek(file_ptr, 0, SEEK_END);
    file_len = ftell(file_ptr);
    rewind(file_ptr);
    buffer = (char *)malloc((file_len+1)*sizeof(char));
    fread(buffer, file_len, 1, file_ptr);
    //bytes_read = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, file_ptr);
	VM* vm = newVM(buffer,   // program to execute
	                   0,    // start address of main function
	                   0);   // locals to be reserved, fib doesn't require them
	run(vm);
    fclose(file_ptr);
	return 0;
};