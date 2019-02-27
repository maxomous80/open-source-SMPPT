--------------------------------------------------------------------------------
--
--Or between external bypass and calculated bypass
--enabled bypass condition
--    
--------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee. std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE IEEE.numeric_std.all;


ENTITY or_bypass IS
	PORT(
		bypass_ext: IN STD_LOGIC;	--internal bypass			
		bypass_int: IN STD_LOGIC;	--external bypass 
		enable: IN STD_LOGIC;
		enable_DCDC:OUT STD_LOGIC;
		bypass: OUT STD_LOGIC);		--bypass state
END or_bypass;

ARCHITECTURE rtl OF or_bypass IS

BEGIN
	PROCESS (bypass_int,bypass_ext,enable)
	BEGIN
		bypass<=bypass_int OR bypass_ext;
		enable_DCDC<=enable AND (NOT(bypass_int OR bypass_ext));
	END PROCESS;
END rtl;