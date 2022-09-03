#pragma once

#ifndef OS_SPECIFIC_H
#define OS_SPECIFIC_H

#include "patcher_interface.h"

void ConsoleOut(const char* text);

void* __cdecl operator new  (size_t  size);
void __cdecl operator delete  (void* ptr);

_ptr_ _CodeAlloc(_size_t_ size, _size_t_ max_size = 0);
#define CodeAlloc(size) _CodeAlloc(size)
#define CodePreAlloc(max_size) _CodeAlloc(0, max_size)

// prepares memory for setting a patch / hook 
class Unprotect {

private:
	_dword_ protect_;
	_ptr_ address_;
	_size_t_ size_;

public:
	Unprotect(_ptr_ address, _size_t_ size);
	~Unprotect();
};

#endif //OS_SPECIFIC_H