library verilog;
use verilog.vl_types.all;
entity half_adder is
    port(
        A               : in     vl_logic;
        B               : in     vl_logic;
        \out\           : out    vl_logic;
        carry           : out    vl_logic
    );
end half_adder;
