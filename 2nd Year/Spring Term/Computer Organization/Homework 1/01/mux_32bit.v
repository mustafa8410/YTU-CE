`include "mux_4bit.v"

module mux_2x1_32bit(a,b,select,out);
    input [31:0] a,b;
    input select;
    output [31:0] out;

    mux_2x1_4bit mux0(
        .a(a[3:0]),
        .b(b[3:0]),
        .select(select),
        .out(out[3:0])
    );
    mux_2x1_4bit mux1(
        .a(a[7:4]),
        .b(b[7:4]),
        .select(select),
        .out(out[7:4])
    );
    mux_2x1_4bit mux2(
        .a(a[11:8]),
        .b(b[11:8]),
        .select(select),
        .out(out[11:8])
    );
    mux_2x1_4bit mux3(
        .a(a[15:12]),
        .b(b[15:12]),
        .select(select),
        .out(out[15:12])
    );
    mux_2x1_4bit mux4(
        .a(a[19:16]),
        .b(b[19:16]),
        .select(select),
        .out(out[19:16])
    );
    mux_2x1_4bit mux5(
        .a(a[23:20]),
        .b(b[23:20]),
        .select(select),
        .out(out[23:20])
    );
    mux_2x1_4bit mux6(
        .a(a[27:24]),
        .b(b[27:24]),
        .select(select),
        .out(out[27:24])
    );
    mux_2x1_4bit mux7(
        .a(a[31:28]),
        .b(b[31:28]),
        .select(select),
        .out(out[31:28])
    );
endmodule

module mux_5x1_32bit(a,b,c,d,e,select,out);
    input [31:0] a,b,c,d,e;
    input [2:0] select;
    output [31:0] out;

    mux_5x1_4bit mux0(
        .a(a[3:0]),
        .b(b[3:0]),
        .c(c[3:0]),
        .d(d[3:0]),
        .e(e[3:0]),
        .select(select[2:0]),
        .out(out[3:0])
    );
    mux_5x1_4bit mux1(
        .a(a[7:4]),
        .b(b[7:4]),
        .c(c[7:4]),
        .d(d[7:4]),
        .e(e[7:4]),
        .select(select[2:0]),
        .out(out[7:4])
    );
    mux_5x1_4bit mux2(
        .a(a[11:8]),
        .b(b[11:8]),
        .c(c[11:8]),
        .d(d[11:8]),
        .e(e[11:8]),
        .select(select[2:0]),
        .out(out[11:8])
    );
    mux_5x1_4bit mux3(
        .a(a[15:12]),
        .b(b[15:12]),
        .c(c[15:12]),
        .d(d[15:12]),
        .e(e[15:12]),
        .select(select[2:0]),
        .out(out[15:12])
    );
    mux_5x1_4bit mux4(
        .a(a[19:16]),
        .b(b[19:16]),
        .c(c[19:16]),
        .d(d[19:16]),
        .e(e[19:16]),
        .select(select[2:0]),
        .out(out[19:16])
    );
    mux_5x1_4bit mux5(
        .a(a[23:20]),
        .b(b[23:20]),
        .c(c[23:20]),
        .d(d[23:20]),
        .e(e[23:20]),
        .select(select[2:0]),
        .out(out[23:20])
    );
    mux_5x1_4bit mux6(
        .a(a[27:24]),
        .b(b[27:24]),
        .c(c[27:24]),
        .d(d[27:24]),
        .e(e[27:24]),
        .select(select[2:0]),
        .out(out[27:24])
    );
    mux_5x1_4bit mux7(
        .a(a[31:28]),
        .b(b[31:28]),
        .c(c[31:28]),
        .d(d[31:28]),
        .e(e[31:28]),
        .select(select[2:0]),
        .out(out[31:28])
    );

endmodule