library verilog;
use verilog.vl_types.all;
entity Complete_MIPS is
    port(
        CLK             : in     vl_logic;
        RST             : in     vl_logic;
        HALT            : in     vl_logic;
        leds            : out    vl_logic_vector(7 downto 0);
        light           : out    vl_logic
    );
end Complete_MIPS;
