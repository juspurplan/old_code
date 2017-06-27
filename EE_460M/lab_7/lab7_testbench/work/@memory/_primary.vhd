library verilog;
use verilog.vl_types.all;
entity Memory is
    port(
        CS              : in     vl_logic;
        WE              : in     vl_logic;
        CLK             : in     vl_logic;
        ADDR            : in     vl_logic_vector(6 downto 0);
        Mem_Bus         : inout  vl_logic_vector(31 downto 0)
    );
end Memory;
