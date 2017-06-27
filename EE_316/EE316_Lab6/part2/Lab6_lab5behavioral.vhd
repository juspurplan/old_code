
library ieee;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;


entity SM is
port(X, clk, rst : in STD_LOGIC;
	Z, Q1, Q2, Q3 : out STD_LOGIC);
end SM;

architecture behavioral of SM is
	signal dff1, dff2, dff3 : STD_LOGIC;
begin
	process(clk, rst)
	begin
		if(rst = '0') then
			dff1 <= '0';
			dff2 <= '0';
			dff3 <= '0';
		end if;
		
		if(clk'event and clk = '1') then
			dff1 <= (not X) or ((dff1) and (dff2) and (not dff3));
			dff2 <= X or dff1 or dff2;
			dff3 <= (X and (not dff2)) or ((not dff1) and dff2);
			
		end if;
	end process;
	
	Z <= (not X) and (not dff1) and (dff2) and (not dff3);
	Q1 <= dff1;
	Q2 <= dff2;
	Q3 <= dff3;
end architecture behavioral;

