// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#define NOINLINE __declspec(noinline)

#include "os_specific.h"
#include <windows.h>


//###################################################################################################


NOINLINE void ConsoleOut(const char* text) {

	static bool initialized = false;
	if (!initialized) {

		AllocConsole(); //Kernel32.lib
		initialized = true;
	}


	DWORD Written;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
	GetConsoleScreenBufferInfo(hOutput, &BufferInfo);
	WriteConsoleA(hOutput, text, strlen(text), &Written, NULL);
}



//###################################################################################################

HANDLE g_process_heap = NULL;

void* __cdecl operator new(size_t size)
{
	if (!g_process_heap) g_process_heap = GetProcessHeap();
	if (!g_process_heap) return NULL;
	return HeapAlloc(g_process_heap, 0, size);
}

void __cdecl operator delete(void* ptr)
{
	if (!g_process_heap) return;
	HeapFree(g_process_heap, 0, ptr);
}

//###################################################################################################

#define CODE_ALLOCATION_GRANULARITY 0x10000
#define VMEM_BLOCK_SIZE CODE_ALLOCATION_GRANULARITY

// minimum multiple of <multiple_of> enough to accommodate <size>
// <multiple_of> must be a power of two 
#define CalculatePitch(size, multiple_of) (((size) + (multiple_of - 1)) & ~(multiple_of - 1)) 

// allocates meomory for code execution. always 4 byte aligned.
// zero size with max_size are used for getting pointer of next CodeAlloc with size <= max_size
NOINLINE _ptr_ _CodeAlloc(_size_t_ size, _size_t_ max_size) {

	static _ptr_ vmem = NULL; 
	static _dword_ vmem_block_size = 0;
	static _dword_ vmem_pos = 0;

	if (max_size < size) max_size = size;
	if (max_size == 0) max_size = 1;

	_size_t_ pitch = CalculatePitch(size, 4);
	_size_t_ max_pitch = CalculatePitch(max_size, 4);

	// if the code does not fit into the remaining space in the block, then we allocate a new one 
	if (max_pitch > vmem_block_size - vmem_pos) {

		// allocate the minimum memory multiple of VMEM_BLOCK_SIZE enough to accommodate pitch
		_size_t_ need_size = CalculatePitch(max_pitch, VMEM_BLOCK_SIZE);
		vmem = (_ptr_)VirtualAlloc(NULL, need_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		vmem_block_size = need_size;
		vmem_pos = 0;
	}

	_ptr_ result = (_ptr_)vmem + vmem_pos;
	vmem_pos += pitch;
	return result;
}

//###################################################################################################

Unprotect::Unprotect(_ptr_ address, _size_t_ size)
	: address_(address)
	, size_(size) {

	VirtualProtect((LPVOID)address, (SIZE_T)size, PAGE_EXECUTE_READWRITE, (PDWORD)&protect_);
}

Unprotect::~Unprotect() {

	VirtualProtect((LPVOID)address_, (SIZE_T)size_, protect_, NULL);
}

