module adder_1bit (carryOut,sum,a,b,carryIn);
    input a,b,carryIn;
    output sum, carryOut;
    assign sum = a^b^carryIn;
    assign carryOut = a&b | b&carryIn | carryIn&a;
    
endmodule

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

module and_4bit(out,a,b);
    input [3:0] a,b;
    output [3:0] out;

    assign out[0] = a[0] & b[0];
    assign out[1] = a[1] & b[1];
    assign out[2] = a[2] & b[2];
    assign out[3] = a[3] & b[3];
endmodule

module and_32bit(out,a,b);
    input [31:0] a,b;
    output [31:0] out;

    and_4bit and0(
        .out(out[3:0]),
        .a(a[3:0]),
        .b(b[3:0])
    );
    and_4bit and1(
        .out(out[7:4]),
        .a(a[7:4]),
        .b(b[7:4])
    );
    and_4bit and2(
        .out(out[11:8]),
        .a(a[11:8]),
        .b(b[11:8])
    );
    and_4bit and3(
        .out(out[15:12]),
        .a(a[15:12]),
        .b(b[15:12])
    );
    and_4bit and4(
        .out(out[19:16]),
        .a(a[19:16]),
        .b(b[19:16])
    );
    and_4bit and5(
        .out(out[23:20]),
        .a(a[23:20]),
        .b(b[23:20])
    );
    and_4bit and6(
        .out(out[27:24]),
        .a(a[27:24]),
        .b(b[27:24])
    );
    and_4bit and7(
        .out(out[31:28]),
        .a(a[31:28]),
        .b(b[31:28])
    );
endmodule

module mux_2x1(a,b,select,out); //a if 0, b if 1
    input a,b,select;
    output out;
    wire selectNot, and1,and2;

    not(selectNot,select);
    and(and1,selectNot,a);
    and(and2,select,b);
    or(out,and1,and2);

endmodule

module mux_4x1(a,b,c,d,select,out); //
input a,b,c,d;
input[1:0] select;
output out;
wire [1:0] internalOutputs;

mux_2x1 mux1(
    .a(a),
    .b(b),
    .select(select[1]),
    .out(internalOutputs[0])
);

mux_2x1 mux2(
    .a(c),
    .b(d),
    .select(select[1]),
    .out(internalOutputs[1])
);

mux_2x1 mux3(
    .a(internalOutputs[0]),
    .b(internalOutputs[1]),
    .select(select[0]),
    .out(out)
);

endmodule

module mux_5x1_1bit(a,b,c,d,e,select,out);
    input a,b,c,d,e;
    input [2:0] select;
    output out;
    wire internalOutput;
    
    mux_4x1 mux1(
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .select(select[1:0]),
        .out(internalOutput)
    );

    mux_2x1 mux2(
        .a(internalOutput),
        .b(e),
        .select(select[2]),
        .out(out)
    );

endmodule

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

module xor_4bit(out,a,b);
    input [3:0] a,b;
    output [3:0] out;

    assign out[0] = a[0] ^ b[0];
    assign out[1] = a[1] ^ b[1];
    assign out[2] = a[2] ^ b[2];
    assign out[3] = a[3] ^ b[3];
endmodule

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

module zeroExtend_1bit(a,out);
    input a;
    output out;
    assign out = a;
endmodule

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

module not_4bit(out,in);
    input [3:0] in;
    output [3:0] out;

    assign out[0] = ~in[0];
    assign out[1] = ~in[1];
    assign out[2] = ~in[2];
    assign out[3] = ~in[3];
endmodule

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

module mux_2(a,b,select,out);
    input [31:0] a,b;
    input select;
    output [31:0] out;

    assign out = select ? b : a;
endmodule

module mux_3(a,b,c,select,out);
    input [31:0] a,b,c;
    input[1:0] select;
    output reg [31:0] out;
    
    always @(*) begin
        case (select)
            2'b00:  out = a;
            2'b01:  out = b;
            2'b10:  out = c;
        endcase

    end

endmodule

module mux_4(a,b,c,d,select,out);
    input [31:0] a,b,c,d;
    input[1:0] select;
    output reg [31:0] out;
    
    always @(*) begin
        case (select)
            2'b00:  out = a;
            2'b01:  out = b;
            2'b10:  out = c;
            2'b11:  out = d;
        endcase

    end

endmodule

module arithmetic_right_shifter(a,b,out);
    input [31:0] a,b;
    output [31:0] out;

    assign out = a >>> b;
endmodule