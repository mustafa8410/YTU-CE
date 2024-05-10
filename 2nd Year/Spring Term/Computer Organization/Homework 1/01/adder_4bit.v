`include "adder_1bit.v"

module adder_4bit(carryOut,sum,a,b,carryIn);
    input [3:0] a,b;
    input carryIn;
    output [3:0] sum;
    output carryOut;
    wire [2:0] internalCarry;

    adder_1bit adder0(internalCarry[0],sum[0],a[0],b[0],carryIn);
    adder_1bit adder1(internalCarry[1],sum[1],a[1],b[1],internalCarry[0]);
    adder_1bit adder2(internalCarry[2],sum[2],a[2],b[2],internalCarry[1]);
    adder_1bit adder3(carryOut,sum[3],a[3],b[3],internalCarry[2]);
endmodule