----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Code_Lock is
	port(	clk, reset, codeEntry	:	in std_logic;
			code							:	in std_logic_vector(7 downto 0);
			lock							:	out std_logic;
			err							:	out std_logic_vector(1 downto 0)
			);
end Code_Lock;

architecture simple of Code_Lock is
type state is (idle, eval, unlocked, going_idle, wcode, permlock);
type state2 is (Err_0, Err_1, Err_2, Err_3);

signal present_state, next_state : state;
signal code_lock_present_state, code_lock_next_state : state2;
signal codeString 	: std_logic_vector (7 downto 0) :="01000110"; --signal declaration code string for 70b user login
signal adminCode		: std_logic_vector (7 downto 0) :="00110110"; --signal declaration code string for 54b for admin login
signal adminUnlock	: std_logic_vector (7 downto 0) :="00101010"; --signal declaration code string for 42b for admin resetting login tries

begin
state_reg: process(clk, reset)	-- reset and clocking to next state
begin
	if reset = '0' then
		present_state <= idle;
	elsif rising_edge(clk) then
		present_state <= next_state;
	end if;
end process;

lock_reg: process(clk, reset)		-- reset and clocking to next state
begin
	if reset = '0' then
		code_lock_present_state <= Err_0;
	elsif rising_edge(clk) then
		code_lock_present_state <= code_lock_next_state;
	end if;
end process;

nxt_state: process(present_state, code, codeEntry)	-- State Machine transitions
begin
	next_state <= present_state;
	case present_state is
		when idle =>
			if codeEntry = '1' then
				next_state <= eval;
			end if;
		when eval =>
			if code = codeString then
				next_state <= unlocked;
			elsif code /= codeString then
				next_state <= wcode;
			end if;
		when unlocked =>
			if codeEntry = '0' then
				next_state <= going_idle;
			end if;
		when going_idle =>
			if codeEntry = '0' then
				next_state <= idle;
			end if;
		when wcode =>
			if code_lock_next_state = Err_3 then	-- if 3 errors occured go to permlock
				next_state <= permlock;
			else
				next_state <= going_idle;
			end if;
		when permlock =>
			if codeEntry = '1' and code = adminUnlock then
				next_state <= unlocked;
			else
				null;
			end if;
		when others =>
			next_state <= idle;
	end case;
end process;

wrongcode: process(present_state)	-- State Machine transitions
begin
	code_lock_next_state <= code_lock_present_state;
	if present_state = wcode then
		case code_lock_present_state is
			when Err_0 =>
				code_lock_next_state <= Err_1;
			when Err_1 =>
				code_lock_next_state <= Err_2;
			when Err_2 =>
				code_lock_next_state <= Err_3;
			when Err_3 =>
				code_lock_next_state <= Err_0;
			when others =>
				code_lock_next_state <= Err_0;
		end case;
	elsif present_state = unlocked then -- Resets error counter if machine is unlocked
		code_lock_next_state <= Err_0;
	end if;
end process;

outputs: process(present_state, code)	-- State machine output
begin
	case present_state is
		when unlocked =>
			lock <= '1';
		when permlock =>
			if codeEntry = '1' and code = adminCode then
				lock <= '1';
			else
				lock <= '0';
			end if;
		when others =>
			lock <= '0';
		end case;
end process;

lock_out: process(code_lock_present_state)	-- State machine output
begin
	case code_lock_present_state is
		when Err_0 =>
			err <= "00";
		when Err_1 =>
			err <= "01";
		when Err_2 =>
			err <= "10";
		when Err_3 =>
			err <= "11";
		when others =>
			err <= "00";
	end case;
end process;

end simple;