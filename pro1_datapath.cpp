#include"systemc.h"

SC_MODULE(choose){
  sc_in<sc_uint<16> > in1;
  sc_in<sc_uint<16> > in2;
  sc_in<sc_uint<16> > control;
  sc_out<sc_uint<16> > choose_out;
  sc_in<bool> clock;

  sc_uint<16> control1;
  sc_uint<16> in11;
  sc_uint<16> in21;
  sc_uint<1> C9;

  void prc_choose(){
    control1 = control.read();
    in11 = in1.read();
    in21 = in2.read();
    C9 = control1.range(2,2);

    if(C9==0){
      choose_out.write(in11);
    }
    if(C9==1){
      choose_out.write(in21);
    }
  }
 
  SC_CTOR(choose){
    SC_METHOD(prc_choose);
    sensitive << in1 << in2<<clock.pos();
  }
};

SC_MODULE(dm){
   sc_in<sc_uint<16> > addr;
   sc_in<sc_uint<16> > data_in;
   sc_out<sc_uint<16> > data_out;
   sc_in<bool> clock;

   sc_uint<16> addr1;
   sc_uint<16> din;
   sc_uint<16> R1[15];


   void dm_r(){
     static uint R1[16] = {0,0,0,0,0,0,0,0,0,0,36,0,12,0,-24,0};
     addr1 = addr.read();
     if(addr1<16){
     data_out.write(R1[addr1]);
}
     else{
       data_out.write(0b1111111111111111);
}

   }
   void dm_w(){

     addr1 = addr.read();
     din = data_in.read();
     if(addr1<16){
     R1[addr1] = din;

}
     else{
     R1[0] = din;
}

   }

   SC_CTOR(dm){
     SC_METHOD(dm_r);
     sensitive << addr<<clock.pos();
     SC_METHOD(dm_w);
     sensitive << data_in;
   }

};

SC_MODULE(pm){
  sc_in<sc_uint<16> > addr;
  sc_out<sc_uint<16> > instr;
  sc_in<bool> clock;

  sc_uint<16> addr1;
  sc_uint<16> R2[30];

  void prc_pm(){
    static uint R2[30] = {0,0,0,0,0,0,0,0,0,0,0b0000000101010010,0b0000000101010011,0b0000000101010100,
    0b0000000101010101,0,0,0,0,0b1011000100001010,0,0b0100000111001010,0b0000000101010110,0b0000000101010111,0b0000000101011000,0,0,0,0,0,0};
    addr1 = addr.read();
    if(addr1<30){
    instr.write(R2[addr1]);

  }
  }


  SC_CTOR(pm){
    SC_METHOD(prc_pm);
    sensitive << addr<<clock.pos();
  }
};
SC_MODULE(rf){
  sc_in<sc_uint<4> > r1;
  sc_in<sc_uint<4> > r2;
  sc_in<sc_uint<4> > r3;
  sc_in<sc_uint<16> > data_in;
  sc_out<sc_uint<16> > data_out1;
  sc_out<sc_uint<16> > data_out2;
  sc_in<bool> clock;

  sc_uint<4> r11,r21,r31;
  sc_uint<16> din;

 uint  R[16] = {0,1,2,3,4,5,6,7,8,0,26,0,0,0,0,0};
  void prc_rrf(){
    r11 = r1.read();
    r21 = r2.read();
    data_out1.write(R[r11]);
    data_out2.write(R[r21]);

   }
  void prc_wrf(){

    r31 = r3.read();
    din = data_in.read();
    if(r31 <  65535){
    R[r31] = din;
}
    else{
    R[r31] = R[r31];
}

  }

  SC_CTOR(rf){
    SC_METHOD(prc_rrf);
    sensitive << r1 << r2 << clock.pos();
    SC_METHOD(prc_wrf);
    sensitive << data_in ;
  }
};


