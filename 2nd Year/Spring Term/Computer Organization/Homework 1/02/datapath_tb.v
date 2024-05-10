`include "datapath.v"

module datapath_tb;
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

        //R0 = R1 + R2
        aluControl = 3'b000; 
        addr1 = 2'b01; 
        addr2 = 2'b10; 
        addr3 = 2'b00; 
        wr = 1'b1;
        rst = 1'b0;
        #10;

        //R1 = R2 & R3

        aluControl = 3'b010; 
        addr1 = 2'b10; 
        addr2 = 2'b11; 
        addr3 = 2'b01; 
        wr = 1'b1;
        #10;

        // R3 = R2 XOR R0

        aluControl = 3'b011; 
        addr1 = 2'b10; 
        addr2 = 2'b00; 
        addr3 = 2'b11;
        wr = 1'b1;
        #10;

         //R2 = R1 - R3
        aluControl = 3'b001; // Subtract operation
        addr1 = 2'b01; // R1
        addr2 = 2'b11; // R3
        addr3 = 2'b10; // R2
        wr = 1'b1;
        #10;

        $finish;


    end

    always #5 clk = ~clk;

    initial begin
        $dumpfile("datapath_tb.vcd"); 
        $dumpvars(0, datapath_tb);
        #0;
    end


endmodule

//iverilog -o datapath_tb.vvp datapath_tb.v
//vvp datapath_tb.vvp
//gtkwave