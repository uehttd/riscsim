//
// Created by ilya on 13.04.18.
//

#ifndef RISCSIM_RV32I_OP_H
#define RISCSIM_RV32I_OP_H

inline void  add_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  sub_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  sll_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  slt_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void sltu_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  xor_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  srl_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  sra_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void   or_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);
inline void  and_op(int32_t op1, int32_t op2, int32_t* rd, int32_t* pc);

inline void  jal_op(int32_t offset, int32_t* rd, int32_t* pc);
inline void jalr_op(int32_t offset, int32_t base, int32_t* rd, int32_t* pc);
inline void  beq_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
inline void  bne_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
inline void  blt_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
inline void bltu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
inline void  bge_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);
inline void bgeu_op(int32_t offset, int32_t op1, int32_t op2, int32_t* pc);

inline void   lw_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc);
inline void   lh_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc);
inline void   lb_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc);
inline void  lhu_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc);
inline void  lbu_op(int32_t offset, int32_t base, char* mem, int32_t* rd, int32_t* pc);

inline void   sw_op(int32_t offset, int32_t base, char* mem, int32_t rs1, int32_t* pc);
inline void   sh_op(int32_t offset, int32_t base, char* mem, int32_t rs1, int32_t* pc);
inline void   sb_op(int32_t offset, int32_t base, char* mem, int32_t rs1, int32_t* pc);


#endif //RISCSIM_RV32I_OP_H
