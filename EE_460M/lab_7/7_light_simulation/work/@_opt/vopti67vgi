library verilog;
use verilog.vl_types.all;
entity MIPS is
    generic(
        add             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi0, Hi0, Hi0);
        sub             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi0, Hi1, Hi0);
        xor1            : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi1, Hi1, Hi0);
        and1            : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi1, Hi0, Hi0);
        or1             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi1, Hi0, Hi1);
        slt             : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi0);
        \srl\           : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        \sll\           : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi0, Hi0, Hi0);
        jr              : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        addi            : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi1, Hi0, Hi0, Hi0);
        andi            : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi1, Hi1, Hi0, Hi0);
        ori             : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi1, Hi1, Hi0, Hi1);
        lw              : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi0, Hi0, Hi1, Hi1);
        sw              : vl_logic_vector(0 to 5) := (Hi1, Hi0, Hi1, Hi0, Hi1, Hi1);
        beq             : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi0);
        bne             : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi1, Hi0, Hi1);
        j               : vl_logic_vector(0 to 5) := (Hi0, Hi0, Hi0, Hi0, Hi1, Hi0);
        R               : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        I               : vl_logic_vector(0 to 1) := (Hi0, Hi1);
        \J\             : vl_logic_vector(0 to 1) := (Hi1, Hi0)
    );
    port(
        CLK             : in     vl_logic;
        RST             : in     vl_logic;
        CS              : out    vl_logic;
        WE              : out    vl_logic;
        ADDR            : out    vl_logic_vector(6 downto 0);
        Mem_Bus         : inout  vl_logic_vector(31 downto 0);
        R1              : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of add : constant is 1;
    attribute mti_svvh_generic_type of sub : constant is 1;
    attribute mti_svvh_generic_type of xor1 : constant is 1;
    attribute mti_svvh_generic_type of and1 : constant is 1;
    attribute mti_svvh_generic_type of or1 : constant is 1;
    attribute mti_svvh_generic_type of slt : constant is 1;
    attribute mti_svvh_generic_type of \srl\ : constant is 1;
    attribute mti_svvh_generic_type of \sll\ : constant is 1;
    attribute mti_svvh_generic_type of jr : constant is 1;
    attribute mti_svvh_generic_type of addi : constant is 1;
    attribute mti_svvh_generic_type of andi : constant is 1;
    attribute mti_svvh_generic_type of ori : constant is 1;
    attribute mti_svvh_generic_type of lw : constant is 1;
    attribute mti_svvh_generic_type of sw : constant is 1;
    attribute mti_svvh_generic_type of beq : constant is 1;
    attribute mti_svvh_generic_type of bne : constant is 1;
    attribute mti_svvh_generic_type of j : constant is 1;
    attribute mti_svvh_generic_type of R : constant is 1;
    attribute mti_svvh_generic_type of I : constant is 1;
    attribute mti_svvh_generic_type of \J\ : constant is 1;
end MIPS;
