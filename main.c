#include "main.h"
int status;
int BH1750_Read();	//Function Prototype
void Delay(volatile uint32_t nCount);
int main(){
  SystemInit();
  UB_LCD_Init();
  UB_Led_Init();
  UB_LCD_LayerInit_Fullscreen();
  UB_LCD_SetLayer_1();
  UB_LCD_FillLayer(RGB_COL_WHITE);
  UB_LCD_SetLayer_2();
  UB_LCD_FillLayer(RGB_COL_GREEN);
  UB_LCD_Rotate_0();
  UB_Font_DrawString(5,10,"STM32F429-BH1750 TEST",&Arial_11x18,RGB_COL_BLUE,RGB_COL_GREEN);
  UB_I2C3_Init();
  UB_I2C3_WriteByte(0x23<<1,0x00,0x10);
  /*Set resolution data 0x10 at slave address 0x23<<1
  * page 5 @ http://www.dfrobot.com/image/data/SEN0097/BH1750FVI.pdf
  */
  while(1){
	  int lux;
	  char buf[5];
	  lux = BH1750_Read();
	  if(lux >= 0){
		  sprintf(buf,"Lux = %d",lux);
		  UB_Font_DrawString(10,40,buf,&Arial_11x18,RGB_COL_BLUE,RGB_COL_GREEN);
	  }
	  else
		  sprintf(buf,"Status = %d",status);
		  UB_Font_DrawString(10,40,"FAILED!",&Arial_11x18,RGB_COL_RED,RGB_COL_GREEN);
	  	  UB_Font_DrawString(10,60,buf,&Arial_11x18,RGB_COL_RED,RGB_COL_GREEN);
	  UB_Led_Toggle(LED_GREEN);
	  Delay(50000000);
  }

}

int BH1750_Read(){
	UB_Led_Toggle(LED_GREEN);
	uint16_t val;
	/* Check if any error occur from I2C communication */
	status = UB_I2C3_ReadMultiByte(0x23<<1,0x00,2);
	if(status == 0){
		/* Luminous Calculation */
		val=((I2C3_DATA[0]<<8)|I2C3_DATA[1])/1.2;
		/* Return calculated luminosity */
		return val;
	}
	else
		/* Return error in I2C communication */
		return -1;
}

void Delay(volatile uint32_t nCount) {
  while(nCount--) {
  }
}
