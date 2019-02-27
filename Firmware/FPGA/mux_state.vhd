LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE IEEE.numeric_std.all;


ENTITY mux_state IS
	GENERIC(
		bits_duty : INTEGER := 12);
	PORT( 
		duty_M1_int : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);  		     
		duty_M3_int : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0); 		
		duty_M1_ext : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);  		     
		duty_M3_ext : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0); 	
		select_duty_ext: IN STD_LOGIC;	
		bypass: IN STD_LOGIC;		
		buck_mode : out STD_LOGIC;          
		boost_mode : out STD_LOGIC);       
END mux_state;

ARCHITECTURE rtl OF mux_state IS
BEGIN
	PROCESS(duty_M1_ext,duty_M3_ext,duty_M1_int,duty_M3_int,select_duty_ext,bypass)
	BEGIN 
		CASE select_duty_ext IS
			WHEN '0' =>
				IF( duty_M1_int=4095 AND duty_M3_int/=0 AND bypass='0') THEN
					buck_mode  <= '0';         
					boost_mode <= '1';
				ELSIF (duty_M3_int=0 AND duty_M1_int/=4095 AND bypass='0')THEN
					buck_mode  <= '1';         
					boost_mode <= '0';
				ELSIF( duty_M1_int/=4095 AND duty_M3_int/=0  AND bypass='0') THEN
					buck_mode  <= '1';         
					boost_mode <= '1';
				ELSE
					buck_mode  <= '0';         
					boost_mode <= '0';
				END IF;
			WHEN '1' =>
				IF( duty_M1_ext=4095 AND duty_M3_ext/=0 AND bypass='0') THEN
					buck_mode  <= '0';         
					boost_mode <= '1';
				ELSIF (duty_M3_ext=0 AND duty_M1_ext/=4095 AND bypass='0')THEN
					buck_mode  <= '1';         
					boost_mode <= '0';
				ELSIF( duty_M1_ext/=4095 AND duty_M3_ext/=0  AND bypass='0') THEN
					buck_mode  <= '1';         
					boost_mode <= '1';
				ELSE
					buck_mode  <= '0';         
					boost_mode <= '0';
				END IF;
		END CASE;
	END PROCESS;
END rtl;		