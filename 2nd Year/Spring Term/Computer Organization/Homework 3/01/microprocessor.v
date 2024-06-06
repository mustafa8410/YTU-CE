`include "alu.v"
`include "instruction_memory.v"
`include "data_memory.v"

module register_file(read_address1, read_address2, write_address, read_data1, read_data2, write_data, clk, wr);
    input clk, wr;
    input [4:0] read_address1, read_address2, write_address;
    input [31:0] write_data;
    output [31:0] read_data1, read_data2;
    reg [31:0] register[31:0];
    integer i;

    initial begin
        
        for( i=0; i<32; i = i +1) begin
                register[i] = 32'h00000000;
            end
    end
    
    assign read_data1 = register[read_address1];
    assign read_data2 = register[read_address2];
   
    always @(posedge clk) begin
        if(wr) begin
            register[write_address] = write_data;
        end
    end
endmodule

module program_counter(pc,pcnext,clk);
    input [31:0] pcnext;
    input clk;
    output reg [31:0] pc;
    initial pc = 32'h00000000;

    always @(posedge clk) begin
        pc <= pcnext;
    end
endmodule



module extend(ImmExt,ImmSrc,Instr);
    input [31:7] Instr;
    input [1:0] ImmSrc;
    output reg[31:0] ImmExt;

    always @(*) begin
        case(ImmSrc)
        2'b00: ImmExt = {{20{Instr[31]}}, Instr[31:20]};
        2'b01: ImmExt = {{20{Instr[31]}}, Instr[31:25], Instr[11:7]};
        2'b10: ImmExt = {{20{Instr[31]}}, Instr[7], Instr[30:25], Instr[11:8], 1'b0};
        2'b11: ImmExt = {{12{Instr[31]}}, Instr[19:12], Instr[20], Instr[30:21], 1'b0};

        endcase
end

endmodule

module datapath(
    input clk, PCSrc, MemWrite, ALUSrc, RegWrite,shiftControl,
    input [2:0] ALUControl,
    input[1:0] ImmSrc, ResultSrc,
    output Zero,
    output [31:0] instructionOut);
    wire [31:0] PC, PCNext, PCPlus4, ImmExt, PCTarget, read_data1, read_data2,SrcB, ALUResult,ReadData,Result,instruction, shiftResult,AluMuxResult;


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
    arithmetic_right_shifter sra(
        .a(read_data1),
        .b(read_data2),
        .out(shiftResult)
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

    mux_2 alushift(
        .a(ALUResult),
        .b(shiftResult),
        .select(shiftControl),
        .out(AluMuxResult)
    );

    data_memory dm(
        .address(AluMuxResult),
        .write_enable(MemWrite),
        .read_data(ReadData),
        .write_data(read_data2),
        .clk(clk)
    );

    mux_3 getResult(
        .a(AluMuxResult),
        .b(ReadData),
        .c(PCPlus4),
        .select(ResultSrc),
        .out(Result)
    );



endmodule

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

module microprocessor(clk);
    input clk;
    wire [31:0] instruction;
    wire Zero;
    wire PCSrc, MemWrite, ALUSrc, RegWrite,shiftControl;
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
        .Zero(Zero),
        .shiftControl(shiftControl)
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
        .instructionOut(instruction),
        .shiftControl(shiftControl)
    );

endmodule