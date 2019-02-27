

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY pwm_bootstrap IS
  GENERIC(
      sys_clk         : INTEGER := 48_000_000; --system clock frequency in Hz
      pwm_freq        : INTEGER := 200;        --PWM switching frequency in Hz
	const_dead_time : INTEGER := 8;            --clock cycle PWM dead-time
      bits_duty : INTEGER := 14;               --bits of resolution setting the duty cycle
	  duty_1 :integer :=1;                     --minimum value
      phases          : INTEGER := 2);         --number of output pwms and phases
  PORT(
      clk       : IN  STD_LOGIC;                          --system clock
      reset_n,enable   : IN  STD_LOGIC;                   --asynchronous reset
      pwm_1  : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);   --pwm outputs
      pwm_2 : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0));   --pwm inverse outputs
END pwm_bootstrap;

ARCHITECTURE rtl OF pwm_bootstrap IS
  CONSTANT  period     :  INTEGER := sys_clk/pwm_freq;                     
  TYPE counters IS ARRAY (0 TO phases-1) OF INTEGER RANGE 0 TO period - 1; 
  SIGNAL  count        :  counters := (OTHERS => 0);                       
  SIGNAL   half_duty_new  :  INTEGER RANGE 0 TO period/2 := 0;             
  TYPE half_duties IS ARRAY (0 TO phases-1) OF INTEGER RANGE 0 TO period/2; 
  SIGNAL  half_duty    :  half_duties := (OTHERS => 0);                    
BEGIN
  PROCESS(clk, reset_n,enable)
  BEGIN
    IF(reset_n = '0') THEN                     
      count <= (OTHERS => 0);                   
      pwm_1<= (OTHERS => '0');                
      pwm_2 <= (OTHERS => '0');                 
    ELSIF(clk'EVENT AND clk = '1'AND enable='1') THEN  
		half_duty_new <= duty_1*period/(2**bits_duty)/2; 
			FOR i IN 0 to phases-1 LOOP                        
			  IF(count(0) = period - 1  - i*period/phases) THEN 
				 count(i) <= 0;                  
				 half_duty(i) <= half_duty_new;  
			  ELSE                              
				 count(i) <= count(i) + 1;       
			  END IF;
			END LOOP;
			FOR i IN 0 to phases-1 LOOP                                       
				  IF(count(i) = half_duty(i)+period/2) THEN                  
					 pwm_1(i) <= '0';                                           
				  ELSIF(count(i) = half_duty(i)+period/2+const_dead_time) THEN 
					 pwm_2(i) <= '1';                                                   
				  ELSIF(count(i) = period-period/2 - half_duty(i)-const_dead_time) THEN
					 pwm_2(i) <= '0';                                                   
				  ELSIF(count(i) = period -period/2- half_duty(i)) THEN               
					 pwm_1(i) <= '1';                                                   
				  END IF;
			END LOOP;
    END IF;
  END PROCESS;
END rtl;


