----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;

entity Receiver is
	port (	rxd, reset, clk_baud	: in std_logic;
				rxdata					: out std_logic_vector(128 downto 1); --Skal også ændres i FullTester (linje 15), Code_Lock (linje 8) og her (linje 7 og 16)
				rxvalid					: out std_logic
			);
end Receiver;

architecture Rec of Receiver is
type state is (idle, reading, stopping, latchData);
signal present_state, next_state : state;
signal counter : natural := 0;
constant end_length : natural := 128;	--Skal også ændres i FullTester (linje 15), Code_Lock (linje 8) og her (linje 7 og 16)

begin

state_reg : process(clk_baud, reset)
begin
	if reset = '0' then
		present_state <= idle;
	elsif rising_edge(clk_baud) then
		present_state <= next_state;
	end if;
end process;


nxt_state : process(present_state, clk_baud)
begin
	next_state <= present_state;
	case present_state is
		when idle =>
			if rxd = '0' then
				next_state <= reading;
			end if;
		when reading =>
			if counter = end_length then
				next_state <= stopping;
			else
				null;
			end if;
		when stopping =>
			if rxd = '1' then
				next_state <= latchData;
			else
				next_state <= idle;
			end if;
		when latchData =>
			next_state <= idle;
		when others =>
			next_state <= idle;
		end case;
end process;

output : process(present_state)
begin
if falling_edge(clk_baud) then
	case present_state is
		when latchData =>
			rxvalid <= '1';
		when reading =>
			rxdata(counter) <= rxd;
			counter <= counter + 1;
		when others	=>
			rxvalid <= '0';
			counter <= 0;
	end case;
else
	null;
end if;
end process;
end Rec;