#include"systemc.h"

SC_MODULE(pc_gen){

  sc_in<bool> clock;
  sc_in<sc_uint<16> > Rtag;
  sc_in<sc_uint<16> > Disp;
  sc_out<sc_uint<16> > pc;
  sc_out<sc_uint<16> > pc_c;

  sc_uint<16> pc1 = 0;
  sc_uint<16> Rtag1;
  sc_uint<16> Disp1;

  void prc_pc1(){
    Rtag1 = Rtag.read();
    Disp1 = Disp.read();

   if(Disp1 == 0 & Rtag1 != 65535){
      pc1 = 0;
      pc1 += Rtag1;
      pc.write(pc1);
    }
    else if(Disp1 != 0 & Rtag1 == 65535)
    {
      pc1 += Disp1;
      pc.write(pc1);
    }
    else{
      pc.write(pc1);
      pc1 +=1;
   }
}
  SC_CTOR(pc_gen){
    SC_METHOD(prc_pc1);
    sensitive <<Rtag<<clock.pos();
}
};


SC_MODULE(RD){
  sc_in<sc_uint<16> > instr;
  sc_in<sc_uint<4> > psr;
  sc_in<bool> clock;
  sc_in<sc_uint<16> > pc;
  sc_out<sc_uint<4> > addr1;
  sc_out<sc_uint<4> > addr2;
  sc_out<sc_uint<4> > addr3;
  sc_out<sc_uint<8> > Imm;
  sc_out<sc_uint<16> > ctr;
  sc_out<sc_uint<16> > Rlink;
  sc_out<sc_uint<16> > Disp;

  sc_uint<16> instr1;
  sc_uint<4> psr1;
  sc_uint<4> opcode;
  sc_uint<4> op_ext;
  sc_uint<4> addr1_1;
  sc_uint<4> addr2_1;
  sc_uint<4> addr3_1;
  sc_uint<8> Imm1;
  sc_uint<16> pc1;
  sc_uint<8> Disp1;
  sc_uint<16> Disp_ex;
  sc_uint<4> Cond;
  sc_uint<1> F,C,N,Z;

  int i;

  void prc_RD(){
    instr1 = instr.read();
    opcode = instr1.range(15,12);
    op_ext = instr1.range(7,4);
    addr1_1 = instr1.range(11,8);
    addr2_1 = instr1.range(3,0);
    addr3_1 = instr1.range(11,8);
    Imm1 = instr1.range(7,0);
    Disp1 =instr1.range(7,0);
    Cond = instr1.range(11,8);
    pc1 = pc.read();
    psr1 = psr.read();
    F = psr1.range(3,3);
    C = psr1.range(2,2);
    N = psr1.range(1,1);
    Z = psr1.range(0,0);

    for(i = 0; i < 8; i++)
    Disp_ex[i] = Disp1[i];
    for(i = 8; i < 16; i++)
    Disp_ex[i] = 0;
  if(opcode==0 & op_ext==5)//ADD
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b0100111000101000);
    }
    else if(opcode==5) //ADDI
   {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
     ctr.write(0b1100111001011000);
   }
   else if(opcode==11) //CMPI
   {
     addr1.write(addr1_1);
     addr2.write(addr2_1);
     addr3.write(addr3_1);
     Imm.write(Imm1);
     ctr.write(0b1000111001011000);
   }
else if(opcode==0 & op_ext==1) //AND
   {
     addr1.write(addr1_1);
     addr2.write(addr2_1);
     addr3.write(addr3_1);
     Imm.write(Imm1);
     ctr.write(0b0100111000001000);
   }
   else if(opcode==1) //ANDI
   {
     addr1.write(addr1_1);
     addr2.write(addr2_1);
     addr3.write(addr3_1);
     Imm.write(Imm1);
     ctr.write(0b0000111000001000);
   }
else if(opcode==0 & op_ext==2) //OR
   {
     addr1.write(addr1_1);
     addr2.write(addr2_1);
     addr3.write(addr3_1);
     Imm.write(Imm1);
     ctr.write(0b0100111000010000);
   }
   else if(opcode==2) //ORI
   {
     addr1.write(addr1_1);
     addr2.write(addr2_1);
     addr3.write(addr3_1);
     Imm.write(Imm1);
     ctr.write(0b1000111000010000);
   }
   else if(opcode==0 & op_ext==3) //XOR
   {
     addr1.write(addr1_1);
     addr2.write(addr2_1);
     addr3.write(addr3_1);
     Imm.write(Imm1);
     ctr.write(0b0100111000011000);
   }
