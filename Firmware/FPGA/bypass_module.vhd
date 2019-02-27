LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE IEEE.numeric_std.all;


ENTITY bypass_module IS
	GENERIC(
		overflow_timer:INTEGER:= 20250;-- 1'15"/(1/4KHz)
		bits_voltage : INTEGER := 16;  -- Duty cycle bit
		max_voltage :INTEGER :=65535); ---Maximum value 16 bit
   PORT(
		clk_dcdc,reset_n, enable: IN STD_LOGIC;
		 Vin: IN STD_LOGIC_VECTOR(bits_voltage-1 DOWNTO 0);
		 Vout: IN STD_LOGIC_VECTOR(bits_voltage-1 DOWNTO 0);
		 bypass: OUT STD_LOGIC);
END bypass_module;

ARCHITECTURE rtl OF bypass_module IS
	SIGNAL bypass_temp: STD_LOGIC:='0';
	SIGNAL timer: INTEGER RANGE 0 to overflow_timer+1:=0;
	SIGNAL B_min :INTEGER RANGE 0 to max_voltage:=0;
	SIGNAL B_max :INTEGER RANGE 0 to max_voltage:=0;
BEGIN
	PROCESS (clk_dcdc,reset_n)
	BEGIN
		IF (reset_n='0')THEN
			timer<=0;
			bypass_temp<='0';
			B_min<=0;
			B_max<=0;
		ELSIF(clk_dcdc'EVENT AND clk_dcdc = '1') THEN   
			IF (enable='1')THEN
				B_min<=(conv_integer(Vin)*95)/100;-- -5%
				B_max<=(conv_integer(Vin)*105)/100;-- +5% 
				IF (bypass_temp='0')THEN
					IF ((Vout>=conv_std_logic_vector(B_min,16)) AND (Vout<=conv_std_logic_vector(B_max,16)))THEN
						IF timer=(overflow_timer/5) THEN --15 sec
							bypass_temp<='1';
							timer<=timer+1;
						ELSE
							timer<=timer+1;
						END IF;
					ELSE
						timer<=0;
					END IF;
				ELSE
					IF timer=overflow_timer THEN--1 min
						bypass_temp<='0';
						timer<=0;		
					ELSE
						timer<=timer+1;
					END IF;
				END IF;
			END IF;
		END IF;
	END PROCESS;
	bypass<=bypass_temp;
END rtl;	