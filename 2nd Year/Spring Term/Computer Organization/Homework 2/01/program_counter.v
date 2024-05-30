module program_counter(pc,pcnext,clk);
    input [31:0] pcnext;
    input clk;
    output reg [31:0] pc;
    initial pc = 32'h00000000;

    always @(posedge clk) begin
        pc <= pcnext;
    end
endmodule