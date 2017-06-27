library verilog;
use verilog.vl_types.all;
entity ALU is
    port(
        A               : in     vl_logic_vector(3 downto 0);
        B               : in     vl_logic_vector(3 downto 0);
        cb_in           : in     vl_logic;
        control         : in     vl_logic_vector(2 downto 0);
        \out\           : out    vl_logic_vector(3 downto 0);
        cb_out          : out    vl_logic
    );
end ALU;
