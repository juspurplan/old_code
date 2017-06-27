library verilog;
use verilog.vl_types.all;
entity ParkingMeter is
    generic(
        CLOCK_FREQUENCY : integer := 100000000
    );
    port(
        add50           : in     vl_logic;
        add150          : in     vl_logic;
        add200          : in     vl_logic;
        add500          : in     vl_logic;
        reset10         : in     vl_logic;
        reset205        : in     vl_logic;
        clock           : in     vl_logic;
        commons         : out    vl_logic_vector(3 downto 0);
        segments        : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLOCK_FREQUENCY : constant is 1;
end ParkingMeter;
