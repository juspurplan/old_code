----------------Testbench for the state machine problems from chapter 16------------------
---------------- Owner: Imranul Islam,Last modified: 03/24/2006-------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity top is
    Port (A, B, C, D: in std_logic;
         st, rst, sysclk: in std_logic;
			clock_ext, x_ext, reset_ext:in std_logic;
         output: out std_logic_vector (1 to 7);
         ctr: out std_logic_vector (7 downto 0));
end top;

architecture Behavioral of top is
-- Student module must conform to the following 
-- port declaration ---------------------------
component SM is
    Port ( rst, clk, x: in std_logic;
           Q1,Q2,Q3,z: out std_logic);
end component;

signal dbSt: std_logic;
signal dumb: std_logic;
signal deb_Reg: integer range 0 to 50000000;

-- These signal are used for the main program
signal cur_state, next_state: std_logic_vector(3 downto 0):="0000";
signal done,sh, ld, half: std_logic;
signal index: Integer range 1 to 15;
signal zero: Integer range 0 to 15 := 1;
signal array_x: std_logic_vector(0 to 63); 
signal array_z: std_logic_vector(0 to 63); 
signal Counter: integer range 0 to 64;
signal reset_to: std_logic;
signal clock_to: std_logic;
signal LED5678: std_logic_vector(3 downto 0);

signal z: std_logic;
signal x: std_logic;
signal Qout: std_logic_vector(2 downto 0);
signal reset: std_logic;
signal clock: std_logic;
signal gate_x, gate_clock, gate_reset:std_logic;


-- x_array are the test sequences
type x_array is array (1 to 15) of std_logic_vector (0 to 63);
constant XArray: x_array := (
x"CB576DFF3356ADFF", x"34A892FFCCA952FF", x"C2A6D195D3C2A6E1", 
x"084C2A6E19084C2A", x"C86BFFFF5C27FFFF", x"AE9A93AA54AA90FF", 
x"9AC0F7FF4310F77F", x"EE53A3C51B9F53FF", x"6DCCF76F9E4FA6EF", 
x"2FD9E6A0E2E6FA00", x"8591E6A25E6A2C40", x"591E084C51E084C2", 
x"6CA85D5FF5835E0F", x"72DDF72FF5DF04CF", x"F0F8FCFE0103070F");

-- z_array are the test sequences solutions
type z_array is array (1 to 15) of std_logic_vector (0 to 63);
constant ZArray: z_array := (
x"01426D8011428580",x"01426D0011428500",x"F7B3E591E6F7B3D5",
x"4C2A6E195D4C2A6E",x"0C04000020140000",x"104000000A000000",
x"09D5F00000B5F0FF",x"00C2021410300200",x"B2733993CFB3D933",
x"D6517B3F7D7B63FF",x"A7B3D5917D591E62",x"084C591E04C591E6",
x"0028105001001000",x"0C96A5CA0695F88A",x"F0F8FCFE0103070F");

begin
    
	 
    index <= conv_integer (To_stdLogicVector(A&B&C&D));
    zero <= conv_integer (To_stdLogicVector(A&B&C&D));
    Done <='1' when Counter = 64 else '0';
    Half <='1' when Counter = 32 else '0';
    
    -- Signals sent to the student board
    x <= array_x(0) when gate_x = '0'
	 					  else 'Z';
    reset <= reset_to when gate_reset = '0'
	 					    else 'Z';
    clock <= clock_to when gate_clock = '0'
	 						 else 'Z';
    x <= x_ext when gate_x = '1'
	 				else 'Z';
    reset <= reset_ext when gate_reset = '1'
	 				else 'Z';
    clock <= clock_ext when gate_clock = '1'
	 				else 'Z';
	 ctr <= conv_std_logic_vector (Counter, 8) when (gate_x = '0'
	 														 or gate_reset = '0'
															 or gate_clock = '0')
	 														 else  ("0000" & z & Qout);

    SM0: SM port map (rst=>reset,
	 						 clk=>clock,
							 x=>x,
							 Q3=>Qout(2),
							 Q2=>Qout(1),
							 Q1=>Qout(0),
							 z=>z);

-- Clock divider to slow down the testbench clock --
-- Enables testbench activity observation ---------- 
process (sysclk)
    begin
       if sysclk'event and sysclk = '1' then
              dbSt <= '0';
              deb_Reg <= deb_Reg + 1;
          end if;
  
          if deb_Reg = 250000 then  
              dbSt <= '1';
              deb_Reg <= 0;
         end if;
end process;

