`include "datapath.v"

module sequence_tb;
    reg clk;
    reg rst;
    reg wr;
    reg [1:0] addr1, addr2, addr3;
    reg[2:0] aluControl;
    wire [31:0] data1,data2,data3;

    datapath uut(
        .clk(clk),
        .wr(wr),
        .rst(rst),
        .addr1(addr1[1:0]),
        .addr2(addr2[1:0]),
        .addr3(addr3[1:0]),
        .aluControl(aluControl[2:0]),
        .data1(data1[31:0]),
        .data2(data2[31:0]),
        .data3(data3[31:0])
    );

initial begin
    clk = 0;

    //R1 = 0

    aluControl = 3'b001; 
    addr1 = 2'b11; 
    addr2 = 2'b11; 
    addr3 = 2'b01; //r2 - r2 = 0, assign that to r1
    wr = 1'b1;
    rst = 1'b0;
    #10;

    //R0 = -1

    #10;

    aluControl = 3'b001;
    addr1 = 2'b01;
    addr2 = 2'b11;
    addr3 = 2'b00; //r1 - r2 = -1, assign that to r0
    wr = 1'b1;
    rst = 1'b0;
    #10;

    //R2 = R1 - 1

    aluControl = 3'b001;
    addr1 = 2'b01;
    addr2 = 2'b11;
    addr3 = 2'b10;  
    wr = 1'b1;
    rst = 1'b0;
    #10;

    //R3 = R0 + 1

    aluControl = 3'b000;
    addr1 = 2'b00;
    addr2 = 2'b11;
    addr3 = 2'b11;
    wr = 1'b1;
    rst = 1'b0;
    #10;
    $finish;
end

always #5 clk = ~clk;

initial begin
        $dumpfile("sequence_tb.vcd"); 
        $dumpvars(0, sequence_tb);
        #0;
end

endmodule

//iverilog -o sequence_tb.vvp sequence_tb.v
//vvp sequence_tb.vvp
//gtkwave

