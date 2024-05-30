module alu_decoder(ALUControl,funct3,funct7,ALUOp, op);
    output reg[2:0] ALUControl;
    input[2:0] funct3;
    input funct7;
    input[6:0] op;
    input[1:0] ALUOp;
    wire op5;
    wire [1:0] opfunct7;
    assign op5 = op[5];
    assign opfunct7[1] = op5;
    assign opfunct7[0] = funct7;
    
    always @(*) begin
        
    
        case(ALUOp)
            2'b00: ALUControl = 3'b000;
            2'b01: ALUControl = 3'b001;
            2'b10: begin
                case(funct3)
                    3'b000: begin
                        case(opfunct7)
                            2'b00, 2'b01, 2'b10: ALUControl = 3'b000;
                            2'b11: ALUControl = 3'b001;
                        endcase
                    end
                    3'b010: ALUControl = 3'b101;
                    3'b110: ALUControl = 3'b011;
                    3'b111: ALUControl = 3'b010;
                endcase
            end

        endcase

    end

endmodule