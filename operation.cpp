//
// Created by serhio on 14.05.20.
//

#include "operation.h"
#include <iostream>
#include <cstdarg>
#include <memory.h>
#include "vm_var.h"
#include "context.h"
#include "stack.h"

using namespace std;

operation::operation(operation_id op) : op(op) {
    this->op = op;
    this->args_count = 0;
}

operation::~operation() {
}

void operation::argument(op_argument arg) {
    this->args[this->args_count++] = arg;
}

void operation::argument_int(int arg) {
    auto cur = &this->args[this->args_count++];
    cur->data.ival = arg;
    cur->type = 1;
}

void operation::argument_str(char *arg) {
    auto cur = &this->args[this->args_count++];
    cur->data.str = strdup(arg);
    cur->type = 2;
}

void operation::argument_ptr(void *ptr) {
    auto cur = &this->args[this->args_count++];
    cur->data.ptr = ptr;
    cur->type = 3;
}

void operation::argument_var_ref(int refId) {
    auto cur = &this->args[this->args_count++];
    cur->data.ival = refId;
    cur->type = 4;
}