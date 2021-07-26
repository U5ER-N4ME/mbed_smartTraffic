#ifndef MBED_3RD_OV2640_HPP
#define MBED_3RD_OV2640_HPP

#include "mbed.h"

// namespace camera
// {

#define OV2640_ADDRESS 0x60

typedef enum
{
    CAMERA_OK            = 0x00,
    CAMERA_ERROR         = 0x01,
    CAMERA_TIMEOUT       = 0x02,
    CAMERA_NOT_DETECTED  = 0x03,
    CAMERA_NOT_SUPPORTED = 0x04
} cameraStatusTypeDef;
typedef enum
{
    CAMERA_PWR_ON  = true,
    CAMERA_PWR_OFF = false
} cameraPowerStateTypeDef;
typedef enum
{
    CAMERA_RES_UXGA  = 1600*1200,
    CAMERA_RES_SXGA  = 1280*1024,
    CAMERA_RES_SVGA  = 800*600,
    CAMERA_RES_VGA   = 640*480,
    CAMERA_RES_QVGA  = 320*240,
    CAMERA_RES_QQVGA = 160*120
} cameraResolutionTypeDef;
typedef enum
{
    CAMERA_FMT_YUV422 = 0x00,
    CAMERA_FMT_RGB565 = 0x01
} cameraFormatTypeDef;

class OV2640
{
public:
    OV2640(
        PinName HW_PWR, PinName HW_RST,
        PinName I2C_SDA, PinName I2C_SCL, 
        PinName DCMI_VSYNC, PinName DCMI_HSYNC, PinName DCMI_PCLK, 
        PinName DCMI_0, PinName DCMI_1, PinName DCMI_2, PinName DCMI_3, 
        PinName DCMI_4, PinName DCMI_5, PinName DCMI_6, PinName DCMI_7
    );
    ~OV2640();

    cameraPowerStateTypeDef powerStateGet(void);
    cameraStatusTypeDef powerStateSet(cameraPowerStateTypeDef);
    cameraStatusTypeDef hwReset(void);
    cameraStatusTypeDef swReset(uint8_t);
    uint16_t midGet(uint8_t);
    uint16_t pidGet(uint8_t);
    cameraStatusTypeDef idCheck(uint8_t, uint16_t, uint16_t);
    cameraStatusTypeDef init(uint8_t, cameraResolutionTypeDef);
    cameraStatusTypeDef captureFrameRateSet(uint8_t, uint8_t);
    cameraStatusTypeDef outputFormatSet(uint8_t, cameraFormatTypeDef);
    cameraStatusTypeDef outputResolutionSet(uint8_t, uint16_t, uint16_t);
    cameraStatusTypeDef outputClockFreqSet(uint8_t devAddr, uint8_t divider);
    cameraStatusTypeDef abandonFrames(uint8_t);
    uint32_t capture(uint8_t*);

// private members, comment the following line for public access
private:
    I2C cmd_i2c;
    DigitalOut cmd_pwr, cmd_rst;
    DigitalIn sig_v, sig_h, sig_c;
    BusIn dat;
};

// } // end of namespace

#endif