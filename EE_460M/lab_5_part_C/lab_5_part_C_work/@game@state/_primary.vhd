library verilog;
use verilog.vl_types.all;
entity GameState is
    generic(
        SNAKE_MAX_LENGTH: integer := 10;
        SNAKE_DEFAULT_LENGTH: integer := 4;
        SNAKE_LENGTH_INC: integer := 1;
        SNAKE_MAX_SPEED : integer := 5;
        SNAKE_DEFAULT_SPEED: integer := 1;
        SNAKE_SPEED_INC : integer := 1;
        SNAKE_SEGMENT_SIZE: integer := 10;
        SNAKE_START_X   : integer := 100;
        SNAKE_START_Y   : integer := 100;
        SNAKE_START_DIR : integer := 1;
        TICKS_BEFORE_INC: integer := 300
    );
    port(
        clock           : in     vl_logic;
        \in\            : in     vl_logic_vector(3 downto 0);
        x_coord_in      : in     vl_logic_vector(31 downto 0);
        y_coord_in      : in     vl_logic_vector(31 downto 0);
        pixel_color_out : out    vl_logic_vector(11 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SNAKE_MAX_LENGTH : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_DEFAULT_LENGTH : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_LENGTH_INC : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_MAX_SPEED : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_DEFAULT_SPEED : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_SPEED_INC : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_SEGMENT_SIZE : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_START_X : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_START_Y : constant is 1;
    attribute mti_svvh_generic_type of SNAKE_START_DIR : constant is 1;
    attribute mti_svvh_generic_type of TICKS_BEFORE_INC : constant is 1;
end GameState;
