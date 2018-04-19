//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_RV32I_OP_H
#define RISCSIM_RV32I_OP_H

void  add_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  sub_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  sll_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  slt_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void sltu_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  xor_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  srl_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  sra_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void   or_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
void  and_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);

void  jal_op(int32_t offset, int32_t* rd, int32_t* pc);
void jalr_op(int32_t offset, int32_t base, int32_t* rd, int32_t* pc);
void  beq_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
void  bne_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
void  blt_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
void bltu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
void  bge_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
void bgeu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);

#endif //RISCSIM_RV32I_OP_H
