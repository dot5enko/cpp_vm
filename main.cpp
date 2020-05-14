#include <iostream>
#include "stack.h"
#include "vm_var.h"

#define VAR_I 0
#define VAR_COUNT 1
#define VAR_A 2

int main() {

    stack x;

    int iters = 10000000;

    operation set_i_var(SET_FIELD);
    {
        // field id
        set_i_var.argument_int(VAR_I);
        set_i_var.argument_int(0);
    }

    x.pushOp(set_i_var);

    operation set_count_var(SET_FIELD);
    {

        set_count_var.argument_int( VAR_COUNT);
        set_count_var.argument_int(iters);
    }
    x.pushOp(set_count_var);

    {
        operation set_var(SET_FIELD);
        set_var.argument_int(VAR_A);
        set_var.argument_int(0);
        x.pushOp(set_var);
    }

    operation inc_i(INC_REF);
    inc_i.argument_int(VAR_I);
    auto loopStart  = x.pushOp(inc_i);

    cout << " loop start address " << loopStart << endl;

    operation mul_a(MUL_REF_CONST);
    mul_a.argument_int(VAR_I);
    mul_a.argument_int(2);
    x.pushOp(mul_a);

    operation assign_a(ASSIGN_INT);
    assign_a.argument_int(VAR_A);
    x.pushOp(assign_a);

    if (true){
        // this puts first element of var
        operation calc_div(DIV_REF_CONST);
        calc_div.argument_int(VAR_I);
        calc_div.argument_int(100000);
        x.pushOp(calc_div);

        operation print_each_n_status(NOT_EQ_CONST);
        print_each_n_status.argument_int(0);
        int curPos = x.pushOp(print_each_n_status);

        // jump over echo string
        operation jmp_if_true(JMP_IF);
        jmp_if_true.argument_int(curPos + 3);
        x.pushOp(jmp_if_true);

        operation print_i_op(PRINT);
        print_i_op.argument_var_ref(VAR_A);
        x.pushOp(print_i_op);
    }

    operation cmp_i_and_count(NOT_EQ_REFS_INT);
    cmp_i_and_count.argument_int(VAR_I);
    cmp_i_and_count.argument_int(VAR_COUNT);

    x.pushOp(cmp_i_and_count);

    operation jmp_if_true(JMP_IF);
    jmp_if_true.argument_int(loopStart);
    x.pushOp(jmp_if_true);

    int iter = 0;


        auto opRet = x.execute();

        if (opRet != 0) {
            if (opRet == 1) {
                cout << "done executing program with " <<iter << " iterations " << endl;
            } else {
                cout << "Unable to execute some operation " << endl;
            }
        }

    return 0;
}
