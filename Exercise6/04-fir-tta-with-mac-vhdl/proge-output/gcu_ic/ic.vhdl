library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use STD.textio.all;
use work.toplevel_globals.all;

entity toplevel_interconn is

  port (
    socket_lsu_i1_data : out std_logic_vector(14 downto 0);
    socket_lsu_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_lsu_o1_data0 : in std_logic_vector(31 downto 0);
    socket_lsu_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_lsu_i2_data : out std_logic_vector(31 downto 0);
    socket_lsu_i2_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_RF_i1_data : out std_logic_vector(31 downto 0);
    socket_RF_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_RF_o1_data0 : in std_logic_vector(31 downto 0);
    socket_RF_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_bool_i1_data : out std_logic_vector(0 downto 0);
    socket_bool_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_bool_o1_data0 : in std_logic_vector(0 downto 0);
    socket_bool_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_gcu_i1_data : out std_logic_vector(IMEMADDRWIDTH-1 downto 0);
    socket_gcu_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_gcu_i2_data : out std_logic_vector(IMEMADDRWIDTH-1 downto 0);
    socket_gcu_i2_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_gcu_o1_data0 : in std_logic_vector(IMEMADDRWIDTH-1 downto 0);
    socket_gcu_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_ALU_i1_data : out std_logic_vector(31 downto 0);
    socket_ALU_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_ALU_i2_data : out std_logic_vector(31 downto 0);
    socket_ALU_i2_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_ALU_o1_data0 : in std_logic_vector(31 downto 0);
    socket_ALU_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_MAC_i1_data : out std_logic_vector(31 downto 0);
    socket_MAC_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_MAC_i2_data : out std_logic_vector(31 downto 0);
    socket_MAC_i2_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_MAC_o1_data0 : in std_logic_vector(31 downto 0);
    socket_MAC_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_INPUT_i1_data : out std_logic_vector(7 downto 0);
    socket_INPUT_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_INPUT_o1_data0 : in std_logic_vector(7 downto 0);
    socket_INPUT_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_INPUT_o2_data0 : in std_logic_vector(7 downto 0);
    socket_INPUT_o2_bus_cntrl : in std_logic_vector(1 downto 0);
    socket_OUTPUT_i1_data : out std_logic_vector(7 downto 0);
    socket_OUTPUT_i1_bus_cntrl : in std_logic_vector(0 downto 0);
    socket_OUTPUT_o1_data0 : in std_logic_vector(7 downto 0);
    socket_OUTPUT_o1_bus_cntrl : in std_logic_vector(1 downto 0);
    simm_B1 : in std_logic_vector(31 downto 0);
    simm_cntrl_B1 : in std_logic_vector(0 downto 0);
    simm_B1_1 : in std_logic_vector(31 downto 0);
    simm_cntrl_B1_1 : in std_logic_vector(0 downto 0));

end toplevel_interconn;

architecture comb_andor of toplevel_interconn is

  signal databus_B1 : std_logic_vector(31 downto 0);
  signal databus_B1_alt0 : std_logic_vector(31 downto 0);
  signal databus_B1_alt1 : std_logic_vector(31 downto 0);
  signal databus_B1_alt2 : std_logic_vector(31 downto 0);
  signal databus_B1_alt3 : std_logic_vector(31 downto 0);
  signal databus_B1_alt4 : std_logic_vector(31 downto 0);
  signal databus_B1_alt5 : std_logic_vector(31 downto 0);
  signal databus_B1_alt6 : std_logic_vector(31 downto 0);
  signal databus_B1_alt7 : std_logic_vector(31 downto 0);
  signal databus_B1_alt8 : std_logic_vector(31 downto 0);
  signal databus_B1_simm : std_logic_vector(31 downto 0);
  signal databus_B1_1 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt0 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt1 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt2 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt3 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt4 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt5 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt6 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt7 : std_logic_vector(31 downto 0);
  signal databus_B1_1_alt8 : std_logic_vector(31 downto 0);
  signal databus_B1_1_simm : std_logic_vector(31 downto 0);

  component toplevel_input_socket_cons_2
    generic (
      BUSW_0 : integer := 32;
      BUSW_1 : integer := 32;
      DATAW : integer := 32);
    port (
      databus0 : in std_logic_vector(BUSW_0-1 downto 0);
      databus1 : in std_logic_vector(BUSW_1-1 downto 0);
      data : out std_logic_vector(DATAW-1 downto 0);
      databus_cntrl : in std_logic_vector(0 downto 0));
  end component;

  component toplevel_output_socket_cons_2_1
    generic (
      BUSW_0 : integer := 32;
      BUSW_1 : integer := 32;
      DATAW_0 : integer := 32);
    port (
      databus0_alt : out std_logic_vector(BUSW_0-1 downto 0);
      databus1_alt : out std_logic_vector(BUSW_1-1 downto 0);
      data0 : in std_logic_vector(DATAW_0-1 downto 0);
      databus_cntrl : in std_logic_vector(1 downto 0));
  end component;

  component toplevel_output_socket_cons_1_1
    generic (
      BUSW_0 : integer := 32;
      DATAW_0 : integer := 32);
    port (
      databus0_alt : out std_logic_vector(BUSW_0-1 downto 0);
      data0 : in std_logic_vector(DATAW_0-1 downto 0);
      databus_cntrl : in std_logic_vector(0 downto 0));
  end component;


