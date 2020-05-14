//
// Created by serhio on 14.05.20.
//

#ifndef CPP_VM_STACK_H
#define CPP_VM_STACK_H


#include "context.h"
#include <vector>
#include <iostream>
#include "operation.h"

using namespace std;

const int reg_size = 5;

struct registers {
    bool bool_v[reg_size];
    int int_v[reg_size];
    op_argument var_v[reg_size];
};

struct loopstate {
    int countervar;
    int condTill;
    int step;

    // command addr
    int op_addr;
};

class stack {
public:
    context ctx;
    vector<operation> operations;
    int curOp = 0;
    registers r;
    int opsSize = 0;

    loopstate loop;

    stack() {
    }

    /**
     *
     * @return exit code
     */
     int execute();

    int pushOp(operation op);

};


#endif //CPP_VM_STACK_H
