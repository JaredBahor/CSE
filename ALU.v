`timescale 1ns / 1ps


module ALU(op, operand1, operand2, result);

  input op;
  input [7:0] operand1;
  input [7:0] operand2;
  
  output reg [7:0] result;
  
  // determining addition or subtration based off opcode
  always @* begin
      case(op)
        1'b1 : begin result = operand1 + operand2; end
        1'b0 : begin result = operand1 - operand2; end
      endcase
   end
   
endmodule