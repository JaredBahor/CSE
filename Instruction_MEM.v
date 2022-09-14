`timescale 1ns / 1ps

module Instruction_MEM(address, Ins_output);
 
  input [7:0]address; //Input Address from PC
 
  output [7:0]Ins_output; //Instruction stored in the address
  
  reg [7:0]Instruction_MEM[255:0]; //Max limit of memory locations
  
  initial 
  begin   

    // loading instructions to execute 
    Instruction_MEM[0] = 8'b01001001; //sw $s0, 0 ($s1)
    Instruction_MEM[1] = 8'b00111000; //lw $s1,0($s1)
    Instruction_MEM[2] = 8'b10011000; //add $s1,$s1,$s1
    Instruction_MEM[3] = 8'b10100010; //addi $s0,$s0,2
    Instruction_MEM[4] = 8'b01100111; //j L1
    Instruction_MEM[5] = 8'b00000000; 
    Instruction_MEM[6] = 8'b00000000;
    Instruction_MEM[7] = 8'b11010000; // L1: sub $s1,$s1,s0
    Instruction_MEM[8] = 8'b00000000;
    Instruction_MEM[9] = 8'b00000000;
    Instruction_MEM[10] = 8'b00000000;
  end 
  
  assign Ins_output = Instruction_MEM[address]; //output of address
  
endmodule