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