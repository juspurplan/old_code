// You can use this skeleton testbench code, the textbook testbench code, or your own
// module MIPS_Testbench ();
//   reg CLK;
//   reg RST;
//   wire CS;
//   wire WE;
//   wire [31:0] Mem_Bus;
//   wire [6:0] Address;
//   
//   //parameter N = 32;   /* number of automated tests */
//   //reg[31:0] expected[N:1];
//     
//   wire[6:0] Address_Mux
//   wire[31:0] Mem_Bus_Wire;
//   wire WE_Mux, CS_Mux;
//   reg init, WE_TB, CS_TB;
//   
//   integer i;
//   
//   //assign Address_Mux = (init) ? AddressTB : Address;
//   assign WE_Mux = (init) ? WE_TB : WE;
//   assign CS_Mux = (init) ? CS_TB : CS;
// 
//   initial
//   begin
//   //	expected[1] = 32'
//     CLK = 0;
//   end
// 
//   MIPS CPU(CLK, RST, CS, WE, Address, Mem_Bus);
//   Memory MEM(CS, WE, CLK, Address, Mem_Bus);
// 
//   always
//   begin
//     #5 CLK = !CLK;
//   end
// 
//   always
//   begin
//     RST <= 1'b1; //reset the processor
// 
//     //Notice that the memory is initialize in the in the memory module not here
// 
//     @(posedge CLK);
//     // Initialize the instructions from the testbench
//     init <= 1;
//     CS_TB <= 1;
//     WE_TB <= 1;
//     
//     @(posedge CLK);
//     // driving reset low here puts processor in normal operating mode
//     RST = 1'b0;
// 
//     /* add your testing code here */
//     // you can add in a 'Halt' signal here as well to test Halt operation
//     // you will be verifying your program operation using the
//     // waveform viewer and/or self-checking operations
//     for(i = 0; i <= 144; i + 1) begin
//     	@(posedge CLK);
//     end
// 
//     $display("TEST COMPLETE");
//     $stop;
//   end
// 
// endmodule

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

