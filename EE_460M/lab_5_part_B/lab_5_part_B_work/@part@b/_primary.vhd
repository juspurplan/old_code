library verilog;
use verilog.vl_types.all;
entity PartB is
    port(
        clock           : in     vl_logic;
        switches        : in     vl_logic_vector(7 downto 0);
        hsync           : out    vl_logic;
        vsync           : out    vl_logic;
        R               : out    vl_logic_vector(3 downto 0);
        G               : out    vl_logic_vector(3 downto 0);
        B               : out    vl_logic_vector(3 downto 0)
    );
end PartB;
