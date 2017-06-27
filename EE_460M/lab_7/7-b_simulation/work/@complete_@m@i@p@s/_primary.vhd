library verilog;
use verilog.vl_types.all;
entity Complete_MIPS is
    generic(
        CLOCK_FREQUENCY : integer := 100000000
    );
    port(
        CLK             : in     vl_logic;
        RST             : in     vl_logic;
        HALT            : in     vl_logic;
        an              : out    vl_logic_vector(3 downto 0);
        segs            : out    vl_logic_vector(6 downto 0);
        SW              : in     vl_logic_vector(2 downto 0);
        BTN             : in     vl_logic_vector(1 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLOCK_FREQUENCY : constant is 1;
end Complete_MIPS;
