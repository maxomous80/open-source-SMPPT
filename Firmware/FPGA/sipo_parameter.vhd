LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY sipo_parameter IS
	GENERIC(
		bits_duty : INTEGER := 12;      --bits of resolution setting the duty cycle
		bits_freq : INTEGER := 3;       --bits of resolution setting the frequency
		bits_deadtime : INTEGER := 4);  --bits of resolution setting the deadtime   
	port(
		in_parameter : IN STD_LOGIC;
		clk_micro : IN STD_LOGIC;
		reset_n : IN STD_LOGIC;
		enable : IN STD_LOGIC;
		start_parameter : IN STD_LOGIC;
		frequenza: OUT STD_LOGIC_VECTOR(bits_freq-1 DOWNTO 0);
		deadtime: OUT STD_LOGIC_VECTOR(bits_deadtime-1 DOWNTO 0);
		duty_M1_EXT: OUT STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);
		duty_M3_EXT: OUT STD_LOGIC_VECTOR(bits_duty-1 DOWNTO 0);
		select_duty_ext : OUT STD_LOGIC;
		select_bootstrap: OUT STD_LOGIC);
END sipo_parameter;

ARCHITECTURE rtl OF sipo_parameter IS
	SIGNAL data_temp : std_logic_vector(32 DOWNTO 0) := (OTHERS => '0');
	SIGNAL dm1 : std_logic_vector(bits_duty-1 DOWNTO 0) := (OTHERS => '0'); --duty cycle M1
	SIGNAL dm3 : std_logic_vector(bits_duty-1 DOWNTO 0) := (OTHERS => '0'); --duty cycle M1m3
	SIGNAL freq_temp : std_logic_vector(bits_freq-1 DOWNTO 0) := (OTHERS => '0');
	SIGNAL deadtime_temp : std_logic_vector(bits_deadtime-1 DOWNTO 0) := (OTHERS => '0');
	SIGNAL count :integer RANGE 0 TO 34:=0;-- 33bit+1
	SIGNAL select_duty_temp: std_logic:='0';
	SIGNAL select_bootstrap_temp: std_logic:='0';	
BEGIN
	sipo_par_pro : PROCESS (clk_micro,reset_n)
	BEGIN
		IF(reset_n='0') THEN
			data_temp<=(OTHERS => '0');
			dm1<=(OTHERS => '0');
			dm3<=(OTHERS => '0');
			deadtime_temp<=(OTHERS => '0');
			freq_temp<=(OTHERS => '0');
			select_duty_temp<='0';
			select_bootstrap_temp<='0';
			count<=0;
		ELSIF(clk_micro'EVENT AND clk_micro = '1') THEN    
			IF (enable='1')THEN
				IF ((start_parameter='1'))THEN
					IF count=33 THEN
						dm1<=data_temp(32 DOWNTO 21);
						dm3<=data_temp(20 DOWNTO 9);
						freq_temp<=data_temp(8 DOWNTO 6);
						deadtime_temp<=data_temp(5 DOWNTO 2);
						select_duty_temp<= data_temp(1);
						select_bootstrap_temp<= data_temp(0);
						count<=0;
					ELSE
						data_temp(32 DOWNTO 1) <= data_temp(31 DOWNTO 0);
						data_temp(0) <= in_parameter;
						count<=count+1;
					END IF;
				ELSE --Allows to avoid incorrect acquisitions
					data_temp<=(OTHERS => '0');
					count<=0;
				END IF;
			END IF;
		END IF;
	END process sipo_par_pro;
	select_bootstrap <=select_bootstrap_temp;
	select_duty_ext <=select_duty_temp;
	duty_M1_EXT<=dm1;
	duty_M3_EXT<=dm3;
	deadtime<=deadtime_temp;
	frequenza<=freq_temp;
END rtl;
