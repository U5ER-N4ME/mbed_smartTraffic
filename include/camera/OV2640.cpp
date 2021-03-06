#include "OV2640.hpp"
#include "OV2640cfg.hpp"
#include "stm32l4xx_ll_gpio.h"

// namespace camera
// {

OV2640::OV2640(
    PinName HW_PWR, PinName HW_RST, 
    PinName I2C_SDA, PinName I2C_SCL, 
    PinName DCMI_VSYNC, PinName DCMI_HSYNC, PinName DCMI_PCLK, 
    PinName DCMI_0, PinName DCMI_1, PinName DCMI_2, PinName DCMI_3, 
    PinName DCMI_4, PinName DCMI_5, PinName DCMI_6, PinName DCMI_7
) : 
cmd_pwr(HW_PWR), cmd_rst(HW_RST),
cmd_i2c(I2C_SDA, I2C_SCL),
sig_v(DCMI_VSYNC), sig_h(DCMI_HSYNC), sig_c(DCMI_PCLK),
dat(DCMI_0, DCMI_1, DCMI_2, DCMI_3, DCMI_4, DCMI_5, DCMI_6, DCMI_7)
{
    cmd_i2c.stop();
    cmd_i2c.frequency(100000);
}

OV2640::~OV2640(){}

cameraPowerStateTypeDef OV2640::powerStateGet(void)
{
    if (cmd_pwr == 1)
    {
        return CAMERA_PWR_OFF;
    }
    else 
    {
        return CAMERA_PWR_ON;
    }
}

cameraStatusTypeDef OV2640::powerStateSet(cameraPowerStateTypeDef state)
{
    cameraStatusTypeDef rtn = CAMERA_ERROR; // return value

    if (state == CAMERA_PWR_ON)
    {
        cmd_pwr = 0;
        rtn = CAMERA_OK;
    }
    else if (state == CAMERA_PWR_OFF)
    {
        cmd_pwr = 1;
        rtn = CAMERA_OK;
    }
    else 
    {
        // do nothing
        rtn = CAMERA_NOT_DETECTED;
    }
    ThisThread::sleep_for(3ms);

    return rtn;
}

cameraStatusTypeDef OV2640::hwReset(void)
{
    cmd_rst = 0;
    ThisThread::sleep_for(10ms);
    cmd_rst = 1;
    ThisThread::sleep_for(10ms);

    return CAMERA_OK;
}

cameraStatusTypeDef OV2640::swReset(uint8_t devAddr)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

	char cam_cmd_wrbuf_sensor[2] = {0xFF, 0x01};
	if (cmd_i2c.write(devAddr, cam_cmd_wrbuf_sensor, 2, false) != 0)
    {
        rtn = CAMERA_ERROR;
    }
	ThisThread::sleep_for(200ms);

	char cam_cmd_wrbuf_reset[2] = {0x12, 0x80};
	if (cmd_i2c.write(devAddr, cam_cmd_wrbuf_reset, 2, false) != 0)
    {
        rtn = CAMERA_ERROR;
    }
	ThisThread::sleep_for(200ms);
    
    return rtn;
}

uint16_t OV2640::midGet(uint8_t devAddr)
{
    char midAddr[2] = {0x1C, 0x1D}, midBuffer[2];

    cmd_i2c.write(devAddr, &midAddr[0], 1, false);
	cmd_i2c.read(devAddr|0x01, &midBuffer[0], 1, false);
	cmd_i2c.write(devAddr, &midAddr[1], 1, false);
	cmd_i2c.read(devAddr|0x01, &midBuffer[1], 1, false);

    return (midBuffer[0] << 8) + midBuffer[1];
}

uint16_t OV2640::pidGet(uint8_t devAddr)
{
    char pidAddr[2] = {0x0A, 0x0B}, pidBuffer[2];

    cmd_i2c.write(devAddr, &pidAddr[0], 1, false);
	cmd_i2c.read(devAddr|0x01, &pidBuffer[0], 1, false);
	cmd_i2c.write(devAddr, &pidAddr[1], 1, false);
	cmd_i2c.read(devAddr|0x01, &pidBuffer[1], 1, false);

	return (pidBuffer[0] << 8) + pidBuffer[1];
}

