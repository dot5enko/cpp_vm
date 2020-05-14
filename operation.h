//
// Created by serhio on 14.05.20.
//

#ifndef CPP_VM_OPERATION_H
#define CPP_VM_OPERATION_H


enum operation_id {
    SET_FIELD,
    GET_FIELD,
    PRINT,
    JMP_IF,
    JMP,
    CMP,
    ADD,
    DIV,
    INC,
    EQ,
    NOT_EQ,
    NOT_EQ_ZERO,
    MOV_TO_VAR
};

#include <cstdint>
#include <vector>
#include "vm_var.h"
#include "op_argument.h"

using namespace std;

class operation {
public:
    operation(operation_id op);
    ~operation();

    operation_id    op;

    int args_count;
    op_argument args[4];

    void argument(op_argument arg);
    void argument_int(int arg);
    void argument_str(char* arg);
    void argument_ptr(void* ptr);
    void argument_var_ref(char* name);
};


#endif