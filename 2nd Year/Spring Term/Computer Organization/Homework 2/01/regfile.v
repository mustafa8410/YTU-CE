module register_file(read_address1, read_address2, write_address, read_data1, read_data2, write_data, clk, wr);
    input clk, wr;
    input [4:0] read_address1, read_address2, write_address;
    input [31:0] write_data;
    output [31:0] read_data1, read_data2;
    reg [31:0] register[31:0];
    integer i;

    initial begin
        
        for( i=0; i<32; i = i +1) begin
                register[i] = 32'h00000000;
            end
        register[3] = 32'd3;
        register[4] = 32'd4;
        register[5] = 32'd5;
    end
    
    assign read_data1 = register[read_address1];
    assign read_data2 = register[read_address2];
   
    always @(posedge clk) begin
        if(wr) begin
            register[write_address] = write_data;
        end
    end
endmodule