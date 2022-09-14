`timescale 1ns / 1ps

module Sign_Extend(in, out);

  input signed [2:0] in;
  output signed [7:0] out;
  
  // extending to 8 bits
  assign out = in;
    
endmodule
