library verilog;
use verilog.vl_types.all;
entity fiforeader is
    port(
        clk             : in     vl_logic;
        data            : in     vl_logic_vector(7 downto 0);
        q               : out    vl_logic_vector(7 downto 0);
        ack             : out    vl_logic;
        dv              : out    vl_logic;
        notfull         : in     vl_logic;
        rstx            : in     vl_logic
    );
end fiforeader;
