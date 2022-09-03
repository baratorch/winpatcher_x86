#pragma once

#include "patcher_interface.h"


#ifndef PATCHER_IMPLEMENTATION_H
#define PATCHER_IMPLEMENTATION_H


#pragma pack(push, 4)


class Patch : public IPatch
{
public:
	virtual _ptr_ __stdcall address();
	virtual _dword_ __stdcall size();

	_ptr_ address_;
	_word_ size_;

	Patch(_ptr_ address, _ptr_ new_data, _word_ size);
	inline Patch() {}
};


class LoHook : public Patch, public ILoHook
{
public:
	virtual _ptr_ __stdcall address();
	virtual _dword_ __stdcall size();

	_ptr_ code_;

	LoHook(_ptr_ address, void* func);
};

class HiHook : public Patch, public IHiHook
{
public:
	virtual _ptr_ __stdcall address();
	virtual _dword_ __stdcall size();

	virtual _ptr_ __stdcall GetDefaultFunc();

	_ptr_ default_func_;

	_byte_ hooktype_;
	_byte_ subtype_;
	_byte_ calltype_;

	HiHook(_ptr_ address, int type, int subtype, int calltype, void* new_func);
};




class Patcher : public IPatcher
{
public:

	virtual IPatch* __stdcall SetPatch(_ptr_ address, _ptr_ data, _dword_ size);
	virtual ILoHook* __stdcall SetLoHook(_ptr_ address, LoHookFunc func);
	virtual IHiHook* __stdcall SetHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func);

	//################################################################################################################################

	Patcher() {};
	~Patcher() {};
};



#pragma pack(pop)


#define MAX_OPCODE_SIZE 16 // it's 15 but we use 16
#define MAX_HOOKPATCH_SIZE (4 + MAX_OPCODE_SIZE) // e.g. 2 short conditional jumps + MAX_OPCODE_SIZE
#define MAX_COPIED_HOOKPATCH_DEFAULT_CODE (6 + 6 + MAX_OPCODE_SIZE) // 2 short conditional jumps converted to 2 long conditional jumps + MAX_OPCODE_SIZE
#define JMP_OPCODE_SIZE 5
#define CALL_OPCODE_SIZE 5
#define JMP_OR_CALL_OPCODE_SIZE 5

#define PATCHER_EXPORT extern "C" __declspec(dllexport)


#endif //PATCHER_IMPLEMENTATION_H