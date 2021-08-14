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
    else 
    {
        cmd_pwr = 1;
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

//设置图像输出大小
//OV2640输出图像的大小(分辨率),完全由该函数确定
//width,height:宽度(对应:horizontal)和高度(对应:vertical),width和height必须是4的倍数
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
        SCCB_WR_Reg(0X5A,outw&0XFF); //设置OUTW的低八位
        SCCB_WR_Reg(0X5B,outh&0XFF); //设置OUTH的低八位
        temp=(outw>>8)&0X03;
        temp|=(outh>>6)&0X04;
        SCCB_WR_Reg(0X5C,temp);      //设置OUTH/OUTW的高位 
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

//设置图像输出窗口 
//sx,sy,起始地址
//width,height:宽度(对应:horizontal)和高度(对应:vertical)
void OV2640::windowSet(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
	uint16_t endx;
	uint16_t endy;
	uint8_t temp; 
	endx=sx+width/2;	//V*2
 	endy=sy+height/2;
	
	SCCB_WR_Reg(0XFF,0X01);			
	temp=SCCB_RD_Reg(0X03);				//读取Vref之前的值
	temp&=0XF0;
	temp|=((endy&0X03)<<2)|(sy&0X03);
	SCCB_WR_Reg(0X03,temp);				//设置Vref的start和end的最低2位
	SCCB_WR_Reg(0X19,sy>>2);			//设置Vref的start高8位
	SCCB_WR_Reg(0X1A,endy>>2);			//设置Vref的end的高8位
	
	temp=SCCB_RD_Reg(0X32);				//读取Href之前的值
	temp&=0XC0;
	temp|=((endx&0X07)<<3)|(sx&0X07);
	SCCB_WR_Reg(0X32,temp);				//设置Href的start和end的最低3位
	SCCB_WR_Reg(0X17,sx>>3);			//设置Href的start高8位
	SCCB_WR_Reg(0X18,endx>>3);			//设置Href的end的高8位
}

//设置图像开窗大小
//由:OV2640_ImageSize_Set确定传感器输出分辨率从大小.
//该函数则在这个范围上面进行开窗,用于OV2640_OutSize_Set的输出
//注意:本函数的宽度和高度,必须大于等于OV2640_OutSize_Set函数的宽度和高度
//     OV2640_OutSize_Set设置的宽度和高度,根据本函数设置的宽度和高度,由DSP
//     自动计算缩放比例,输出给外部设备.
//width,height:宽度(对应:horizontal)和高度(对应:vertical),width和height必须是4的倍数
void OV2640::imageWinSet(uint16_t offx, uint16_t offy, uint16_t width, uint16_t height)
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
        SCCB_WR_Reg(0X51,hsize&0XFF);		//设置H_SIZE的低八位
        SCCB_WR_Reg(0X52,vsize&0XFF);		//设置V_SIZE的低八位
        SCCB_WR_Reg(0X53,offx&0XFF);		//设置offx的低八位
        SCCB_WR_Reg(0X54,offy&0XFF);		//设置offy的低八位
        temp=(vsize>>1)&0X80;
        temp|=(offy>>4)&0X70;
        temp|=(hsize>>5)&0X08;
        temp|=(offx>>8)&0X07; 
        SCCB_WR_Reg(0X55,temp);				//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
        SCCB_WR_Reg(0X57,(hsize>>2)&0X80);	//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
        SCCB_WR_Reg(0XE0,0X00);	
	}
}

//该函数设置图像尺寸大小,也就是所选格式的输出分辨率
//UXGA:1600*1200,SVGA:800*600,CIF:352*288
//width,height:图像宽度和图像高度
void OV2640::imageSizeSet(uint16_t width, uint16_t height)
{
    uint8_t temp; 
	SCCB_WR_Reg(0XFF,0X00);			
	SCCB_WR_Reg(0XE0,0X04);			
	SCCB_WR_Reg(0XC0,(width)>>3&0XFF);		//设置HSIZE的10:3位
	SCCB_WR_Reg(0XC1,(height)>>3&0XFF);		//设置VSIZE的10:3位
	temp=(width&0X07)<<3;
	temp|=height&0X07;
	temp|=(width>>4)&0X80; 
	SCCB_WR_Reg(0X8C,temp);	
	SCCB_WR_Reg(0XE0,0X00);
}

// } // end of namespace