begin -- comb_andor

  lsu_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 15)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_lsu_i1_data,
      databus_cntrl => socket_lsu_i1_bus_cntrl);

  lsu_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 32)
    port map (
      databus0_alt => databus_B1_alt8,
      databus1_alt => databus_B1_1_alt8,
      data0 => socket_lsu_o1_data0,
      databus_cntrl => socket_lsu_o1_bus_cntrl);

  lsu_i2 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 32)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_lsu_i2_data,
      databus_cntrl => socket_lsu_i2_bus_cntrl);

  RF_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 32)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_RF_i1_data,
      databus_cntrl => socket_RF_i1_bus_cntrl);

  RF_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 32)
    port map (
      databus0_alt => databus_B1_alt7,
      databus1_alt => databus_B1_1_alt7,
      data0 => socket_RF_o1_data0,
      databus_cntrl => socket_RF_o1_bus_cntrl);

  bool_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 1)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_bool_i1_data,
      databus_cntrl => socket_bool_i1_bus_cntrl);

  bool_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 1)
    port map (
      databus0_alt => databus_B1_alt6,
      databus1_alt => databus_B1_1_alt6,
      data0 => socket_bool_o1_data0,
      databus_cntrl => socket_bool_o1_bus_cntrl);

  gcu_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => IMEMADDRWIDTH)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_gcu_i1_data,
      databus_cntrl => socket_gcu_i1_bus_cntrl);

  gcu_i2 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => IMEMADDRWIDTH)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_gcu_i2_data,
      databus_cntrl => socket_gcu_i2_bus_cntrl);

  gcu_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => IMEMADDRWIDTH)
    port map (
      databus0_alt => databus_B1_alt5,
      databus1_alt => databus_B1_1_alt5,
      data0 => socket_gcu_o1_data0,
      databus_cntrl => socket_gcu_o1_bus_cntrl);

  ALU_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 32)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_ALU_i1_data,
      databus_cntrl => socket_ALU_i1_bus_cntrl);

  ALU_i2 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 32)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_ALU_i2_data,
      databus_cntrl => socket_ALU_i2_bus_cntrl);

  ALU_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 32)
    port map (
      databus0_alt => databus_B1_alt4,
      databus1_alt => databus_B1_1_alt4,
      data0 => socket_ALU_o1_data0,
      databus_cntrl => socket_ALU_o1_bus_cntrl);

  MAC_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 32)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_MAC_i1_data,
      databus_cntrl => socket_MAC_i1_bus_cntrl);

  MAC_i2 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 32)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_MAC_i2_data,
      databus_cntrl => socket_MAC_i2_bus_cntrl);

  MAC_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 32)
    port map (
      databus0_alt => databus_B1_alt3,
      databus1_alt => databus_B1_1_alt3,
      data0 => socket_MAC_o1_data0,
      databus_cntrl => socket_MAC_o1_bus_cntrl);

  INPUT_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 8)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_INPUT_i1_data,
      databus_cntrl => socket_INPUT_i1_bus_cntrl);

  INPUT_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 8)
    port map (
      databus0_alt => databus_B1_alt2,
      databus1_alt => databus_B1_1_alt2,
      data0 => socket_INPUT_o1_data0,
      databus_cntrl => socket_INPUT_o1_bus_cntrl);

  INPUT_o2 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 8)
    port map (
      databus0_alt => databus_B1_alt1,
      databus1_alt => databus_B1_1_alt1,
      data0 => socket_INPUT_o2_data0,
      databus_cntrl => socket_INPUT_o2_bus_cntrl);

  OUTPUT_i1 : toplevel_input_socket_cons_2
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW => 8)
    port map (
      databus0 => databus_B1,
      databus1 => databus_B1_1,
      data => socket_OUTPUT_i1_data,
      databus_cntrl => socket_OUTPUT_i1_bus_cntrl);

  OUTPUT_o1 : toplevel_output_socket_cons_2_1
    generic map (
      BUSW_0 => 32,
      BUSW_1 => 32,
      DATAW_0 => 8)
    port map (
      databus0_alt => databus_B1_alt0,
      databus1_alt => databus_B1_1_alt0,
      data0 => socket_OUTPUT_o1_data0,
      databus_cntrl => socket_OUTPUT_o1_bus_cntrl);

  simm_socket_B1 : toplevel_output_socket_cons_1_1
    generic map (
      BUSW_0 => 32,
      DATAW_0 => 32)
    port map (
      databus0_alt => databus_B1_simm,
      data0 => simm_B1,
      databus_cntrl => simm_cntrl_B1);

  simm_socket_B1_1 : toplevel_output_socket_cons_1_1
    generic map (
      BUSW_0 => 32,
      DATAW_0 => 32)
    port map (
      databus0_alt => databus_B1_1_simm,
      data0 => simm_B1_1,
      databus_cntrl => simm_cntrl_B1_1);

  databus_B1 <= databus_B1_alt0 or databus_B1_alt1 or databus_B1_alt2 or databus_B1_alt3 or databus_B1_alt4 or databus_B1_alt5 or databus_B1_alt6 or databus_B1_alt7 or databus_B1_alt8 or databus_B1_simm;
  databus_B1_1 <= databus_B1_1_alt0 or databus_B1_1_alt1 or databus_B1_1_alt2 or databus_B1_1_alt3 or databus_B1_1_alt4 or databus_B1_1_alt5 or databus_B1_1_alt6 or databus_B1_1_alt7 or databus_B1_1_alt8 or databus_B1_1_simm;

end comb_andor;
