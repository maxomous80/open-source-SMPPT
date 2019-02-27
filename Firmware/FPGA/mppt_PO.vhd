LIBRARY ieee;
USE ieee. std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee. std_logic_unsigned.all;

ENTITY mppt_PO IS
	GENERIC(
		DELAY_MPTT: integer :=20; --Duty cycle delay
		bits_duty : INTEGER := 12; 
		AUMENTO_DUTY: std_logic_vector(6 DOWNTO 0):="0010100"); -- 20 //0.5%
	port ( 	
		Vin : IN std_logic_vector(15 DOWNTO 0);--Input Voltage
		Iin : IN std_logic_vector(15 DOWNTO 0);--Input Current
		clk,reset_n,enable: IN std_logic;
		dutyM1: OUT STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);	--Duty cycle M1 MOSFET
		dutyM3: OUT STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);	--Duty cycle M1 MOSFE
		Vref_A0: OUT STD_LOGIC;-- A0A1: 00	Vref<=Vref_min; 01 Vref<Vref_pre; 10 Vref>Vref_pre; 11 Vref>=Vref_max 
		Vref_A1: OUT STD_LOGIC);
END mppt_PO;

architecture rtl of mppt_PO is
SIGNAL Vin_prec: std_logic_vector(15 DOWNTO 0):= (OTHERS => '0');  
SIGNAL Pin_prec: std_logic_vector(31 DOWNTO 0):= (OTHERS => '0');  
SIGNAL Pin: std_logic_vector(31 DOWNTO 0):= (OTHERS => '0');  
SIGNAL state_DCDC :std_logic:= '1';--true buck, false boost
SIGNAL dutyM1_temp : std_logic_vector(bits_duty-1 DOWNTO 0):="100000000000";
SIGNAL dutyM3_temp : std_logic_vector(bits_duty-1 DOWNTO 0):=(OTHERS => '0');
SIGNAL num_cicli: integer RANGE 0 TO DELAY_MPTT+1;
SIGNAL Vref_A0_temp: STD_LOGIC:='0';
SIGNAL Vref_A1_temp: STD_LOGIC:='0';

BEGIN
   MPPT : PROCESS(clk,reset_n)
	BEGIN
	IF (reset_n = '0')  THEN
		Vin_prec <= (OTHERS => '0');
		Pin_prec <= (OTHERS => '0'); 
		dutyM1_temp <= "100000000000";
		dutyM3_temp <= (OTHERS => '0'); 
		Pin <= (OTHERS => '0');
		Vref_A0_temp<='0';
		Vref_A1_temp<='0';
		num_cicli<=0;
		state_DCDC<='1';
				
	ELSIF(clk'event AND clk = '1') THEN 
		IF(enable='1')THEN 
			num_cicli<=num_cicli+1;
			Pin <= Vin*Iin;  
			IF(num_cicli = DELAY_MPTT) THEN
            num_cicli<=0;
				IF(state_DCDC='1') THEN
			   --P&O algorithm buck converter
					IF((Pin>Pin_prec AND Vin>Vin_prec)OR(Pin<Pin_prec AND Vin<Vin_prec))THEN
						IF((dutyM1_temp-("00000" & AUMENTO_DUTY))<"000001111000")THEN--120 Min value
							dutyM1_temp<="000001111000";--120
							dutyM3_temp<=(OTHERS => '0');
							state_DCDC<='1';
						ELSIF ((dutyM1_temp-("00000" & AUMENTO_DUTY))>"111110100000") THEN--4000 Max value
							dutyM1_temp<="111111111111";
							dutyM3_temp<="000011001000";--200
							state_DCDC<='0';
						ELSE
							dutyM1_temp<=dutyM1_temp-("00000" & AUMENTO_DUTY);
							dutyM3_temp<=(OTHERS => '0');
							Vref_A0_temp<='1';
							Vref_A1_temp<='0';
							state_DCDC<='1';
						END IF;	
					ELSE
						IF((dutyM1_temp+("00000" & AUMENTO_DUTY))<"000001111000")THEN--120
							dutyM1_temp<="000001111000";--120
							dutyM3_temp<=(OTHERS => '0');
							state_DCDC<='1';
						ELSIF ((dutyM1_temp+("00000" & AUMENTO_DUTY))>"111110100000") THEN--4000
							dutyM1_temp<="111111111111";
							dutyM3_temp<="000011001000";--120
							state_DCDC<='0';
						ELSE
							dutyM1_temp<=dutyM1_temp+("00000" & AUMENTO_DUTY);
							dutyM3_temp<=(OTHERS => '0');
							Vref_A0_temp<='0';
							Vref_A1_temp<='1';
							state_DCDC<='1';
						END IF;
					END IF;
				ELSIF(state_DCDC='0')THEN
            --P&O algorithm boost converter
               IF((Pin>Pin_prec AND Vin>Vin_prec)OR(Pin<Pin_prec AND Vin<Vin_prec))THEN
						--MIN-MAX control
						IF ((dutyM3_temp-("00000" & AUMENTO_DUTY))<"000001111000") THEN--120
							dutyM1_temp<="111110100000"; 
							dutyM3_temp<=(OTHERS =>'0');
							state_DCDC<='1';
						ELSIF ((dutyM3_temp-("00000" & AUMENTO_DUTY))>"111110100000") THEN--4000
							dutyM1_temp<="111111111111";--4095
							dutyM3_temp<="111110100000";--4000
							state_DCDC<='0';
						ELSE
							dutyM3_temp<=dutyM3_temp-("00000" & AUMENTO_DUTY);
							dutyM1_temp<="111111111111";--4095
							Vref_A0_temp<='1';
							Vref_A1_temp<='0';	
							state_DCDC<='0';
						END IF; 
               ELSE 
						--MIN-MAX control
						IF ((dutyM3_temp-("00000" & AUMENTO_DUTY))<"000001111000") THEN--120
							dutyM1_temp<="111110100000"; 
							dutyM3_temp<=(OTHERS =>'0');
							state_DCDC<='1';
						ELSIF ((dutyM3_temp-("00000" & AUMENTO_DUTY))>"111110100000") THEN--4000
							dutyM1_temp<="111111111111";--4095
							dutyM3_temp<="111110100000";--4000
							state_DCDC<='0';
						ELSE
							dutyM3_temp<=dutyM3_temp+("00000" & AUMENTO_DUTY);
							dutyM1_temp<="111111111111";
							Vref_A0_temp<='0';
							Vref_A1_temp<='1';
							state_DCDC<='0';
						END IF; 
					END IF;		
				END IF;
            Pin_prec<=Pin; 
			Vin_prec<=Vin;
			END IF;
		END IF; 
	END IF;
	END PROCESS MPPT;
	Vref_A0<=Vref_A0_temp;
	Vref_A1<=Vref_A1_temp;
	dutyM1<=dutyM1_temp;
	dutyM3<=dutyM3_temp;
END rtl;

