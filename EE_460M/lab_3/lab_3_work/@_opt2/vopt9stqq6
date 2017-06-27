library verilog;
use verilog.vl_types.all;
entity sorter is
    generic(
        GROUP1_UPPER_LIMIT: integer := 250;
        GROUP2_UPPER_LIMIT: integer := 500;
        GROUP3_UPPER_LIMIT: integer := 750;
        GROUP4_UPPER_LIMIT: integer := 1500;
        GROUP5_UPPER_LIMIT: integer := 2000
    );
    port(
        weight          : in     vl_logic_vector(11 downto 0);
        clock           : in     vl_logic;
        reset           : in     vl_logic;
        group1          : out    vl_logic_vector(7 downto 0);
        group2          : out    vl_logic_vector(7 downto 0);
        group3          : out    vl_logic_vector(7 downto 0);
        group4          : out    vl_logic_vector(7 downto 0);
        group5          : out    vl_logic_vector(7 downto 0);
        group6          : out    vl_logic_vector(7 downto 0);
        current_group   : out    vl_logic_vector(2 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of GROUP1_UPPER_LIMIT : constant is 1;
    attribute mti_svvh_generic_type of GROUP2_UPPER_LIMIT : constant is 1;
    attribute mti_svvh_generic_type of GROUP3_UPPER_LIMIT : constant is 1;
    attribute mti_svvh_generic_type of GROUP4_UPPER_LIMIT : constant is 1;
    attribute mti_svvh_generic_type of GROUP5_UPPER_LIMIT : constant is 1;
end sorter;
