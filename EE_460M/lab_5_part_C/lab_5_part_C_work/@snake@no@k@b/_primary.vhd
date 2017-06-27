library verilog;
use verilog.vl_types.all;
entity SnakeNoKB is
    port(
        clock           : in     vl_logic;
        up              : in     vl_logic;
        down            : in     vl_logic;
        left            : in     vl_logic;
        right           : in     vl_logic;
        start           : in     vl_logic;
        stop            : in     vl_logic;
        pause           : in     vl_logic;
        resume          : in     vl_logic;
        hsync           : out    vl_logic;
        vsync           : out    vl_logic;
        R               : out    vl_logic_vector(3 downto 0);
        G               : out    vl_logic_vector(3 downto 0);
        B               : out    vl_logic_vector(3 downto 0)
    );
end SnakeNoKB;
