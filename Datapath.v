`timescale 1ns / 1ps

module Datapath(clk_in, displayInstruction, operationCode, ALUorMEMOut, jumpOut);

    input clk_in;
    
    output [7:0]displayInstruction;
    output[2:0]operationCode;
    output ALUorMEMOut;
    output jumpOut;

    wire [7:0] address;
    wire clock;
    wire [2:0]op; 
    wire [2:0] RegWrite; 
    wire ALUSrc; 
    wire MEM; 
    wire RegOrSign;
    wire rs, rt;
    wire [7:0]data;
    wire [7:0] rs_out; 
    wire [7:0] rd_out;
    wire ALUorMEM;
    wire Jump;
    
    //PC output
    wire [7:0]addressOUT;
    
    //Instruction MEM output
    wire [7:0]instructionOUT;
    
    //Signextend wire + MUX output
    wire [7:0]SignEx; //might not need
    wire [7:0]MuxOut;
    
    //output from ALU
    wire [7:0]ALUdata;
    
    //stores imm value
    wire [7:0]imm;
    
    //
    wire [7:0]MEMout;
    
    wire [7:0]MUX2OUT;
    
    wire [7:0]NexInstruction;
    wire [7:0]JumpAddress;
    wire [7:0]MuxAddress;
    
    
    PC ProgramCounter(clk_in, address, addressOUT);
    
    // adder to +1 to address to get to next instruction address

    Instruction_MEM InstructionMemory(addressOUT, instructionOUT);
    assign displayInstruction = instructionOUT;
 
    assign op = instructionOUT[7:5]; //assigning OP code based off instruction determined by InstructionMEM
    
    Control_Unit ControlUnit(op, RegWrite, ALUSrc, MEM, RegOrSign, ALUorMEM, Jump);
    
    assign operationCode = op;
    
    assign ALUorMEMOut = ALUorMEM;
    assign jumpOut = Jump;
    
    assign rs = instructionOUT[3];
    assign rt = instructionOUT[4];
    
    //Sign_Extend_5 inst10(instructionOUT[4:0], JumpAddress);  
    
    Sign_Extend SignExtend(instructionOUT[2:0], imm);
    
    RegMod RegisterModule(rs, rt, data, RegWrite, rs_out, rd_out);

    
    MUX MUX(rd_out, imm, RegOrSign, MuxOut);
    
    ALU ALU(ALUSrc, rs_out, MuxOut, ALUdata);
    
    
    Data_MEM DataMemory(MEM, ALUdata, rd_out, MEMout);
    
    MUX MUX1(ALUdata , MEMout, ALUorMEM, data);
    //assign data = MUX2OUT;
    
    //ALU inst9(1, addressOUT, 1, address);
    PCAdder PC_Adder( addressOUT, instructionOUT[4:0], Jump, address);

    
    //MUX1 inst11(NexInstruction, JumpAddress, Jump, MuxAddress);
    
    
endmodule 
