library verilog;
use verilog.vl_types.all;
entity SinglePulser is
    port(
        PINPUT          : in     vl_logic;
        CLK             : in     vl_logic;
        PULINPUT        : out    vl_logic
    );
end SinglePulser;
