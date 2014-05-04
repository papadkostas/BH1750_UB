#include "main.h"

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
  BH1750_Init();
  Delay(50000000);
  while(1){
	  int lux;
	  lux = BH1750_Read();
	  if(lux >= 0){
		  sprintf(buf,"Lux = %d",lux);
		  UB_Font_DrawString(10,60,buf,&Arial_11x18,RGB_COL_BLUE,RGB_COL_GREEN);
	  }
	  else
		  sprintf(buf,"Status = %d",statusread);
	  	  UB_Font_DrawString(10,60,buf,&Arial_11x18,RGB_COL_RED,RGB_COL_GREEN);
	  Delay(50000000);
  }
}

void BH1750_Init(){
	/*Set resolution data 0x10 at slave address 0x23<<1
	* page 5 @ http://www.dfrobot.com/image/data/SEN0097/BH1750FVI.pdf
	*/
	statusinit = UB_I2C3_WriteByte(0x23<<1,0x00,0x10);
	if(statusinit == 0){
		/* Print Initialization Ok! */
		UB_Font_DrawString(10,40,"Init Ok!",&Arial_11x18,RGB_COL_BLUE,RGB_COL_GREEN);
	}
	else {
		/* Print Initialization Error ID */
		sprintf(buf,"Init Failed : %d", statusinit);
		UB_Font_DrawString(10,40,buf,&Arial_11x18,RGB_COL_RED,RGB_COL_GREEN);
	}
}

int BH1750_Read(){
	/* Do not read if init failed before */
	if(statusinit < 0){
		/* Blink RED LED if init failed */
		UB_Led_Toggle(LED_RED);
		statusread = -10;
		return statusread;
	}
	uint16_t val;
	/* Check if any error occur from I2C communication */
	statusread = UB_I2C3_ReadMultiByte(0x23<<1,0x00,2);
	if(statusread == 0){
		/* Blink GREEN LED if read is done */
		UB_Led_Toggle(LED_GREEN);
		/* Luminous Calculation */
		val=((I2C3_DATA[0]<<8)|I2C3_DATA[1])/1.2;
		/* Return calculated luminosity */
		return val;
	}
	else
		/* Return error in I2C communication */
		return -1;
}

void Delay(volatile uint32_t nCount){
  while(nCount--) {
  }
}
