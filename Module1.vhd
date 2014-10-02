LIBRARY ieee;

USE ieee.std_logic_1164.all; 

USE ieee.std_logic_arith.all; 

USE ieee.std_logic_unsigned.all; 

ENTITY Module1 IS

   PORT (

      SW : IN STD_LOGIC_VECTOR(7 DOWNTO 0);

      KEY : IN STD_LOGIC_VECTOR(3 DOWNTO 0);

      CLOCK_50 : IN STD_LOGIC;

      LEDG : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);

      DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;

      DRAM_ADDR : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);

      DRAM_BA_0, DRAM_BA_1 : BUFFER STD_LOGIC;

      DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
 
      DRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);

      DRAM_UDQM, DRAM_LDQM : BUFFER STD_LOGIC ;
		
		VGA_R:	OUT std_logic_vector (9	downto 0);	
		
		VGA_G: OUT	std_logic_vector(9 downto 0);	
		
		VGA_B:	OUT	std_logic_vector(9	downto	0);	

		VGA_CLK:		OUT	std_logic;
		
		VGA_BLANK:	OUT		std_logic;
		
		VGA_HS:	OUT	std_logic;
		
		VGA_VS:	OUT	std_logic;
		
		VGA_SYNC: OUT		std_logic;
		
		SRAM_DQ	:	INOUT	STD_LOGIC_VECTOR(15	downto	0);
		
		SRAM_ADDR	:	OUT	STD_LOGIC_VECTOR(17	downto	0);
		
		SRAM_LB_N	:	OUT	STD_LOGIC;
		
		SRAM_UB_N	:	OUT	STD_LOGIC;
		
		SRAM_CE_N	:	OUT	STD_LOGIC;
		
		SRAM_OE_N	:	OUT	STD_LOGIC;
		
		SRAM_WE_N	:	OUT	STD_LOGIC;
		
		sd_cmd : inout std_logic;
		
		sd_dat : inout std_logic;
		
		sd_dat3 : inout std_logic;
		
		sd_clk : out std_logic);

   END Module1;



ARCHITECTURE Structure OF Module1 IS

   COMPONENT nios_system PORT (

      clk_clk : IN STD_LOGIC;

      reset_reset_n : IN STD_LOGIC;

      sdram_clk_clk : OUT STD_LOGIC;

      leds_export : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
 
      switches_export : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
		
		pushbutton_export : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
 
      sdram_wire_addr : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
 
      sdram_wire_ba : BUFFER STD_LOGIC_VECTOR(1 DOWNTO 0);
 
      sdram_wire_cas_n : OUT STD_LOGIC;

      sdram_wire_cke : OUT STD_LOGIC;

      sdram_wire_cs_n : OUT STD_LOGIC;

      sdram_wire_dq : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
 
      sdram_wire_dqm : BUFFER STD_LOGIC_VECTOR(1 DOWNTO 0);
 
      sdram_wire_ras_n : OUT STD_LOGIC;

      sdram_wire_we_n : OUT STD_LOGIC ;
		
		vga_controller_R:	OUT	std_logic_vector(9	downto	0);	
		
		vga_controller_G: OUT	std_logic_vector(9	downto	0);	
		
		vga_controller_B:	OUT	std_logic_vector(9	downto	0);	

		vga_controller_CLK:		OUT	std_logic;
		
		vga_controller_BLANK:	OUT		std_logic;
		
		vga_controller_HS:	OUT	std_logic;
		
		vga_controller_VS:	OUT	std_logic;
		
		vga_controller_SYNC:	OUT	std_logic;
		
		pixel_buffers_DQ	:	INOUT	STD_LOGIC_VECTOR(15	downto	0);
		
		pixel_buffers_ADDR	:	OUT	STD_LOGIC_VECTOR(17	downto	0);
		
		pixel_buffers_LB_N	:	OUT	STD_LOGIC;
		
		pixel_buffers_UB_N	:	OUT	STD_LOGIC;
		
		pixel_buffers_CE_N	:	OUT	STD_LOGIC;
		
		pixel_buffers_OE_N	:	OUT	STD_LOGIC;
		
		pixel_buffers_WE_N	:	OUT	STD_LOGIC;
		
		sd_data_b_SD_cmd : inout std_logic;
		
		sd_data_b_SD_dat : inout std_logic;
		
		sd_data_b_SD_dat3 : inout std_logic;
		
		sd_data_o_SD_clock : out std_logic);
	
 
   END COMPONENT;


   SIGNAL DQM : STD_LOGIC_VECTOR(1 DOWNTO 0);

   SIGNAL BA : STD_LOGIC_VECTOR(1 DOWNTO 0);


   BEGIN

      DRAM_BA_0 <= BA(0);
 
      DRAM_BA_1 <= BA(1);
 
      DRAM_UDQM <= DQM(1);
 
      DRAM_LDQM <= DQM(0);

      NiosII: nios_system PORT MAP (

      clk_clk => CLOCK_50,

      reset_reset_n => KEY(0),

      sdram_clk_clk => DRAM_CLK,
 
      leds_export => LEDG,

      switches_export => SW,
		
		pushbutton_export => KEY,
 
      sdram_wire_addr => DRAM_ADDR,
 
      sdram_wire_ba => BA,
 
      sdram_wire_cas_n => DRAM_CAS_N,
 
      sdram_wire_cke => DRAM_CKE,
 
      sdram_wire_cs_n => DRAM_CS_N,
 
      sdram_wire_dq => DRAM_DQ,
 
      sdram_wire_dqm => DQM,
 
      sdram_wire_ras_n => DRAM_RAS_N,
 
      sdram_wire_we_n => DRAM_WE_N ,
			
		vga_controller_CLK	=>	VGA_CLK,	
			
		vga_controller_HS	=>	VGA_HS,	
			
		vga_controller_VS	=>	VGA_VS,	
			
		vga_controller_BLANK	=>	VGA_BLANK,	
			
		vga_controller_SYNC	=>	VGA_SYNC,	
			
		vga_controller_R	=>	VGA_R,	
			
		vga_controller_G	=>	VGA_G,	
			
		vga_controller_B	=>	VGA_B,
			
		pixel_buffers_DQ	=>	SRAM_DQ,
			
		pixel_buffers_ADDR	=>	SRAM_ADDR,
			
		pixel_buffers_LB_N	=>	SRAM_LB_N,
			
		pixel_buffers_UB_N	=>	SRAM_UB_N,	
			
		pixel_buffers_CE_N	=>	SRAM_CE_N,
			
		pixel_buffers_OE_N	=>	SRAM_OE_N,
			
		pixel_buffers_WE_N	=>	SRAM_WE_N,
		
		sd_data_b_SD_cmd => sd_cmd,
		
		sd_data_b_SD_dat => sd_dat,
		
		sd_data_b_SD_dat3 => sd_dat3,
		
		sd_data_o_SD_clock => sd_clk);

   END Structure;