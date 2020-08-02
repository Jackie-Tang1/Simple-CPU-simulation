#include"systemc.h"
#include"pro1_ctr.cpp"
#include"pro1_datapath.h"



int sc_main(int argc, char*argv[]){
   sc_signal<sc_uint<16> > pc1;
   sc_signal<sc_uint<16> > instr1;
   sc_signal<sc_uint<4> > r1_1;
   sc_signal<sc_uint<4> > r2_1;
   sc_signal<sc_uint<4> > r3_1;
   sc_signal<sc_uint<4> > psr1;
   sc_signal<sc_uint<16> > Rtag1;
   sc_signal<sc_uint<16> > Rlink1;
   sc_signal<sc_uint<8> > Imm1;
   sc_signal<sc_uint<16> > control1;
   sc_signal<sc_uint<16> > Disp_out;
   sc_signal<sc_uint<16> > pc_out;

   sc_clock clk("clk1",40,SC_NS);

   pc_gen p("pc_gen1");
   RD r("RD1");
   top t("top1");


   p.clock(clk);
   p.Rtag(Rtag1);
   p.Disp(Disp_out);
   p.pc(pc1);
   p.pc_c(pc_out);

   r.instr(instr1);
   r.psr(psr1);
   r.clock(clk);
   r.pc(pc_out);
   r.addr1(r1_1);
   r.addr2(r2_1);
   r.addr3(r3_1);
   r.Imm(Imm1);
   r.ctr(control1);
   r.Rlink(Rlink1);
   r.Disp(Disp_out);

  

   t.r1(r1_1);
   t.r2(r2_1);
   t.r3(r3_1);
   t.control(control1);
   t.Imm(Imm1);
   t.pc(pc1);
   t.Rlink(Rlink1);
   t.instr(instr1);
   t.Rtag(Rtag1);
   t.psr(psr1);
   t.clock(clk);

   sc_start(1280,SC_NS);
   return 0;
}

