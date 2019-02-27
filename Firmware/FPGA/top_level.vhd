-- Copyright (C) 2016  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Intel and sold by Intel or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- PROGRAM		"Quartus Prime"
-- VERSION		"Version 16.1.0 Build 196 10/24/2016 SJ Lite Edition"
-- CREATED		"Tue Nov 06 16:34:28 2018"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY my_first_fpga IS 
	PORT
	(
		FORCE_BYPASS :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_PARAMETER :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_START_PARAMETER :  IN  STD_LOGIC;
		CLK_48M_FPGA :  IN  STD_LOGIC;
		RESET_FPGA :  IN  STD_LOGIC;
		ENABLE_FPGA :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_VIN :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_VOUT :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_START :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_CLK :  IN  STD_LOGIC;
		FPGA_SERIAL_IN_IIN :  IN  STD_LOGIC;
		FPGA_SERIAL_OUT_CLK :  OUT  STD_LOGIC;
		FPGA_SERIAL_OUT_DATA :  OUT  STD_LOGIC;
		FPGA_SERIAL_OUT_START :  OUT  STD_LOGIC;
		PWM_MBYPASS :  OUT  STD_LOGIC;
		MODE_BYPASS :  OUT  STD_LOGIC;
		MODE_BUCK :  OUT  STD_LOGIC;
		MODE_BOOST :  OUT  STD_LOGIC;
		PWM_M1 :  OUT  STD_LOGIC_VECTOR(1 DOWNTO 0);
		PWM_M2 :  OUT  STD_LOGIC_VECTOR(1 DOWNTO 0);
		PWM_M3 :  OUT  STD_LOGIC_VECTOR(1 DOWNTO 0);
		PWM_M4 :  OUT  STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END my_first_fpga;

ARCHITECTURE bdf_type OF my_first_fpga IS 

COMPONENT sipo_parameter
GENERIC (bits_deadtime : INTEGER;
			bits_duty : INTEGER;
			bits_freq : INTEGER
			);
	PORT(in_parameter : IN STD_LOGIC;
		 clk_micro : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 start_parameter : IN STD_LOGIC;
		 select_duty_ext : OUT STD_LOGIC;
		 select_bootstrap : OUT STD_LOGIC;
		 deadtime : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
		 duty_M1_EXT : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M3_EXT : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
		 frequenza : OUT STD_LOGIC_VECTOR(2 DOWNTO 0)
	);
END COMPONENT;

COMPONENT clk_debug
GENERIC (bits_duty : INTEGER;
			freq_debug : INTEGER;
			sys_clk : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 clk_debug : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT mux_pwm
GENERIC (phases : INTEGER
			);
	PORT(buck : IN STD_LOGIC;
		 boost : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 select_bootstrap : IN STD_LOGIC;
		 pwm_1_bootstrap : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_2_bootstrap : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M1 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M2 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M3 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M4 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M_1 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M_2 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M_3 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M_4 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END COMPONENT;

COMPONENT or_bypass
	PORT(bypass_ext : IN STD_LOGIC;
		 bypass_int : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 enable_DCDC : OUT STD_LOGIC;
		 bypass : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT mux_duty
GENERIC (bits_duty : INTEGER
			);
	PORT(select_duty_ext : IN STD_LOGIC;
		 duty_M1_ext : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M1_int : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M3_ext : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M3_int : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M1_out : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M3_out : OUT STD_LOGIC_VECTOR(11 DOWNTO 0)
	);
END COMPONENT;

COMPONENT controllo_pwm
GENERIC (phases : INTEGER
			);
	PORT(enable : IN STD_LOGIC;
		 pwm_M1 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M2 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M3 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M4 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M1 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M2 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M3 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 M4 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END COMPONENT;

COMPONENT clk_dcdc
GENERIC (bits_duty : INTEGER;
			freq_DCDC : INTEGER;
			sys_clk : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 clk_dcdc : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT mux_state
GENERIC (bits_duty : INTEGER
			);
	PORT(select_duty_ext : IN STD_LOGIC;
		 bypass : IN STD_LOGIC;
		 duty_M1_ext : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M1_int : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M3_ext : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 duty_M3_int : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 buck_mode : OUT STD_LOGIC;
		 boost_mode : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT sipo_16bit
	PORT(bit_Vin : IN STD_LOGIC;
		 bit_Vout : IN STD_LOGIC;
		 bit_Iin : IN STD_LOGIC;
		 clk_micro : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 start : IN STD_LOGIC;
		 Iin : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		 Vin : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		 Vout : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
	);
END COMPONENT;

COMPONENT pwm_bootstrap
GENERIC (bits_duty : INTEGER;
			const_dead_time : INTEGER;
			duty_1 : INTEGER;
			phases : INTEGER;
			pwm_freq : INTEGER;
			sys_clk : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 pwm_1 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_2 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END COMPONENT;

COMPONENT piso_out
GENERIC (bits_deadtime : INTEGER;
			bits_duty : INTEGER;
			bits_freq : INTEGER;
			data_1 : STD_LOGIC_VECTOR(3 DOWNTO 0);
			data_2 : STD_LOGIC_VECTOR(3 DOWNTO 0);
			data_3 : STD_LOGIC_VECTOR(3 DOWNTO 0)
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 bypass : IN STD_LOGIC;
		 buck : IN STD_LOGIC;
		 boost : IN STD_LOGIC;
		 VrefA0 : IN STD_LOGIC;
		 VrefA1 : IN STD_LOGIC;
		 dead_time_bit : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		 dutyM1 : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 dutyM3 : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 pwm_freq_bit : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 data_out : OUT STD_LOGIC;
		 start_piso_out : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT bypass_module
GENERIC (bits_voltage : INTEGER;
			max_voltage : INTEGER;
			overflow_timer : INTEGER
			);
	PORT(clk_dcdc : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 Vin : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
		 Vout : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
		 bypass : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT pwmbuck
GENERIC (bits_deadtime : INTEGER;
			bits_duty : INTEGER;
			bits_freq : INTEGER;
			deadtime_1 : INTEGER;
			deadtime_10 : INTEGER;
			deadtime_11 : INTEGER;
			deadtime_12 : INTEGER;
			deadtime_13 : INTEGER;
			deadtime_14 : INTEGER;
			deadtime_15 : INTEGER;
			deadtime_2 : INTEGER;
			deadtime_3 : INTEGER;
			deadtime_4 : INTEGER;
			deadtime_5 : INTEGER;
			deadtime_6 : INTEGER;
			deadtime_7 : INTEGER;
			deadtime_8 : INTEGER;
			deadtime_9 : INTEGER;
			deadtime_default : INTEGER;
			freq_1 : INTEGER;
			freq_2 : INTEGER;
			freq_3 : INTEGER;
			freq_4 : INTEGER;
			freq_5 : INTEGER;
			freq_6 : INTEGER;
			freq_7 : INTEGER;
			freq_default : INTEGER;
			phases : INTEGER;
			sys_clk : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 bypass_state : IN STD_LOGIC;
		 dead_time_bit : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		 duty_M1 : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 pwm_freq_bit : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 pwm_M1 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M2 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END COMPONENT;

COMPONENT mppt_po
GENERIC (AUMENTO_DUTY : STD_LOGIC_VECTOR(6 DOWNTO 0);
			bits_duty : INTEGER;
			DELAY_MPTT : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 Iin : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
		 Vin : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
		 Vref_A0 : OUT STD_LOGIC;
		 Vref_A1 : OUT STD_LOGIC;
		 dutyM1 : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
		 dutyM3 : OUT STD_LOGIC_VECTOR(11 DOWNTO 0)
	);
END COMPONENT;

COMPONENT pwmboost
GENERIC (bits_deadtime : INTEGER;
			bits_duty : INTEGER;
			bits_freq : INTEGER;
			deadtime_1 : INTEGER;
			deadtime_10 : INTEGER;
			deadtime_11 : INTEGER;
			deadtime_12 : INTEGER;
			deadtime_13 : INTEGER;
			deadtime_14 : INTEGER;
			deadtime_15 : INTEGER;
			deadtime_2 : INTEGER;
			deadtime_3 : INTEGER;
			deadtime_4 : INTEGER;
			deadtime_5 : INTEGER;
			deadtime_6 : INTEGER;
			deadtime_7 : INTEGER;
			deadtime_8 : INTEGER;
			deadtime_9 : INTEGER;
			deadtime_default : INTEGER;
			freq_1 : INTEGER;
			freq_2 : INTEGER;
			freq_3 : INTEGER;
			freq_4 : INTEGER;
			freq_5 : INTEGER;
			freq_6 : INTEGER;
			freq_7 : INTEGER;
			freq_default : INTEGER;
			phases : INTEGER;
			sys_clk : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 reset_n : IN STD_LOGIC;
		 enable : IN STD_LOGIC;
		 bypass_state : IN STD_LOGIC;
		 dead_time_bit : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		 duty_M3 : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
		 pwm_freq_bit : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		 pwm_M3 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		 pwm_M4 : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END COMPONENT;

SIGNAL	SYNTHESIZED_WIRE_51 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_52 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_3 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_4 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_5 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_6 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_7 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_8 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_9 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_53 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_54 :  STD_LOGIC_VECTOR(11 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_55 :  STD_LOGIC_VECTOR(11 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_56 :  STD_LOGIC_VECTOR(11 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_57 :  STD_LOGIC_VECTOR(11 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_15 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_16 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_17 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_18 :  STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_58 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_25 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_29 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_30 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_59 :  STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_60 :  STD_LOGIC_VECTOR(11 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_61 :  STD_LOGIC_VECTOR(11 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_62 :  STD_LOGIC_VECTOR(2 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_63 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_64 :  STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_37 :  STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_43 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_44 :  STD_LOGIC_VECTOR(15 DOWNTO 0);


BEGIN 
FPGA_SERIAL_OUT_CLK <= SYNTHESIZED_WIRE_25;
PWM_MBYPASS <= SYNTHESIZED_WIRE_58;
MODE_BYPASS <= SYNTHESIZED_WIRE_58;
MODE_BUCK <= SYNTHESIZED_WIRE_51;
MODE_BOOST <= SYNTHESIZED_WIRE_52;



b2v_inst : sipo_parameter
GENERIC MAP(bits_deadtime => 4,
			bits_duty => 12,
			bits_freq => 3
			)
PORT MAP(in_parameter => FPGA_SERIAL_IN_PARAMETER,
		 clk_micro => FPGA_SERIAL_IN_CLK,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 start_parameter => FPGA_SERIAL_IN_START_PARAMETER,
		 select_duty_ext => SYNTHESIZED_WIRE_53,
		 select_bootstrap => SYNTHESIZED_WIRE_2,
		 deadtime => SYNTHESIZED_WIRE_59,
		 duty_M1_EXT => SYNTHESIZED_WIRE_54,
		 duty_M3_EXT => SYNTHESIZED_WIRE_56,
		 frequenza => SYNTHESIZED_WIRE_62);


b2v_inst1 : clk_debug
GENERIC MAP(bits_duty => 12,
			freq_debug => 100,
			sys_clk => 48000000
			)
PORT MAP(clk => CLK_48M_FPGA,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 clk_debug => SYNTHESIZED_WIRE_25);


b2v_inst10 : mux_pwm
GENERIC MAP(phases => 2
			)
PORT MAP(buck => SYNTHESIZED_WIRE_51,
		 boost => SYNTHESIZED_WIRE_52,
		 enable => ENABLE_FPGA,
		 select_bootstrap => SYNTHESIZED_WIRE_2,
		 pwm_1_bootstrap => SYNTHESIZED_WIRE_3,
		 pwm_2_bootstrap => SYNTHESIZED_WIRE_4,
		 pwm_M1 => SYNTHESIZED_WIRE_5,
		 pwm_M2 => SYNTHESIZED_WIRE_6,
		 pwm_M3 => SYNTHESIZED_WIRE_7,
		 pwm_M4 => SYNTHESIZED_WIRE_8,
		 M_1 => SYNTHESIZED_WIRE_15,
		 M_2 => SYNTHESIZED_WIRE_16,
		 M_3 => SYNTHESIZED_WIRE_17,
		 M_4 => SYNTHESIZED_WIRE_18);


b2v_inst11 : or_bypass
PORT MAP(bypass_ext => FORCE_BYPASS,
		 bypass_int => SYNTHESIZED_WIRE_9,
		 enable => ENABLE_FPGA,
		 enable_DCDC => SYNTHESIZED_WIRE_43,
		 bypass => SYNTHESIZED_WIRE_58);


b2v_inst12 : mux_duty
GENERIC MAP(bits_duty => 12
			)
PORT MAP(select_duty_ext => SYNTHESIZED_WIRE_53,
		 duty_M1_ext => SYNTHESIZED_WIRE_54,
		 duty_M1_int => SYNTHESIZED_WIRE_55,
		 duty_M3_ext => SYNTHESIZED_WIRE_56,
		 duty_M3_int => SYNTHESIZED_WIRE_57,
		 duty_M1_out => SYNTHESIZED_WIRE_60,
		 duty_M3_out => SYNTHESIZED_WIRE_61);


b2v_inst13 : controllo_pwm
GENERIC MAP(phases => 2
			)
PORT MAP(enable => ENABLE_FPGA,
		 pwm_M1 => SYNTHESIZED_WIRE_15,
		 pwm_M2 => SYNTHESIZED_WIRE_16,
		 pwm_M3 => SYNTHESIZED_WIRE_17,
		 pwm_M4 => SYNTHESIZED_WIRE_18,
		 M1 => PWM_M1,
		 M2 => PWM_M2,
		 M3 => PWM_M3,
		 M4 => PWM_M4);


b2v_inst2 : clk_dcdc
GENERIC MAP(bits_duty => 12,
			freq_DCDC => 270,
			sys_clk => 48000000
			)
PORT MAP(clk => CLK_48M_FPGA,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 clk_dcdc => SYNTHESIZED_WIRE_63);


b2v_inst3 : mux_state
GENERIC MAP(bits_duty => 12
			)
PORT MAP(select_duty_ext => SYNTHESIZED_WIRE_53,
		 bypass => SYNTHESIZED_WIRE_58,
		 duty_M1_ext => SYNTHESIZED_WIRE_54,
		 duty_M1_int => SYNTHESIZED_WIRE_55,
		 duty_M3_ext => SYNTHESIZED_WIRE_56,
		 duty_M3_int => SYNTHESIZED_WIRE_57,
		 buck_mode => SYNTHESIZED_WIRE_51,
		 boost_mode => SYNTHESIZED_WIRE_52);


b2v_inst30 : sipo_16bit
PORT MAP(bit_Vin => FPGA_SERIAL_IN_VIN,
		 bit_Vout => FPGA_SERIAL_IN_VOUT,
		 bit_Iin => FPGA_SERIAL_IN_IIN,
		 clk_micro => FPGA_SERIAL_IN_CLK,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 start => FPGA_SERIAL_IN_START,
		 Iin => SYNTHESIZED_WIRE_44,
		 Vin => SYNTHESIZED_WIRE_64,
		 Vout => SYNTHESIZED_WIRE_37);


b2v_inst32 : pwm_bootstrap
GENERIC MAP(bits_duty => 14,
			const_dead_time => 8,
			duty_1 => 1,
			phases => 2,
			pwm_freq => 200,
			sys_clk => 48000000
			)
PORT MAP(clk => CLK_48M_FPGA,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 pwm_1 => SYNTHESIZED_WIRE_3,
		 pwm_2 => SYNTHESIZED_WIRE_4);


b2v_inst33 : piso_out
GENERIC MAP(bits_deadtime => 4,
			bits_duty => 12,
			bits_freq => 3,
			data_1 => "0001",
			data_2 => "0010",
			data_3 => "0100"
			)
PORT MAP(clk => SYNTHESIZED_WIRE_25,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 bypass => SYNTHESIZED_WIRE_58,
		 buck => SYNTHESIZED_WIRE_51,
		 boost => SYNTHESIZED_WIRE_52,
		 VrefA0 => SYNTHESIZED_WIRE_29,
		 VrefA1 => SYNTHESIZED_WIRE_30,
		 dead_time_bit => SYNTHESIZED_WIRE_59,
		 dutyM1 => SYNTHESIZED_WIRE_60,
		 dutyM3 => SYNTHESIZED_WIRE_61,
		 pwm_freq_bit => SYNTHESIZED_WIRE_62,
		 data_out => FPGA_SERIAL_OUT_DATA,
		 start_piso_out => FPGA_SERIAL_OUT_START);


b2v_inst5 : bypass_module
GENERIC MAP(bits_voltage => 16,
			max_voltage => 65535,
			overflow_timer => 20250
			)
PORT MAP(clk_dcdc => SYNTHESIZED_WIRE_63,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 Vin => SYNTHESIZED_WIRE_64,
		 Vout => SYNTHESIZED_WIRE_37,
		 bypass => SYNTHESIZED_WIRE_9);


b2v_inst6 : pwmbuck
GENERIC MAP(bits_deadtime => 4,
			bits_duty => 12,
			bits_freq => 3,
			deadtime_1 => 4,
			deadtime_10 => 13,
			deadtime_11 => 14,
			deadtime_12 => 16,
			deadtime_13 => 17,
			deadtime_14 => 18,
			deadtime_15 => 19,
			deadtime_2 => 5,
			deadtime_3 => 6,
			deadtime_4 => 7,
			deadtime_5 => 8,
			deadtime_6 => 9,
			deadtime_7 => 10,
			deadtime_8 => 11,
			deadtime_9 => 12,
			deadtime_default => 15,
			freq_1 => 80,
			freq_2 => 120,
			freq_3 => 150,
			freq_4 => 175,
			freq_5 => 200,
			freq_6 => 225,
			freq_7 => 250,
			freq_default => 100,
			phases => 2,
			sys_clk => 48000
			)
PORT MAP(clk => CLK_48M_FPGA,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 bypass_state => SYNTHESIZED_WIRE_58,
		 dead_time_bit => SYNTHESIZED_WIRE_59,
		 duty_M1 => SYNTHESIZED_WIRE_60,
		 pwm_freq_bit => SYNTHESIZED_WIRE_62,
		 pwm_M1 => SYNTHESIZED_WIRE_5,
		 pwm_M2 => SYNTHESIZED_WIRE_6);


b2v_inst7 : mppt_po
GENERIC MAP(AUMENTO_DUTY => "0010100",
			bits_duty => 12,
			DELAY_MPTT => 20
			)
PORT MAP(clk => SYNTHESIZED_WIRE_63,
		 reset_n => RESET_FPGA,
		 enable => SYNTHESIZED_WIRE_43,
		 Iin => SYNTHESIZED_WIRE_44,
		 Vin => SYNTHESIZED_WIRE_64,
		 Vref_A0 => SYNTHESIZED_WIRE_29,
		 Vref_A1 => SYNTHESIZED_WIRE_30,
		 dutyM1 => SYNTHESIZED_WIRE_55,
		 dutyM3 => SYNTHESIZED_WIRE_57);


b2v_inst8 : pwmboost
GENERIC MAP(bits_deadtime => 4,
			bits_duty => 12,
			bits_freq => 3,
			deadtime_1 => 4,
			deadtime_10 => 13,
			deadtime_11 => 14,
			deadtime_12 => 16,
			deadtime_13 => 17,
			deadtime_14 => 18,
			deadtime_15 => 19,
			deadtime_2 => 5,
			deadtime_3 => 6,
			deadtime_4 => 7,
			deadtime_5 => 8,
			deadtime_6 => 9,
			deadtime_7 => 10,
			deadtime_8 => 11,
			deadtime_9 => 12,
			deadtime_default => 15,
			freq_1 => 80,
			freq_2 => 120,
			freq_3 => 150,
			freq_4 => 175,
			freq_5 => 200,
			freq_6 => 225,
			freq_7 => 250,
			freq_default => 100,
			phases => 2,
			sys_clk => 48000
			)
PORT MAP(clk => CLK_48M_FPGA,
		 reset_n => RESET_FPGA,
		 enable => ENABLE_FPGA,
		 bypass_state => SYNTHESIZED_WIRE_58,
		 dead_time_bit => SYNTHESIZED_WIRE_59,
		 duty_M3 => SYNTHESIZED_WIRE_61,
		 pwm_freq_bit => SYNTHESIZED_WIRE_62,
		 pwm_M3 => SYNTHESIZED_WIRE_7,
		 pwm_M4 => SYNTHESIZED_WIRE_8);


END bdf_type;