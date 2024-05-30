`include "alu_decoder.v"
`include "main_decoder.v"

module control_unit(PCSrc,ResultSrc,MemWrite,ALUControl,ALUSrc,ImmSrc,RegWrite,op,funct3,funct7,Zero);
    input [6:0] op;
    input [2:0] funct3;
    input funct7, Zero;
    output PCSrc, MemWrite, ALUSrc, RegWrite;
    output [1:0] ResultSrc, ImmSrc;
    output [2:0] ALUControl;
    wire Branch, Jump;
    wire [1:0] ALUOp;

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

endmodule