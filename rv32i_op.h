//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_RV32I_OP_H
#define RISCSIM_RV32I_OP_H

void  add_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  sub_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  sll_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  slt_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void sltu_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  xor_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  srl_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  sra_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void   or_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);
void  and_op(int32_t* rs1, int32_t* rs2, int32_t* rd, int32_t pc);

#endif //RISCSIM_RV32I_OP_H
