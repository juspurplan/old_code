library verilog;
use verilog.vl_types.all;
entity SevenSegmentDisplayController is
    generic(
        CLOCK_FREQUENCY : integer := 100000000;
        REFRESH_RATE    : integer := 80;
        DIVIDE_FREQUENCY: vl_notype
    );
    port(
        bcd3            : in     vl_logic_vector(3 downto 0);
        bcd2            : in     vl_logic_vector(3 downto 0);
        bcd1            : in     vl_logic_vector(3 downto 0);
        bcd0            : in     vl_logic_vector(3 downto 0);
        clock           : in     vl_logic;
        commons         : out    vl_logic_vector(3 downto 0);
        segments        : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLOCK_FREQUENCY : constant is 1;
    attribute mti_svvh_generic_type of REFRESH_RATE : constant is 1;
    attribute mti_svvh_generic_type of DIVIDE_FREQUENCY : constant is 3;
end SevenSegmentDisplayController;
