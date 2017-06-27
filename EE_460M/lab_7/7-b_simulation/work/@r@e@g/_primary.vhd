library verilog;
use verilog.vl_types.all;
entity REG is
    port(
        CLK             : in     vl_logic;
        RegW            : in     vl_logic;
        DR              : in     vl_logic_vector(4 downto 0);
        SR1             : in     vl_logic_vector(4 downto 0);
        SR2             : in     vl_logic_vector(4 downto 0);
        Reg_In          : in     vl_logic_vector(31 downto 0);
        ReadReg1        : out    vl_logic_vector(31 downto 0);
        ReadReg2        : out    vl_logic_vector(31 downto 0);
        memR            : out    vl_logic_vector(31 downto 0);
        R1              : in     vl_logic_vector(2 downto 0);
        sevensegreg     : in     vl_logic
    );
end REG;
