-- Copyright (c) 2002-2009 Tampere University of Technology.
--
-- This file is part of TTA-Based Codesign Environment (TCE).
-- 
-- Permission is hereby granted, free of charge, to any person obtaining a
-- copy of this software and associated documentation files (the "Software"),
-- to deal in the Software without restriction, including without limitation
-- the rights to use, copy, modify, merge, publish, distribute, sublicense,
-- and/or sell copies of the Software, and to permit persons to whom the
-- Software is furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
-- 
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
-- FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
-- DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------------
-- Title      : Processor based on TTA TCE architecture template
-- Project    : FlexDSP
-------------------------------------------------------------------------------
-- File       : proc_arch.vhdl
-- Author     : Teemu Pitkänen (teemu.pitkanen@tut.fi)
-- Company    : TUT/IDCS
-- Created    : 2003-11-26
-- Last update: 2007/04/23
-- Platform   : 
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: architecture for processor with a core with single port data
-- memory/cache (structural) and with a core with dual-port data memory/cache
-- (structural_dp_dmem)
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author  Description
-- 2003-11-26  1.0      sertamo	Created
-------------------------------------------------------------------------------

use work.testbench_constants.all;
use work.toplevel_imem_mau.all;
use work.toplevel_params.all;

architecture structural_dp_dmem of proc is

  component toplevel

  port (
    clk : in std_logic;
    rstx : in std_logic;
    busy : in std_logic;
    imem_en_x : out std_logic;
    imem_addr : out std_logic_vector(IMEMADDRWIDTH-1 downto 0);
    imem_data : in std_logic_vector(IMEMWIDTHINMAUS*IMEMMAUWIDTH-1 downto 0);
    pc_init : in std_logic_vector(IMEMADDRWIDTH-1 downto 0);
    fu_LSU_data_in : in std_logic_vector(fu_LSU_dataw-1 downto 0);
    fu_LSU_data_out : out std_logic_vector(fu_LSU_dataw-1 downto 0);
    fu_LSU_addr : out std_logic_vector(fu_LSU_addrw-2-1 downto 0);
    fu_LSU_mem_en_x : out std_logic_vector(0 downto 0);
    fu_LSU_wr_en_x : out std_logic_vector(0 downto 0);
    fu_LSU_wr_mask_x : out std_logic_vector(fu_LSU_dataw-1 downto 0);
    fu_INPUT_ext_data : in std_logic_vector(7 downto 0);
    fu_INPUT_ext_status : in std_logic_vector(fu_INPUT_statusw-1 downto 0);
    fu_INPUT_ext_rdack : out std_logic_vector(0 downto 0);
    fu_OUTPUT_ext_data : out std_logic_vector(7 downto 0);
    fu_OUTPUT_ext_status : in std_logic_vector(fu_OUTPUT_statusw-1 downto 0);
    fu_OUTPUT_ext_dv : out std_logic_vector(0 downto 0));

  end component;

  signal dmem_q_a        : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal dmem_d_a        : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal dmem_addr_a     : std_logic_vector(DMEMADDRWIDTH-1 downto 0);
  signal dmem_en_a_x     : std_logic;
  signal dmem_wr_a_x     : std_logic;
  signal dmem_bit_wr_a_x : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal dmem_q_b        : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal dmem_d_b        : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal dmem_addr_b     : std_logic_vector(DMEMADDRWIDTH-1 downto 0);
  signal dmem_en_b_x     : std_logic; --:='1';
  signal dmem_wr_b_x     : std_logic;
  signal dmem_bit_wr_b_x : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal imem_data       : std_logic_vector(IMEMWIDTHINMAUS*IMEMMAUWIDTH-1 downto 0);
  signal imem_addr    : std_logic_vector(IMEMADDRWIDTH-1 downto 0);
  signal imem_en_x       : std_logic;

  signal q_a        : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal d_a        : std_logic_vector(DMEMDATAWIDTH-1 downto 0);
  signal addr_a     : std_logic_vector(DMEMADDRWIDTH-1 downto 0);
  signal en_a_x     : std_logic;
  signal en_b_x     : std_logic;
  signal wr_a_x     : std_logic;
  signal bit_wr_a_x : std_logic_vector(DMEMDATAWIDTH-1 downto 0);

  signal imem_d_arb : std_logic_vector(IMEMWIDTHINMAUS*IMEMMAUWIDTH-1 downto 0);
  signal imem_addr_arb : std_logic_vector(IMEMADDRWIDTH-1 downto 0);
  signal imem_en_arb_x : std_logic;
  signal imem_wr_arb_x : std_logic;
  signal imem_bit_wr_arb_x : std_logic_vector(IMEMWIDTHINMAUS*IMEMMAUWIDTH-1 downto 0);
  
  component synch_rom
    generic (
      DATAW : integer;
      ADDRW : integer);
    port (
      clk  : in  std_logic;
      en_x : in  std_logic;
      addr : in  std_logic_vector(ADDRW-1 downto 0);
      q    : out std_logic_vector(DATAW-1 downto 0));
  end component;


  component synch_dualport_sram
    generic (
      INITFILENAME : string;
      DATAW        : integer;
      ADDRW        : integer);
    port (
      clk        : in  std_logic;
      d_a        : in  std_logic_vector(DATAW-1 downto 0);
      d_b        : in  std_logic_vector(DATAW-1 downto 0);
      addr_a     : in  std_logic_vector(ADDRW-1 downto 0);
      addr_b     : in  std_logic_vector(ADDRW-1 downto 0);
      en_a_x     : in  std_logic;
      en_b_x     : in  std_logic;
      wr_a_x     : in  std_logic;
      wr_b_x     : in  std_logic;
      bit_wr_a_x : in  std_logic_vector(DATAW-1 downto 0);
      bit_wr_b_x : in  std_logic_vector(DATAW-1 downto 0);
      q_a        : out std_logic_vector(DATAW-1 downto 0);
      q_b        : out std_logic_vector(DATAW-1 downto 0));
  end component;

  component synch_sram
    generic (
      INITFILENAME : string;
      DATAW        : integer;
      ADDRW        : integer);
    port (
      clk      : in  std_logic;
      d        : in  std_logic_vector(DATAW-1 downto 0);
      addr     : in  std_logic_vector(ADDRW-1 downto 0);
      en_x     : in  std_logic;
      wr_x     : in  std_logic;
      bit_wr_x : in  std_logic_vector(DATAW-1 downto 0);
      q        : out std_logic_vector(DATAW-1 downto 0));
  end component;

  component mem_arbiter
    generic (
      PORTW     : integer;
      ADDRWIDTH : integer);
    port (
      d_1        : in  std_logic_vector(PORTW-1 downto 0);
      d_2        : in  std_logic_vector(PORTW-1 downto 0);
      d          : out std_logic_vector(PORTW-1 downto 0);
      addr_1     : in  std_logic_vector(ADDRWIDTH-1 downto 0);
      addr_2     : in  std_logic_vector(ADDRWIDTH-1 downto 0);
      addr       : out std_logic_vector(ADDRWIDTH-1 downto 0);
      en_1_x     : in  std_logic;
      en_2_x     : in  std_logic;
      en_x       : out std_logic;
      wr_1_x     : in  std_logic;
      wr_2_x     : in  std_logic;
      wr_x       : out std_logic;
      bit_wr_1_x : in  std_logic_vector(PORTW-1 downto 0);
      bit_wr_2_x : in  std_logic_vector(PORTW-1 downto 0);
      bit_wr_x   : out std_logic_vector(PORTW-1 downto 0);
      mem_busy   : out std_logic);
  end component;

  component imem_arbiter
  generic (
    PORTW     : integer := 32;
    ADDRWIDTH : integer := 11);

  port (
    d_2 : in  std_logic_vector(PORTW-1 downto 0);
    d   : out std_logic_vector(PORTW-1 downto 0);

    addr_1 : in  std_logic_vector(ADDRWIDTH-1 downto 0);
    addr_2 : in  std_logic_vector(ADDRWIDTH-1 downto 0);
    addr   : out std_logic_vector(ADDRWIDTH-1 downto 0);

    en_1_x : in  std_logic;
    en_2_x : in  std_logic;
    en_x   : out std_logic;

    wr_2_x : in  std_logic;
    wr_x   : out std_logic;

    bit_wr_2_x : in  std_logic_vector(PORTW-1 downto 0);
    bit_wr_x   : out std_logic_vector(PORTW-1 downto 0);

    mem_busy : out std_logic);
  end component;
  
