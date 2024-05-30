module data_memory(address,write_enable,read_data,write_data,clk);
    input [31:0] address, write_data;
    input clk, write_enable;
    output  [31:0] read_data;
    reg[31:0] data[99:0];
    integer i;

    initial begin
        
        for(i=0; i<100; i= i + 1) begin
            data[i] = 32'h00000000;
        end
        data[1] = 32'd7;
    end
    assign read_data = data[address >> 2];
    always @(posedge clk)begin
        if(write_enable) begin
            data[address >> 2] = write_data;
        end
    end
endmodule