// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "patcher_implementation.h"


#include "length_disassembler.h"

#include "os_specific.h"


//it's needed for abstract classes without dependency on msvcrt. 
int __cdecl _purecall(void)
{
	ConsoleOut("ERROR:  Pure virtual method call!.\n");
	return 0;
}

//###################################################################################################



PATCHER_EXPORT Patcher* PATCHER_CALL GetPatcherX86() {

	static Patcher* patcher = nullptr;
	if (patcher == nullptr) {

		patcher = new Patcher();
	}
	return patcher;
}



PATCHER_EXPORT _dword_ __stdcall GetPatcherX86Version() {

	return 0x00000001;
}



//###################################################################################################



#define SINGLEEXPR(code) do { code } while (false)

#define SetJmpAt(address, to_address) SINGLEEXPR( ByteAt(address) = 0xE9; IntAt(address + 1) = (_int_)(to_address) -  (_int_)(address) - 5; )
#define SetCallAt(address, to_address) SINGLEEXPR( ByteAt(address) = 0xE8; IntAt(address + 1) = (_int_)(to_address) -  (_int_)(address) - 5; )

#define InvertDword(v) ((_dword_)((_dword_)(v) >> 24) | (_dword_)((((_dword_)(v) >> 16) << 24) >> 16) | (_dword_)((((_dword_)(v) >> 8) << 24) >> 8) | (_dword_)((_dword_)(v) << 24))
#define InvertWord(v) ((_word_)((_word_)(v) >> 8) | (_word_)((_word_)(v) << 8))

void MemCopy(_ptr_ dst, _ptr_ src, _size_t_ size) {

	//The average size in the MemCopy used in this library with my projects is 2-3.
	//Maximum size with my projects is 10. Possible maximum is 15. I don't think this code really needs optimization by speed. 
	while (size--) ByteAt(dst++) = ByteAt(src++);
}
void FillWithNops(_ptr_ dst, _size_t_ size) {

	//The average size in the FillWithNops used in this library with my projects is 1.
	//Maximum size with my projects is 5. Possible maximum is 10. I don't think this code really needs optimization by speed. 
	while (size--) ByteAt(dst++) = 0x90;
}


//###################################################################################################


_size_t_ GetNeededCodeLength(_ptr_ p_code, int need_len) {

	int full_len = 0;
	int o_len;

	do {

		o_len = GetOpcodeLength(p_code + full_len);

		if (!o_len) {

			return 0;
		}
		full_len += o_len;

	} while (full_len < need_len);

	return full_len;
}



//###################################################################################################


