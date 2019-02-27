----------------------------------------------------
--
--CLOCK GENERATOR(duty cycle=50%, frequency=100Hz)
--    
----------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY clk_debug IS
	GENERIC(
		sys_clk         : INTEGER := 48_000_000;--system clock frequency in Hz
		freq_debug		: INTEGER := 100;    	--debug clock switching frequency in Hz
		bits_duty : INTEGER := 12);             --bit of duty cycle
	PORT(
		clk              : IN  STD_LOGIC;     --system clock
		reset_n,enable   : IN  STD_LOGIC;     --asynchronous reset
		clk_debug        : OUT STD_LOGIC);    --debug clock
END clk_debug;

ARCHITECTURE rtl OF clk_debug IS
	CONSTANT  period        :  INTEGER := sys_clk/freq_debug;     --number of clocks in one pwm period
	CONSTANT  duty          :  STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0):= ( bits_duty-1 => '0', others => '1');     --duty cycle of 50%
	SIGNAL    count         :   INTEGER RANGE 0 TO period - 1:= 0;		
	SIGNAL    half_duty_new :  INTEGER RANGE 0 TO period/2 := 0;   
	SIGNAL    half_duty     :  integer RANGE 0 TO period/2:= 0;       
BEGIN
	PROCESS(clk, reset_n)
	BEGIN
		IF(reset_n = '0') THEN  
			count <= 0;          
			clk_debug <= '0';    
		ELSIF(clk'EVENT AND clk = '1') THEN 
			IF (enable='1') THEN
				half_duty_new <= conv_integer(duty)*period/(2**bits_duty)/2;   
				IF(count = period - 1) THEN 	
					count <= 0; 					
					half_duty <= half_duty_new;
				ELSE            					
					count <= count + 1; 			
				END IF;                                         
				IF(count = half_duty) THEN              
					clk_debug <= '0';                     
				ELSIF(count = period - half_duty) THEN   
					clk_debug  <= '1';                    
				END IF;
			END IF;
		END IF;
	END PROCESS;
END rtl;