module Complete_MIPS(CLK, RST, HALT/*, A_Out, D_Out, leds, light*/, an, segs, SW, BTN);
  // Will need to be modified to add functionality
  input CLK;
  input RST;
  input HALT;
  //output [7:0] leds;
  output [6:0] segs;
  output [3:0] an;
  input [2:0] SW;
  input [1:0] BTN;	// BTN[1] = BTNL, BTN[0] = BTNR
  
  parameter CLOCK_FREQUENCY = 100000000;	// default to 100 MHz
  wire debouncer_clock;
  //output light;

  wire CS, WE;
  wire [6:0] ADDR;
  wire [31:0] Mem_Bus;
  //wire [31:0] R1;
  wire CPUclock;
  wire divCLK;
  wire [2:0] deb_swtch;
  wire [1:0] dp_btns;
  reg [15:0] data;
  reg sevensegreg;
  wire [31:0] memR;
  
  assign CPUclock = divCLK & (~HALT);
  //assign leds = R1[7:0];
  //assign light = CPUclock;
  
  // reduced clock for the debouncer
  Divider #(
  	.DIVIDE_BY	(CLOCK_FREQUENCY/100),
  	.DURATION	()
  )
  db_div (
  	.clock_in	(CLK),
  	.clock_out	(debouncer_clock)
  );
  
  // logic block, depending on deb_swtch/dp_btns, give sevensegreg & send part of memR to SST
  always @(*)
  begin
  	sevensegreg = 0;
  	if((deb_swtch == 3'd0) && (dp_btns[1] == 1'b1))
  		sevensegreg = 1;
  		
  	data = memR[31:16];
  	if(dp_btns[0] == 1'b0)
  		data = memR[15:0];
  end

  MIPS CPU(CPUclock, RST, CS, WE, ADDR, Mem_Bus, memR, deb_swtch, sevensegreg);
  Memory MEM(CS, WE, CPUclock, ADDR, Mem_Bus);
  Divider #(100) div(CLK, divCLK);
  SevenSegTop SST(CLK, data, an, segs);
  Debouncer btn1(BTN[1], debouncer_clock, dp_btns[1]);
  Debouncer btn0(BTN[0], debouncer_clock, dp_btns[0]);
  Debouncer swtch2(SW[2], debouncer_clock, deb_swtch[2]);
  Debouncer swtch1(SW[1], debouncer_clock, deb_swtch[1]);
  Debouncer swtch0(SW[0], debouncer_clock, deb_swtch[0]);

endmodule

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

module Memory(CS, WE, CLK, ADDR, Mem_Bus);
  input CS;
  input WE;
  input CLK;
  input [6:0] ADDR;
  inout [31:0] Mem_Bus;

  reg [31:0] data_out;
  reg [31:0] RAM [0:127];


  initial
  begin
    /* Write your Verilog-Text IO code here */
    $readmemb("MIPS_Instructions_partb", RAM);
  end

  assign Mem_Bus = ((CS == 1'b0) || (WE == 1'b1)) ? 32'bZ : data_out;

  always @(negedge CLK)
  begin

    if((CS == 1'b1) && (WE == 1'b1))
      RAM[ADDR] <= Mem_Bus[31:0];

    data_out <= RAM[ADDR];
  end
endmodule

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

module REG(CLK, RegW, DR, SR1, SR2, Reg_In, ReadReg1, ReadReg2, memR, R1, sevensegreg);
  input CLK;
  input RegW;
  input [4:0] DR;
  input [4:0] SR1;
  input [4:0] SR2;
  input [31:0] Reg_In;
  output reg [31:0] ReadReg1;
  output reg [31:0] ReadReg2;
  output reg [31:0] memR;
  input [2:0] R1;
  input sevensegreg;

  reg [31:0] REG [0:31];
  integer i;

  initial begin
    ReadReg1 = 0;
    ReadReg2 = 0;
	for(i = 0; i < 32; i = i+1) begin
		REG[i] = 32'd 0;
	end
	
  end

  always @(posedge CLK)
  begin

    if((RegW == 1'b1) && (DR != 5'b1))
      REG[DR] <= Reg_In[31:0];

    ReadReg1 <= REG[SR1];
    ReadReg2 <= REG[SR2];
    //memR1 <= REG[5'd1];
    REG[5'd1] <= {29'd 0, R1};
    
    if(sevensegreg == 1'b0)
    	memR <= REG[5'd2];
    else
    	memR <= REG[5'd3];
  end
endmodule


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

`define opcode instr[31:26]
`define sr1 instr[25:21]
`define sr2 instr[20:16]
`define f_code instr[5:0]
`define numshift instr[10:6]

module MIPS (CLK, RST, CS, WE, ADDR, Mem_Bus, memR, R1, sevensegreg);
  input CLK, RST;
  output reg CS, WE;
  output [6:0] ADDR;
  inout [31:0] Mem_Bus;
  //output [31:0] R1;

  //special instructions (opcode == 000000), values of F code (bits 5-0):
  parameter add = 6'b100000;
  parameter sub = 6'b100010;
  parameter xor1 = 6'b100110;
  parameter and1 = 6'b100100;
  parameter or1 = 6'b100101;
  parameter slt = 6'b101010;
  parameter srl = 6'b000010;
  parameter sll = 6'b000000;
  parameter jr = 6'b001000;

  //non-special instructions, values of opcodes:
  parameter addi = 6'b001000;
  parameter andi = 6'b001100;
  parameter ori = 6'b001101;
  parameter lw = 6'b100011;
  parameter sw = 6'b101011;
  parameter beq = 6'b000100;
  parameter bne = 6'b000101;
  parameter j = 6'b000010;
  
  // new instruction opcodes
  parameter jal = 6'b 000011;
  parameter lui = 6'b 001111;
  
  parameter mult = 6'b 011000; //special. this is fcode
  parameter mfhi = 6'b 010000; //fcode
  parameter mflo = 6'b 010010; //fcode
  parameter add8 = 6'b 101101; //fcode
  parameter rbit = 6'b 101111; //fcode
  parameter rev = 6'b 110000; //fcode
  parameter sadd = 6'b 110001; //fcode
  parameter ssub = 6'b 110010; //fcode

  //instruction format
  parameter R = 2'd0;
  parameter I = 2'd1;
  parameter J = 2'd2;

  //internal signals
  reg [5:0] op, opsave;
  wire [1:0] format;
  reg [31:0] instr, alu_result;
  reg [6:0] pc, npc;
  wire [31:0] imm_ext, alu_in_A, alu_in_B, reg_in, readreg1, readreg2;
  reg [31:0] alu_result_save;
  reg alu_or_mem, alu_or_mem_save, regw, writing, reg_or_imm, reg_or_imm_save;
  reg fetchDorI;
  reg [4:0] dr;
  reg [2:0] state, nstate;
  
  // special registers
  reg [31:0] HI_result, LO_result;
  reg [31:0] special_reg_HI, special_reg_LO;
  initial begin
	special_reg_HI <= 0;
	special_reg_LO <= 0;
  end
  
  //wire [31:0] memR1;
  output [31:0] memR;
  input [2:0] R1;
  input sevensegreg;
  
  integer i;

  //combinational
  assign imm_ext = (instr[15] == 1)? {16'hFFFF, instr[15:0]} : {16'h0000, instr[15:0]};//Sign extend immediate field
  //assign dr = (format == R)? instr[15:11] : instr[20:16]; //Destination Register MUX (MUX1)
  always @(*) begin
	if(format == I) begin
		if(`opcode == jal) begin
			dr = 5'd 31;
		end
		else begin
			dr = instr[20:16]; // dr is rt
		end
	end
	else if (format == R && `f_code != rbit && `f_code != rev) begin
		dr = instr[15:11]; // dr is rd
	end
	else begin
		dr = instr[25:21]; // dr is rs
	end
  end
  assign alu_in_A = readreg1;
  assign alu_in_B = (reg_or_imm_save)? imm_ext : readreg2; //ALU MUX (MUX2)
  assign reg_in = (alu_or_mem_save)? Mem_Bus : alu_result_save; //Data MUX
  assign format = (`opcode == 6'd0)? R : ((`opcode == 6'd2)? J : I);
  assign Mem_Bus = (writing)? readreg2 : 32'bZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ;
  
  // display R1 to leds.
  //assign R1 = memR1;

  //drive memory bus only during writes
  assign ADDR = (fetchDorI)? pc : alu_result_save[6:0]; //ADDR Mux
  REG Register(CLK, regw, dr, `sr1, `sr2, reg_in, readreg1, readreg2, memR, R1, sevensegreg);

  initial begin
    op = and1; opsave = and1;
    state = 3'b0; nstate = 3'b0;
    alu_or_mem = 0;
    regw = 0;
    fetchDorI = 0;
    writing = 0;
    reg_or_imm = 0; reg_or_imm_save = 0;
    alu_or_mem_save = 0;
  end

  always @(*)
  begin
    fetchDorI = 0; CS = 0; WE = 0; regw = 0; writing = 0; alu_result = 32'd0;
    npc = pc; op = jr; reg_or_imm = 0; alu_or_mem = 0; nstate = 3'd0;
	HI_result = special_reg_HI; LO_result = special_reg_LO;
    case (state)
      0: begin //fetch
        npc = pc + 7'd1; CS = 1; nstate = 3'd1;
        fetchDorI = 1;
      end
      1: begin //decode
        nstate = 3'd2; reg_or_imm = 0; alu_or_mem = 0;
        if (format == J) begin //jump, and finish
          npc = instr[6:0];
          nstate = 3'd0;
        end
        else if (format == R) //register instructions
          op = `f_code;
        else if (format == I) begin //immediate instructions
          reg_or_imm = 1;
          if(`opcode == lw) begin
            op = add;
            alu_or_mem = 1;
          end
          else if ((`opcode == lw)||(`opcode == sw)||(`opcode == addi)) op = add;
          else if ((`opcode == beq)||(`opcode == bne)) begin
            op = sub;
            reg_or_imm = 0;
          end
          else if (`opcode == andi) op = and1;
          else if (`opcode == ori) op = or1;
		  else if (`opcode == lui) op = lui;
		  else if (`opcode == jal) op = jal;
        end
      end
      2: begin //execute
        nstate = 3'd3;
        if (opsave == and1) alu_result = alu_in_A & alu_in_B;
        else if (opsave == or1) alu_result = alu_in_A | alu_in_B;
        else if (opsave == add) alu_result = alu_in_A + alu_in_B;
        else if (opsave == sub) alu_result = alu_in_A - alu_in_B;
        else if (opsave == srl) alu_result = alu_in_B >> `numshift;
        else if (opsave == sll) alu_result = alu_in_B << `numshift;
        else if (opsave == slt) alu_result = (alu_in_A < alu_in_B)? 32'd1 : 32'd0;
        else if (opsave == xor1) alu_result = alu_in_A ^ alu_in_B;
		// new instructions
		else if (opsave == mult) begin	// MULT never writes to REG file.
									{HI_result, LO_result} = alu_in_A * alu_in_B;
									nstate = 3'd 0; //bypasses state 3 and 4, so it will never write to Reg File.
								end
		else if (opsave == mfhi) alu_result = special_reg_HI;
		else if (opsave == mflo) alu_result = special_reg_LO;
		else if (opsave == add8) alu_result = {alu_in_A[31:24]+alu_in_B[31:24], alu_in_A[23:16]+alu_in_B[23:16], 
													alu_in_A[15:8]+alu_in_B[15:8], alu_in_A[7:0]+alu_in_B[7:0]};
		else if (opsave == rbit) begin
									for (i = 0; i < 32; i = i + 1) begin
										alu_result[i] = alu_in_B[31-i];
									end
								 end
		else if (opsave == rev) alu_result = {alu_in_B[7:0], alu_in_B[15:8], alu_in_B[23:16], alu_in_B[31:24]};
		else if (opsave == sadd) begin : alu_sadd
									reg [32:0] carry;
									carry = (alu_in_A + alu_in_B);
									alu_result = (carry[32] == 1'b 1) ? (2^32-1) : (alu_in_A + alu_in_B);
								end
		else if (opsave == ssub) alu_result = (alu_in_A < alu_in_B) ? 0 : (alu_in_A - alu_in_B);
		else if (opsave == lui) alu_result = alu_in_B << 16;
		else if (opsave == jal) begin
									alu_result = pc;
									npc = instr[25:0];
								end
		
		// check BR condition
        if (((alu_in_A == alu_in_B)&&(`opcode == beq)) || ((alu_in_A != alu_in_B)&&(`opcode == bne))) begin
			//BR taken
          npc = pc + imm_ext[6:0];
          nstate = 3'd0;
        end
        else if ((`opcode == bne)||(`opcode == beq)) nstate = 3'd0; // BR not taken
        else if (opsave == jr) begin
			// JMP based on register
          npc = alu_in_A[6:0];
          nstate = 3'd0;
        end
      end
      3: begin //prepare to write to mem
        nstate = 3'd0;
        if ((format == R)||(`opcode == addi)||(`opcode == andi)||(`opcode == ori) || (`opcode == jal) || (`opcode == lui)) regw = 1;	// enable write to Reg File.
        else if (`opcode == sw) begin
          CS = 1;
          WE = 1;
          writing = 1;
        end
        else if (`opcode == lw) begin
          CS = 1;
          nstate = 3'd4;
        end
      end
	  
      4: begin
        nstate = 3'd0;
        CS = 1;
        if (`opcode == lw) regw = 1;
      end
    endcase
  end //always

  always @(posedge CLK) begin

    if (RST) begin
      state <= 3'd0;
      pc <= 7'd0;
    end
    else begin
      state <= nstate;
      pc <= npc;
    end
	
	// update special registers
	special_reg_HI <= HI_result;
	special_reg_LO <= LO_result;

    if (state == 3'd0) instr <= Mem_Bus;
    else if (state == 3'd1) begin
      opsave <= op;
      reg_or_imm_save <= reg_or_imm;
      alu_or_mem_save <= alu_or_mem;
    end
    else if (state == 3'd2) alu_result_save <= alu_result;

  end //always

endmodule