else if(opcode==3) //XORI
   {
     addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b1000111000011000);
    }
    else if(opcode==0 & op_ext==13) //MOV
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b0100111001101000);
    }
    else if(opcode==13) //MOVI
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b1000111001101000);
    }
    else if(opcode==8 & op_ext==4) //LSH
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b0100111000100000);
    }
    else if(opcode==8 & op_ext==0 || opcode==8 & op_ext==1) //LSHI
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b0000111000100000);
    }
else if(opcode==8 & op_ext==6) //ASH
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b0100111000110000);
    }
    else if(opcode==8 & op_ext==4 || opcode==8 & op_ext==5) //ASHI
    {
      addr1.write(addr1_1);
      addr2.write(addr2_1);
      addr3.write(addr3_1);
      Imm.write(Imm1);
      ctr.write(0b0000111000110000);
    }
 else if(opcode==15) //LUI
 {
   addr1.write(addr1_1);
   addr2.write(addr2_1);
   addr3.write(addr3_1);
   Imm.write(Imm1);
   ctr.write(0b0000111001111000);
 }
 else if(opcode==4 & op_ext==0) //LOAD
 {
   addr1.write(addr1_1);
   addr2.write(addr2_1);
   addr3.write(addr3_1);
   Imm.write(Imm1);
   ctr.write(0b0100101000111100);
 }
 else if(opcode==4 & op_ext==4) //STORE
 {
   addr1.write(addr1_1);
   addr2.write(addr2_1);
   addr3.write(addr3_1);
   Imm.write(Imm1);
   ctr.write(0b0100100001010000);
 }
 else if(opcode==4 & op_ext==8) //JAL
 {
   addr1.write(addr1_1);
   addr2.write(addr2_1);
   addr3.write(addr3_1);
   Imm.write(Imm1);
   Rlink.write(pc1);
   ctr.write(0b0000011111000000);
 }
else if(opcode==12) //Bcond
 {
   if(Cond==0 & Z==1) //BEQ
   {
     Disp.write(Disp_ex);
   }
   else if(Cond==1 & Z==0) //BNE
   {
     Disp.write(Disp_ex);
   }
   else if(Cond==13 & Z==1 ||Cond==13 & N==1) //BGE
   {
     Disp.write(Disp_ex);
   }
   else if(Cond==2 & C==1) //BCS
   {
     Disp.write(Disp_ex);
   }
   else if(Cond==3 & C==0) //BCC
   {
        Disp.write(Disp_ex);
      }
      else if(Cond==6 & N==1) //BGT
      {
        Disp.write(Disp_ex);
      }
      else if(Cond==7 & N==0) //BLE
      {
        Disp.write(Disp_ex);
      }
      else if(Cond==12 & N==0 ||Cond==12 & Z==0) //BLT
      {
        Disp.write(Disp_ex);
      }
      else
      {
        Disp.write(0);
      }
    }
else if(opcode==4 & op_ext==12) //Jcond
    {
      if(Cond==0 & Z==1) //JEQ
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==1 & Z==0) //JNE
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==13 & Z==1 ||Cond==13 & N==1) //JGE
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==2 & C==1) //JCS
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==3 & C==0) //JCC
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==6 & N==1) //JGT
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==7 & N==0) //JLE
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else if(Cond==12 & N==0 ||Cond==12 & Z==0) //JLT
      {
        addr1.write(addr2_1);
        addr2.write(addr1_1);
        addr3.write(addr2_1);
        ctr.write(0b0100011100010000);
      }
      else
      {
        addr1.write(0);
        addr2.write(10);
        addr3.write(10);
        Imm.write(0);
        ctr.write(0b0100111000010000);
      }
    }
    else //NOP
    {
      addr1.write(0);
      addr2.write(0);
      addr3.write(0);
      Imm.write(0);
      ctr.write(0b0100111000010000);
    }
  }

  SC_CTOR(RD){
    SC_METHOD(prc_RD);
    sensitive << clock.pos()<<instr;
  }

};

