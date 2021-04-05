#pragma once

#include <vector>

#define OP_NOP 0x90
#define OP_JMP 0xE9
#define OP_JMP_LEN 5

#define OP_CALL_LEN 6

typedef void (*fn_ptr_t)();

fn_ptr_t install_void_hook(void* src, fn_ptr_t f, int len);

uintptr_t follow_offsets(uintptr_t ptr, std::vector<uintptr_t> offsets);

bool __stdcall set_call_func(void* src, fn_ptr_t f);

bool set_nops(void* adr, unsigned int len);