SC_MODULE(alu){
    sc_in<sc_uint<8> > Imm;
    sc_in<sc_uint<16> > Rfin_1;
    sc_in<sc_uint<16> > Rfin_2;
    sc_in<sc_uint<16> > Rlink;
    sc_out<sc_uint<16> > Rtarget;
    sc_out<sc_uint<4> > psr;
    sc_out<sc_uint<16> > to_rf;
    sc_out<sc_uint<16> > mar;
    sc_out<sc_uint<16> > mdr;
    sc_in<sc_uint<16> > control;
    sc_in<bool> clock;

    sc_uint<1> C0,C1,C2,C3,C4,C5,C6,C7,C8;
    sc_uint<4> ctr;
    sc_uint<8> Imm1;
    sc_uint<8> Rfin_11;
    sc_uint<8> Rfin_22;
    sc_uint<16> Rlink1;
    sc_uint<16> Im;
    sc_uint<16> Im_zero;
    sc_uint<4> C1_outLo;
    sc_uint<16> mar1;
    sc_uint<16> mdr1;
    sc_uint<16> result;
    sc_uint<16> Rtarget1;
    sc_uint<4> psr1;
    sc_uint<16> control1;
    sc_uint<16> allzs;

    sc_uint<16>  C0_out;
    sc_uint<16>  C1_out;
    sc_uint<16>  C2_out;
    sc_uint<16>  C3_out;
    sc_uint<16>  C4_out;
    sc_uint<16>  C5_out;
    sc_uint<16>  C6_out;
    sc_uint<16>  C7_out;
    sc_uint<16>  C8_out;
    sc_uint<16>  alu_out;
    sc_uint<4> psr_out;


    int i;


    void prc_alu(){

      control1 = control.read();
      allzs = 0b1111111111111111;

      C0 = control1.range(15,15);
      C1 = control1.range(14,14);
      C2 = control1.range(13,13);
      C3 = control1.range(12,12);
      C4 = control1.range(11,11);
      C5 = control1.range(10,10);
      C6 = control1.range(9,9);
      C7 = control1.range(8,8);
      C8 = control1.range(7,7);

      ctr = control1.range(6,3);
      Imm1 = Imm.read();
      Rfin_11 = Rfin_1.read();
      Rfin_22 = Rfin_2.read();
      Rlink1 = Rlink.read();


      for(i = 0; i < 8; i++) //sign extended
      Im[i] = Imm1[i];
      for(i = 8; i < 16; i++)
      Im[i] = Imm1[7];

      for(i = 0; i < 8; i++) //zero extended
      Im_zero[i] = Imm1[i];
      for(i = 8; i < 16; i++)
      Im_zero[i] = 0 ;


      if(C0==0){
        C0_out = Im;
      }
      else{
        C0_out = Im_zero;
      }

      if(C1==0){
        C1_out = C0_out;
      }
      else{
        C1_out = Rfin_22;
      }

      if(C3==0){
        C3_out = Rfin_11;
      }
      else{
        C3_out = 0;
      }

      if(C4==0){
        Rtarget1 = C3_out;
        Rtarget.write(Rtarget1);
      }
   else{
     Rtarget1 = allzs;
     Rtarget.write(Rtarget1);
   }


   if(ctr==5){
     alu_out = C3_out + C1_out;
   }
   else if(ctr==9){
     alu_out = C3_out - C1_out;
   }
   else if(ctr==11){
     alu_out = C3_out;
     if(C3_out == C1_out ){
       psr_out = 1;
     }
     else if(C3_out < C1_out){
       psr_out = 2;
     }
     else{
       psr_out = 0;
     }
   }
   else if(ctr==1){
     alu_out = C3_out & C1_out;
   }
   else if(ctr==2){
     alu_out = C3_out | C1_out;
   }
   else if(ctr==3){
     alu_out = C3_out ^ C1_out;
   }
   else if(ctr==13){
     alu_out = C1_out;
   }
   else if(ctr==4){
     for(i = 0; i < 4; i++)//C1_out Lo
     C1_outLo[i] = C1_out[i];

     if(C1_out.range(3,3)==1){
       alu_out = C3_out >> C1_outLo;
     }
     else{
       alu_out = C3_out << C1_outLo;
     }
   }
   else if(ctr==6){
     for(i = 0; i < 4; i++)//C1_out Lo
     C1_outLo[i] = C1_out[i];

     if(C1_out.range(3,3)==1){
       alu_out = C3_out >> C1_outLo;
        }
        else{
          alu_out = C3_out << C1_outLo;
        }
      }
      else if(ctr==15){
        alu_out = C1_out << 8;
      }
      else if(ctr==7){
        alu_out = C1_out;
      }
      else if(ctr==10){
        alu_out = C1_out;
      }
      else if(ctr==8){
        alu_out = C1_out;
      }
    else{
      alu_out = 0b1111111111111111;
    }

    if(C5==0){
      mar1 = alu_out;
      mar.write(mar1);
    }
    else{
      mar1 = allzs;
      mar.write(mar1);
    }

    if(C6==0){
      mdr1 = C3_out;
      mdr.write(mdr1);
    }
    else{
      mdr1 = allzs;
      mdr.write(mdr1);
    }

    if(C7==0){
      C7_out = alu_out;
    }
    else{
      C7_out = allzs;
    }

    if(C8==0){
      result = C7_out;
      to_rf.write(result);
    }
    else{
      result = Rlink1;
      to_rf.write(Rlink1);
    }

    psr1 = psr_out;
    psr.write(psr1);
  }

  SC_CTOR(alu){
    SC_METHOD(prc_alu);
    sensitive << control<<Rfin_1<<Rfin_2<<clock.pos();
  }
};

SC_MODULE(mon){
   sc_in<sc_uint<4> >  addr1;
   sc_in<sc_uint<4> >  addr2;
   sc_in<sc_uint<4> >  addr3;
   sc_in<sc_uint<16> >  choose_r;
   sc_in<sc_uint<16> > instr;
   sc_in<sc_uint<16> > data_m;
   sc_in<sc_uint<16> > pc;
   sc_in<sc_uint<16> > Rfin_1;
   sc_in<sc_uint<16> > Rfin_2;
   sc_in<sc_uint<8> > Imm;
   sc_in<bool>  clock;
   sc_in<sc_uint<16> > contr;
   sc_in<sc_uint<16> > rtag;
   sc_uint<16>  instr1;
   const char* instr2;
   sc_uint<1> z;
   sc_uint<1> t;
 void prc_mon(){
    instr1 = instr.read();
    if(instr1.range(15,12)==11){
    instr2 = "CMPI";
    t = 1;
    z = 0;
}
    else if(instr1.range(15,12)==0 & instr1 !=0){
    instr2 = "ADD";
    t = 0;
    z = 0;
}
    else if(instr1.range(15,12)==4){
    instr2 = "JNE";
    t = 0;
    z = 1;
}
   else {
   instr2 = "OR";
   t = 0;
   z = 0;
 }

  cout <<"start:" << sc_time_stamp()<<"  ";
  cout <<"pc is"<<pc<<"   ";
  cout << instr2 <<"   ";
  if(z==0){
  if(t==0){
  cout << "R" << addr2<< "  ";
  }
  else{
  cout << Imm << "  ";
  }
  cout << "R" << addr3<< "  ";
}
  else{
  cout << "R"<< addr2 <<"  ";
}
  cout<<" R["<<addr3<<"]is:"<<choose_r<<"   "<<endl;
}

SC_CTOR(mon){
 SC_METHOD(prc_mon);
 sensitive << clock.pos();
}

};
