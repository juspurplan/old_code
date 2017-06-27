library verilog;
use verilog.vl_types.all;
entity LEDController is
    generic(
        CLOCK_FREQUENCY : integer := 10000000
    );
    port(
        current_state   : in     vl_logic_vector(3 downto 0);
        clock           : in     vl_logic;
        led_a           : out    vl_logic_vector(2 downto 0);
        led_b           : out    vl_logic_vector(2 downto 0);
        led_walk        : out    vl_logic_vector(1 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CLOCK_FREQUENCY : constant is 1;
end LEDController;
