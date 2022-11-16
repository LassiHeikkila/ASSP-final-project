library verilog;
use verilog.vl_types.all;
entity start_trigger is
    port(
        clk             : in     vl_logic;
        \in\            : in     vl_logic;
        rstx            : in     vl_logic;
        \out\           : out    vl_logic
    );
end start_trigger;
