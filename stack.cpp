//
// Created by serhio on 14.05.20.
//

#include "stack.h"

#define arg_int(argIndex) that->args[argIndex].data.ival
#define arg_str(argIndex) that->args[argIndex].data.str
#define arg_ptr(argIndex) that->args[argIndex].data.ptr
#define arg_var(argIndex) that->args[argIndex]
#define get_ctx_var(id) this->ctx.variables[id]->static_value

int stack::execute() {

    while (true) {

        if (this->opsSize == this->curOp) {
            return 1;
        }

        auto that = &this->operations[this->curOp++];

        switch (that->op) {
            case INIT_LOOP:{

                int loop_id = arg_int(0);

                this->loop.countervar = arg_int(1);
                this->loop.condTill = get_ctx_var(arg_int(2)).i;
                this->loop.step = arg_int(3);
                this->loop.op_addr = arg_int(4);

            }
                break;
            case LOOP_STEP:{

                int iValOld = get_ctx_var(this->loop.countervar).i;

                get_ctx_var(this->loop.countervar).i += this->loop.step;
                int iVal = get_ctx_var(this->loop.countervar).i;

                if (iVal <= this->loop.condTill) {
                    this->curOp = this->loop.op_addr;
                } else {
                    // free loop closure resources
                }
            }
            break;
            case SET_FIELD: {
                int id = arg_int(0);
                auto x = arg_var(1);

                vm_var *newVar = new vm_var();

                switch (x.type) {
                    case 1:
                        newVar->static_value.i = x.data.ival;
                        break;
                    default:
                        cout << "dont know how to set a var type " << x.type << endl;

                }

//                cout << " going to set a variable in vm : " << id << " -> " << newVar->static_value.i << endl;
                this->ctx.variables[id] = newVar;
            }
                break;

            case NOT_EQ_CONST: {
                int val0 = this->r.var_v[0].data.ival;
                int val1 = arg_int(0);

                this->r.bool_v[0] = val0 != val1;
            }
                break;
            case NOT_EQ: {
                auto var = this->r.var_v[0];
                auto var1 = this->r.var_v[1];

                int val0;
                int val1;

                if (var.type == 4) {
                    val0 = this->ctx.variables[var.data.ival]->static_value.i;
                } else {
                    val0 = var.data.ival;
                }

                if (var1.type == 4) {
                    val1 = this->ctx.variables[var1.data.ival]->static_value.i;
                } else {
                    val1 = var1.data.ival;
                }

                this->r.bool_v[0] = val0 != val1;
            }
                break;

            case NOT_EQ_REF_CONST: {
                int val0 = get_ctx_var(arg_int(0)).i;
                int val1 = arg_int(1);

                this->r.bool_v[0] = val0 != val1;
            }
                break;
            case NOT_EQ_REFS_INT: {

                int val0 = get_ctx_var(arg_int(0)).i;
                int val1 = get_ctx_var(arg_int(1)).i;

                this->r.bool_v[0] = val0 != val1;
            }
                break;

            case EQ: {
                auto var = this->r.var_v[0];
                auto var1 = this->r.var_v[1];

                int val0;
                int val1;

                if (var.type == 4) {
                    val0 = this->ctx.variables[var.data.ival]->static_value.i;
                } else {
                    val0 = var.data.ival;
                }

                if (var1.type == 4) {
                    val1 = this->ctx.variables[var1.data.ival]->static_value.i;
                } else {
                    val1 = var1.data.ival;
                }

                this->r.bool_v[0] = val0 == val1;
            }
                break;
            case MOV_TO_VAR: {

                this->r.var_v[arg_int(0)] = arg_var(1);

            }break;
            case ASSIGN_INT: {
                get_ctx_var(arg_int(0)).i =  this->r.int_v[0];
            } break;
            case MUL_REF_CONST: {
                this->r.int_v[0] = get_ctx_var(arg_int(0)).i *  arg_int(1);
            }
                break;
            case JMP_IF: {
                if (this->r.bool_v[0]) {
                    this->curOp = arg_int(0);;
                }
            }
                break;
            case JMP: {
                this->curOp = arg_int(0);
            }
                break;
            case INC_REF: {
                // todo check type
               get_ctx_var(arg_int(0)).i++;
            }
                break;
            case DIV_REF_CONST : {
                int val0 = this->ctx.variables[arg_int(0)]->static_value.i;
                int val1 = arg_int(1);

                // put result into first var register

                // int only
                this->r.var_v[0].data.ival = val0 % val1;
                this->r.var_v[0].type = 1;
            }
                break;
            case DIV : {
                auto var = this->r.var_v[0];
                auto var1 = this->r.var_v[1];


                if (var.type != 4 && var1.type != 4) {
                    this->r.int_v[0] = var.data.ival % var1.data.ival;
                } else {
                    int val0;
                    int val1;

                    if (var.type == 4) {
                        val0 = this->ctx.variables[var.data.ival]->static_value.i;
                    } else {
                        val0 = var.data.ival;
                    }

                    if (var1.type == 4) {
                        val1 = this->ctx.variables[var1.data.ival]->static_value.i;
                    } else {
                        val1 = var1.data.ival;
                    }

                    // put result into first var register

                    // int only
                    this->r.var_v[0].data.ival = val0 % val1;
                    this->r.var_v[0].type = 1;
                }
            }
                break;
            case PRINT: {
                auto var = arg_var(0);
                if (var.type != 4) {

                    // switch case type :)

                    cout << "this is the print op of static val " << var.data.ival << endl;
                } else {
                    auto var_val = this->ctx.variables[var.data.ival];

                    // its a reference or func call
                    cout << " this the print op of referenced context `" << var.data.ival << "`= "
                         << var_val->static_value.i << endl;
                }

            }
                break;
            default:
                cout << "unable to handle op " << that->op << endl;
        }
    }
    return 0;
}


int stack::pushOp(operation op) {
    this->operations.push_back(op);
    this->opsSize = this->operations.size();
    return this->opsSize - 1;
}