// MemCopyCode copies the code from memory at src address to memory at dst address
// MemCopyCode always copies an integer amount of opcodes with summary size >= size from argument. Be careful!
// returns the size of the copied code.
// it is different from direct memory copy, because
// it correctly copies opcodes E8 (call), E9 (jmp long), 0F80 - 0F8F (j** long)
// with relative addressing without changing the absolute address of jump/call, if this address is out of copied block
// 
// if transform_short_jumps == true, then MemCopyCode correctly copies opcodes EB (jmp short), 70 - 7F (j** short)
// with relative addressing without changing the absolute address of jumps,
// if this address is out of the copied block (in this case they are replaced with corresponding E9 (jmp long), 0F80 - 0F8F (j** long) opcodes.
int __stdcall MemCopyCode(_ptr_ dst, _ptr_ dst_base, _ptr_ src, _ptr_ src_base, int size, bool transform_short_jumps) {

	int si = 0;
	int di = 0;

	while (si < size) {

		int ol = GetOpcodeLength(src + si);

		switch (ol) {

		case 0: // unknown opcode
			return di;

		case 2:
			if (transform_short_jumps) {

				if (ByteAt(src + si) == 0xEB) {

					_dword_ to_abs = (src_base + si) + (int)*(signed __int8*)(src + si + 1) + 2;
					if ((to_abs < src_base) || (to_abs > (src_base + size))) {

						if (dst) {

							ByteAt(dst + di) = 0xE9;
							DwordAt(dst + di + 1) = to_abs - (dst_base + di) - 5;
						}
						di += 5;
						break;
					}
				}
				else if ((ByteAt(src + si) >= 0x70) && (ByteAt(src + si) <= 0x7F)) {

					_dword_ to_abs = (src_base + si) + (int)*(signed __int8*)(src + si + 1) + 2;
					if ((to_abs < src_base) || (to_abs > (src_base + size))) {

						if (dst) {

							ByteAt(dst + di) = 0x0F;
							ByteAt(dst + di + 1) = ByteAt(src + si) + 0x10;
							DwordAt(dst + di + 2) = to_abs - (dst_base + di) - 6;
						}
						di += 6;
						break;
					}
				}
			}

			if (dst) {

				MemCopy(dst + di, src + si, ol);
			}
			di += ol;
			break;

		case 5:
			if (dst) {

				if (ByteAt(src + si) == 0xE8) {

					_dword_ to_abs = DwordAt((src + si) + 1) + (src_base + si) + 5;
					if ((to_abs < src_base) || (to_abs > (src_base + size))) {

						ByteAt(dst + di) = 0xE8;
						IntAt(dst + di + 1) = (_int_)(to_abs) - (_int_)(dst_base + di) - 5;
					}
					else {

						MemCopy(dst + di, src + si, ol);
					}
				}
				else if (ByteAt(src + si) == 0xE9) {

					_dword_ to_abs = DwordAt((src + si) + 1) + (src_base + si) + 5;
					if ((to_abs < src_base) || (to_abs > (src_base + size))) {

						ByteAt(dst + di) = 0xE9;
						IntAt(dst + di + 1) = (_int_)(to_abs) - (_int_)(dst_base + di) - 5;
					}
					else {

						MemCopy(dst + di, src + si, ol);
					}
				}
				else {

					MemCopy(dst + di, src + si, ol);
				}
			}
			di += ol;
			break;

		case 6:
			if (dst) {
				if ((ByteAt(src + si) == 0x0F) && (ByteAt(src + si + 1) >= 0x80) && (ByteAt(src + si + 1) <= 0x8F)) {
					_dword_ to_abs = DwordAt((src + si) + 2) + (src_base + si) + 6;
					if ((to_abs < src_base) || (to_abs > (src_base + size))) {
						WordAt(dst + di) = WordAt(src + si);
						DwordAt(dst + di + 2) = to_abs - (dst_base + di) - 6;
					}
					else {

						MemCopy(dst + di, src + si, ol);
					}
				}
				else {

					MemCopy(dst + di, src + si, ol);
				}
			}
			di += ol;
			break;

		default:
			if (dst) {

				MemCopy(dst + di, src + si, ol);
			}
			di += ol;
			break;
		}
		si += ol;
	}
	return di;
}



//###################################################################################################



_ptr_ Patch::address() {

	return address_;
}
_ptr_ LoHook::address() {

	return address_;
}
_ptr_ HiHook::address() {

	return address_;
}



_dword_ Patch::size() {

	return size_;
}
_dword_ LoHook::size() {

	return size_;
}
_dword_ HiHook::size() {

	return size_;
}



_ptr_ HiHook::GetDefaultFunc() {

	return default_func_;
}



Patch::Patch(_ptr_ address, _ptr_ new_data, _word_ size) {

	address_ = address;
	size_ = size;

	Unprotect memory(address_, size_);
	MemCopy(address_, new_data, size_);
}



IPatch* Patcher::SetPatch(_ptr_ address, _ptr_ data, _dword_ size) {

	return new Patch(address, data, size);
}



