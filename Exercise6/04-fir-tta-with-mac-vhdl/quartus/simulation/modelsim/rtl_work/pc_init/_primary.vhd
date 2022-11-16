library verilog;
use verilog.vl_types.all;
entity pc_init is
    generic(
        width           : integer := 0
    );
    port(
        zeros           : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of width : constant is 1;
end pc_init;
