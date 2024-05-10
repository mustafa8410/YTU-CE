
`include "zeroextend_4bit.v"

module zeroExtend_32bit(a,out);
    input a;
    output [31:0] out;
    zeroExtend_4bit extend0(
        .a(a),
        .out(out[3:0])
    );
    zeroExtend_4bit extend1(
        .a(1'b0),
        .out(out[7:4])
    );
    zeroExtend_4bit extend2(
        .a(1'b0),
        .out(out[11:8])
    );
    zeroExtend_4bit extend3(
        .a(1'b0),
        .out(out[15:12])
    );
    zeroExtend_4bit extend4(
        .a(1'b0),
        .out(out[19:16])
    );
    zeroExtend_4bit extend5(
        .a(1'b0),
        .out(out[23:20])
    );
    zeroExtend_4bit extend6(
        .a(1'b0),
        .out(out[27:24])
    );
    zeroExtend_4bit extend7(
        .a(1'b0),
        .out(out[31:28])
    );
endmodule