LoHook::LoHook(_ptr_ address, void* func) {

	address_ = address;

	size_ = GetNeededCodeLength(address, JMP_OPCODE_SIZE);
	if (size_ < JMP_OPCODE_SIZE) {

		ConsoleOut("LoHook error: Unknown opcode.\n");
		return;
	}

	const int default_code_offset = 27;

	const _size_t_ bridge_max_size = default_code_offset + MAX_COPIED_HOOKPATCH_DEFAULT_CODE + JMP_OPCODE_SIZE;
	
	const _ptr_ bridge = CodePreAlloc(bridge_max_size); // Pre allocate memory. Get pointer of next CodeAlloc. Here, we don't know exactly the bridge size yet.

	//////ByteAt(   bridge + 0) = 0x60;						// +0: pushad -> LoContext registers
	//////													// +1: push address_ + size_ -> LoContext::return_address
	//////ByteAt(   bridge + 1) = 0x68;						
	//////DwordAt(  bridge + 2) = address_ + size_;			
	//////ByteAt(   bridge + 6) = 0x54;						// +6: push esp
	//////SetCallAt(bridge + 7,	func);						// +7: call func
	//////
	//////													// +12: test eax, eax
	//////													// +14: pop eax
	//////													// +15: popad
	//////DwordAt(  bridge + 12) = InvertDword(0x85C05861); 
	//////WordAt(   bridge + 16) = InvertWord(0x7505);		// +16: jne copied_default_code
	//////DwordAt(  bridge + 18) = InvertDword(0xFF7424DC);	// +18: push dword ptr [esp - 36]  // modified return address
	//////ByteAt(	  bridge + 22) = 0xC3;						// +22: ret
	//////													// +23: copied_default_code:
	//////const _ptr_ copied_default_code = (_ptr_)bridge + 23;
	ByteAt(bridge + 0) = 0x60;						// +0: pusha -> LoContext registers
	ByteAt(bridge + 1) = 0x9C;						// +0: pushf -> LoContext flags
													// +1: push address_ + size_ -> LoContext::return_address
	ByteAt(bridge + 2) = 0x68;
	DwordAt(bridge + 3) = address_ + size_;
	
	ByteAt(bridge + 7) = 0x54;						// +6: push esp
	SetCallAt(bridge + 8, func);					// +7: call func

	WordAt(bridge + 13) = InvertWord(0x85C0);		// +13: test   eax,eax
	ByteAt(bridge + 15) = 0x58;						// +15: pop eax

	WordAt(bridge + 16) = InvertWord(0x7507);			// +16: jne exec_default_label
	ByteAt(bridge + 18) = 0x9D;						// +18: popf
	ByteAt(bridge + 19) = 0x61;						// +19: popa
	DwordAt(bridge + 20) = InvertDword(0xFF7424D8);	// +20: push dword ptr [esp - 40]  // modified return address
	ByteAt(bridge + 24) = 0xC3;						// +24: ret
//exec_default_label:
	ByteAt(bridge + 25) = 0x9D;						// +25: popf
	ByteAt(bridge + 26) = 0x61;						// +26: popa
													// +27 default_code_offset: copied_default_code:
	const _ptr_ copied_default_code = (_ptr_)bridge + default_code_offset;
	int copied_default_code_size = MemCopyCode(copied_default_code, copied_default_code, address_, address_, size_, true);

	if (copied_default_code_size < size_) {

		ConsoleOut("LoHook error: MemCopyCode - Unknown opcode\n");
	}
													// +..: jmp  (address_ + size_)
	SetJmpAt(copied_default_code + copied_default_code_size, address_ + size_); 

	const _size_t_ bridge_size = default_code_offset + copied_default_code_size + JMP_OPCODE_SIZE;

	if (bridge_size > bridge_max_size) {

		ConsoleOut("LoHook error: bridge_size > bridge_max_size.\n");
		return;
	}

	if (bridge != CodeAlloc(bridge_size)) { // finish the allocation of <bridge_size> bytes
	
		ConsoleOut("LoHook error: CodeAlloc != GetNextCodePointer\n");
	}

	Unprotect memory(address_, size_);
	SetJmpAt(address_, bridge);

	if (size_ > JMP_OPCODE_SIZE) FillWithNops(address_ + JMP_OPCODE_SIZE, size_ - JMP_OPCODE_SIZE); //This is not required, but makes it easier to debug modified code. 
}



ILoHook* Patcher::SetLoHook(_ptr_ address, LoHookFunc func) {

	return new LoHook(address, func);
}



