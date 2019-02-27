--------------------------------------------------------------------------------
--
--buck PWM generator : PWM_M1, pwm_M2 
--    
--------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY pwmbuck IS
  GENERIC(
		sys_clk         : INTEGER := 48_000; --system clock frequency in Hz valore di f_clk/1000
		bits_duty : INTEGER := 12;           --bits of resolution setting the duty cycle
		bits_freq : INTEGER := 3;            --bits of resolution setting the frequency
		bits_deadtime : INTEGER := 4;        --bits of resolution setting the deadtime
		phases          : INTEGER := 2;
		--frequency values from 80KHz to 250 KHz/1000
		freq_default: INTEGER :=100;
		freq_1: INTEGER :=80;
		freq_2: INTEGER :=120;
		freq_3: INTEGER :=150;
		freq_4: INTEGER :=175;
		freq_5: INTEGER :=200;
		freq_6: INTEGER :=225;
		freq_7: INTEGER :=250;
		---deadtime values from 4 to 19 (number of clock cycle)
		deadtime_default: INTEGER := 15;
		deadtime_1: INTEGER := 4;
		deadtime_2: INTEGER := 5;
		deadtime_3: INTEGER := 6;
		deadtime_4: INTEGER := 7;
		deadtime_5: INTEGER := 8;
		deadtime_6: INTEGER := 9;
		deadtime_7: INTEGER := 10;
		deadtime_8: INTEGER := 11;
		deadtime_9: INTEGER := 12;
		deadtime_10: INTEGER := 13;
		deadtime_11: INTEGER := 14;
		deadtime_12: INTEGER := 16;
		deadtime_13: INTEGER := 17;
		deadtime_14: INTEGER := 18;
		deadtime_15: INTEGER := 19	); 
	PORT(
		clk          : IN  STD_LOGIC;                                 --system clock
		reset_n      : IN  STD_LOGIC;                                 --asynchronous reset
		enable       : IN  STD_LOGIC; 
		bypass_state : IN  STD_LOGIC; 								  --bypass state
		pwm_freq_bit : IN STD_LOGIC_VECTOR(bits_freq-1 DOWNTO 0);     --bit select frequency
		dead_time_bit: IN STD_LOGIC_VECTOR(bits_deadtime-1 DOWNTO 0); --bit select deadtime	
		duty_M1     : IN  STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0); 	  --duty cycle M3
		pwm_M1      : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);        --pwm outputs
		pwm_M2       : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0));      --pwm inverse outputs
END pwmbuck;

ARCHITECTURE rtl OF pwmbuck IS
	SIGNAL period : INTEGER RANGE 0 TO 1000;              --1000: 50MHz/50KHz                  
	TYPE counters IS ARRAY (0 TO phases-1) OF INTEGER RANGE 0 TO 1000 - 1; 
	SIGNAL count : counters := (OTHERS => 0);            
	SIGNAL half_duty_new : INTEGER RANGE 0 TO 1000/2 := 0;
	TYPE half_duties IS ARRAY (0 TO phases-1) OF INTEGER RANGE 0 TO 1000/2; 
	SIGNAL half_duty : half_duties := (OTHERS => 0); 
	SIGNAL pwm_freq :INTEGER RANGE 0 TO 250:=100;
	SIGNAL const_dead_time:INTEGER RANGE 0 TO 19:=15;
BEGIN
	PROCESS(clk, reset_n)
	BEGIN
		IF(reset_n = '0') THEN     	
			count <= (OTHERS => 0);    
			pwm_M1<= (OTHERS => '0');  
			pwm_M2 <= (OTHERS => '0'); 
			pwm_freq<=100;
			const_dead_time<=15;
		ELSIF(clk'EVENT AND clk = '1') THEN  
			IF (enable='1')THEN
			    --frequency selection
				CASE pwm_freq_bit IS
					WHEN "000" =>
						pwm_freq<=freq_default;
					WHEN "001" =>
						pwm_freq<=freq_1;
					WHEN "010" =>
						pwm_freq<=freq_2;
					WHEN "011" =>
						pwm_freq<=freq_3;
					WHEN "100" =>
						pwm_freq<=freq_4;
					WHEN "101" =>
						pwm_freq<=freq_5;
					WHEN "110" =>
						pwm_freq<=freq_6;
					WHEN "111" =>
						pwm_freq<=freq_7;
				END CASE;
				--deadtime selection
				CASE dead_time_bit IS
					WHEN "0000" =>
						const_dead_time<=deadtime_default;
					WHEN "0001" =>
						const_dead_time<=deadtime_1;
					WHEN "0010" =>
						const_dead_time<=deadtime_2;
					WHEN "0011" =>
						const_dead_time<=deadtime_3;
					WHEN "0100" =>
						const_dead_time<=deadtime_4;
					WHEN "0101" =>
						const_dead_time<=deadtime_5;
					WHEN "0110" =>
						const_dead_time<=deadtime_6;
					WHEN "0111" =>
						const_dead_time<=deadtime_7;
					WHEN "1000" =>
						const_dead_time<=deadtime_8;
					WHEN "1001" =>
						const_dead_time<=deadtime_9;
					WHEN "1010" =>
						const_dead_time<=deadtime_10;
					WHEN "1011" =>
						const_dead_time<=deadtime_11;
					WHEN "1100" =>
						const_dead_time<=deadtime_12;
					WHEN "1101" =>
						const_dead_time<=deadtime_13;
					WHEN "1110" =>
						const_dead_time<=deadtime_14;
					WHEN "1111" =>
						const_dead_time<=deadtime_15;
				END case;
				period<=sys_clk/(pwm_freq);
				IF (bypass_state='0')THEN
					half_duty_new <= conv_integer(duty_M1)*period/(2**bits_duty)/2;
					FOR i IN 0 to phases-1 LOOP                                   
						IF(count(0) = period - 1  - i*period/phases) THEN           
							count(i) <= 0;                                           
							half_duty(i) <= half_duty_new;                         
						ELSE                                                       
							count(i) <= count(i) + 1;                               
						END IF;
					END LOOP;
					FOR i IN 0 to phases-1 LOOP                                 
						IF (conv_integer(duty_M1)<=const_dead_time)THEN  
							pwm_M1(i) <= '0';
							pwm_M2(i) <= '1';
						ELSIF(conv_integer(duty_M1)>=4095-(const_dead_time))THEN  
							pwm_M1(i) <= '1'; 
							pwm_M2(i) <= '0'; 
						ELSE
							IF(count(i) = half_duty(i)+period/2) THEN                            
								pwm_M1(i) <= '0';                                                 
							ELSIF(count(i) = half_duty(i)+period/2+const_dead_time) THEN         
								pwm_M2(i) <= '1';                                                 
							ELSIF(count(i) = period-period/2 - half_duty(i)-const_dead_time) THEN
								pwm_M2(i) <= '0';                                                 
							ELSIF(count(i) = period -period/2- half_duty(i)) THEN                
								pwm_M1(i) <= '1';                                                 
							END IF;
						END IF;
					END LOOP;
				ELSE
					FOR i IN 0 to phases-1 LOOP
						pwm_M1(i) <= '0';
						pwm_M2(i) <= '0';
					END LOOP;
				END IF;
			END IF;
		END IF;
	END PROCESS;
END rtl;