cameraStatusTypeDef OV2640::idCheck(uint8_t devAddr, uint16_t midExpected, uint16_t pidExpected)
{
    uint16_t midObtained = 0, pidObtained = 0;   

    midObtained = midGet(devAddr);
    pidObtained = pidGet(devAddr);

    // check mid and pid match
    if (midObtained != midExpected || pidObtained != pidExpected)
	{
		return CAMERA_NOT_SUPPORTED;
	}
	else
	{
		return CAMERA_OK;
	}
}

cameraStatusTypeDef OV2640::init(uint8_t devAddr, cameraResolutionTypeDef resolution)
{
    uint32_t index;
    cameraStatusTypeDef rtn = CAMERA_OK;

    switch (resolution)
    {
        case CAMERA_RES_SXGA: 
            for(index=0; index<(sizeof(ov2640_sxga_init_reg_tbl)/2); index++)
            {
                if (cmd_i2c.write(devAddr, ov2640_sxga_init_reg_tbl[index], 2, false) != 0)
                {
                    rtn = CAMERA_ERROR;
                }
                ThisThread::sleep_for(2ms);
            }
            break;
        case CAMERA_RES_SVGA: 
            for(index=0; index<(sizeof(ov2640_svga_init_reg_tbl)/2); index++)
            {
                if (cmd_i2c.write(devAddr, ov2640_svga_init_reg_tbl[index], 2, false) != 0)
                {
                    rtn = CAMERA_ERROR;
                }
                ThisThread::sleep_for(2ms);
            }
            break;
        default: 
            rtn = CAMERA_NOT_SUPPORTED;
            break;
    }

    return rtn;
}

cameraStatusTypeDef OV2640::captureFrameRateSet(uint8_t devAddr, uint8_t divider)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    char frameRateRegTbl[][2] = 
    {
        0xff, 0x01, 
        // 0x11, (char) (divider&0x3F)
        0x11, (char) divider
    };
    for (int i=0; i<sizeof(frameRateRegTbl)/2; i++)
    {
        if (cmd_i2c.write(OV2640_ADDRESS, frameRateRegTbl[i], 2, false) != 0)
        {
            rtn = CAMERA_ERROR;
            break;
        }
    }

    return rtn;
}

cameraStatusTypeDef OV2640::outputFormatSet(uint8_t devAddr, cameraFormatTypeDef format)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    switch (format) 
    {
        case CAMERA_FMT_RGB565: 
            for (int i=0; i<sizeof(ov2640_rgb565_reg_tbl)/2; i++)
            {
                if (cmd_i2c.write(devAddr, ov2640_rgb565_reg_tbl[i], 2, false) != 0)
                {
                    rtn = CAMERA_ERROR;
                    break;
                }
            }
            for (int i=0; i<sizeof(ov2640_raw_reg_tbl)/2; i++)
            {
                if (cmd_i2c.write(devAddr, ov2640_raw_reg_tbl[i], 2, false) != 0)
                {
                    rtn = CAMERA_ERROR;
                    break;
                }
            }
            break;
        case CAMERA_FMT_YUV422: 
            for (int i=0; i<sizeof(ov2640_yuv422_reg_tbl)/2; i++)
            {
                if (cmd_i2c.write(devAddr, ov2640_yuv422_reg_tbl[i], 2, false) != 0)
                {
                    rtn = CAMERA_ERROR;
                    break;
                }
            }
            for (int i=0; i<sizeof(ov2640_jpg_reg_tbl)/2; i++)
            {
                if (cmd_i2c.write(devAddr, ov2640_jpg_reg_tbl[i], 2, false) != 0)
                {
                    rtn = CAMERA_ERROR;
                    break;
                }
            }
            break;
        default:
            rtn = CAMERA_NOT_SUPPORTED;
            break;
    }

    return rtn;
}

