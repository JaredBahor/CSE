`timescale 1ns / 1ps

//It initialize the first address and then update to the new address when clock = 1. 
module PC(clock, addressIN, addressOUT);

  input clock;
  input [7:0] addressIN;
  output reg [7:0] addressOUT;
  
  reg reset;
  
  //starting address
    initial 
     begin
        reset = 1'b1;
        addressOUT = 8'b00000000; 
    end
   
  // update address value on pos edge 
  always @ (posedge clock) begin
   if(reset == 1'b1) begin
   addressOUT=8'b00000000;
   reset = 1'b0; end
   else begin
      
   addressOUT = addressIN;end
   end 
  
endmodule
