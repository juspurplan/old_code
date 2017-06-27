library verilog;
use verilog.vl_types.all;
entity BCDCounter_2digit is
    port(
        D1              : in     vl_logic_vector(3 downto 0);
        D0              : in     vl_logic_vector(3 downto 0);
        enable          : in     vl_logic;
        up              : in     vl_logic;
        load            : in     vl_logic;
        clear           : in     vl_logic;
        clock           : in     vl_logic;
        Q1              : out    vl_logic_vector(7 downto 0);
        Q0              : out    vl_logic_vector(7 downto 0);
        carry_out       : out    vl_logic
    );
end BCDCounter_2digit;
