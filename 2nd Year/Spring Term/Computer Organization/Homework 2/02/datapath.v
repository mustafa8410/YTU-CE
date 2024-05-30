`include "alu.v"
module data_memory(address,write_enable,read_data,write_data,clk);
    input [31:0] address, write_data;
    input clk, write_enable;
    output  [31:0] read_data;
    reg[31:0] data[99:0];
    integer i;

    initial begin
        
        for(i=0; i<100; i= i + 1) begin
            data[i] = 32'h00000000;
        end
        data[1] = 32'd7;
    end
    assign read_data = data[address >> 2];
    always @(posedge clk)begin
        if(write_enable) begin
            data[address >> 2] = write_data;
        end
    end
endmodule

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
        register[3] = 32'd3;
        register[4] = 32'd4;
        register[5] = 32'd5;
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

module instruction_memory(address,read_data);
    input[31:0] address;
    output reg [31:0] read_data;
    reg[31:0] instructions[20:0];
    initial begin
        //initial instructions to be inserted here
        instructions[0] = 32'b00000000000000000000000000110011; //add 0, 0, 0
        instructions[1] = 32'b00000000000000100010000100000011; //lw 2, 0(4)
        instructions[2] = 32'b00000000001101000010000000100011; //sw 3, 0(8)
        instructions[3] = 32'b00000000000000010000010010110011; //add  9, 2, 0
        instructions[4] = 32'b01000000001000010000000100110011; //sub  2, 2, 2
        instructions[5] = 32'b00000000000001001010010010110011; //slt  9, 9, 0
        instructions[6] = 32'b01000000010100100101000100110011;  //sra 2, 4, 5
        instructions[7] = 32'b00000000010100100110000110110011; //or  3,4,5
        instructions[8] = 32'b00000000010100100111001100110011; //and  6,4,5
        instructions[9] = 32'b00000000000100100000000100010011; //addi 2,4,1
        instructions[10] = 32'b00000000011000010010000100010011; //slti 2,2,6
        instructions[11] = 32'b00000000000000100110001010010011; //ori  5,4,0
        instructions[12] = 32'b00000000000000100111001000010011; //andi  4,4,0
        instructions[13] = 32'b00000000010000000000000011101111; //jal 1, 4 -> 100
        instructions[14] = 32'b00000000000000000000000001100011; //beq  0,0,0
    end
    always @(address) begin
        read_data <= instructions[address >> 2];
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