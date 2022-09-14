`timescale 1ns / 1ps

module RegMod(
  input rs_in, // rs register
  input rd_in, // rd/rt resigter
  input [7:0] data_in, // value for write back form alu or data mem
  input [2:0]opcode,  // singnal for opperation
  output [7:0] rs_out, // value of rs resigter
  output [7:0] rd_out // value of rd/rt resiter 
	);
  
  
    reg [7:0]rd_out;
    reg [7:0]rs_out;
  	reg [7:0] reg0;
    reg [7:0] reg1;

    initial begin
        reg0 = 8'b00000110; // setting r0 to 6, default value
        reg1 = 8'b00010010; // setting r1 to 18, default value
    end
  	
        always @ (rs_in, rd_in, opcode) begin
              if (opcode == 3'b001 | 3'b010 | 3'b100) begin //add & sub & addi
              
              // picking the correct register values for rs out
                case (rs_in)
                     1'b0 : rs_out  = reg0;
                     1'b1 : rs_out = reg1;
                     endcase 
                case (rd_in)
                    1'b0 : rd_out  = reg0;
                    1'b1 : rd_out = reg1;
                     endcase 
              end
              
              if (opcode == 3'b011)begin //LW
                case (rs_in)
                    1'b0 : rs_out  = reg0;
                    1'b1 : rs_out = reg1;
                endcase
              end 
              
              if (opcode == 3'b010)begin// SW //dont use reg for jump only use the opcode & imm value
                case (rs_in)
                     1'b0 : rs_out  = reg0;
                     1'b1 : rs_out = reg1;
                     endcase 
                case (rd_in)
                    1'b0 : rd_out  = reg0;
                    1'b1 : rd_out = reg1;
                     endcase 
              end
              
            end
          
          
          // when data in is received, update the resigter value  
          always @(data_in) begin
                case(rd_in)
                   1'b0 : reg0 = data_in;
                   1'b1 : reg1 = data_in;
                endcase
                        end
            
  
endmodule