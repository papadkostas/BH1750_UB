#include "BH1750.h"

//--------------------------------------------------------------
// Private Functions
//--------------------------------------------------------------
int8_t BH1750_Command(uint8_t cmd);

//--------------------------------------------------------------
// Private Variables
//--------------------------------------------------------------

char bufbh[20];
int8_t cmdstatus;
int16_t readstatus;

int8_t BH1750_Command(uint8_t cmd){
	/* Check if NULL */
	assert_param(cmd);
	cmdstatus = UB_I2C3_WriteByte(0x23<<1,0x00,cmd,1);
	/* Print Initialization Error ID */
#ifdef DEBUG
	if(cmdstatus < 0){
		sprintf(bufbh,"Command 0x%04x", cmd);
		UB_Font_DrawString(10,40,bufbh,&Arial_11x18,RGB_COL_RED,RGB_COL_BLACK);
		sprintf(bufbh,"Returned %d", cmdstatus);
		UB_Font_DrawString(10,60,bufbh,&Arial_11x18,RGB_COL_RED,RGB_COL_BLACK);
		return cmdstatus;
	}
#endif
	return cmdstatus;
}

int BH1750_Read(uint8_t mode){
	/* Check if NULL */
	assert_param(mode);
	/* Command BH1750 */
	cmdstatus = BH1750_Command(mode);
	if(cmdstatus < 0){
		return cmdstatus;
	}
	/* Check if any error occur from I2C communication */
	readstatus = UB_I2C3_ReadMultiByte(0x23<<1,0x00,2,1);
	if(readstatus == 0){
		/* Luminous Calculation */
		float val = ((I2C3_DATA[0]<<8)|I2C3_DATA[1])/1.2;
		/* Return calculated luminosity */
		return val;
	}
	else{
		/* Return error in I2C communication */
		return -1;
	}
}
