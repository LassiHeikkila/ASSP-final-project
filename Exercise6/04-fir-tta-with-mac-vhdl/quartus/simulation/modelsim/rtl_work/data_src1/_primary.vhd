library verilog;
use verilog.vl_types.all;
entity data_src1 is
    port(
        address         : in     vl_logic_vector(13 downto 0);
        clock           : in     vl_logic;
        q               : out    vl_logic_vector(7 downto 0)
    );
end data_src1;
