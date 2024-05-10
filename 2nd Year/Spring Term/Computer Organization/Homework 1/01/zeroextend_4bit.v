`include "zeroextend_1bit.v"

module zeroExtend_4bit(a,out);
    input a;
    output [3:0] out;
    zeroExtend_1bit extend0(
        .a(a),
        .out(out[0])
    );
    zeroExtend_1bit extend1(
        .a(1'b0),
        .out(out[1])
    );
    zeroExtend_1bit extend2(
        .a(1'b0),
        .out(out[2])
    );
    zeroExtend_1bit extend3(
        .a(1'b0),
        .out(out[3])
    );
endmodule