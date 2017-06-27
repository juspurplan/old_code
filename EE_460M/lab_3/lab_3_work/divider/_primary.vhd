library verilog;
use verilog.vl_types.all;
entity divider is
    generic(
        DIVIDE_BY       : integer := 1000;
        DURATION        : vl_notype
    );
    port(
        clock_in        : in     vl_logic;
        clock_out       : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of DIVIDE_BY : constant is 1;
    attribute mti_svvh_generic_type of DURATION : constant is 3;
end divider;
