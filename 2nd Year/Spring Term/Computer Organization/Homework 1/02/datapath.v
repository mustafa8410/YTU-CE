`include "alu.v"
`include "regfile.v"

module datapath(clk, wr, rst, addr1, addr2, addr3, aluControl, data1, data2, data3);
input clk, wr, rst;
input [1:0] addr1, addr2, addr3;
input [2:0] aluControl;
output wire[31:0] data1, data2, data3;
wire [31:0] aluResult;

ALU alu_inst(
    .a(data1[31:0]),
    .b(data2[31:0]),
    .aluControl(aluControl[2:0]),
    .result(aluResult[31:0])
);

regfile reg_inst(
    .addr1(addr1[1:0]),
    .addr2(addr2[1:0]),
    .addr3(addr3[1:0]),
    .data1(data1[31:0]),
    .data2(data2[31:0]),
    .data3(aluResult[31:0]),
    .clk(clk),
    .wr(wr),
    .rst(rst)
);

assign data3 = aluResult;






endmodule