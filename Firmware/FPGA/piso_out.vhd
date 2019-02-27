library IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY piso_out IS
	GENERIC(
		bits_duty : INTEGER := 12;      --bits of resolution setting the duty cycle
		bits_freq : INTEGER := 3;       --bits of resolution setting the duty cycle
		bits_deadtime : INTEGER := 4;	--bits of resolution setting the duty cycle
		data_1: STD_LOGIC_VECTOR(3 DOWNTO 0):="0001";
		data_2: STD_LOGIC_VECTOR(3 DOWNTO 0):="0010";
		data_3: STD_LOGIC_VECTOR(3 DOWNTO 0):="0100");  
   PORT(
		clk: IN STD_LOGIC;
		reset_n : IN STD_LOGIC;
		enable : IN STD_LOGIC;
		bypass,buck,boost,VrefA0,VrefA1 : IN STD_LOGIC;
		dutyM1 : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);
		dutyM3 : IN STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);
		pwm_freq_bit		:IN STD_LOGIC_VECTOR(bits_freq-1 DOWNTO 0);  --PWM switching frequency in Hz
		dead_time_bit :IN STD_LOGIC_VECTOR(bits_deadtime-1 DOWNTO 0);    --deadtime	
		data_out: OUT STD_LOGIC;
		start_piso_out: OUT std_logic);
END piso_out;

ARCHITECTURE rtl OF piso_out IS
	SIGNAL temp_data1 : std_logic_vector (15 DOWNTO 0):=(OTHERS=>'0');
	SIGNAL temp_data2 : std_logic_vector (15 DOWNTO 0):=(OTHERS=>'0');
	SIGNAL temp_data3 : std_logic_vector (15 DOWNTO 0):=(OTHERS=>'0');
	SIGNAL count: integer RANGE 0 TO 50:=0;
	SIGNAL start_piso_temp :std_logic:='0';
	SIGNAL data_t : std_logic:='0';
BEGIN	
	piso_o : PROCESS (clk,reset_n) IS
   BEGIN
		IF(reset_n='0') THEN
			temp_data1 <= (OTHERS=>'0');
			temp_data2 <= (OTHERS=>'0');
			temp_data3 <= (OTHERS=>'0');
			count<=0;
			start_piso_temp<='0';
			data_t<='0';
       ELSIF (rising_edge (clk)) THEN
			IF(enable='1') THEN
				IF (count=0)THEN
		  			count<=count+1;
					data_t<=data_1(3); 
					IF(bypass='0')THEN
						temp_data1 <= data_1 & dutyM1;
						temp_data2 <= data_2 & dutyM3;
					ELSE
						temp_data1 <= data_1 & "000000000000";
						temp_data2 <= data_2 & "000000000000";
					END IF;
					temp_data3 <= data_3 & dead_time_bit & pwm_freq_bit & VrefA0 & VrefA1 & buck&  boost & bypass;
					start_piso_temp<='1';
				ELSE
					IF (count>=1 AND count<=15)THEN
						count<=count+1;
						data_t<=temp_data1(15-count);--from msb to lsb
					ELSIF(count=16) THEN 
						count<=count+1;
						start_piso_temp<='0';
					ELSIF(count=17) THEN
						count<=count+1;
						start_piso_temp<='1';
						data_t<=temp_data2(32-count);
					ELSIF(count>=18 AND count<=32) THEN
						count<=count+1;
						data_t<=temp_data2(32-count);--from msb to lsb
					ELSIF(count=33) THEN
						count<=count+1;
						start_piso_temp<='0';
					ELSIF(count=34) THEN
						count<=count+1;
						start_piso_temp<='1';
						data_t<=temp_data3(49-count);						
					ELSIF(count>=35 AND count<=49) THEN
						count<=count+1;
						data_t<=temp_data3(49-count);--from msb to lsb
					ELSIF(count=50) THEN
						count<=0;
						start_piso_temp<='0';
					END IF;
				END IF;
			END IF;
		END IF;
	END PROCESS piso_o;
	data_out<= data_t;
	start_piso_out<=NOT(start_piso_temp);
END rtl;