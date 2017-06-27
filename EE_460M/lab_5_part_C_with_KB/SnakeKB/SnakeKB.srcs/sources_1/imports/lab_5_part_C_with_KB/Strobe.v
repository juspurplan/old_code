module Strobe(clk, PS2Clk, en_check, en_change, strobe);
    input clk, PS2Clk, en_check, en_change;
    output strobe;
    
    reg [0:23] count;
    reg [0:1] state;
    reg strobe;
    
    initial begin
        strobe = 1'b 0;
        count = 24'd 0;
        state = 2'd 0;
    end
    
    always @(posedge clk)
    begin
        case(state)
            2'd 0:
                begin
                    strobe <= 1'b 0;
                    count <= 24'd 0;
                    if(en_change)
                        state <= 2'd 1;
                    else
                        state <= 2'd 0;
                end
            2'd 1:
                begin
                    strobe <= 1'b 1;
                    count <= count + 24'd 1;
                    if(count == 24'd 10000000)
                        state <= 2'd 2;
                    else
                        state <= 2'd 1;
                end
            2'd 2:
                begin
                    strobe <= 1'b 0;
                    count <= 24'd 0;
                    if(PS2Clk == 1'b 0)
                        state <= 2'd 0;
                    else
                        state <= 2'd 2;
                end
            default:
                begin
                    strobe = 1'b 0;
                    count = 24'd 0;
                    state = 2'd 0;
                end
        endcase
    end
    
    //assign count = next_count;
    
    //assign state = next_state;
 endmodule
    
 /*    always @(posedge clock) begin
               case(s)
               2'd 0: s <= 2'd 1;
               2'd 1: s <= 2'd 2;
               2'd 2: s <= 2'd 3;
               2'd 3: s <= 2'd 0;
               endcase
           end
    always @(negedge clk)
    begin
        if(count == 24'd 10000000)
          begin
            strobe = 1'b 0;
            count = 24'd 0;
          end
        else if((en_check && en_change) || (count != 24'd 0))
          begin
            strobe = 1'b 1;
            count = count + 1;
          end
        else
          begin
            strobe = 1'b 0;
            count = 24'd 0;
          end
    end
    
    initial begin
            s <= 0;
        end
        
       
        
        assign current_state = s;
    */