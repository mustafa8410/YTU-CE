`include "adder_4bit.v"

module adder_32bit(carryOut,sum,a,b,carryIn);
input [31:0] a,b;
input carryIn;
output [31:0] sum;
output carryOut;
wire [6:0] internalCarry;

adder_4bit adder0(
    .carryOut(internalCarry[0]),
    .sum(sum[3:0]),
    .a(a[3:0]),
    .b(b[3:0]),
    .carryIn(carryIn)
);
adder_4bit adder1(
    .carryOut(internalCarry[1]),
    .sum(sum[7:4]),
    .a(a[7:4]),
    .b(b[7:4]),
    .carryIn(internalCarry[0])
);
adder_4bit adder2(
    .carryOut(internalCarry[2]),
    .sum(sum[11:8]),
    .a(a[11:8]),
    .b(b[11:8]),
    .carryIn(internalCarry[1])
);
adder_4bit adder3(
    .carryOut(internalCarry[3]),
    .sum(sum[15:12]),
    .a(a[15:12]),
    .b(b[15:12]),
    .carryIn(internalCarry[2])
);
adder_4bit adder4(
    .carryOut(internalCarry[4]),
    .sum(sum[19:16]),
    .a(a[19:16]),
    .b(b[19:16]),
    .carryIn(internalCarry[3])
);
adder_4bit adder5(
    .carryOut(internalCarry[5]),
    .sum(sum[23:20]),
    .a(a[23:20]),
    .b(b[23:20]),
    .carryIn(internalCarry[4])
);
adder_4bit adder6(
    .carryOut(internalCarry[6]),
    .sum(sum[27:24]),
    .a(a[27:24]),
    .b(b[27:24]),
    .carryIn(internalCarry[5])
);
adder_4bit adder7(
    .carryOut(carryOut),
    .sum(sum[31:28]),
    .a(a[31:28]),
    .b(b[31:28]),
    .carryIn(internalCarry[6])
);

endmodule