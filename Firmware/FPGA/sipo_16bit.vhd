LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY sipo_16bit IS
	PORT(
		bit_Vin : IN STD_LOGIC;
		bit_Vout : IN STD_LOGIC;
		bit_Iin : IN STD_LOGIC;
		--bit_Iout : IN STD_LOGIC;
		clk_micro : IN STD_LOGIC;
		reset_n : IN STD_LOGIC;
		enable : IN STD_LOGIC;
		start : IN STD_LOGIC;
		--enable_piso : out STD_LOGIC;
		Vin: OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		Vout: OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		--Iout: OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
		Iin: OUT STD_LOGIC_VECTOR(15 DOWNTO 0));	
END sipo_16bit;

ARCHITECTURE rtl OF sipo_16bit IS
	SIGNAL d1_temp : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	SIGNAL d2_temp : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	SIGNAL d3_temp : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	--SIGNAL d4_temp : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	SIGNAL d1 : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	SIGNAL d2 : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	SIGNAL d3 : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	--SIGNAL d4 : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '0');
	SIGNAL count :INTEGER RANGE 0 TO 17:=0;
BEGIN
	sipo_pro : PROCESS (clk_micro,reset_n)
	BEGIN
		IF (reset_n='0') THEN
			d1_temp<=(OTHERS => '0');
			d2_temp<=(OTHERS => '0');
			d3_temp<=(OTHERS => '0');
			--d4_temp<=(OTHERS => '0');
			d1<=(OTHERS => '0');
			d2<=(OTHERS => '0');
			d3<=(OTHERS => '0');
			--d4<=(OTHERS => '0');
			count<=0;
		ELSIF(clk_micro'EVENT AND clk_micro = '1') THEN
			IF (enable='1') THEN
				IF ((start='1'))THEN
					IF count=16 THEN
						d1<=d1_temp;
						d2<=d2_temp;
						d3<=d3_temp;
						--d4<=d4_temp;
						count<=0;
					ELSE
						d1_temp(15 DOWNTO 1) <= d1_temp(14 DOWNTO 0);
						d1_temp(0) <= bit_Vin;
						d2_temp(15 DOWNTO 1) <= d2_temp(14 DOWNTO 0);
						d2_temp(0) <= bit_Vout;
						d3_temp(15 DOWNTO 1) <= d3_temp(14 DOWNTO 0);
						d3_temp(0) <= bit_Iin;
						--d4_temp(15 DOWNTO 1) <= d4_temp(14 DOWNTO 0);
						--d4_temp(0) <= bit_Iout;
						count<=count+1;
					END IF;
				ELSE--Allows to avoid incorrect acquisitions
					d1_temp<=(OTHERS => '0');
					d2_temp<=(OTHERS => '0');
					d3_temp<=(OTHERS => '0');
					--d4_temp<=(OTHERS => '0');
					count<=0;
				END IF;
			END IF;
		END IF;
	END PROCESS sipo_pro;
	Vin <=d1;
	Vout <=d2;
	Iin <=d3;
	--Iout <=d4;
END rtl;
