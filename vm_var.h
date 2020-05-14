//
// Created by serhio on 14.05.20.
//

#ifndef CPP_VM_VM_VAR_H
#define CPP_VM_VM_VAR_H


union var_val {
    int i;
    float f;
};

struct vm_var {

    bool is_static = false;

    var_val static_value;
    const char *referenced_name;

    bool isStatic() {
        return is_static;
    }

    vm_var(int val) {
        is_static = true;
        static_value.i = val;
    }

    vm_var(float val) {
        is_static = true;
        static_value.f = val;
    }

    vm_var(int istatic, const char* reference) {
        is_static = istatic;
        referenced_name = reference;
    }

    vm_var() {

    }
};


#endif //CPP_VM_VM_VAR_H
