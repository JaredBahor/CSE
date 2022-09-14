`timescale 1ns / 1ps

module MUX(Regvalue ,SignExtend ,sel , out);
  input [7:0]Regvalue;
  input [7:0]SignExtend; //establishing x and y are representing the inputs to select from
  input sel; //establishing s represents the input that is the selector for the mux
  output reg [7:0]out; //establishing that the output of the mux will be connected to m
  
  //based on sel value, returns RegisterValue or SignExtend
  always @* begin
      case(sel)
        1'b1 : begin out = SignExtend; end
        1'b0 : begin out = Regvalue; end
      endcase
   end
    
  
  
  endmodule