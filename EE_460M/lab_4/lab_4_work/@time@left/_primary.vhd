library verilog;
use verilog.vl_types.all;
entity TimeLeft is
    port(
        decrement       : in     vl_logic;
        add50           : in     vl_logic;
        add150          : in     vl_logic;
        add200          : in     vl_logic;
        add500          : in     vl_logic;
        reset10         : in     vl_logic;
        reset205        : in     vl_logic;
        clock           : in     vl_logic;
        count           : out    vl_logic_vector(13 downto 0)
    );
end TimeLeft;