begin  -- struct

  core : toplevel
port map (
clk  => clk,
rstx => rst_x,
busy => '0',
imem_en_x => imem_en_x,
imem_addr => imem_addr,
imem_data => imem_data,
pc_init => pc_init,
fu_LSU_data_in => dmem_q_a,
fu_LSU_data_out => dmem_d_a,
fu_LSU_addr => dmem_addr_a,
fu_LSU_mem_en_x(0) => dmem_en_a_x,
fu_LSU_wr_en_x(0) => dmem_wr_a_x,
fu_LSU_wr_mask_x => dmem_bit_wr_a_x);
  datamem : synch_dualport_sram
    generic map (
      -- pragma translate_off
      INITFILENAME => DMEM_INIT_FILE,
      -- pragma translate_on
      DATAW        => DMEMDATAWIDTH,
      ADDRW        => DMEMADDRWIDTH)
    port map (
      clk        => clk,
      d_a        => d_a,
      addr_a     => addr_a,
      en_a_x     => en_a_x,
      wr_a_x     => wr_a_x,
      bit_wr_a_x => bit_wr_a_x,
      d_b        => dmem_d_b,
      addr_b     => dmem_addr_b,
      en_b_x     => dmem_en_b_x,
      wr_b_x     => dmem_wr_b_x,
      bit_wr_b_x => dmem_bit_wr_b_x,
      q_a        => q_a,
      q_b        => dmem_q_b);

  dmem_q_a <= q_a;
  data_out <= q_a;

  dmem_arbiter : mem_arbiter
    generic map (
      PORTW     => DMEMDATAWIDTH,
      ADDRWIDTH => DMEMADDRWIDTH)
    port map (
      d_1 => dmem_d_a,
      d_2 => dmem_ext_data,
      d   => d_a,

      addr_1 => dmem_addr_a,
      addr_2 => dmem_ext_addr,
      addr   => addr_a,

      en_1_x => dmem_en_a_x,
      en_2_x => dmem_ext_en_x,
      en_x   => en_a_x,

      wr_1_x => dmem_wr_a_x,
      wr_2_x => dmem_ext_wr_x,
      wr_x   => wr_a_x,

      bit_wr_1_x => dmem_bit_wr_a_x,
      bit_wr_2_x => dmem_ext_bit_wr_x,
      bit_wr_x   => bit_wr_a_x,
      mem_busy   => dmem_busy);

  instrmem_arbiter : imem_arbiter
    generic map (
      PORTW     => IMEMWIDTHINMAUS*IMEMMAUWIDTH,
      ADDRWIDTH => IMEMADDRWIDTH)
    port map (
      d_2       => imem_ext_data,
      d         => imem_d_arb,

      addr_1 => imem_addr,
      addr_2 => imem_ext_addr,
      addr   => imem_addr_arb,

      en_1_x => imem_en_x,
      en_2_x => imem_ext_en_x,
      en_x   => imem_en_arb_x,

      wr_2_x => imem_ext_wr_x,
      wr_x   => imem_wr_arb_x,

      bit_wr_2_x => imem_ext_bit_wr_x,
      bit_wr_x   => imem_bit_wr_arb_x,
      mem_busy   => imem_busy);

  instmem : synch_sram
    generic map (
      -- pragma translate_off
      INITFILENAME => IMEM_INIT_FILE,
      -- pragma translate_on;
      DATAW => IMEMWIDTHINMAUS*IMEMMAUWIDTH,
      ADDRW => IMEMADDRWIDTH)
    port map (
      clk  => clk,
      d => imem_d_arb,
      addr => imem_addr_arb,      
      en_x => imem_en_arb_x,
      wr_x => imem_wr_arb_x,
      bit_wr_x => imem_bit_wr_arb_x,
      q => imem_data);

end structural_dp_dmem;

