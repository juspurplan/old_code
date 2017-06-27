library verilog;
use verilog.vl_types.all;
entity SevenSegTop is
    generic(
        CLOCK_FREQUENCY : integer := 100000000
    );
    port(
        clock           : in     vl_logic;
        data            : in     vl_logic_vector(15 downto 0);
        commons         : out    vl_logic_vector(3 downto 0);
        segments        : out    vl_logic_vector(6 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLOCK_FREQUENCY : constant is 1;
end SevenSegTop;
