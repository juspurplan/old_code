module KeyToCommand(clk, PS2Clk, hex1, hex0, en_change, command);
    input clk, PS2Clk;
    input [3:0] hex1, hex0;
    output [3:0] command;
	input en_change;
    
//20 ms, then go back to 0

    reg [3:0] key;
    reg [20:0] count;
    reg [1:0] state;
	
	reg [3:0] command_out;
	
	assign command = command_out;

    /*
    0 - no input
    1 - start (s)       1B
    2 - end/stop (esc)  76
    3 - pause (p)       4D
    4 - resume (r)      2D
    5 - up              75
    6 - right           74
    7 - down            72
    8 - left            6B
    */
    
    always @(*)
    begin
        if({hex1, hex0} == 8'h 1B)
            key = 4'd 1;
        else if({hex1, hex0} == 8'h F6)
            key = 4'd 2;
        else if({hex1, hex0} == 8'h CD)
            key = 4'd 3;
        else if({hex1, hex0} == 8'h 2D)
            key = 4'd 4;
        else if({hex1, hex0} == 8'h F5)
            key = 4'd 5;
        else if({hex1, hex0} == 8'h F4)
            key = 4'd 6;
        else if({hex1, hex0} == 8'h F2)
            key = 4'd 7;
        else if({hex1, hex0} == 8'h EB)
            key = 4'd 8;
        else
            key = 4'd 0;
    end
    
    always @(posedge clk)
    begin
          case(state)
            2'd 0:
                begin
                    command_out <= 4'd 0;
                    count <= 21'd 0;
                    if(en_change == 1'b 1)
                        state <= 2'd 1;
                    else
                        state <= 2'd 0;
                end
            2'd 1:
                begin
                    command_out <= key;
                    count <= count + 21'd 1;
                    if(count == 21'd 2000000)
                        state <= 2'd 2;
                    else
                        state <= 2'd 1;
                end
            2'd 2:
                begin
                    command_out <= 4'd 0;
                    count <= 21'd 0;
                    if(PS2Clk == 1'b 0)
                        state <= 2'd 0;
                    else
                        state <= 2'd 2;
                end
            default:
                begin
                    command_out <= 4'd 0;
                    count <= 21'd 0;
                    state <= 2'd 0;
                end
          endcase
    end
endmodule
