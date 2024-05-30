`include "datapath.v"
`include "control_unit.v"

module microprocessor(clk);
    input clk;
    wire [31:0] instruction;
    wire Zero;
    wire PCSrc, MemWrite, ALUSrc, RegWrite;
    wire [1:0] ResultSrc, ImmSrc;
    wire [2:0] ALUControl;

    control_unit cu(
        .PCSrc(PCSrc),
        .ResultSrc(ResultSrc),
        .MemWrite(MemWrite),
        .ALUControl(ALUControl),
        .ALUSrc(ALUSrc),
        .ImmSrc(ImmSrc),
        .RegWrite(RegWrite),
        .op(instruction[6:0]),
        .funct3(instruction[14:12]),
        .funct7(instruction[30]),
        .Zero(Zero)
    );

    datapath dp(
        .clk(clk),
        .PCSrc(PCSrc),
        .MemWrite(MemWrite),
        .ALUSrc(ALUSrc),
        .RegWrite(RegWrite),
        .ALUControl(ALUControl),
        .ImmSrc(ImmSrc),
        .ResultSrc(ResultSrc),
        .Zero(Zero),
        .instructionOut(instruction)
    );

endmodule