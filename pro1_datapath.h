#include"systemc.h"
#include"pro1_datapath.cpp"

SC_MODULE(top){
  sc_in<sc_uint<4> > r1;
  sc_in<sc_uint<4> > r2;
  sc_in<sc_uint<4> > r3;
  sc_in<sc_uint<16> > control;
  sc_in<sc_uint<8> > Imm;
  sc_in<sc_uint<16> > pc;
  sc_in<sc_uint<16> > Rlink;
  sc_in<bool> clock;
  sc_out<sc_uint<16> > instr;
  sc_out<sc_uint<16> > Rtag;
  sc_out<sc_uint<4> > psr;

  sc_signal<sc_uint<16> > rf_out1;
  sc_signal<sc_uint<16> > rf_out2;
  sc_signal<sc_uint<16> > alu_result;
  sc_signal<sc_uint<16> > alu_mar;
  sc_signal<sc_uint<16> > alu_mdr;
  sc_signal<sc_uint<16> > dm_out;
  sc_signal<sc_uint<16> > c_out;

  rf* rf1;
  pm* pm1;
  alu* alu1;
  dm* dm1;
  choose* choose1;
  mon* mon1;

  SC_CTOR(top){

    rf1 = new rf("rf1");
    pm1 = new pm("pm1");
    alu1 = new alu("alu1");
    dm1 = new dm("dm1");
    choose1 = new choose("choose1");
    mon1 = new mon("mon1");

    pm1->addr(pc);
    pm1->instr(instr);
    pm1->clock(clock);

    rf1->r1(r1);
    rf1->r2(r2);
    rf1->r3(r3);
    rf1->data_in(c_out);
    rf1->data_out1(rf_out1);
    rf1->data_out2(rf_out2);
    rf1->clock(clock);

    dm1->addr(alu_mar);
    dm1->data_in(alu_mdr);
    dm1->data_out(dm_out);
    dm1->clock(clock);

    alu1->Imm(Imm);
    alu1->Rfin_1(rf_out1);
    alu1->Rfin_2(rf_out2);
    alu1->Rlink(Rlink);
    alu1->Rtarget(Rtag);
    alu1->psr(psr);
    alu1->to_rf(alu_result);
    alu1->mar(alu_mar);
    alu1->mdr(alu_mdr);
    alu1->control(control);
    alu1->clock(clock);

    choose1->in1(alu_result);
    choose1->in2(dm_out);
    choose1->choose_out(c_out);
    choose1->control(control);
    choose1->clock(clock);

    mon1->addr1(r1);
    mon1->addr2(r2);
    mon1->addr3(r3);
    mon1->instr(instr);
    mon1->pc(pc);
    mon1->choose_r(c_out);
    mon1->data_m(alu_mdr);
    mon1->Rfin_1(rf_out1);
    mon1->Rfin_2(rf_out2);
    mon1->clock(clock);
    mon1->Imm(Imm);
    mon1->contr(control);
    mon1->rtag(Rtag);
  }

};
