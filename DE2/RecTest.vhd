----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;

entity RecTest is
	port (	CLOCK_50	: in std_logic;
				KEY		: in std_logic_vector(3 downto 0);
				LEDR		: out std_logic_vector(16 downto 0);
				GPIO_0	: in std_logic_vector(0 downto 0);
				GPIO_1	: out std_logic_vector(0 downto 0)
	);
end RecTest;

architecture test of RecTest is
signal clk_115200, recvalid, lockSignal	: std_logic; -- recvalid er det 1 eller 0 fra rxvalid, som checker om vi har fået en korrekt string på 9 bit inklusiv parity bit.
signal indata						: std_logic_vector(7 downto 0);
begin
gen		: entity work.BaudRateGenerator		port map (clk => CLOCK_50, reset => KEY(0), clk_baud => clk_115200);
rec		: entity work.Receiver					port map (rxd => GPIO_0(0), reset => KEY(0), clk_baud => clk_115200, rxdata => indata, rxvalid => recvalid);
codelock	: entity work.Code_Lock 				port map (clk => CLOCK_50, reset => KEY(0), codeEntry => recvalid,
																		code => indata, lock => lockSignal, err => LEDR(2 downto 1));
process(recvalid)
begin
	if recvalid = '1' then
		LEDR(16 downto 9) <= indata;
		GPIO_1(0) <= lockSignal;
	else
		null;
	end if;
end process;

end test;