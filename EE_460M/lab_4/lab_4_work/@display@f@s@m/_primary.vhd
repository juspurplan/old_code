library verilog;
use verilog.vl_types.all;
entity DisplayFSM is
    port(
        clock           : in     vl_logic;
        current_state   : out    vl_logic_vector(1 downto 0)
    );
end DisplayFSM;
