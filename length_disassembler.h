// https://github.com/Nomade040/length-disassembler
// * There is no support for AVX and processor-specific instructions.

#pragma once

#ifndef LDISASM_H
#define LDISASM_H

#include "patcher_interface.h"

_size_t_ GetOpcodeLength(const _ptr_ address, const bool x86_64_mode = false);

#endif //LDISASM_H