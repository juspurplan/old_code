library verilog;
use verilog.vl_types.all;
entity DFF is
    port(
        D               : in     vl_logic;
        Q               : out    vl_logic;
        clk             : in     vl_logic;
        reset           : in     vl_logic
    );
end DFF;
