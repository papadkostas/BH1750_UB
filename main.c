#include "main.h"

int main(){
  SystemInit();
  UB_LCD_Init();
  UB_Led_Init();
  UB_LCD_LayerInit_Fullscreen();
  UB_LCD_SetLayer_1();
  UB_LCD_FillLayer(RGB_COL_WHITE);
  UB_LCD_SetLayer_2();
  UB_LCD_FillLayer(RGB_COL_BLACK);
  UB_LCD_Rotate_0();
  UB_Font_DrawString(5,10,"STM32F429-BH1750 TEST",&Arial_11x18,RGB_COL_BLUE,RGB_COL_BLACK);
  UB_I2C3_Init();
  Delay(5000000);
  while(1){
	  int lux;
	  char buf[20];
	  lux = BH1750_Read(ONE_TIME_H_1LX);
	  if(lux < 0){
		  return 0;
	  }
	  else{
		  sprintf(buf,"Lux = %d    ",lux);
		  UB_Font_DrawString(10,40,buf,&Arial_11x18,RGB_COL_BLUE,RGB_COL_BLACK);
	  }
	  Delay(5000000);
  }
}
void Delay(volatile uint32_t nCount){
  while(nCount--) {
  }
}
