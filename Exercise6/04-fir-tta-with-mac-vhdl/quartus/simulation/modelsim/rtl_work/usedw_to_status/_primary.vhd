library verilog;
use verilog.vl_types.all;
entity usedw_to_status is
    port(
        usedw           : in     vl_logic_vector(6 downto 0);
        full            : in     vl_logic;
        status          : out    vl_logic_vector(7 downto 0)
    );
end usedw_to_status;
