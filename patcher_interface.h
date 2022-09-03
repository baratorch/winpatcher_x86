#pragma once

#ifndef PATCHER_INTERFACE_H
#define PATCHER_INTERFACE_H

#define PATCHER_CALL __stdcall

// all the structures of library interface must have 4-byte alignment
#pragma pack(push, 4)

#define	_byte_ unsigned __int8
#define	_word_ unsigned __int16
#define	_dword_ unsigned __int32
#define	_qword_ unsigned __int64

#define	_char_ char
#define	_int8_ signed __int8
#define	_int16_ signed __int16
#define	_int32_ signed __int32

#define	_float_ float

#define	_bool8_ _char_
#define	_bool32_ _int32_
#define	_bool_ _bool32_


#define	_int_ _int32_
#define _cstr_ _char_*

// all addresses and the part of pointers are defined with this type,
// if another way is more convenient for you, you may replace _ptr_ with any other type, for example void* or int
typedef _dword_ _ptr_;
#define _size_t_ _dword_

#define IntAt(address)		(*(_int_*)(address))
#define DwordAt(address)	(*(_dword_*)(address))
#define ByteAt(address)		(*(_byte_*)(address))
#define WordAt(address)		(*(_word_*)(address))
#define CstrAt(address)		(*(_cstr_*)(address))
#define PtrAt(address)		(*(_ptr_*)(address))
#define FloatAt(address)	(*(_float_*)(address))
#define QwordAt(address)	(*(_qword_*)(address))

#define NULL 0

//?CALL? macros allow to call an arbitrary function at specific address
//their use includes the case of calling functions that are got with IHiHook::GetDefaultFunc
#define CALL_0(return_type, call_type, address) \
	((return_type (call_type *)(void))address)()
#define CALL_1(return_type, call_type, address, a1) \
	((return_type (call_type *)(_dword_))(address))((_dword_)(a1))
