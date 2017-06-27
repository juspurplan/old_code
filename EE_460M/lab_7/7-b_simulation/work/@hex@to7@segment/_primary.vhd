library verilog;
use verilog.vl_types.all;
entity HexTo7Segment is
    port(
        hex             : in     vl_logic_vector(3 downto 0);
        segments        : out    vl_logic_vector(6 downto 0)
    );
end HexTo7Segment;
