module instruction_memory(address,read_data);
    input[31:0] address;
    output reg [31:0] read_data;
    reg[31:0] instructions[40:0];
    initial begin
        //initial instructions to be inserted here
        instructions[0] = 32'b00000000000000000000000000110011; //add 0, 0, 0 
        instructions[1] = 32'h00000913; 
        instructions[2] = 32'h05000993; 
        instructions[3] = 32'h0a000a13; 
        instructions[4] = 32'h05000393; 
        instructions[5] = 32'h02790863; 
        instructions[6] = 32'h00092283; 
        instructions[7] = 32'h0009a303; 
        instructions[8] = 32'h00630e33; 
        instructions[9] = 32'h006e0e33; 
        instructions[10] = 32'h01c30333; 
        instructions[11] = 32'h006a0eb3; 
        instructions[12] = 32'h005ea023; 
        instructions[13] = 32'h00490913; 
        instructions[14] = 32'h00498993; 
        instructions[15] = 32'hfc000ce3; 
        instructions[16] = 32'h050a0313;
        instructions[17] = 32'h006a0663;
        instructions[18] = 32'h000a2283;
        instructions[19] = 32'h004a0a13;
        instructions[20] = 32'hfe000ce3; 
        
    end
    always @(address) begin
        read_data <= instructions[address >> 2];
    end

endmodule