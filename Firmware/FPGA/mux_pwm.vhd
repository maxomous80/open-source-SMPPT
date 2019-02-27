LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE IEEE.numeric_std.all;


entity mux_pwm is
		GENERIC(
	  phases          : INTEGER := 2);  --number of output pwms and phases
     port(
		buck: in STD_LOGIC; 
		boost: in STD_LOGIC; 
		enable: in STD_LOGIC; 
		pwm_M1  : in STD_LOGIC_VECTOR(phases-1 DOWNTO 0);       
		pwm_M2 : in STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		pwm_M3  : in STD_LOGIC_VECTOR(phases-1 DOWNTO 0);          
		pwm_M4 : in STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
        pwm_1_bootstrap  : in STD_LOGIC_VECTOR(phases-1 DOWNTO 0); --pwm dc dc bootstrap
		pwm_2_bootstrap  : in STD_LOGIC_VECTOR(phases-1 DOWNTO 0); --pwm dc dc bootstrap
		M_1  : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);         
		M_2 : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);         
	    M_3  : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);          
		M_4 : OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0);
		select_bootstrap: in STD_LOGIC);         
		 
	
end mux_pwm;

architecture rtl of mux_pwm is
BEGIN
  PROCESS(enable)
  BEGIN 
    IF (enable='1')THEN
		CASE select_bootstrap IS
			WHEN '1'=>
				FOR i IN 0 to phases-1 LOOP     
					IF(buck='1' and boost='0')THEN
						M_1(i)<=pwm_M1(i);
						M_2(i)<=pwm_M2(i);
						M_3(i)<=pwm_1_bootstrap(i);
						M_4(i)<=pwm_2_bootstrap(i);
					ELSIF(buck='0' and boost='1')THEN
						M_1(i)<=pwm_2_bootstrap(i);
						M_2(i)<=pwm_1_bootstrap(i);
						M_3(i)<=pwm_M3(i);
						M_4(i)<=pwm_M4(i);
					ELSE
						M_1(i)<=pwm_M1(i);
						M_2(i)<=pwm_M2(i);
						M_3(i)<=pwm_M3(i);
						M_4(i)<=pwm_M4(i);							
					END IF;
				END LOOP;
			WHEN '0'=>
				FOR i IN 0 to phases-1 LOOP     
						M_1(i)<=pwm_M1(i);
						M_2(i)<=pwm_M2(i);
						M_3(i)<=pwm_M3(i);
						M_4(i)<=pwm_M4(i);							
				END LOOP;
			END CASE;
		END IF;
	END PROCESS;
END rtl;		