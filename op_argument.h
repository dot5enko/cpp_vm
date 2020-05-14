//
// Created by serhio on 14.05.20.
//

#ifndef CPP_VM_OP_ARGUMENT_H
#define CPP_VM_OP_ARGUMENT_H

#include <cstdint>
#include "vm_var.h"


union _op_arg_data {
    int ival;
    float fval;
    char* str;
    void* ptr;
};

struct op_argument {

    _op_arg_data data;

   uint16_t type;
};

#endif //CPP_VM_OP_ARGUMENT_H
