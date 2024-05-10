module adder_1bit (carryOut,sum,a,b,carryIn);
    input a,b,carryIn;
    output sum, carryOut;
    assign sum = a^b^carryIn;
    assign carryOut = a&b | b&carryIn | carryIn&a;
    
endmodule