//????????????????????????
//OV2640?????????????????????(?????????),????????????????????????
//width,height:??????(??????:horizontal)?????????(??????:vertical),width???height?????????4?????????
cameraStatusTypeDef OV2640::outputResolutionSet(uint8_t devAddr, uint16_t width, uint16_t height)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

	uint16_t outh;
	uint16_t outw;
	uint8_t temp; 
    if (width%4 == 0 && height%4 == 0)
    {
        outw=width/4;
        outh=height/4; 
        SCCB_WR_Reg(0XFF,0X00);
        SCCB_WR_Reg(0XE0,0X04);		
        SCCB_WR_Reg(0X5A,outw&0XFF); //??????OUTW????????????
        SCCB_WR_Reg(0X5B,outh&0XFF); //??????OUTH????????????
        temp=(outw>>8)&0X03;
        temp|=(outh>>6)&0X04;
        SCCB_WR_Reg(0X5C,temp);      //??????OUTH/OUTW????????? 
        SCCB_WR_Reg(0XE0,0X00);	
    }
    else
    {
        rtn = CAMERA_ERROR;
    }

    return rtn;
}
/* cameraStatusTypeDef OV2640::outputResolutionSet(uint8_t devAddr, uint16_t width, uint16_t height)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    if (width%4 == 0 && height%4 == 0)
    {
        uint16_t wSize = width / 4, hSize = height / 4; 
        char resize_reg_tbl[][2] = 
        {
            0xFF, 0x00,
            0xE0, 0x04,
            0x5A, (char) (wSize & 0xFF), 
            0x5B, (char) (hSize & 0xFF), 
            0x5C, (char) ( ((wSize>>8) & 0X03) | ((hSize>>6) & 0X04) ),
            0xE0, 0x00
        };
        for (int i=0; i<sizeof(resize_reg_tbl)/2; i++)
        {
            if (cmd_i2c.write(OV2640_ADDRESS, resize_reg_tbl[i], 2, false) != 0)
            {
                rtn = CAMERA_ERROR;
                break;
            }
        }
    }
    else
    {
        rtn = CAMERA_ERROR;
    }

    return rtn;
} */

cameraStatusTypeDef OV2640::outputClockFreqSet(uint8_t devAddr, uint8_t divider)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    char clockFreqRegTbl[][2] = 
    {
        0xFF, 0x00, 
        // 0xD3, (char) (divider&0x7F),
        0xD3, (char)divider,
        // 0xFF, 0x01,
        // 0x32, 0xB6 // default val: 0x36, alternatives: 0xB6 (half PCLK freq), 0xF6 (quarter)
    }; 
    for (int i=0; i<sizeof(clockFreqRegTbl)/2; i++)
    {
        if (cmd_i2c.write(OV2640_ADDRESS, clockFreqRegTbl[i], 2, false) != 0)
        {
            rtn = CAMERA_ERROR;
            break;
        }
    }

    return rtn;
}


cameraStatusTypeDef OV2640::abandonFrames(uint8_t frames)
{
    for(int i=0; i<frames; i++)
    {
        while(sig_v == 1);
        while(sig_v == 0);
    }

    return CAMERA_OK;
}

uint32_t OV2640::capture(uint8_t* cap)
{
    uint32_t length = 0;

    abandonFrames(1); // throw the first (not complete) frame

    while(sig_v == 1) // start collecting
    {
        while(sig_h == 1)
        {
            while(sig_c == 0); 
            cap[length] = dat;
            while(sig_c == 1); 
            length++;
        }
    }
    
    return length;
}