#define CALL_2(return_type, call_type, address, a1, a2) \
	((return_type (call_type *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))
#define CALL_3(return_type, call_type, address, a1, a2, a3) \
	((return_type (call_type *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))
#define CALL_4(return_type, call_type, address, a1, a2, a3, a4) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))
#define CALL_5(return_type, call_type, address, a1, a2, a3, a4, a5) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))
#define CALL_6(return_type, call_type, address, a1, a2, a3, a4, a5, a6) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))
#define CALL_7(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))
#define CALL_8(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define CALL_9(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))
#define CALL_10(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))
#define CALL_11(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))
#define CALL_12(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))
#define CALL_13(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))
#define CALL_14(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))
#define CALL_15(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))
#define CALL_16(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))
#define CALL_17(return_type, call_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
	((return_type (call_type *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))

#define CALL_VA(return_type, adress, a1, ...) \
	((return_type (__cdecl *)(_dword_, ...))(adress))((_dword_)(a1), __VA_ARGS__)

#define CDECLCALL(return_type, adress, ...) \
	((return_type (__cdecl *)(...))(adress))(__VA_ARGS__)

#define STDCALL_0(return_type, address) \
	((return_type (__stdcall *)(void))address)()
#define STDCALL_1(return_type, address, a1) \
	((return_type (__stdcall *)(_dword_))(address))((_dword_)(a1))
#define STDCALL_2(return_type, address, a1, a2) \
	((return_type (__stdcall *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))
#define STDCALL_3(return_type, address, a1, a2, a3) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))
#define STDCALL_4(return_type, address, a1, a2, a3, a4) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))
#define STDCALL_5(return_type, address, a1, a2, a3, a4, a5) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))
#define STDCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))
#define STDCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))
#define STDCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define STDCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define STDCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))
#define STDCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))
#define STDCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))
#define STDCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))
#define STDCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))
#define STDCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))
#define STDCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))
#define STDCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))
#define STDCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
	((return_type (__stdcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))


#define THISCALL_1(return_type, address, a1) \
	((return_type (__thiscall *)(_dword_))(address))((_dword_)(a1))
#define THISCALL_2(return_type, address, a1, a2) \
	((return_type (__thiscall *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))
#define THISCALL_3(return_type, address, a1, a2, a3) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))
#define THISCALL_4(return_type, address, a1, a2, a3, a4) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))
#define THISCALL_5(return_type, address, a1, a2, a3, a4, a5) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))
#define THISCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))
#define THISCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))
#define THISCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define THISCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define THISCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))
#define THISCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))
#define THISCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))
#define THISCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))
#define THISCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))
#define THISCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))
#define THISCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))
#define THISCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))
#define THISCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
	((return_type (__thiscall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))

#define FASTCALL_1(return_type, address, a1) \
	((return_type (__fastcall *)(_dword_))(address))((_dword_)(a1))
#define FASTCALL_2(return_type, address, a1, a2) \
	((return_type (__fastcall *)(_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2))
#define FASTCALL_3(return_type, address, a1, a2, a3) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3))
#define FASTCALL_4(return_type, address, a1, a2, a3, a4) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4))
#define FASTCALL_5(return_type, address, a1, a2, a3, a4, a5) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5))
#define FASTCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6))
#define FASTCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7))
#define FASTCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define FASTCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8))
#define FASTCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9))
#define FASTCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10))
#define FASTCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11))
#define FASTCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12))
#define FASTCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13))
#define FASTCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14))
#define FASTCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15))
#define FASTCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16))
#define FASTCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
	((return_type (__fastcall *)(_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_,_dword_))(address))((_dword_)(a1),(_dword_)(a2),(_dword_)(a3),(_dword_)(a4),(_dword_)(a5),(_dword_)(a6),(_dword_)(a7),(_dword_)(a8),(_dword_)(a9),(_dword_)(a10),(_dword_)(a11),(_dword_)(a12),(_dword_)(a13),(_dword_)(a14),(_dword_)(a15),(_dword_)(a16),(_dword_)(a17))




namespace Call {

	template
		<
		typename			RetType,
		typename			Addr,
		typename...			Args
		>
		__forceinline RetType Std(Addr addr, Args... args) {

		typedef RetType(__stdcall* func)(Args...);
		return ((func)addr)(args...);
	}
	template
		<
		typename			RetType,
		typename			Addr,
		typename...			Args
		>
		__forceinline RetType This(Addr addr, Args... args) {

		typedef RetType(__thiscall* func)(Args...);
		return ((func)addr)(args...);
	}
	template
		<
		typename			RetType,
		typename			Addr,
		typename...			Args
		>
		__forceinline RetType Fast(Addr addr, Args... args) {

		typedef RetType(__fastcall* func)(Args...);
		return ((func)addr)(args...);
	}
	template
		<
		typename			RetType,
		typename			Addr,
		typename...			Args
		>
		__forceinline RetType Cdecl(Addr addr, Args... args) {

		typedef RetType(__cdecl* func)(Args...);
		return ((func)addr)(args...);
	}
};


// Abstract class IPatch
// instance may be created with IPatcher class methods
class IPatch {

public:
	// returns the address on which patch is placed
	virtual _ptr_ __stdcall address() = 0;

	// returns the size of the patch
	virtual _dword_ __stdcall size() = 0;
};

// LoHookContext structure
// it is used in functions triggered by LoHook hook
class LoHookContext {
public:
	_ptr_ return_address;

	_dword_ flags;

	_int_ edi; // edi register, read/modify
	_int_ esi; // esi register, read/modify
	_int_ ebp; // ebp register, read/modify
private:
	_int_ esp; // esp register, read only (If you modify it, you will most likely get a crash)
public:
	_int_ ebx; // ebx register, read/modify
	_int_ edx; // edx register, read/modify
	_int_ ecx; // ecx register, read/modify
	_int_ eax; // eax register, read/modify

	// get esp register value
	_int_ Esp() { return esp;
	}
private:
	LoHookContext();
};

// values that may be returned by the function triggered by LoHook hook
#define EXEC_DEFAULT 1
#define SKIP_DEFAULT 0


// Abstract class ILoHook (the heir of IPatch, so the LoHook is Patch in fact)
// instance may be created with IPatcher class methods
class ILoHook : public IPatch {
};

typedef int(__stdcall* LoHookFunc)(LoHookContext*);

// the values for hooktype argument in IPatcher::SetHiHook
#define CALL_ 0
#define SPLICE_ 1
#define FUNCPTR_ 2

// the values for subtype argument in IPatcher::SetHiHook
#define DIRECT_  0
#define EXTENDED_  1

// the values for calltype argument in IPatcher::SetHiHook
#define ANY_		0
#define STDCALL_	0
#define THISCALL_	1
#define FASTCALL_	2 
#define CDECL_		3
#define FASTCALL_1_	1 

// Abstract class IHiHook (the heir of IPatch, so the HiHook is Patch in fact)
// instance may be created with IPatcher class methods
class IHiHook : public IPatch
{
public:

	// returns the pointer to the function (the bridge to the function in case of SPLICE_)
	// which is replaced with hook
	virtual _ptr_ PATCHER_CALL GetDefaultFunc() = 0;
};



class IPatcher
{
public:
	//base methods

	// Writes data from memory at 'data' to memory at 'address' with the specified size
	// Returns a pointer to the IPatch
	virtual IPatch* PATCHER_CALL SetPatch(_ptr_ address, _ptr_ data, _dword_ size) = 0;

	// Writes a low-level hook at the specified address
	// returns a pointer to the hook
	// func is the function which is called when the hook is triggered
	// it must be of _LoHookFunc_ type: int __stdcall func(ILoHook* h, LoHookContext* c);
	// LoHookContext* c allows to read/modify CPU register values and return address
	// if func returns SKIP_DEFAULT then the replaced code is not executed and execution goes to LoHookContext::return_address
	// if func returns EXEC_DEFAULT the original code replaced by hook is executed after finishing func call 
	// and and execution goes to the address following the replaced code (changed LoHookContext::return_address value is ignored)
	// ATTENTION!  We assume LoHookContext::esp is read only (If you modify it, you will most likely get a crash)
	virtual ILoHook* PATCHER_CALL SetLoHook(_ptr_ address, LoHookFunc func) = 0;

	// creates a high-level hook at the specified address and applies it
	// returns a pointer to the hook
	//
	// new_func is a function which replaces the original one
	//
	// hooktype is the type of the hook:
	//  CALL_ - hook applied ON CALL of the function from the specified address
	//     opcodes E8 and FF 15 are supported, in other cases hook is not applied
	//     and information about this error is written to popup console
	//  SPLICE_ - hook is applied directly ON FUNCTION ITSELF at the specified address
	//  FUNCPTR_ - hook is applied on the pointer to the function (rarely used, mostly for hooks in import tables)
	//
	// subtype is hook subtype:
	//  DIRECT_ - new_func has the same type as
	//     the replaced original function
	//     note: instead of __thiscall f(this) 
	//        you can use __fastcall f(this_)
	//        instead of __thiscall f(this, ...)  you can use 
	//        __fastcall f(this_, no_used_edx, ...) 
	//  EXTENDED_ - the return address of called function is passed to new_func function as  the first stack argument and in case 
	//     the original function was of __thiscall or __fastcall calling convention
	//     register arguments are passed as the second stack arguments
	// So, new_func function must take the form
	// __stdcall new_func(_ptr_ return_address, ?) for __stdcall orig(?),  __thiscall orig(?) and  __fastcall orig(?), 
	// __cdecl orig(_ptr_ return_address, ?) for __cdecl orig(?),
	//
	// ATTENTION! EXTENDED_ FASTCALL_ supports only the functions with 2 or more arguments
	// for __fastcall with 1 argument use EXTENDED_ FASTCALL_1 / EXTENDED_ THISCALL_
	//
	// calltype is a calling convention of the original replaced function:
	//  STDCALL_
	//  THISCALL_
	//  FASTCALL_
	//  CDECL_
	// it is necessary to specify right convention for EXTENDED_ hook to
	// create correct bridge to new_func
	virtual IHiHook* PATCHER_CALL SetHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) = 0;

	//shell methods
	inline IPatch* SetByte(_ptr_ address, int value) { return SetPatch(address, (_ptr_)&value, 1); }
	inline IPatch* SetDword(_ptr_ address, int value) { return SetPatch(address, (_ptr_)&value, 4); }
	inline IPatch* SetPtr(_ptr_ address, const char* value) { return SetDword(address, (int)value); }
};


#pragma pack(pop)



#endif //PATCHER_INTERFACE_H