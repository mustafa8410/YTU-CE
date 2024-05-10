module not_4bit(out,in);
    input [3:0] in;
    output [3:0] out;

    assign out[0] = ~in[0];
    assign out[1] = ~in[1];
    assign out[2] = ~in[2];
    assign out[3] = ~in[3];
endmodule