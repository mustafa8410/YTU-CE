`include "all_components_combined.v"

module ALU(a,b,aluControl,result,zeroFlag);
    input [31:0] a,b;
    input [2:0] aluControl;
    output [31:0] result;
    output zeroFlag;
    wire [31:0] bNot, b_adderControlOutput,adderResult, and_1_result, xor_1_result, zeroextend_result, or_result;
    wire carryOut, overflow_xnor,overflow_xnor_partial, overflow_xor,overflow_alu_not,overflow,overflow_sum_xor;

    not_32bit not0(
        .out(bNot[31:0]),
        .in(b[31:0])
    );
    mux_2x1_32bit mux_adderControl(
        .a(b[31:0]),
        .b(bNot[31:0]),
        .select(aluControl[0]),
        .out(b_adderControlOutput[31:0])
    );
    adder_32bit adder(
        .carryOut(carryOut),
        .sum(adderResult[31:0]),
        .a(a[31:0]),
        .b(b_adderControlOutput[31:0]),
        .carryIn(aluControl[0])
    );
    and_32bit and1(
        .out(and_1_result[31:0]),
        .a(a[31:0]),
        .b(b[31:0])
    );
    assign or_result = a | b;
    assign overflow_xnor_partial = a[31] ^ b[31] ^ aluControl[0];
    assign overflow_xnor = ~overflow_xnor_partial;
    assign overflow_xor = a[31] ^ adderResult[31];
    assign overflow_alu_not = ~aluControl[1];
    assign overflow = overflow_xnor & overflow_xor & overflow_alu_not;
    assign overflow_sum_xor = overflow ^ adderResult[31];
    
    zeroExtend_32bit extend(
        .a(overflow_sum_xor),
        .out(zeroextend_result[31:0])
    );

    mux_5x1_32bit muxEnd(
        .a(adderResult[31:0]),
        .b(and_1_result[31:0]),
        .c(adderResult[31:0]),
        .d(or_result[31:0]),
        .e(zeroextend_result[31:0]),
        .select(aluControl[2:0]),
        .out(result[31:0])
    );

    assign zeroFlag = (result == 32'b0);

endmodule