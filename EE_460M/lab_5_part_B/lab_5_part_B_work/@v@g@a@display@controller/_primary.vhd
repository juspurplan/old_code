library verilog;
use verilog.vl_types.all;
entity VGADisplayController is
    generic(
        WIDTH           : integer := 640;
        HEIGHT          : integer := 480;
        X_BLANK_SIZE    : integer := 160;
        X_BLANK_LOW     : integer := 19;
        X_BLANK_HIGH    : integer := 116;
        Y_BLANK_SIZE    : integer := 45;
        Y_BLANK_LOW     : integer := 13;
        Y_BLANK_HIGH    : integer := 15
    );
    port(
        pixel_clock     : in     vl_logic;
        color           : in     vl_logic_vector(11 downto 0);
        hsync           : out    vl_logic;
        vsync           : out    vl_logic;
        RED             : out    vl_logic_vector(3 downto 0);
        GREEN           : out    vl_logic_vector(3 downto 0);
        BLUE            : out    vl_logic_vector(3 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of WIDTH : constant is 1;
    attribute mti_svvh_generic_type of HEIGHT : constant is 1;
    attribute mti_svvh_generic_type of X_BLANK_SIZE : constant is 1;
    attribute mti_svvh_generic_type of X_BLANK_LOW : constant is 1;
    attribute mti_svvh_generic_type of X_BLANK_HIGH : constant is 1;
    attribute mti_svvh_generic_type of Y_BLANK_SIZE : constant is 1;
    attribute mti_svvh_generic_type of Y_BLANK_LOW : constant is 1;
    attribute mti_svvh_generic_type of Y_BLANK_HIGH : constant is 1;
end VGADisplayController;