-- This is the clk process
process (dbSt, rst)   
    begin
       if rst = '1' then
         cur_state <= "0000";
       elsif dbSt'event and dbSt = '1' then

         if Ld ='1' then
          array_x <= to_stdlogicvector(to_bitvector(XArray(index)));
          array_z <= to_stdlogicvector(to_bitvector(ZArray(index)));
          Counter <= 0;end if;

         if Sh ='1' then 
          array_x <= array_x (1 to 63)&'0'; 
          array_z <= array_z (1 to 63)&'0'; 
          Counter <= Counter + 1;end if;
    
         cur_state <= next_state;end if;
end process;

    -- States for the checker board
process (cur_state, st, Half, Done, z, rst, array_z)
    begin
       output <= "1111111";  sh <='0'; ld <='0'; reset_to <='1'; clock_to <='0';
       gate_x <= '1';
	    gate_reset <= '1';
	    gate_clock <= '1';
		 
		 case conv_integer(cur_state) is

       -- State 0 wait for start signal, once signal is received
       -- reset is sent to the student board, x_array is loaded with 
       -- sequence to test and x is output to the student board
       when 0 => 
         if st = '1' then
			 gate_x <= '0';
	       gate_reset <= '0';
	       gate_clock <= '0';
          if zero = 0 then next_state <= "0100";  -- Check if ABCD = "0000", then U
          else reset_to <= '0'; next_state <= "1010"; end if;
         else
         next_state <="0000";end if;
         LED5678 <="0000";clock_to <='0';
       
       -- Load x_array test sequence and z_array with solution sequence.
       when 10 =>
		   gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
         Ld <= '1'; next_state <= "0001"; LED5678 <="1010";

       -- State 1 checks for the output z from the student's board.
       -- If the z matches, then it advances to the next state.
       -- Otherwise it goes to state 4 to output U.
       when 1 =>
		    gate_x <= '0';
	       gate_reset <= '0';
	       gate_clock <= '0';
          if Half = '1' then next_state <="0110";
         else
          if z = array_z(0) then next_state <= "0010";
          else next_state <="0100";end if;end if;
         LED5678 <="0001";
       -- State 2 sends the clock high to the student board and
       -- then goes to the next state.
       when 2 =>
			gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
			clock_to <='1'; next_state <="0011";
         LED5678 <="0010";

       -- State 3 shifts x_array to send the next bit of the testing
       -- sequence. Clock for the student board is now low.
       -- Next state is back to 1.
       when 3 =>
         gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
			sh <='1'; 
         clock_to <= '0';
         next_state <= "0001";
         LED5678 <="0011";

       -- State 4 Outputs a U on the 7-Segment display
       when 4 => 
			gate_x <= '1';
	      gate_reset <= '1';
	      gate_clock <= '1';
			output(2) <='0';
         output(3) <='0';
         output(4) <='0';
         output(5) <='0';
         output(6) <='0';
         next_state <= "0100";--end if;
         LED5678 <="0100"; clock_to <='0';

       -- State 5 Outputs an S on the 7-Segment display
       when 5 =>
		   clock_to <='0'; 
         gate_x <= '1';
	      gate_reset <= '1';
	      gate_clock <= '1';
			output(1) <='0';
         output(3) <='0';
         output(4) <='0';
         output(6) <='0';
         output(7) <='0';
         next_state <= "0101";--end if;
         LED5678 <="0101";

       -- State 6 is reached after the first 32 bits of the 
       -- testing sequence is complete. In this state a reset 
       -- signal is sent to the student board.
       when 6 =>
         gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
			reset_to <='0';
         next_state <="0111"; 
         LED5678 <="0110";
         clock_to <='0';  
       -- State 7 checks for the output z from the student's board.
       -- If the z matches, then it advances to the next state.
       -- Otherwise it goes to state 4 to output U.
       when 7 =>
         gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
			if done = '1' then next_state <="0101";
         else
          if z = array_z(0) then next_state <= "1000";
          else next_state <="0100";end if;end if;
         LED5678 <="0111";

       -- State 8 sends the clock high to the student board and
       -- then goes to the next state.
       when 8 =>
		   gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
         clock_to <='1'; 
         next_state <="1001"; 
         LED5678 <="1000";
       -- State 9 shifts x_array to send the next bit of the testing
       -- sequence. Clock for the student board is now low.
       -- Next state is back to 7.
       when 9 => 
		   gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
         sh <='1'; clock_to <= '0'; 
         next_state <= "0111"; 
         LED5678 <="1001";
       when others =>
		   gate_x <= '0';
	      gate_reset <= '0';
	      gate_clock <= '0';
         null;
       end case;
end process;

end Behavioral;
