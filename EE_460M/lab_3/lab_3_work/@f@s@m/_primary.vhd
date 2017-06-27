library verilog;
use verilog.vl_types.all;
entity FSM is
    port(
        clock           : in     vl_logic;
        reset           : in     vl_logic;
        current_state   : out    vl_logic_vector(3 downto 0)
    );
end FSM;
