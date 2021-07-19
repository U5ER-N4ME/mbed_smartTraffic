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

    /* test */
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_6,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_7,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_8,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_9,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_6,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_7,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_8,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_9,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_8,  LL_GPIO_SPEED_FREQ_VERY_HIGH);
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
        0x11, (char) (divider&0x3F)
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

cameraStatusTypeDef OV2640::outputResolutionSet(uint8_t devAddr, uint16_t width, uint16_t height)
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
}

cameraStatusTypeDef OV2640::outputClockFreqSet(uint8_t devAddr, uint8_t divider)
{
    cameraStatusTypeDef rtn = CAMERA_OK; // return value

    char clockFreqRegTbl[][2] = 
    {
        0xff, 0x00, 
        0xD3, (char) (divider&0x7F) // this should be greater than 0x3A=58 when RGB565
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

// } // end of namespace