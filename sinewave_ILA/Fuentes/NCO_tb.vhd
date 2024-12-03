library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;

entity tb_NCO is
end tb_NCO;

architecture tb_NCO_arq of tb_NCO is

  -- NCO component declaration
  component NCO is
    port (
      c_i         : in std_logic; -- Clock signal
      en_i        : in std_logic; -- Enable signal
      wave_type_i : in std_logic_vector(1 downto 0); -- Wave type selector
      freq_word_i : in std_logic_vector(31 downto 0); -- Frequency tuning word
      wave_o      : out std_logic_vector(15 downto 0) -- Output wave
    );
  end component;

  -- Signal declarations
  signal clk         : std_logic                     := '0'; -- Clock signal
  signal en          : std_logic                     := '1'; -- Enable signal
  signal wave_type_i : std_logic_vector(1 downto 0)  := (others => '0'); -- Wave type selector
  signal freq_word   : std_logic_vector(31 downto 0) := (others => '0'); -- Frequency tuning word
  signal wave_output : std_logic_vector(15 downto 0); -- Output wave from NCO

  -- Clock period constant
  constant clk_period : time := 10 ns;

begin

  -- Clock generation
  clk <= not clk after clk_period / 2;

  -- Instantiate the NCO (DUT)
  DUT : NCO
  port map
  (
    c_i         => clk,
    en_i        => en,
    wave_type_i => wave_type_i,
    freq_word_i => freq_word,
    wave_o      => wave_output
  );

  -- Stimulus process to apply different test cases
  stimulus : process
  begin
    -- Apply different wave types and frequency tuning words
    wave_type_i <= "00"; -- Sine wave
    freq_word   <= x"00010000"; -- Low frequency
    wait for 1000 us;

    wave_type_i <= "01"; -- Square wave
    freq_word   <= x"00080000"; -- Medium frequency
    wait for 1000 us;

    wave_type_i <= "10"; -- Triangle wave
    freq_word   <= x"00010000"; -- High frequency
    wait for 1000 us;

    wave_type_i <= "11"; -- Sawtooth wave
    freq_word   <= x"00FFFFFF"; -- Higher frequency
    wait for 1000 us;

    -- End simulation
    wait;
  end process;

end tb_NCO_arq;
