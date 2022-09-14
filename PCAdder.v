`timescale 1ns / 1ps

module PCAdder(address, instruct, Jump, PCconnect);
        
        input Jump;
        input [7:0]address;
        input [4:0]instruct;
        
        output reg [7:0]PCconnect;
        
    // if Jump == 0 we add 1 to go tot next Instruction address
    // if Jump == 1 we signEx the address imm value and then return it to PC.     
    always @* begin
          case(Jump)
            1'b1 : begin PCconnect = instruct; end // Jump is true 
            1'b0 : begin PCconnect = address + 1'b1 ; end // Jump is false
          endcase
       end


endmodule
