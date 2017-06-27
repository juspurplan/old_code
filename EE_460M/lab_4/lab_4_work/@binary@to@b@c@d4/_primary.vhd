library verilog;
use verilog.vl_types.all;
entity BinaryToBCD4 is
    port(
        num             : in     vl_logic_vector(13 downto 0);
        bcd3            : out    vl_logic_vector(3 downto 0);
        bcd2            : out    vl_logic_vector(3 downto 0);
        bcd1            : out    vl_logic_vector(3 downto 0);
        bcd0            : out    vl_logic_vector(3 downto 0)
    );
end BinaryToBCD4;
