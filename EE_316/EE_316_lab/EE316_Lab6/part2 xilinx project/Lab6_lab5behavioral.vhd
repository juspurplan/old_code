
library ieee;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;


entity SM is
port(X, clk, rst : in STD_LOGIC;
	Z, Q1, Q2, Q3 : out STD_LOGIC);
end SM;

architecture behavioral of SM is
	signal state : integer range 0 to 7;
	signal outstate : STD_LOGIC_VECTOR(2 downto 0);
begin
	process(clk, rst)
	begin
		if(rst = '0') then
			state <= 0;
		
		--states
		--A = 0
		--B = 4
		--E = 3
		--H = 6
		--J = 7
		--M = 2
		
		elsif(rising_edge(clk)) then
			case state is
			when 0 =>
				if (X = '0') then
					state <= 4;
				else
					state <= 3;
				end if;
			when 1 =>
			when 2 =>
				if (X = '0') then
					state <= 7;
				else
					state <= 3;
				end if;
			when 3 =>
				if (X = '0') then
					state <= 7;
				else
					state <= 3;
				end if;
			when 4 =>
				if (X = '0') then
					state <= 6;
				else
					state <= 3;
				end if;
			when 5 =>
			when 6 =>
				state <= 6;
			when 7 =>
				if (X = '0') then
					state <= 6;
				else
					state <= 2;
				end if;
			end case;
			
		end if;
	end process;
	
	outstate <= conv_std_logic_vector(state,3);
	Z <= (not X) and (not outstate(0)) and (outstate(1)) and (not outstate(2));
	Q1 <= outstate(0);
	Q2 <= outstate(1);
	Q3 <= outstate(2);
	
	
end architecture behavioral;

