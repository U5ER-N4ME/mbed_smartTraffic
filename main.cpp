#include "mbed.h"
#include "include/camera/OV2640.hpp"

BufferedSerial pc(USBTX, USBRX, 115200);
Timer t;

/*  HW_PWR, HW_RST,
    I2C_SDA, I2C_SCL, 
    DCMI_VSYNC, DCMI_HSYNC, DCMI_PCLK, 
    DCMI_0, DCMI_1, DCMI_2, DCMI_3, DCMI_4, DCMI_5, DCMI_6, DCMI_7 */
OV2640 camera1(
    PF_15, PF_3,
    PD_13, PD_12, // I2C4
    PB_7, PD_8, PA_6,
    PC_6, PC_7, PC_8, PC_9, PC_11, PB_6, PB_8, PB_9
);

int main(void)
{
    t.start();
    printf("[%7lld] Start\n", t.elapsed_time().count()/1000);

    camera1.powerStateSet(CAMERA_PWR_ON) == CAMERA_OK ? 
        printf("[%7lld] Power on\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Power on failed\n", t.elapsed_time().count()/1000);

    camera1.hwReset() == CAMERA_OK ? 
        printf("[%7lld] Hardware reset\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Hardware reset fail\n", t.elapsed_time().count()/1000);

    camera1.idCheck(OV2640_ADDRESS, 0x7FA2, 0x2642) == CAMERA_OK ?
        printf("[%7lld] ID checked\n", t.elapsed_time().count()/1000):
        printf("[%7lld] ID check fail\n", t.elapsed_time().count()/1000);
    
    camera1.swReset(OV2640_ADDRESS) == CAMERA_OK ? 
        printf("[%7lld] Software Reset\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Software reset fail\n", t.elapsed_time().count()/1000); 

    camera1.init(OV2640_ADDRESS, CAMERA_RES_SXGA) == CAMERA_OK ? 
        printf("[%7lld] Inited\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Init fail\n", t.elapsed_time().count()/1000); 

    camera1.outputFormatSet(OV2640_ADDRESS, CAMERA_FMT_RGB565) == CAMERA_OK ? 
        printf("[%7lld] Output format set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output format set fail\n", t.elapsed_time().count()/1000); 

    camera1.outputResolutionSet(OV2640_ADDRESS, 16, 12) == CAMERA_OK ? 
        printf("[%7lld] Output resolution set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output resolution set fail\n", t.elapsed_time().count()/1000); 

    /* set FPS */
    camera1.captureFrameRateSet(OV2640_ADDRESS, 0x3F) == CAMERA_OK ? 
        printf("[%7lld] Capture frame rate set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Capture frame rate fail\n", t.elapsed_time().count()/1000); 

    camera1.outputClockFreqSet(OV2640_ADDRESS, 0x7F) == CAMERA_OK ? // this should be greater than 0x3A=58 when RGB565
        printf("[%7lld] Output frequency set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output frequency set fail\n", t.elapsed_time().count()/1000); 

    uint8_t* cap = (uint8_t*) malloc(sizeof(uint8_t) * 160 * 120 * 2);
    camera1.abandonFrames(3);
    uint32_t length = camera1.capture(cap);
    printf("[%7lld] Captured: %d\n", t.elapsed_time().count()/1000, length);

    if (length <= 5000)
    {
        for (int i=length%2; i<length; i+=2)
        {
            // printf("#%02X%02X%02X", cap[i]&0xF8, (cap[i]&0x07)<<5 | (cap[i+1]&0xE0)>>3, cap[i+1]&0x1F);
            // printf("#%02X%02X%02X", cap[i+1]&0xF8, (cap[i+1]&0x07)<<5 | (cap[i]&0xE0)>>3, cap[i]&0x1F);
            printf("%02X %02X ", cap[i], cap[i+1]);
        }
        printf("\n\n");
    }
    if (length <= 5000)
    {
        for (int i=length%2; i<length; i+=2)
        {
            // printf("%02X %02X %02X FF ", (cap[i+1]&0x1F)<<3, (cap[i]&0x07)<<5 | (cap[i+1]&0xE0)>>3, cap[i]&0xF8);
            printf("%02X %02X %02X FF ", (cap[i]&0x1F)<<3, (cap[i+1]&0x07)<<5 | (cap[i]&0xE0)>>3, cap[i+1]&0xF8); // BMP: B G R FF
        }
        printf("\n\n");
    }

    free(cap);
    printf("[%7lld] Pointer free\n", t.elapsed_time().count()/1000);

    camera1.powerStateSet(CAMERA_PWR_OFF);

	while (true)
    {
	}

}