/** TEST **/
/* uint32_t OV2640::capture(uint8_t* cap)
{
    uint32_t length = 0;
    GPIO_TypeDef* port = GPIOC;

    abandonFrames(1); // throw the first (not complete) frame

    while(sig_v == 1) // start collecting
    {
        while(sig_h == 1)
        {
            while(sig_c == 0); 
            cap[length] = GPIOC->IDR;
            while(sig_c == 1); 
            length++;
        }
    }
    
    return length;
} */

cameraStatusTypeDef OV2640::colorBarSet(uint8_t devAddr, bool enable)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value
	char buffer[2] = {0x12, 0x00};
    
    char cam_cmd_wrbuf_sensor[2] = {0xFF, 0x01};
	if (cmd_i2c.write(devAddr, cam_cmd_wrbuf_sensor, 2, false) != 0)
    {
        rtn = CAMERA_ERROR;
    }
    cmd_i2c.write(devAddr, &buffer[0], 1, false);
    cmd_i2c.read(devAddr|0x01, &buffer[1], 1, false);

	buffer[1] &= ~(1<<1);

	if(enable==true)
    {
        buffer[1] |= 1<<1;
    }
    if (cmd_i2c.write(devAddr, buffer, 2, false) != 0)
    {
        rtn = CAMERA_ERROR;
    }

    return rtn;
}

cameraStatusTypeDef OV2640::SCCB_WR_Reg(char reg, char val)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    char sendBuffer[2] = {reg, val};
    if (cmd_i2c.write(OV2640_ADDRESS, sendBuffer, 2, false) != 0)
    {
        rtn = CAMERA_ERROR;
    }

    return rtn;
}

char OV2640::SCCB_RD_Reg(char reg)
{
    char readBuffer[2] = {reg, 0x00};
    cmd_i2c.write(OV2640_ADDRESS, &readBuffer[0], 1, false);
    cmd_i2c.read(OV2640_ADDRESS|0x01, &readBuffer[1], 1, false);

    return readBuffer[1];
}

//???????????????????????? 
//sx,sy,????????????
//width,height:??????(??????:horizontal)?????????(??????:vertical)
void OV2640::windowSet(uint8_t devAddr, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
	uint16_t endx;
	uint16_t endy;
	uint8_t temp; 
	endx=sx+width/2;	//V*2
 	endy=sy+height/2;
	
	SCCB_WR_Reg(0XFF,0X01);			
	temp=SCCB_RD_Reg(0X03);				//??????Vref????????????
	temp&=0XF0;
	temp|=((endy&0X03)<<2)|(sy&0X03);
	SCCB_WR_Reg(0X03,temp);				//??????Vref???start???end?????????2???
	SCCB_WR_Reg(0X19,sy>>2);			//??????Vref???start???8???
	SCCB_WR_Reg(0X1A,endy>>2);			//??????Vref???end??????8???
	
	temp=SCCB_RD_Reg(0X32);				//??????Href????????????
	temp&=0XC0;
	temp|=((endx&0X07)<<3)|(sx&0X07);
	SCCB_WR_Reg(0X32,temp);				//??????Href???start???end?????????3???
	SCCB_WR_Reg(0X17,sx>>3);			//??????Href???start???8???
	SCCB_WR_Reg(0X18,endx>>3);			//??????Href???end??????8???
}

