`include "microprocessor.v"

module microprocessor_tb;
    reg clk;

    microprocessor uut(
        .clk(clk)
    );

    initial begin
        clk = 0;
        #580;
        $finish;
    end
    always #1 clk = ~clk;
    initial begin
        $dumpfile("microprocessor_tb.vcd");
        $dumpvars(0, microprocessor_tb);
        #0;
    end

endmodule


/*
iverilog -o microprocessor_tb.vvp microprocessor_tb.v
vvp microprocessor_tb.vvp
gtkwave
*/
