library IEEE;
use IEEE.std_logic_1164.all;

package mac32_set_acc_opcodes is

  constant OPC_MAC32  : std_logic_vector(0 downto 0) := "1";
  constant OPC_SET_ACC : std_logic_vector(0 downto 0) := "0";
  
end mac32_set_acc_opcodes;



library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.mac32_set_acc_opcodes.all;

entity fu_mac32 is
  
  generic (
    busw : integer := 32
    );

  port (
    t1data   : in  std_logic_vector(busw-1 downto 0);
    t1load   : in  std_logic;
    t2opcode : in  std_logic_vector(0 downto 0);
    t2data   : in  std_logic_vector(busw-1 downto 0);
    t2load   : in  std_logic;
    r1data   : out std_logic_vector(busw-1 downto 0);
    clk      : in  std_logic;
    rstx     : in  std_logic;
    glock    : in  std_logic
    );
end fu_mac32;

architecture rtl of fu_mac32 is

  signal r1reg : std_logic_vector(busw-1 downto 0);
  
begin

  regs : process (clk, rstx)
  begin  -- process regs
    if rstx = '0' then                  -- asynchronous reset (active low)
      r1reg <= (others => '0');
    elsif clk'event and clk = '1' then  -- rising clock edge
      if glock = '0' then
        if t2load = '1' then
          
          case t2opcode is
            when OPC_MAC32 =>
              r1reg <= std_logic_vector(
                to_signed(
                  to_integer(signed(r1reg)) + (
                    to_integer(signed(t1data)) * to_integer(signed(t2data))
                  ), 
                  busw
                )
              ); -- a = a + b*c
            when OPC_SET_ACC =>
              r1reg <= t1data;  -- just replace r1reg with given value
            when others =>
              null;
          end case;
          
        end if;
      end if;
    end if;
  end process regs;

  r1data <= r1reg;

end rtl;