//????????????????????????
//???:OV2640_ImageSize_Set???????????????????????????????????????.
//?????????????????????????????????????????????,??????OV2640_OutSize_Set?????????
//??????:???????????????????????????,??????????????????OV2640_OutSize_Set????????????????????????
//     OV2640_OutSize_Set????????????????????????,???????????????????????????????????????,???DSP
//     ????????????????????????,?????????????????????.
//width,height:??????(??????:horizontal)?????????(??????:vertical),width???height?????????4?????????
void OV2640::imageWinSet(uint8_t devAddr, uint16_t offx, uint16_t offy, uint16_t width, uint16_t height)
{
    uint16_t hsize;
	uint16_t vsize;
	uint8_t temp; 
    if ((width%4 == 0) && (height%4 == 0))
    {
        hsize=width/4;
        vsize=height/4;
        SCCB_WR_Reg(0XFF,0X00);	
        SCCB_WR_Reg(0XE0,0X04);					
        SCCB_WR_Reg(0X51,hsize&0XFF);		//??????H_SIZE????????????
        SCCB_WR_Reg(0X52,vsize&0XFF);		//??????V_SIZE????????????
        SCCB_WR_Reg(0X53,offx&0XFF);		//??????offx????????????
        SCCB_WR_Reg(0X54,offy&0XFF);		//??????offy????????????
        temp=(vsize>>1)&0X80;
        temp|=(offy>>4)&0X70;
        temp|=(hsize>>5)&0X08;
        temp|=(offx>>8)&0X07; 
        SCCB_WR_Reg(0X55,temp);				//??????H_SIZE/V_SIZE/OFFX,OFFY?????????
        SCCB_WR_Reg(0X57,(hsize>>2)&0X80);	//??????H_SIZE/V_SIZE/OFFX,OFFY?????????
        SCCB_WR_Reg(0XE0,0X00);	
	}
}

//?????????????????????????????????,???????????????????????????????????????
//UXGA:1600*1200,SVGA:800*600,CIF:352*288
//width,height:???????????????????????????
cameraStatusTypeDef OV2640::imageSizeSet(uint8_t devAddr, uint16_t width, uint16_t height)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    uint8_t temp; 
	SCCB_WR_Reg(0XFF,0X00);			
	SCCB_WR_Reg(0XE0,0X04);			
	SCCB_WR_Reg(0XC0,(width)>>3&0XFF);		//??????HSIZE???10:3???
	SCCB_WR_Reg(0XC1,(height)>>3&0XFF);		//??????VSIZE???10:3???
	temp=(width&0X07)<<3;
	temp|=height&0X07;
	temp|=(width>>4)&0X80; 
	SCCB_WR_Reg(0X8C,temp);	
	SCCB_WR_Reg(0XE0,0X00);

    return rtn;
}

//???????????????
//0:??????
//1:??????sunny
//2,??????cloudy
//3,?????????office
//4,??????home
void OV2640::lightModeSet(uint8_t mode)
{
	uint8_t regccval=0X5E;//Sunny 
	uint8_t regcdval=0X41;
	uint8_t regceval=0X54;
	switch(mode)
	{ 
		case 0://auto 
			SCCB_WR_Reg(0XFF,0X00);	 
			SCCB_WR_Reg(0XC7,0X10);//AWB ON 
			return;  	
		case 2://cloudy
			regccval=0X65;
			regcdval=0X41;
			regceval=0X4F;
			break;	
		case 3://office
			regccval=0X52;
			regcdval=0X41;
			regceval=0X66;
			break;	
		case 4://home
			regccval=0X42;
			regcdval=0X3F;
			regceval=0X71;
			break;	
	}
	SCCB_WR_Reg(0XFF,0X00);	 
	SCCB_WR_Reg(0XC7,0X40);	//AWB OFF 
	SCCB_WR_Reg(0XCC,regccval); 
	SCCB_WR_Reg(0XCD,regcdval); 
	SCCB_WR_Reg(0XCE,regceval);  
}

//????????????
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640::colorSaturationSet(uint8_t sat)
{ 
	uint8_t reg7dval=((sat+2)<<4)|0X08;
	SCCB_WR_Reg(0XFF,0X00);		
	SCCB_WR_Reg(0X7C,0X00);		
	SCCB_WR_Reg(0X7D,0X02);				
	SCCB_WR_Reg(0X7C,0X03);			
	SCCB_WR_Reg(0X7D,reg7dval);			
	SCCB_WR_Reg(0X7D,reg7dval); 		
}

