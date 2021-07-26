#include "mbed.h"
#include "include/camera/OV2640.hpp"
#include "mbed-os/storage/blockdevice/COMPONENT_I2CEE/include/I2CEE/I2CEEBlockDevice.h"

BufferedSerial pc(USBTX, USBRX, 115200);
Timer t;

/*  HW_PWR, HW_RST,
    I2C_SDA, I2C_SCL, 
    DCMI_VSYNC, DCMI_HSYNC, DCMI_PCLK, 
    DCMI_0, DCMI_1, DCMI_2, DCMI_3, DCMI_4, DCMI_5, DCMI_6, DCMI_7 */
OV2640 camera1(
    PB_1, PA_8,
    PB_9, PB_8, // I2C1
    PB_7, PA_5, PA_6,
    // PB_1, PA_9, PB_2, PC_7, PB_11, PB_6, PB_12, PA_7
    PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7
);

I2C bd_i2c(PF_0, PF_1); // I2C2
I2CEEBlockDevice bd(&bd_i2c, 0xA0, 64*1024, 32, false); // 512 kb = 64 kB

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

    camera1.outputResolutionSet(OV2640_ADDRESS, 112, 84) == CAMERA_OK ? 
        printf("[%7lld] Output resolution set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output resolution set fail\n", t.elapsed_time().count()/1000); 

    /* set FPS */
    camera1.captureFrameRateSet(OV2640_ADDRESS, 0x3F) == CAMERA_OK ? 
        printf("[%7lld] Capture frame rate set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Capture frame rate fail\n", t.elapsed_time().count()/1000); 

    camera1.outputClockFreqSet(OV2640_ADDRESS, 0x7F) == CAMERA_OK ? 
        printf("[%7lld] Output frequency set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output frequency set fail\n", t.elapsed_time().count()/1000); 

    uint8_t* cap = (uint8_t*) malloc(sizeof(uint8_t) * 160 * 120 * 2);
    camera1.abandonFrames(5);
    uint32_t length = camera1.capture(cap);
    printf("[%7lld] Captured: %d\n", t.elapsed_time().count()/1000, length);

    /* if (length <= 5000)
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
    } */

    bd.init() == 0 ?
        printf("[%7lld] BD inited\n", t.elapsed_time().count()/1000):
        printf("[%7lld] BD init fail\n", t.elapsed_time().count()/1000); 

    printf("[%7lld] Saving\n", t.elapsed_time().count()/1000);

    const char bmp_header[] = 
    {
        0x42, 0x4D,             // header: BM
        0x00, 0x00, 0x01, 0x00, // size: 65536
        0x00, 0x00, 0x00, 0x00, // reserved
        0x36, 0x00, 0x00, 0x00, 
        
        0x28, 0x00, 0x00, 0x00, 
        // 0x50, 0x00, 0x00, 0x00, // width: 80
        // 0xC4, 0xFF, 0xFF, 0xFF, // height: -60
        0x70, 0x00, 0x00, 0x00, // width: 112
        0xAC, 0xFF, 0xFF, 0xFF, // height: -84
        0x01, 0x00, 
        0x20, 0x00, 
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00,
    };
    bd.program(bmp_header, 0, sizeof(bmp_header)) == 0 ?
        :
        printf("[%7lld] Save fail\n", t.elapsed_time().count()/1000); 

    char bmp_pxBuffer[4] = {0x00, 0x00, 0x00, 0xFF}; // B, G, R, reserved
    bool _err = false;
    // for (int i=0; i<sizeof(uint8_t) * 80 * 60 * 2; i+=2)
    for (int i=0; i<length; i+=2)
    {
        bmp_pxBuffer[0] = (cap[i]&0x1F)<<3;
        bmp_pxBuffer[1] = (cap[i+1]&0x07)<<5 | (cap[i]&0xE0)>>3;
        bmp_pxBuffer[2] = cap[i+1]&0xF8;
        bd.program(bmp_pxBuffer, sizeof(bmp_header) + 2*i, 4) == 0 ?
            :
            _err = true;
    }
    _err == false ? 
        printf("[%7lld] Save success\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Save fail\n", t.elapsed_time().count()/1000); 
        
    bd.deinit() == 0 ?
        printf("[%7lld] BD deinited\n", t.elapsed_time().count()/1000):
        printf("[%7lld] BD deinit fail\n", t.elapsed_time().count()/1000); 

    free(cap);
    printf("[%7lld] Pointer free\n", t.elapsed_time().count()/1000);

    camera1.powerStateSet(CAMERA_PWR_OFF);

	while (true)
    {
	}

}
