LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE IEEE.numeric_std.all;


ENTITY mux_duty IS
	GENERIC(
		bits_duty : INTEGER := 12);
	PORT( 
		duty_M1_int  : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);  --calculated value of M1 duty cycle
		duty_M3_int : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);   --calculated value of M3 duty cycle
		duty_M1_ext : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);   --forced value of M1 duty cycle 	     
		duty_M3_ext : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);   --forced value of M3 duty cycle	
		select_duty_ext: IN STD_LOGIC;							   --duty cycle select 
		duty_M1_out : out STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);          
		duty_M3_out : out STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0));         
END mux_duty;

ARCHITECTURE rtl OF mux_duty IS
BEGIN
	PROCESS(duty_M1_ext,duty_M3_ext,duty_M1_int,duty_M3_int,select_duty_ext)
	BEGIN 
		CASE select_duty_ext IS
				WHEN '1' =>
					duty_M1_out <= duty_M1_ext;         
					duty_M3_out <= duty_M3_ext;
				WHEN '0' =>
					duty_M1_out <= duty_M1_int;         
					duty_M3_out <= duty_M3_int;
		 END CASE;
	END PROCESS;
END rtl;		