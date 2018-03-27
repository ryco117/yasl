#pragma once

enum opcodes {
NOP       = 0x00, // pass
NCONST    = 0x01, // push literal undef onto stack
ICONST    = 0x02, // push next 8 bytes onto stack as integer constant
ICONST_M1 = 0x03, // push -1 onto stack
ICONST_0  = 0x04, // push 0 onto stack
ICONST_1  = 0x05, // push 1 onto stack
ICONST_2  = 0x06, // push 2 onto stack
ICONST_3  = 0x07, // push 3 onto stack
ICONST_4  = 0x08, // push 4 onto stack
ICONST_5  = 0x09, // push 5 onto stack
DCONST    = 0x0A, // push next 8 bytes onto st4ack as float constant
DCONST_0  = 0x0B, // push 0.0 onto stack
DCONST_1  = 0x0C, // push 1.0 onto stack
DCONST_2  = 0x0D, // push 2.0 onto stack
BCONST_F  = 0x0E, // push literal false onto stack
BCONST_T  = 0x0F, // push literal true onto stack
MLC_8     = 0x50, // allocate memory (takes next 1 byte as type, next 8 bytes as length)
MCP_8     = 0x52, // copy from memory (takes next byte as offset, next 8 bytes as length, next <length> bytes as data.
DUP       = 0x58, // duplicate top value of stack
SWAP      = 0x5B, // swap top two elements of the stack
POP       = 0x5F, // pop top of stack
ADD       = 0x60, // add two integers
SUB       = 0x61, // subtract two integers
MUL       = 0x62, // multiply two integers
DIV       = 0x64, // divide two integers
IDIV      = 0x65, // divide two ints (return int)
MOD       = 0x66, // modulo two numbers
NEG       = 0x67, // negate an integer
NOT       = 0x69, // negate a boolean
LEN       = 0x6A, // get length
CONCAT    = 0x6B, // concat two strings or lists
COPY      = 0x6C, // get a deep copy
GT        = 0x72, // greater than
GE        = 0x73, // greater than or equal
EQ        = 0x74, // equality
ID        = 0x76, // identity
V2S       = 0x84, // variable to string
BR_4      = 0x90, // branch unconditionally (takes next 4 bytes as jump length)
BR_8      = 0x91, // branch unconditionally (takes next 8 bytes as jump length)
BRF_4     = 0x92, // branch if condition is falsey (takes next 4 bytes as jump length)
BRF_8     = 0x93, // branch if condition is falsey (takes next 8 bytes as jump length)
BRT_4     = 0x94, // branch if condition is truthy (takes next 4 bytes as jump length)
BRT_8     = 0x95, // branch if condition is truthy (takes next 8 bytes as jump length)
BRN_4     = 0x96, // branch if condition is not undef (takes next 4 bytes as jump length)
BRN_8     = 0x97, // branch if condition is not undef (takes next 8 bytes as jump length)
NEWSTR8   = 0xBB, // make new String and push it onto stack (length (8 bytes), string (length bytes))
NEWHASH   = 0xBC, // make new HashTable and push it onto stack
NEWLIST   = 0xBD, // make new List and push it onto stack
HALT      = 0xF0, // halt
PRINT     = 0xF2, // print top of stack (temporary to allow debugging)
GSTORE_1  = 0xF4, // store top of stack at addr provided
LSTORE_1  = 0xF5, // store top of stack as local at addr
GLOAD_1   = 0xF6, // load global from addr
LLOAD_1   = 0xF7, // load local from addr
RET       = 0xF8, // return from function
CALL_8    = 0xF9, // function call (# of parameters (1 byte), addr (8 bytes), # of locals (1 byte))
RCALL_8   = 0xFA, // tail recursive function call
BCALL_8   = 0xFB, // built-in function call
MCALL_8   = 0xFC, // method call
};
