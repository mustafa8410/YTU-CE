`include "mux_1bit.v"

module mux_2x1_4bit(a,b,select,out);
    input [3:0] a,b;
    input select;
    output [3:0] out;

    mux_2x1 mux0(
        .a(a[0]),
        .b(b[0]),
        .select(select),
        .out(out[0])
    );
    mux_2x1 mux1(
        .a(a[1]),
        .b(b[1]),
        .select(select),
        .out(out[1])
    );
    mux_2x1 mux2(
        .a(a[2]),
        .b(b[2]),
        .select(select),
        .out(out[2])
    );
    mux_2x1 mux3(
        .a(a[3]),
        .b(b[3]),
        .select(select),
        .out(out[3])
    );

endmodule

module mux_5x1_4bit(a,b,c,d,e,select,out);
    input [3:0] a,b,c,d,e;
    input [2:0] select;
    output [3:0] out;

    mux_5x1_1bit mux0(
        .a(a[0]),
        .b(b[0]),
        .c(c[0]),
        .d(d[0]),
        .e(e[0]),
        .select(select[2:0]),
        .out(out[0])
    );
    mux_5x1_1bit mux1(
        .a(a[1]),
        .b(b[1]),
        .c(c[1]),
        .d(d[1]),
        .e(e[1]),
        .select(select[2:0]),
        .out(out[1])
    );
    mux_5x1_1bit mux2(
        .a(a[2]),
        .b(b[2]),
        .c(c[2]),
        .d(d[2]),
        .e(e[2]),
        .select(select[2:0]),
        .out(out[2])
    );
    mux_5x1_1bit mux3(
        .a(a[3]),
        .b(b[3]),
        .c(c[3]),
        .d(d[3]),
        .e(e[3]),
        .select(select[2:0]),
        .out(out[3])
    );

endmodule