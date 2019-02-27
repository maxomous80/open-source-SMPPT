LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE IEEE.numeric_std.all;


ENTITY controllo_PWM IS
	GENERIC(
		phases          : INTEGER := 2); --number of output pwms and phases
	PORT(
		pwm_M1: IN STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		pwm_M2: IN STD_LOGIC_VECTOR(phases-1 DOWNTO 0);
		pwm_M3: IN STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		pwm_M4: IN STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		enable: IN STD_LOGIC; 
		M1: OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		M2: OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		M3: OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0); 
		M4: OUT STD_LOGIC_VECTOR(phases-1 DOWNTO 0));
END controllo_PWM;

ARCHITECTURE rtl OF controllo_PWM IS
BEGIN
	PROCESS(pwm_M1,pwm_M2,pwm_M3,pwm_M4,enable)
	BEGIN 
		IF (enable='1')THEN
			FOR i IN 0 to phases-1 LOOP      
				IF (pwm_M1(i)='1'AND pwm_M2(i)='1')THEN --if the pwms are both high, both are set to zero
					M1(i)<='0';
					M2(i)<='0';
				ELSE
					M1(i)<=pwm_M1(i);
					M2(i)<=pwm_M2(i);
				END IF;
				IF (pwm_M3(i)='1'AND pwm_M4(i)='1')THEN--if the pwms are both high, both are set to zero
					M3(i)<='0';
					M4(i)<='0';
				ELSE
					M3(i)<=pwm_M3(i);
					M4(i)<=pwm_M4(i);
				END IF;
			END LOOP;
		ELSE
			FOR i IN 0 to phases-1 LOOP 
				M1(i)<='0';
				M2(i)<='0';	
				M3(i)<='0';
				M4(i)<='0';
			END LOOP;
		END IF;		
	END PROCESS;
END rtl;		