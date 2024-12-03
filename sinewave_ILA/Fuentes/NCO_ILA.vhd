library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity NCO_Testbench is
  port (
    clk         : in std_logic
  );
end NCO_Testbench;


architecture Behavioral of NCO_Testbench is

COMPONENT vio_0
  PORT (
  clk : IN STD_LOGIC;
  probe_out0 : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
  probe_out1 : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
  probe_out2 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
);
END COMPONENT;

COMPONENT ila_0

PORT (
	clk : IN STD_LOGIC;



	probe0 : IN STD_LOGIC_VECTOR(15 DOWNTO 0)
);
END COMPONENT  ;
  -- Signals for inputs and outputs
  signal en_i_vio        : std_logic_vector(0 downto 0);               -- Enable signal
  signal freq_word_i_vio : std_logic_vector(31 downto 0); -- Frequency tuning word
  signal wave_type_i_vio : std_logic_vector(1 downto 0);  -- Wave type selector
  
  -- NCO Output signal
  signal wave_o          : std_logic_vector(15 downto 0); -- Output wave from NCO

begin
  -- Instance of the NCO
  u_NCO : entity work.NCO
    port map (
      c_i         => clk,
      en_i        => en_i_vio(0),
      freq_word_i => freq_word_i_vio,
      wave_type_i => wave_type_i_vio,
      wave_o      => wave_o
    );

vio_inst : vio_0
  PORT MAP (
    clk => clk,
  probe_out0 => freq_word_i_vio,
  probe_out1 => en_i_vio,
  probe_out2 => wave_type_i_vio
  );


ila_inst : ila_0
PORT MAP (
	clk => clk,



	probe0 => wave_o
);
end Behavioral;
