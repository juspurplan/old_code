
library ieee;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity Lab6 is
port(
    lin, rin, shl, shr, clk,  reset : in STD_LOGIC; 
    lout, rout : out STD_LOGIC);
end Lab6;

--lin, rin : inputs to leftside or rightside of register
--shl == 1, shr == 0 : shift left
--shl == 0, shr == 1 : shift right
--shl == shr : do nothing, maintain
--reset : asynchronous clear, active low
--leftside [DFF0 <-> DFF1 <-> DFF2 <-> DFF3 <-> DFF4 <-> DFF5] rightside

architecture stuff of Lab6 is
    signal Q0, Q1, Q2, Q3, Q4, Q5 : STD_LOGIC;
begin
    process(clk, reset)
       variable shifting : Boolean;
    begin
       if (reset = '0') then
         Q0 <= '0';
         Q1 <= '0';
         Q2 <= '0';
         Q3 <= '0';
         Q4 <= '0';
         Q5 <= '0';
       end if;
    
       if (clk'event) and (clk = '1') then
         shifting := (shl /= shr);
         
          if (shifting) then
          if (shl = '0') then
              --right shift
              Q0 <= lin;
              Q1 <= Q0;
              Q2 <= Q1;
              Q3 <= Q2;
              Q4 <= Q3;
              Q5 <= Q4;
          else
              --left shift
              Q0 <= Q1;
              Q1 <= Q2;
              Q2 <= Q3;
              Q3 <= Q4;
              Q4 <= Q5;
              Q5 <= rin;
          end if;
         end if;
         
       end if;
         
    end process;

    lout <= Q0;
    rout <= Q5;

end architecture stuff;
