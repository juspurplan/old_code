library verilog;
use verilog.vl_types.all;
entity BCDTo7Segment is
    port(
        bcd             : in     vl_logic_vector(3 downto 0);
        segments        : out    vl_logic_vector(7 downto 0)
    );
end BCDTo7Segment;
