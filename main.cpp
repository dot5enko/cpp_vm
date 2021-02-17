#include <iostream>
#include "stack.h"
#include "vm_var.h"

#define VAR_I 0
#define VAR_COUNT 1
#define VAR_A 2
#define VAR_AB_FUNCTION_CALL_RESULT 3
#define VAR_10K 4

#define LOOP_MAIN 1


#define FUNC_A_PLUS_B 1
#define FUNC_MAIN 0

int main() {

    stack_frame** globalStackFrame = new stack_frame*[2];

    stack_frame main_program(globalStackFrame);

    globalStackFrame[FUNC_MAIN] = &main_program;

    {
        main_program._stack.ctx.variables = new vm_var[5];

        // stack allocation :)
        int iters = 10000000;

        main_program._stack.ctx.variables[VAR_I].static_value.i = 0;
        main_program._stack.ctx.variables[VAR_COUNT].static_value.i = iters;
        main_program._stack.ctx.variables[VAR_A].static_value.i = 0;
        main_program._stack.ctx.variables[VAR_AB_FUNCTION_CALL_RESULT].static_value.i = 0;
        main_program._stack.ctx.variables[VAR_10K].static_value.i = 10000;

        operation loop_init(INIT_LOOP);
        loop_init.argument_int(LOOP_MAIN);
        loop_init.argument_int(VAR_I); // counter
        loop_init.argument_int(VAR_COUNT); // counter less than reference
        loop_init.argument_int(1); // step
        loop_init.argument_int(1); // next OP addr
        main_program._stack.pushOp(loop_init);

        operation mul_a(MUL_REF_CONST);
        mul_a.argument_int(VAR_I);
        mul_a.argument_int(2);
        main_program._stack.pushOp(mul_a);

        operation assign_a(ASSIGN_INT);
        assign_a.argument_int(VAR_A);
        main_program._stack.pushOp(assign_a);

        if (true) {
            // this puts first element of var
            operation calc_div(DIV_REF_CONST);
            calc_div.argument_int(VAR_I);
            calc_div.argument_int(100000);
            main_program._stack.pushOp(calc_div);

            operation print_each_n_status(NOT_EQ_CONST);
            print_each_n_status.argument_int(0);
            int curPos = main_program._stack.pushOp(print_each_n_status);

            // jump over echo string
            operation jmp_if_true(JMP_IF);
            jmp_if_true.argument_int(curPos + 5);
            main_program._stack.pushOp(jmp_if_true);

            operation fn_apb_call(CALL_FN);
            fn_apb_call.argument_int(1); // address of a function
            fn_apb_call.argument_var_ref(VAR_AB_FUNCTION_CALL_RESULT); // result
            fn_apb_call.argument_var_ref(VAR_10K);
            fn_apb_call.argument_var_ref(VAR_I);
            main_program._stack.pushOp(fn_apb_call);

            {
                operation print_i_op(PRINT);
                print_i_op.argument_var_ref(VAR_I);
                main_program._stack.pushOp(print_i_op);
            }

            operation print_i_op(PRINT);
            print_i_op.argument_var_ref(VAR_AB_FUNCTION_CALL_RESULT);
            main_program._stack.pushOp(print_i_op);
        }

        operation loop_step(LOOP_STEP);
        main_program._stack.pushOp(loop_step);

//        operation print_count_var(PRINT);
//        print_count_var.argument_var_ref(VAR_AB_FUNCTION_CALL_RESULT);
//        main_program._stack.pushOp(print_count_var);
    }

    // declare function(a,b) {
    //  return a + b;
    // }
    stack_frame func_a_plus_b(globalStackFrame);
    {
        operation plusOp(ADD_REFS_INT);

        // stack allocated
        plusOp.argument_var_ref(1); // local var
        plusOp.argument_var_ref(2); // local var
        func_a_plus_b._stack.pushOp(plusOp);

        operation assignResult(ASSIGN_INT);
        assignResult.argument_var_ref(0);
        func_a_plus_b._stack.pushOp(assignResult);

        func_a_plus_b._stack.ctx.count = 3;
        func_a_plus_b._stack.ctx.variables = new vm_var[func_a_plus_b._stack.ctx.count];
    }

    globalStackFrame[FUNC_A_PLUS_B] = &func_a_plus_b;

    execute_stack_frame(&main_program);

    return 0;
}
