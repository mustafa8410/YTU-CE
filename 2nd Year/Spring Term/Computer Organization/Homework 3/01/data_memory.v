module data_memory(address,write_enable,read_data,write_data,clk);
    input [31:0] address, write_data;
    input clk, write_enable;
    output  [31:0] read_data;
    reg[31:0] data[99:0];
    integer i;
    wire [31:0] arrayNumber;
    assign arrayNumber = address >> 2;

    initial begin
        //arr
        data[0] = 32'd3;
        data[1] = 32'd7;
        data[2] = 32'd2;
        data[3] = 32'd6;
        data[4] = 32'd5;
        data[5] = 32'd4;
        data[6] = 32'd1;
        data[7] = 32'd1000;
        data[8] = 32'd999;
        data[9] = 32'd25;
        data[10] = 32'd90;
        data[11] = 32'd100;
        data[12] = 32'd30;
        data[13] = 32'd20;
        data[14] = 32'd10;
        data[15] = 32'd200;
        data[16] = 32'd3300;
        data[17] = 32'd250;
        data[18] = 32'd12;
        data[19] = 32'd75;
        //count
        data[20] = 32'd17;
        data[21] = 32'd13;
        data[22] = 32'd18;
        data[23] = 32'd14;
        data[24] = 32'd15;
        data[25] = 32'd16;
        data[26] = 32'd19;
        data[27] = 32'd1;
        data[28] = 32'd2;
        data[29] = 32'd9;
        data[30] = 32'd6;
        data[31] = 32'd5;
        data[32] = 32'd8;
        data[33] = 32'd10;
        data[34] = 32'd12;
        data[35] = 32'd4;
        data[36] = 32'd0;
        data[37] = 32'd3;
        data[38] = 32'd11;
        data[39] = 32'd7;



        for(i=40; i<100; i= i + 1) begin
            data[i] = 32'h00000000;
        end
    end
    assign read_data = data[address >> 2];
    always @(posedge clk)begin
        if(write_enable) begin
            data[address >> 2] = write_data;
        end
    end
endmodule