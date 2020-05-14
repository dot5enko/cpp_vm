#include <iostream>
#include "stack.h"
#include "vm_var.h"

int main() {

    stack x;

    operation set_i_var(SET_FIELD);
    {
        set_i_var.argument_str("i\0");
        set_i_var.argument_int(0);
    }

    x.pushOp(set_i_var);

    operation set_count_var(SET_FIELD);
    {
        set_count_var.argument_str( "count\0");
        set_count_var.argument_int(10000000);
    }
    x.pushOp(set_count_var);


    operation inc_i(INC);
    inc_i.argument_str("i");
    auto loopStart  = x.pushOp(inc_i);

    cout << " loop start address " << loopStart << endl;

    if (true){
        {
            operation mov(MOV_TO_VAR);
            mov.argument_int(0);
            mov.argument_var_ref("i");
            x.pushOp(mov);
        }

        {
            operation mov(MOV_TO_VAR);
            mov.argument_int(1);
            mov.argument_int(100000);
            x.pushOp(mov);
        }


        // this puts first element of var
            operation calc_div(DIV);
            x.pushOp(calc_div);


//        {
//            operation mov(MOV_TO_VAR);
//            mov.argument_int(1);
//            mov.argument_int(0);
//            x.pushOp(mov);
//        }

        operation print_each_n_status(NOT_EQ_ZERO);
        int curPos = x.pushOp(print_each_n_status);

        // jump over echo string
        operation jmp_if_true(JMP_IF);
        jmp_if_true.argument_int(curPos + 3);
        x.pushOp(jmp_if_true);

        operation print_i_op(PRINT);
        print_i_op.argument_var_ref("i");
        x.pushOp(print_i_op);
    }

    {
        operation mov(MOV_TO_VAR);
        mov.argument_int(0);
        mov.argument_var_ref("i");
        x.pushOp(mov);
    }
    {
        operation mov(MOV_TO_VAR);
        mov.argument_int(1);
        mov.argument_var_ref("count");
        x.pushOp(mov);
    }

    // compare two numbers on registers above
    operation cmp_i_and_count(NOT_EQ);
    x.pushOp(cmp_i_and_count);

    operation jmp_if_true(JMP_IF);
    jmp_if_true.argument_int(loopStart);
    x.pushOp(jmp_if_true);

    int iter = 0;

    while (true) {
        auto opRet = x.executeNextOp();
        iter++;

        if (opRet != 0) {
            if (opRet == 1) {
                cout << "done executing program with " <<iter << " iterations " << endl;
                break;
            } else {
                cout << "Unable to execute some operation " << endl;
            }
        }
    }


    return 0;
}
