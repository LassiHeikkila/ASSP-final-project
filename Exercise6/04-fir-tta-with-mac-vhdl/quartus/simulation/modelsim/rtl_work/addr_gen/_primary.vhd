library verilog;
use verilog.vl_types.all;
entity addr_gen is
    generic(
        cntr_limit      : integer := 0
    );
    port(
        clk             : in     vl_logic;
        ack             : in     vl_logic;
        rstx            : in     vl_logic;
        addr            : out    vl_logic_vector(13 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of cntr_limit : constant is 1;
end addr_gen;
