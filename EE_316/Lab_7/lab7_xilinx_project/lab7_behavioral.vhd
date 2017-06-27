library IEEE;
use IEEE.STD_LOGIC_1164. ALL;
use IEEE.STD_LOGIC_UNSIGNED. ALL;
use IEEE.NUMERIC_STD.ALL;


entity lab7 is
	port(clock, start, reset : IN STD_LOGIC ;
		bus_in : IN STD_LOGIC_VECTOR(3 downto 0);
		done : OUT STD_LOGIC;
		overflow : OUT STD_LOGIC;
		product : OUT STD_LOGIC_VECTOR(7 downto 0));
end lab7;

architecture behavioral of lab7 is
	signal state, next_state : integer range 0 to 11;
	signal loadx, loady, loadz, mult, add, shift, addz : STD_LOGIC;
	signal x : STD_LOGIC_VECTOR( 7 downto 0);
	signal accumulator : STD_LOGIC_VECTOR(8 downto 0);
	signal z : STD_LOGIC_VECTOR( 3 downto 0);
	
	signal x_plus_accum, z_plus_accum : STD_LOGIC_VECTOR(8 downto 0);
	signal shr_accum : STD_LOGIC_VECTOR (8 downto 0);

begin
	process(state, start,  mult)
	begin
		loadx <= '0';
		loady <= '0';
		loadz <= '0';
		--mult <= '0';
		add <= '0';
		shift <= '0';
		addz <= '0';

		case state is
		--RESET
		when 0 =>
			if (start = '1') then
				loadx <= '1';
				next_state <= 1;
			else
				next_state <= 0;
			end if;

		--DONE LOADING X
		when 1 =>
			loady <= '1';
			next_state <= 2;

		--DONE LOADING Y
		when 2 =>
			loadz <='1';
			next_state <= 3;

		--Done Loading Z
		when 3 =>
			if (mult = '1') then
				add <= '1';
				next_state <= 4;
			else
				shift <= '1';
				next_state <= 5;
			end if;

		--After 1 Multiply
		when 4 =>
			shift <= '1';
			next_state <= 5;

		--After 1 shift
		when 5 =>
			if (mult = '1') then
				add <= '1';
				next_state <= 6;
			else
				shift <= '1';
				next_state <= 7;
			end if;

		--After 2 Multiplies
		when 6 =>
			shift <= '1';
			next_state <= 7;

		--After 2 Shifts
		when 7 =>
			if (mult = '1') then
				add <= '1';
				next_state <= 8;
			else
				shift <= '1';
				next_state <= 9;
			end if;

		--After 3 Multiplies
		when 8 =>
			shift <= '1';
			next_state <= 9;

		--After 3 Shifts, do 1 more final shift
		when 9 =>
			shift<= '1';
			next_state <=10;
		
		--After final shift, multiplier done  ::  now start adding z
		when 10 =>
			addz <= '1';
			next_state <= 11;
		
		--After Adding Z
		when 11 =>
			next_state <= 0;

		end case;

	end process;


--
	process(clock, reset)
	begin
		if(reset = '1') then
			x <= "00000000";
			accumulator <= "000000000";
			z <= "0000";
			done <='0';
			overflow <= '0';
			
			state <= 0;

		elsif(rising_edge(clock)) then
			state <= next_state;

			--load x, y, z
			if (loadx = '1') then
				x(7 downto 4) <= bus_in(3 downto 0);
				x(3 downto 0) <= "0000";
			elsif(loady = '1') then
				accumulator(2 downto 0) <= bus_in(2 downto 0);
				accumulator(8 downto 3) <= "000000";
			elsif(loadz = '1') then
				z <= bus_in;
			end if;

			--perform adding/shifting/adding Z
			if(add = '1') then
				accumulator <= x_plus_accum;

			elsif(shift = '1') then
				accumulator <= shr_accum;
			elsif(addz = '1') then
				accumulator <= z_plus_accum;
			end if;

			--if we're done
			if(next_state = 0) then
				done <= '1';
				overflow <= accumulator(8);
			else
				done <='0';
				overflow <= '0';
			end if;

		end if;

	end process;

--combinational logic for adding and shifting
x_plus_accum <= STD_LOGIC_VECTOR(unsigned(x) + unsigned(accumulator));
z_plus_accum <= STD_LOGIC_VECTOR(unsigned(z) + unsigned(accumulator));

shr_accum <= STD_LOGIC_VECTOR( shift_right(unsigned(accumulator), 1) );

--combinational for OUTPUT product
product <= accumulator(7 downto 0);

--combinational for mult
mult <= accumulator(0);

end behavioral;