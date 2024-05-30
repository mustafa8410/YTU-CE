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
        instructions[6] = 32'b00000000010100100110000110110011; //or  3,4,5
        instructions[7] = 32'b00000000010100100111001100110011; //and  6,4,5
        instructions[8] = 32'b00000000000100100000000100010011; //addi 2,4,1
        instructions[9] = 32'b00000000011000010010000100010011; //slti 2,2,6
        instructions[10] = 32'b00000000000000100110001010010011; //ori  5,4,0
        instructions[11] = 32'b00000000000000100111001000010011; //andi  4,4,0
        instructions[12] = 32'b00000000010000000000000011101111; //jal 1, 4 -> 100
        instructions[13] = 32'b00000000000000000000000001100011; //beq  0,0,0
    end
    always @(address) begin
        read_data <= instructions[address >> 2];
    end

endmodule