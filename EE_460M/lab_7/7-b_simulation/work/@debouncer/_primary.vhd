library verilog;
use verilog.vl_types.all;
entity Debouncer is
    port(
        BINPUT          : in     vl_logic;
        CLK             : in     vl_logic;
        DEBOUTPUT       : out    vl_logic
    );
end Debouncer;
