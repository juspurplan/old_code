library verilog;
use verilog.vl_types.all;
entity excess3_structural is
    port(
        X               : in     vl_logic;
        S               : out    vl_logic;
        V               : out    vl_logic;
        clock           : in     vl_logic;
        rst             : in     vl_logic
    );
end excess3_structural;