//????????????
//0:(0X00)-2
//1:(0X10)-1
//2,(0X20) 0
//3,(0X30)+1
//4,(0X40)+2
void OV2640::brightnessSet(uint8_t bright)
{
  SCCB_WR_Reg(0xff, 0x00);
  SCCB_WR_Reg(0x7c, 0x00);
  SCCB_WR_Reg(0x7d, 0x04);
  SCCB_WR_Reg(0x7c, 0x09);
  SCCB_WR_Reg(0x7d, bright<<4); 
  SCCB_WR_Reg(0x7d, 0x00); 
}

//???????????????
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640::contrastSet(uint8_t contrast)
{
	uint8_t reg7d0val=0X20;//?????????????????????
	uint8_t reg7d1val=0X20;
  	switch(contrast)
	{
		case 0://-2
			reg7d0val=0X18;	 	 
			reg7d1val=0X34;	 	 
			break;	
		case 1://-1
			reg7d0val=0X1C;	 	 
			reg7d1val=0X2A;	 	 
			break;	
		case 3://1
			reg7d0val=0X24;	 	 
			reg7d1val=0X16;	 	 
			break;	
		case 4://2
			reg7d0val=0X28;	 	 
			reg7d1val=0X0C;	 	 
			break;	
	}
	SCCB_WR_Reg(0xff,0x00);
	SCCB_WR_Reg(0x7c,0x00);
	SCCB_WR_Reg(0x7d,0x04);
	SCCB_WR_Reg(0x7c,0x07);
	SCCB_WR_Reg(0x7d,0x20);
	SCCB_WR_Reg(0x7d,reg7d0val);
	SCCB_WR_Reg(0x7d,reg7d1val);
	SCCB_WR_Reg(0x7d,0x06);
}

//???????????????????????????,??????5?????????
const static uint8_t OV2640_AUTOEXPOSURE_LEVEL[5][8]=
{
	{
		0xFF,0x01,
		0x24,0x20,
		0x25,0x18,
		0x26,0x60,
	},
	{
		0xFF,0x01,
		0x24,0x34,
		0x25,0x1c,
		0x26,0x00,
	},
	{
		0xFF,0x01,	
		0x24,0x3e,	
		0x25,0x38,
		0x26,0x81,
	},
	{
		0xFF,0x01,
		0x24,0x48,
		0x25,0x40,
		0x26,0x81,
	},
	{
		0xFF,0x01,	
		0x24,0x58,	
		0x25,0x50,	
		0x26,0x92,	
	},
}; 
//OV2640????????????????????????
//level:0~4
void OV2640::autoExposureSet(uint8_t level)
{  
	uint8_t i;
	uint8_t *p=(uint8_t*)OV2640_AUTOEXPOSURE_LEVEL[level];
	for(i=0;i<4;i++)
	{ 
		SCCB_WR_Reg(p[i*2],p[i*2+1]); 
	} 
}  

//????????????
//0:????????????
//1,??????
//2,??????
//3,?????????
//4,?????????
//5,?????????
//6,??????
void OV2640::specialEffectSet(uint8_t eft)
{
	uint8_t reg7d0val=0X00;//?????????????????????
	uint8_t reg7d1val=0X80;
	uint8_t reg7d2val=0X80; 
	switch(eft)
	{
		case 1://??????
			reg7d0val=0X40; 
			break;	
		case 2://??????
			reg7d0val=0X18; 
			break;	 
		case 3://?????????
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0XC0; 
			break;	
		case 4://?????????
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0X40; 
			break;	
		case 5://?????????
			reg7d0val=0X18; 
			reg7d1val=0XA0;
			reg7d2val=0X40; 
			break;	
		case 6://??????
			reg7d0val=0X18; 
			reg7d1val=0X40;
			reg7d2val=0XA6; 
			break;	 
	}
	SCCB_WR_Reg(0xff,0x00);
	SCCB_WR_Reg(0x7c,0x00);
	SCCB_WR_Reg(0x7d,reg7d0val);
	SCCB_WR_Reg(0x7c,0x05);
	SCCB_WR_Reg(0x7d,reg7d1val);
	SCCB_WR_Reg(0x7d,reg7d2val); 
}

// } // end of namespace