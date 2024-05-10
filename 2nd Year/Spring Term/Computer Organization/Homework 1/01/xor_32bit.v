`include "xor_4bit.v"

module xor_32bit(out,a,b);
    input [31:0] a,b;
    output [31:0] out;

    xor_4bit xor0(
        .out(out[3:0]),
        .a(a[3:0]),
        .b(b[3:0])
    );
    xor_4bit xor1(
        .out(out[7:4]),
        .a(a[7:4]),
        .b(b[7:4])
    );
    xor_4bit xor2(
        .out(out[11:8]),
        .a(a[11:8]),
        .b(b[11:8])
    );
    xor_4bit xor3(
        .out(out[15:12]),
        .a(a[15:12]),
        .b(b[15:12])
    );
    xor_4bit xor4(
        .out(out[19:16]),
        .a(a[19:16]),
        .b(b[19:16])
    );
    xor_4bit xor5(
        .out(out[23:20]),
        .a(a[23:20]),
        .b(b[23:20])
    );
    xor_4bit xor6(
        .out(out[27:24]),
        .a(a[27:24]),
        .b(b[27:24])
    );
    xor_4bit xor7(
        .out(out[31:28]),
        .a(a[31:28]),
        .b(b[31:28])
    );
endmodule