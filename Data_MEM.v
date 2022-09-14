`timescale 1ns / 1ps

module Data_MEM(op, address, write_data, data_out);
 
  input op; // 1 read, 0 write
  input [7:0] address; // Indicates the address at which to access/update
  input [7:0] write_data; // Represent the value that needs to be stored at address in the DataMEM
 
  output reg [7:0]data_out; // Represents the value accessed from Data_MEM
 
  reg [7:0]Data_MEM[255:0]; //Max limit of memory locations
   
  
  initial
  begin   
    
	Data_MEM[0] = 8'b00000000;
	Data_MEM[1] = 8'b00000000; // 0 as of now will get updated to 5 after sw, in the following instruction s1 will access this value
	Data_MEM[2] = 8'b00000000;
	Data_MEM[3] = 8'b00000000;
	Data_MEM[4] = 8'b00000000;
	Data_MEM[5] = 8'b00000000;
	Data_MEM[6] = 8'b00000000;
	Data_MEM[7] = 8'b00000000;
	Data_MEM[8] = 8'b00000000;
	Data_MEM[9] = 8'b00000000;
	Data_MEM[10] = 8'b00000000;
	
	Data_MEM[18] = 8'b00000011;
    
  end
 
    // based on opcode we either read data from DataMEM or we write data to DataMEM.
  always @* begin
  	case(op)
    	1'b1 : begin  data_out = Data_MEM[address]; end
    	1'b0 : begin  Data_MEM[address] = write_data; end
  	endcase
   end

 
endmodule
