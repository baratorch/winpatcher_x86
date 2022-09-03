// https://github.com/Nomade040/length-disassembler
// * There is no support for AVX and processor-specific instructions.

#include "length_disassembler.h"

#define R (*b >> 4) // Four high-order bits of an opcode to index a row of the opcode table
#define C (*b & 0xF) // Four low-order bits to index a column of the table

static const _byte_ prefixes[] = { 0xF0, 0xF2, 0xF3, 0x2E, 0x36, 0x3E, 0x26, 0x64, 0x65, 0x66, 0x67 };
static const _byte_ op1modrm[] = { 0x62, 0x63, 0x69, 0x6B, 0xC0, 0xC1, 0xC4, 0xC5, 0xC6, 0xC7, 0xD0, 0xD1, 0xD2, 0xD3, 0xF6, 0xF7, 0xFE, 0xFF };
static const _byte_ op1imm8[] = { 0x6A, 0x6B, 0x80, 0x82, 0x83, 0xA8, 0xC0, 0xC1, 0xC6, 0xCD, 0xD4, 0xD5, 0xEB };
static const _byte_ op1imm32[] = { 0x68, 0x69, 0x81, 0xA9, 0xC7, 0xE8, 0xE9 };
static const _byte_ op2modrm[] = { 0x0D, 0xA3, 0xA4, 0xA5, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF };

bool FindByte(const _byte_* arr, const _size_t_ N, const _byte_ x) { for (_size_t_ i = 0; i < N; i++) { if (arr[i] == x) { return true; } }; return false; }

void ParseModRM(_byte_** b, const bool addressPrefix)
{
	_byte_ modrm = *++ * b;

	if (!addressPrefix || (addressPrefix && **b >= 0x40))
	{
		bool hasSIB = false; //Check for SIB byte
		if (**b < 0xC0 && (**b & 0x7/*0b111*/) == 0x4/*0b100*/ && !addressPrefix)
			hasSIB = true, (*b)++;

		if (modrm >= 0x40 && modrm <= 0x7F) // disp8 (ModR/M)
			(*b)++;
		else if ((modrm <= 0x3F && (modrm & 0x7/*0b111*/) == 0x5/*0b101*/) || (modrm >= 0x80 && modrm <= 0xBF)) //disp16,32 (ModR/M)
			*b += (addressPrefix) ? 2 : 4;
		else if (hasSIB && (**b & 0x7/*0b111*/) == 0x5/*0b101*/) //disp8,32 (SIB)
			*b += (modrm & 0x40/*0b01000000*/) ? 1 : 4;
	}
	else if (addressPrefix && modrm == 0x26)
		*b += 2;
};

_size_t_ GetOpcodeLength(const _ptr_ address, const bool x86_64_mode)
{
	_size_t_ offset = 0;
	bool operandPrefix = false, addressPrefix = false, rexW = false;
	_byte_* b = (_byte_*)(address);

	//Parse legacy prefixes & REX prefixes
	for (int i = 0; i < 14 && FindByte(prefixes, sizeof(prefixes), *b) || ((x86_64_mode) ? (R == 4) : false); i++, b++)
	{
		if (*b == 0x66)
			operandPrefix = true;
		else if (*b == 0x67)
			addressPrefix = true;
		else if (R == 4 && C >= 8)
			rexW = true;
	}

	//Parse opcode(s)
	if (*b == 0x0F) // 2,3 bytes
	{
		b++;
		if (*b == 0x38 || *b == 0x3A) // 3 bytes
		{
			if (*b++ == 0x3A)
				offset++;

			ParseModRM(&b, addressPrefix);
		}
		else // 2 bytes
		{
			if (R == 8) //disp32
				offset += 4;
			else if ((R == 7 && C < 4) || *b == 0xA4 || *b == 0xC2 || (*b > 0xC3 && *b <= 0xC6) || *b == 0xBA || *b == 0xAC) //imm8
				offset++;

			//Check for ModR/M, SIB and displacement
			if (FindByte(op2modrm, sizeof(op2modrm), *b) || (R != 3 && R > 0 && R < 7) || *b >= 0xD0 || (R == 7 && C != 7) || R == 9 || R == 0xB || (R == 0xC && C < 8) || (R == 0 && C < 4))
				ParseModRM(&b, addressPrefix);
		}
	}
	else // 1 byte
	{
		//Check for immediate field
		if ((R == 0xE && C < 8) || (R == 0xB && C < 8) || R == 7 || (R < 4 && (C == 4 || C == 0xC)) || (*b == 0xF6 && !(*(b + 1) & 48)) || FindByte(op1imm8, sizeof(op1imm8), *b)) //imm8
			offset++;
		else if (*b == 0xC2 || *b == 0xCA) //imm16
			offset += 2;
		else if (*b == 0xC8) //imm16 + imm8
			offset += 3;
		else if ((R < 4 && (C == 5 || C == 0xD)) || (R == 0xB && C >= 8) || (*b == 0xF7 && !(*(b + 1) & 48)) || FindByte(op1imm32, sizeof(op1imm32), *b)) //imm32,16
			offset += (rexW) ? 8 : (operandPrefix ? 2 : 4);
		else if (R == 0xA && C < 4)
			offset += (rexW) ? 8 : (addressPrefix ? 2 : 4);
		else if (*b == 0xEA || *b == 0x9A) //imm32,48
			offset += operandPrefix ? 4 : 6;

		//Check for ModR/M, SIB and displacement
		if (FindByte(op1modrm, sizeof(op1modrm), *b) || (R < 4 && (C < 4 || (C >= 8 && C < 0xC))) || R == 8 || (R == 0xD && C >= 8))
			ParseModRM(&b, addressPrefix);
	}

	return (_size_t_)((_ptr_)(++b + offset) - (_ptr_)(address));
}