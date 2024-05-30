`include "alu.v"
`include "extend.v"
`include "program_counter.v"
`include "regfile.v"
`include "instruction_memory.v"
`include "data_memory.v"

module datapath(
    input clk, PCSrc, MemWrite, ALUSrc, RegWrite,
    input [2:0] ALUControl,
    input[1:0] ImmSrc, ResultSrc,
    output Zero,
    output [31:0] instructionOut);
    wire [31:0] PC, PCNext, PCPlus4, ImmExt, PCTarget, read_data1, read_data2,SrcB, ALUResult,ReadData,Result,instruction;


    instruction_memory im(
        .address(PC),
        .read_data(instruction)
    );
    assign instructionOut = instruction;
    
    //pc
    program_counter pcounter(
        .pc(PC),
        .pcnext(PCNext),
        .clk(clk)
    );
    assign PCPlus4 = PC + 4;
    extend ext(
        .ImmExt(ImmExt),
        .ImmSrc(ImmSrc),
        .Instr(instruction[31:7])
    );
    assign PCTarget = ImmExt + PC;
    mux_2 muxpc(
        .a(PCPlus4),
        .b(PCTarget),
        .select(PCSrc),
        .out(PCNext)
    );
    //pc end
    
    register_file regfile(
        .read_address1(instruction[19:15]),
        .read_address2(instruction[24:20]),
        .write_address(instruction[11:7]),
        .read_data1(read_data1),
        .read_data2(read_data2),
        .write_data(Result),
        .clk(clk),
        .wr(RegWrite)
    );
    mux_2 findSrcB(
        .a(read_data2),
        .b(ImmExt),
        .select(ALUSrc),
        .out(SrcB)
    );

    ALU alu(
        .a(read_data1),
        .b(SrcB),
        .aluControl(ALUControl),
        .result(ALUResult),
        .zeroFlag(Zero)
    );

    data_memory dm(
        .address(ALUResult),
        .write_enable(MemWrite),
        .read_data(ReadData),
        .write_data(read_data2),
        .clk(clk)
    );

    mux_3 getResult(
        .a(ALUResult),
        .b(ReadData),
        .c(PCPlus4),
        .select(ResultSrc),
        .out(Result)
    );



endmodule