HiHook::HiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) {

	hooktype_ = hooktype;
	subtype_ = subtype;
	calltype_ = calltype;
	address_ = address;

	default_func_ = 0;

	if (hooktype_ == FUNCPTR_) {

		size_ = 4;
	}
	else {

		size_ = GetNeededCodeLength(address_, JMP_OR_CALL_OPCODE_SIZE);
		if (size_ < JMP_OR_CALL_OPCODE_SIZE) {

			ConsoleOut("HiHook error: Unknown opcode.\n");
			return;
		}
	}

	_ptr_ code_to_call = (_ptr_)new_func;

	if (subtype == EXTENDED_) {

		switch (calltype) {
		case CDECL_: {

				const _ptr_ bridge_to_new_ = CodeAlloc(CALL_OPCODE_SIZE + 1);

				SetCallAt(bridge_to_new_, (_ptr_)new_func);			// call new_func
				ByteAt(bridge_to_new_ + CALL_OPCODE_SIZE) = 0xC3;	// ret			

				code_to_call = bridge_to_new_;
				break;
			}

		case STDCALL_: {

				const _ptr_ bridge_to_new_ = CodeAlloc(3 + JMP_OPCODE_SIZE);

																// +0: pop eax
																// +1: push eax
																// +2: push eax
				DwordAt( bridge_to_new_ + 0) = InvertDword(0x58505090);				
				SetJmpAt(bridge_to_new_ + 3, (_ptr_)new_func);	// +3: jmp new_func

				code_to_call = bridge_to_new_;
				break;
			}

		case THISCALL_: {

				const _ptr_ bridge_to_new_ = CodeAlloc(4 + JMP_OPCODE_SIZE);

																// +0: pop eax
																// +1: push ecx
																// +2: push eax
																// +3: push eax
				DwordAt( bridge_to_new_ + 0) = InvertDword(0x58515050);
				SetJmpAt(bridge_to_new_ + 4, (_ptr_)new_func);	// +4: jmp new_func

				code_to_call = bridge_to_new_;
				break;
			}

		case FASTCALL_: {

				const _ptr_ bridge_to_new_ = CodeAlloc(5 + JMP_OPCODE_SIZE);

																// +0: pop eax
																// +1: push edx
																// +2: push ecx
																// +3: push eax
				DwordAt(bridge_to_new_ + 0) = InvertDword(0x58525150);
				ByteAt(bridge_to_new_ + 4) = 0x50;				// +4: push eax		
				SetJmpAt(bridge_to_new_ + 5, (_ptr_)new_func);	// +5: jmp new_func

				code_to_call = bridge_to_new_;
				break;
			}

		default:
			break;
		}
	}

	Unprotect memory(address_, size_);

	switch (hooktype) {

	case CALL_:
		if (ByteAt(address_) == 0xE8) { // call n32 opcode

			default_func_ = PtrAt(address_ + 1) + address_ + 5;
		}
		else if ((ByteAt(address_) == 0xFF) && (ByteAt(address_ + 1) == 0x15)) { // call [n32] opcode

			default_func_ = PtrAt(PtrAt(address_ + 2));
		}
		else {

			ConsoleOut("CALL_ HiHook error: Unknown opcode\n");
			default_func_ = 0;
		}

		SetCallAt(address_, code_to_call);
		if (size_ > CALL_OPCODE_SIZE) FillWithNops(address_ + CALL_OPCODE_SIZE, size_ - CALL_OPCODE_SIZE); //This is not required, but makes it easier to debug modified code. 
		break;

	case SPLICE_: {

			const _ptr_ bridge_to_default_ = CodePreAlloc(MAX_COPIED_HOOKPATCH_DEFAULT_CODE + JMP_OPCODE_SIZE); // Get pointer of next allocated memory. Here, we don't know exactly bridge_to_default_ size yet.
			int copied_default_code_size = MemCopyCode(bridge_to_default_, bridge_to_default_, address_, address_, size_, true);
			if (copied_default_code_size < size_) {

				ConsoleOut("SPLICE_ HiHook error: MemCopyCode - Unknown opcode\n");
			}
			SetJmpAt(bridge_to_default_ + copied_default_code_size, address_ + size_);

			if (bridge_to_default_ != CodeAlloc(copied_default_code_size + JMP_OPCODE_SIZE)) { // finish the allocation of <copied_default_code_size + JMP_OPCODE_SIZE> bytes

				ConsoleOut("SPLICE_ HiHook error: CodeAlloc != GetNextCodePointer\n");
			}
			default_func_ = bridge_to_default_;

			SetJmpAt(address_, code_to_call);
			if (size_ > JMP_OPCODE_SIZE) FillWithNops(address_ + JMP_OPCODE_SIZE, size_ - JMP_OPCODE_SIZE); //This is not required, but makes it easier to debug modified code. 
			break;
		}

	case FUNCPTR_:
		default_func_ = DwordAt(address_);
		DwordAt(address_) = code_to_call;
		break;
	}
}



IHiHook* Patcher::SetHiHook(_ptr_ address, int hooktype, int subtype, int calltype, void* new_func) {

	return new HiHook(address, hooktype, subtype, calltype, new_func);

}







