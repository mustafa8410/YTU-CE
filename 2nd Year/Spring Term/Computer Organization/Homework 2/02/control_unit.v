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

module main_decoder(op,Branch,Jump,ResultSrc,MemWrite,ALUSrc,ImmSrc,RegWrite,ALUOp);
    input [6:0] op;
    output reg Branch,Jump,MemWrite,ALUSrc,RegWrite;
    output reg [1:0] ResultSrc, ALUOp, ImmSrc;
    always @(*) begin
        case (op)
            7'b0000011: begin //lw
                RegWrite = 1'b1;
                ImmSrc = 2'b00;
                ALUSrc = 1'b1;
                MemWrite = 1'b0;
                ResultSrc = 2'b01;
                Branch = 1'b0;
                ALUOp = 2'b00;
                Jump = 1'b0;
            end
            7'b0100011: begin //sw
                RegWrite = 1'b0;
                ImmSrc = 2'b01;
                ALUSrc = 1'b1;
                MemWrite = 1'b1;
                ResultSrc = 2'bxx;
                Branch = 1'b0;
                ALUOp = 2'b00;
                Jump = 1'b0;
            end
            7'b0110011: begin //R-type
                RegWrite = 1'b1;
                ImmSrc = 2'bxx;
                ALUSrc = 1'b0;
                MemWrite = 1'b0;
                ResultSrc = 2'b00;
                Branch = 1'b0;
                ALUOp = 2'b10;
                Jump = 1'b0;
            end
            7'b1100011: begin //beq
                RegWrite = 1'b0;
                ImmSrc = 2'b10;
                ALUSrc = 1'b0;
                MemWrite = 1'b0;
                ResultSrc = 2'bxx;
                Branch = 1'b1;
                ALUOp = 2'b01;
                Jump = 1'b0;
            end
            7'b0010011: begin //I-type ALU
                RegWrite = 1'b1;
                ImmSrc = 2'b00;
                ALUSrc = 1'b1;
                MemWrite = 1'b0;
                ResultSrc = 2'b00;
                Branch = 1'b0;
                ALUOp = 2'b10;
                Jump = 1'b0;
            end
            7'b1101111: begin //jal
                RegWrite = 1'b1;
                ImmSrc = 2'b11;
                ALUSrc = 1'bx;
                MemWrite = 1'b0;
                ResultSrc = 2'b10;
                Branch = 1'b0;
                ALUOp = 2'bxx;
                Jump = 1'b1;
            end
            
        endcase
    end


endmodule
module control_unit(PCSrc,ResultSrc,MemWrite,ALUControl,ALUSrc,ImmSrc,RegWrite,op,funct3,funct7,Zero,shiftControl);
    input [6:0] op;
    input [2:0] funct3;
    input funct7, Zero;
    output PCSrc, MemWrite, ALUSrc, RegWrite;
    output [1:0] ResultSrc, ImmSrc;
    output [2:0] ALUControl;
    wire Branch, Jump;
    wire [1:0] ALUOp;
    output reg shiftControl;

    main_decoder md(
        .op(op[6:0]),
        .Branch(Branch),
        .Jump(Jump),
        .ResultSrc(ResultSrc[1:0]),
        .MemWrite(MemWrite),
        .ALUSrc(ALUSrc),
        .ImmSrc(ImmSrc[1:0]),
        .RegWrite(RegWrite),
        .ALUOp(ALUOp[1:0])
    );

    alu_decoder ad(
        .ALUControl(ALUControl[2:0]),
        .funct3(funct3[2:0]),
        .funct7(funct7),
        .ALUOp(ALUOp[1:0]),
        .op(op[6:0])
    );

    assign PCSrc = ( Zero & Branch ) | Jump;    

    always @(*) begin
        if(funct3 == 3'b101 && funct7 == 1 && op == 7'b0110011) begin
            shiftControl = 1;
        end else begin
            shiftControl = 0;
        end
    end

endmodule