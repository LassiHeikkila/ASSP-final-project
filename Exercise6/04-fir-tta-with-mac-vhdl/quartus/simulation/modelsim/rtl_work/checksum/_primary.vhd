library verilog;
use verilog.vl_types.all;
entity checksum is
    generic(
        cntr_limit      : integer := 0
    );
    port(
        rstx            : in     vl_logic;
        clk             : in     vl_logic;
        dv              : in     vl_logic;
        data            : in     vl_logic_vector(7 downto 0);
        status          : out    vl_logic_vector(7 downto 0);
        sum             : out    vl_logic_vector(23 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of cntr_limit : constant is 1;
end checksum;
