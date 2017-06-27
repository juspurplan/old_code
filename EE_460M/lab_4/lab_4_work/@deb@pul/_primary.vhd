library verilog;
use verilog.vl_types.all;
entity DebPul is
    port(
        SIG             : in     vl_logic;
        CLK_slow        : in     vl_logic;
        CLK             : in     vl_logic;
        SP              : out    vl_logic
    );
end DebPul;
