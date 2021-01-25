#pragma once

#define OP_NOP 0x90
#define OP_JMP 0xE9
#define OP_JMP_LEN 5

typedef void (*fn_ptr_t)(); //pointer to a function

fn_ptr_t install_void_hook(void* src, fn_ptr_t f, int len);
