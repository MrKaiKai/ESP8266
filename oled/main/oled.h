
#ifndef __OLED_H
#define __OLED_H
#include "stdlib.h"	    	
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "driver/i2c.h"
#include "myiic.h"

//OLED
#define I2C_OLED_MASTER_NUM             I2C_EXAMPLE_MASTER_NUM        /*!< I2C port number for master dev */
#define OLED_WRITE_ADDR    0x78
#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 64
#define WRITE_CMD      			 0X00
#define WRITE_DATA     			 0X40

#define TURN_OFF_CMD             0xAE                     //--turn off oled panel
#define SET1_LOW_COL_ADDR_CMD    0x00                     //---set low column address
#define SET2_HI_COL_ADDR_CMD     0x10                     //---set high column address
#define SET3_START_LINE_CMD      0x40                     //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
#define SET4_CONTR_REG           0x81                     //--set contrast control register
#define SET5_OUT_CURR            0xff                      // Set SEG Output Current Brightness
#define SET6_SEG_MAPPING         0xA1                     //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
#define SET7_SCAN_DIR            0xC8                     //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
#define SET8_NORMAL_DIS          0xA6                     //--set normal display
#define SET9_RATIO               0xA8                     //--set multiplex ratio(1 to 64)
#define SET10_DUTY               0x3f                     //--1/64 duty
#define SET11_DIS_OFFSET         0xD3                     //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
#define SET12_NO_OFFSET          0x00                     //-not offset
#define SET13_CLOCK_DIV          0xd5                     //--set display clock divide ratio/oscillator frequency
#define SET14_CLOCK_FC           0x80                     //--set divide ratio, Set Clock as 100 Frames/Sec
#define SET15_PRE_CHARGE         0xD9                     //--set pre-charge period
#define SET16_PER_CHARGE_15      0xF1                     //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
#define SET17_COM_PIN_CONF       0xDA                     //--set com pins hardware configuration
#define SET18_STG1               0x12
#define SET19_vCOMH              0xDB                     //--set vcomh
#define  SET20_vCOM_D_LEVVEL     0x40                     //Set VCOM Deselect Level
#define  SET21_PAGE_ADDR_MODE    0x20                     //-Set Page Addressing Mode (0x00/0x01/0x02)
#define  SET22_STG2              0x02                     //
#define  SET23_CHARGE_PUMP       0x8D                     //--set Charge Pump enable/disable
#define  SET24_DIS_              0x14                     //--set(0x10) disable
#define  SET25_ENTIRE_DIS        0xA4                     // Disable Entire Display On (0xa4/0xa5)
#define  SET26_INV_DIS           0xA6                     // Disable Inverse Display On (0xa6/a7)
#define  TURN_ON_CMD             0xAF                     //--turn on oled panel

//显示1，擦除0
typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;


#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  



#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
//int oled_write_cmd(uint8_t command);
//int oled_write_data(uint8_t data);
int oled_write_long_data(uint8_t *data,uint16_t len);

void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowNum_F(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);
void OLED_ShowFloatNum (uint8_t x,uint8_t y,float num,uint8_t IntLen,uint8_t FloatLen,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p,uint8_t Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
uint8_t OLED_ShowCH(uint8_t x,uint8_t y,uint8_t *cn);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_Float (uint8_t x,uint8_t y,float num,uint8_t IntLen,uint8_t FloatLen,uint8_t size);
#endif

