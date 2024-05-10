`include "alu.v"

module alu_tb;

    reg [31:0] a,b;
    reg [2:0] aluControl;
    wire [31:0] result;

    ALU uut(
        .a(a[31:0]),
        .b(b[31:0]),
        .aluControl(aluControl[2:0]),
        .result(result[31:0])
    );

    initial begin
        $dumpfile("alu_tb.vcd");
        $dumpvars(0, alu_tb);

        a = 0;
        b = 0;
        aluControl = 0;
        #10;

        //add
        a = 32'd4; //100
        b = 32'd3; //011
        aluControl = 3'b000; 
        #1;
        //subtract
        a = 32'd7; //100
        b = 32'd3; //011
        aluControl = 3'b001; 
        #1;
        //and
        a = 32'd4; //100
        b = 32'd3; //011
        aluControl = 3'b010; 
        #1;
        //xor
        a = 32'd4; //100
        b = 32'd3; //011
        aluControl = 3'b011;
        //slt
        a = 32'd4; //100
        b = 32'd3; //011
        aluControl = 3'b101;
        #1;
        //slt
        a = 32'd3;
        b = 32'd4;
        aluControl = 3'b101;
        #1;
        //add
        a = 32'd1;
        b = 32'd2;
        aluControl = 3'b000;
        #1;
        //subtract
        a = 32'd2;
        b = 32'd1;
        aluControl = 3'b001;
        #1;
        //and
        a = 32'd3;
        b = 32'd0;
        aluControl = 3'b010;
        #1;
        //xor
        aluControl = 3'b011;
        #1;
    end


endmodule

//iverilog -o alu_tb.vvp alu_tb.v
//vvp alu_tb.vvp
//gtkwave