`timescale 1ns / 1ps

module Control_Unit(op, RegWrite, ALUSrc, MEM, RegOrSign, ALUorMEM, Jump);
    input [2:0]op;
    output reg [2:0]RegWrite; // gives OP code to RegMod to perform operations
    output reg ALUSrc; // determines adding or subtracting for the ALU
    output reg MEM; // signifies read or write for DataMEM 
    output reg RegOrSign; // either take signextend from instruction or Register value from register file 
    output reg ALUorMEM; // determines writeback value between ALU output or DataMEM output
    output reg Jump; // determines if we jump to an address or +1 to next instuction
    
    
    always @* begin
    case(op)
        3'b100: begin 
        //add op = 100 
        
        RegWrite = 3'b001;
        ALUSrc = 1'b1; //1 == add
        RegOrSign = 1'b0;
        ALUorMEM = 1'b0;
        Jump = 1'b0;
        
    end
    
        3'b101: begin 
        //addi
        RegWrite = 3'b100;
        ALUSrc = 1'b1;
        RegOrSign = 1'b1;
        ALUorMEM = 1'b0;
        Jump = 1'b0;
        
    end
    
        3'b110: begin 
        //sub
        RegWrite = 3'b010;
        ALUSrc = 1'b0; 
        RegOrSign = 1'b0;
        ALUorMEM = 1'b0;
        Jump = 1'b0;

      
    end
    
        3'b001: begin 
        //lw
        RegWrite = 3'b011;
        ALUSrc = 1'b1;
        MEM = 1'b1;
        RegOrSign = 1'b1;
        ALUorMEM = 1'b1;
        Jump = 1'b0;

        
        //MEM 1 = read
        //MEM 0 = write
    end

        3'b010: begin 
        //sw
        RegWrite = 3'b000;
        ALUSrc = 1'b1;
        MEM = 1'b0;
        RegOrSign = 1'b1;
        ALUorMEM = 1'b0;
        Jump = 1'b0;
        
        //MEM 1 = read
        //MEM 0 = write
        
    end
    
        3'b011: begin 
        //jump
        RegWrite = 3'b000;
        ALUSrc = 1'b0;
        RegOrSign = 1'b1;
        ALUorMEM = 1'b0;
        Jump = 1'b1;

        
    end    
    
    endcase
end

endmodule