//
// Created by serhio on 14.05.20.
//

#ifndef CPP_VM_CONTEXT_H
#define CPP_VM_CONTEXT_H

#include <string>
#include <map>
#include "vm_var.h"

using namespace std;

struct context {
    vm_var* variables[255];
};


#endif //CPP_VM_CONTEXT_H
