`include "not_4bit.v"

module not_32bit(out,in);
    input [31:0] in;
    output [31:0] out;

    not_4bit not0(
        .out(out[3:0]),
        .in(in[3:0])
    );
    not_4bit not1(
        .out(out[7:4]),
        .in(in[7:4])
    );
    not_4bit not2(
        .out(out[11:8]),
        .in(in[11:8])
    );
    not_4bit not3(
        .out(out[15:12]),
        .in(in[15:12])
    );
    not_4bit not4(
        .out(out[19:16]),
        .in(in[19:16])
    );
    not_4bit not5(
        .out(out[23:20]),
        .in(in[23:20])
    );
    not_4bit not6(
        .out(out[27:24]),
        .in(in[27:24])
    );
    not_4bit not7(
        .out(out[31:28]),
        .in(in[31:28])
    );
endmodule