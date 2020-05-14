#include <iostream>
#include "stack.h"
#include "vm_var.h"

#define VAR_I 0
#define VAR_COUNT 1
#define VAR_A 2

#define LOOP_MAIN 1

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

    int curAddr = 0;

    {
        operation set_var(SET_FIELD);
        set_var.argument_int(VAR_A);
        set_var.argument_int(0);
        curAddr = x.pushOp(set_var);
    }

    operation loop_init(INIT_LOOP);
    loop_init.argument_int(LOOP_MAIN);
    loop_init.argument_int(VAR_I); // counter
    loop_init.argument_int(VAR_COUNT); // counter less than reference
    loop_init.argument_int(1); // step
    loop_init.argument_int(curAddr + 2); // first op inside loop address
    x.pushOp(loop_init);

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

    operation loop_step(LOOP_STEP);
    x.pushOp(loop_step);

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
