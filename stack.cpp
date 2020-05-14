//
// Created by serhio on 14.05.20.
//

#include "stack.h"

#define arg_int(argIndex) that->args[argIndex].data.ival
#define arg_str(argIndex) that->args[argIndex].data.str
#define arg_ptr(argIndex) that->args[argIndex].data.ptr
#define arg_var(argIndex) that->args[argIndex]
#define get_ctx_var(vname) this->ctx.variables[vname]->static_value

int stack::executeNextOp() {

    if (this->opsSize == this->curOp) {
        return 1;
    }

    auto that = &this->operations[this->curOp++];

    switch (that->op) {
        case SET_FIELD: {
            auto varname = arg_str(0);

            auto x = arg_var(1);

            vm_var* newVar = new vm_var();

            switch (x.type) {
                case 1:
                    newVar->static_value.i = x.data.ival;
                    break;
                default:
                    cout << "dont know how to set a var type " << x.type << endl;

            }

            cout << " going to set a variable in vm : " << varname << " -> " << newVar->static_value.i << endl;
            this->ctx.variables[varname] = newVar;
            this->ctx.variables_arr[this->ctx.variables.size()] = newVar;

            this->r.int_v[0] = this->ctx.variables.size();
        } break;

        case NOT_EQ_ZERO:
        {
            auto var = this->r.var_v[0];

            int val0;
            int val1 = 0;

            if (var.type == 4) {
                val0 = this->ctx.variables[var.data.str]->static_value.i;
            } else {
                val0 = var.data.ival;
            }

            this->r.bool_v[0] = val0 != val1;
        }break;
        case NOT_EQ:
        {
            auto var = this->r.var_v[0];
            auto var1 = this->r.var_v[1];

            int val0;
            int val1;

            if (var.type == 4) {
                val0 = this->ctx.variables[var.data.str]->static_value.i;
            } else {
                val0 = var.data.ival;
            }

            if (var1.type == 4) {
                val1 = this->ctx.variables[var1.data.str]->static_value.i;
            } else {
                val1 = var1.data.ival;
            }

            this->r.bool_v[0] = val0 != val1;
        } break;
        case EQ: {
            auto var = this->r.var_v[0];
            auto var1 = this->r.var_v[1];

                    int val0;
                    int val1;

                    if (var.type == 4) {
                        val0 = this->ctx.variables[var.data.str]->static_value.i;
                    } else {
                        val0 = var.data.ival;
                    }

                    if (var1.type == 4) {
                        val1 = this->ctx.variables[var1.data.str]->static_value.i;
                    } else {
                        val1 = var1.data.ival;
                    }

                    this->r.bool_v[0] = val0 == val1;
        } break;
        case MOV_TO_VAR:{

            this->r.var_v[arg_int(0)] = arg_var(1);

        } break;
        case JMP_IF: {
            if (this->r.bool_v[0]) {
                this->curOp = arg_int(0);;
            }
        } break;
        case JMP: {
            this->curOp = arg_int(0);
        } break;
        case INC: {

            auto var_name = arg_str(0);

            // todo check type
            auto var_val = get_ctx_var(var_name).i++;

        } break;
        case DIV : {
            auto var = this->r.var_v[0];
            auto var1 = this->r.var_v[1];


                if (var.type != 4 && var1.type != 4) {
                    this->r.int_v[0] = var.data.ival % var1.data.ival;
                } else {
                    int val0;
                    int val1;

                    if (var.type == 4) {
                        val0 = this->ctx.variables[var.data.str]->static_value.i;
                    } else {
                        val0 = var.data.ival;
                    }

                    if (var1.type == 4) {
                        val1 = this->ctx.variables[var1.data.str]->static_value.i;
                    } else {
                        val1 = var1.data.ival;
                    }

                    // put result into first var register

                    // int only
                    this->r.var_v[0].data.ival =  val0 % val1;
                    this->r.var_v[0].type = 1;
                }
        } break;
        case PRINT: {
            auto var = arg_var(0);
            if (var.type != 4) {

                // switch case type :)

                cout << "this is the print op of static val " << var.data.ival << endl;
            } else {
                auto var_val = this->ctx.variables[var.data.str];

                // its a reference or func call
                cout << " this the print op of referenced context `" << var.data.str << "`= " << var_val->static_value.i << endl;
            }

        }
            break;
        default:
            cout << "unable to handle op " << that->op << endl;
    }

    return 0;
}


int stack::pushOp(operation op) {
    this->operations.push_back(op);
    this->opsSize = this->operations.size();
    return this->opsSize - 1;
}
