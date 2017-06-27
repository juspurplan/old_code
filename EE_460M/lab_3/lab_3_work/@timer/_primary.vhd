library verilog;
use verilog.vl_types.all;
entity Timer is
    generic(
        CLOCK_FREQUENCY : integer := 100000000;
        RESOLUTION      : integer := 4;
        STATE1_DURATION : integer := 3;
        STATE2_DURATION : integer := 2;
        STATE3_DURATION : integer := 3;
        STATE4_DURATION : integer := 1;
        STATE5_DURATION : integer := 2;
        STATE6_DURATION : integer := 2
    );
    port(
        in_state        : in     vl_logic_vector(3 downto 0);
        clock           : in     vl_logic;
        out_clock       : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLOCK_FREQUENCY : constant is 1;
    attribute mti_svvh_generic_type of RESOLUTION : constant is 1;
    attribute mti_svvh_generic_type of STATE1_DURATION : constant is 1;
    attribute mti_svvh_generic_type of STATE2_DURATION : constant is 1;
    attribute mti_svvh_generic_type of STATE3_DURATION : constant is 1;
    attribute mti_svvh_generic_type of STATE4_DURATION : constant is 1;
    attribute mti_svvh_generic_type of STATE5_DURATION : constant is 1;
    attribute mti_svvh_generic_type of STATE6_DURATION : constant is 1;
end Timer;
