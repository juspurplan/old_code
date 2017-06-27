library verilog;
use verilog.vl_types.all;
entity AND2 is
    port(
        A1              : in     vl_logic;
        A2              : in     vl_logic;
        Z               : out    vl_logic
    );
end AND2;
