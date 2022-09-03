#pragma once

#include "patcher_interface.h"

extern IPatcher* _P; // must contain the value obtained from GetPactherX86()

#define _DO_JOIN2(a1, a2) a1##a2
#define JOIN2(a1, a2) _DO_JOIN2(a1, a2)
#define _DO_JOIN3(a1, a2, a3) a1##a2##a3
#define JOIN3(a1, a2, a3) _DO_JOIN3(a1, a2, a3)

#define HOOK_CALLTYPE__stdcall 0
#define HOOK_CALLTYPE__thiscall 1
#define HOOK_CALLTYPE__fastcall 2
#define HOOK_CALLTYPE__cdecl 3

#define HOOKFUNC_CALLTYPE_00 __stdcall
#define HOOKFUNC_CALLTYPE_01 __fastcall
#define HOOKFUNC_CALLTYPE_02 __fastcall
#define HOOKFUNC_CALLTYPE_03 __cdecl

#define HOOKFUNC_CALLTYPE_10 __stdcall
#define HOOKFUNC_CALLTYPE_11 __stdcall
#define HOOKFUNC_CALLTYPE_12 __stdcall
#define HOOKFUNC_CALLTYPE_13 __cdecl

#define __ARGS(...) __VA_ARGS__
#define EXT_ARGS(...) _ptr_ return_address, __VA_ARGS__

#define HOOK_ARGS_00 __ARGS
#define HOOK_ARGS_01(this_, ...) this_, _dword_ ___no_used, __VA_ARGS__
#define HOOK_ARGS_02 __ARGS
#define HOOK_ARGS_03 __ARGS

#define HOOK_ARGS_10 EXT_ARGS
#define HOOK_ARGS_11 EXT_ARGS
#define HOOK_ARGS_12 EXT_ARGS
#define HOOK_ARGS_13 EXT_ARGS

#define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#define INTERNAL_EXPAND(x) x

#define INTERNAL_GET_ARG_COUNT_PRIVATE(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, count, ...) count
#define EXPAND_ARGS_PRIVATE_1(...) INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3))
#define EXPAND_ARGS_PRIVATE_2(...) INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3))
#define RIGHT_CALLTYPE_0(...) 0
#define RIGHT_CALLTYPE_1(...) EXPAND_ARGS_PRIVATE_1(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))
#define RIGHT_CALLTYPE_2(...) EXPAND_ARGS_PRIVATE_2(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))
#define RIGHT_CALLTYPE_3(...) 3

#define COMMA ,

//Macro for setting hihook inline. You can't use commas in such a hihook body directly, use the COMMA macro instead.
#define HIHOOK(address, hooktype, subtype, returntype, calltype, name, args, body)																																	\
	[]() -> IHiHook* {																																																		\
		static IHiHook* inline_hook;																																														\
		typedef returntype(calltype* _DefaultFunc_) args;																																									\
		typedef returntype(JOIN3(HOOKFUNC_CALLTYPE_, subtype, JOIN2(RIGHT_CALLTYPE_, HOOK_CALLTYPE##calltype) args) * _HookFunc_)(JOIN3(HOOK_ARGS_, subtype, JOIN2(RIGHT_CALLTYPE_, HOOK_CALLTYPE##calltype) args) args);	\
		_HookFunc_ func_name = [](JOIN3(HOOK_ARGS_, subtype, JOIN2(RIGHT_CALLTYPE_, HOOK_CALLTYPE##calltype) args) args) -> returntype body;																				\
		inline_hook = _P->SetHiHook(address, hooktype, subtype, JOIN2(RIGHT_CALLTYPE_, HOOK_CALLTYPE##calltype) args, func_name);																							\
		return inline_hook;																																																	\
	}()

#define DefaultFunc ((_DefaultFunc_)inline_hook->GetDefaultFunc())


// we can make separate method in the IPatcher for SetJmp but in my projects SetJmp is extremely rare.
#define JMP(address, to)																								\
	[]() -> ILoHook* {																									\
		static _ptr_ to_;																								\
		to_ = to;																										\
		return _P->SetLoHook(address, [](LoHookContext* c) -> int { c->return_address = to_; return SKIP_DEFAULT; });	\
	}()


#define SINGLEEXPR(code)  do { code } while (false)
#define BREAKPOINT SINGLEEXPR(__asm { __asm int 3 })
