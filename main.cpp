#include "mbed.h"
#include "include/camera/OV2640.hpp"
#include "stm32l4xx_ll_gpio.h"

BufferedSerial pc(USBTX, USBRX, 115200);
Timer t;

/*  HW_PWR, HW_RST,
    I2C_SDA, I2C_SCL, 
    DCMI_VSYNC, DCMI_HSYNC, DCMI_PCLK, 
    DCMI_0, DCMI_1, DCMI_2, DCMI_3, DCMI_4, DCMI_5, DCMI_6, DCMI_7 */
OV2640 camera1(
    PF_15, PF_3,
    PD_13, PD_12,
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

    camera1.outputClockFreqSet(OV2640_ADDRESS, 0x7F) == CAMERA_OK ? 
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
            // printf("#%02x%02x%02x", cap[i]&0xF8, (cap[i]&0x07)<<5 | (cap[i+1]&0xE0)>>3, cap[i+1]&0x1F);
            // printf("#%02x%02x%02x", cap[i+1]&0xF8, (cap[i+1]&0x07)<<5 | (cap[i]&0xE0)>>3, cap[i]&0x1F);
            printf("%02x %02x ", cap[i], cap[i+1]);
        }
        printf("\n\n");
    }
    if (length <= 5000)
    {
        for (int i=length%2; i<length; i+=2)
        {
            // printf("#%02x%02x%02x", cap[i]&0xF8, (cap[i]&0x07)<<5 | (cap[i+1]&0xE0)>>3, cap[i+1]&0x1F);
            // printf("#%02x%02x%02x", cap[i+1]&0xF8, (cap[i+1]&0x07)<<5 | (cap[i]&0xE0)>>3, cap[i]&0x1F);
            // printf("%02x %02x ", cap[i], cap[i+1]);
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



#ifdef old

typedef enum
{
	cam_pwrOn = 0, 
	cam_pwrOff = 1
} cam_pwrState;

DigitalOut cam_pwr(PF_15);
DigitalOut cam_rst(PF_3);

I2C cam_cmd(PD_13, PD_12); // SDA, SCL
DigitalIn cam_sigV(PB_7);
DigitalIn cam_sigH(PD_8);
DigitalIn cam_sigC(PA_6);
BusIn cam_dat(PC_6, PC_7, PC_8, PC_9, PC_11, PB_6, PB_8, PB_9);

typedef enum
{
  CAMERA_OK            = 0x00,
  CAMERA_ERROR         = 0x01,
  CAMERA_TIMEOUT       = 0x02,
  CAMERA_NOT_DETECTED  = 0x03,
  CAMERA_NOT_SUPPORTED = 0x04

} Camera_StatusTypeDef;

Camera_StatusTypeDef BSP_CAMERA_Init(void);
void BSP_CAMERA_PwrUp(void);
Camera_StatusTypeDef cam_checkId(uint16_t, uint16_t);
void ov9655_Init(void);

int main()
{
    t.start();
    printf("[%7lld] Start\n", t.elapsed_time().count()/1000);

    cam_cmd.stop();
    cam_cmd.frequency(100000);

    /* test */
    LL_GPIO_SetPinSpeed(
        GPIOA, 
        LL_GPIO_PIN_6, 
        LL_GPIO_SPEED_FREQ_VERY_HIGH
    );
    LL_GPIO_SetPinSpeed(
        GPIOB, 
        LL_GPIO_PIN_6|LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9, 
        LL_GPIO_SPEED_FREQ_VERY_HIGH
    );
    LL_GPIO_SetPinSpeed(
        GPIOC, 
        LL_GPIO_PIN_6|LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_11, 
        LL_GPIO_SPEED_FREQ_VERY_HIGH
    );
    LL_GPIO_SetPinSpeed(
        GPIOD, 
        LL_GPIO_PIN_8, 
        LL_GPIO_SPEED_FREQ_VERY_HIGH
    );

    printf(
        BSP_CAMERA_Init() == CAMERA_OK ? 
        "[%7lld] Init success\n":"[%7lld] Init fail\n", 
        t.elapsed_time().count()/1000
    );

    // resize output to 80*60
    char resize_reg_tbl[][2] = 
    {
        0xFF, 0x00,
        0xE0, 0x04,
        // 0x5A, 0x04,		// width = 16  -> hsize = 4 = 0x04
        // 0x5B, 0x03,  	// height = 12 -> vsize = 3 = 0x03
        // 0x5C, 0x00,
        // 0x5A, 0x08,		// width = 32  -> hsize = 8 = 0x08
        // 0x5B, 0x06,  	// height = 24 -> vsize = 6 = 0x06
        // 0x5C, 0x00,
        0x5A, 0xC8, 		// 80 -> 20
        0x5B, 0x96, 		// 60 -> 15
        0x5C, 0x00,
        0xE0, 0x00
    };
    for (int i=0; i<sizeof(resize_reg_tbl)/2; i++)
    {
        if (cam_cmd.write(0x60, resize_reg_tbl[i], 2, false))
        {
            printf("[%7lld] Failure: setting output size\n", t.elapsed_time().count()/1000);
        }
    }
    printf("[%7lld] Output size set to 80*60\n", t.elapsed_time().count()/1000);

    uint8_t* cap = (uint8_t*) malloc(sizeof(uint8_t) * 160 * 120 * 2);
    uint32_t length = 0;

    for(int i=0; i<3; i++) // abandon 3 frames
    {
        while(cam_sigV==1);	 
        while(cam_sigV==0);
    }
    while(cam_sigV == 1) //开始采集数据
    {
        while(cam_sigH == 1)
        {  
            while(cam_sigC==0); 
            cap[length]=cam_dat;
            while(cam_sigC==1);  
            length++;
        }
    }
    printf("[%7lld] Captured: %d\n", t.elapsed_time().count()/1000, length-1);

    if (length <= 5000)
    {
        for (int i=length%2; i<length; i+=2)
        {
            // printf("#%02x%02x%02x", cap[i]&0xF8, (cap[i]&0x07)<<5 | (cap[i+1]&0xE0)>>3, cap[i+1]&0x1F);
            printf("%02x %02x ", cap[i], cap[i+1]);
        }
        printf("\n");
    }

    free(cap);
    printf("[%7lld] Pointer free\n", t.elapsed_time().count()/1000);

    cam_pwr = cam_pwrOff;

	while (true)
    {

	}
}

Camera_StatusTypeDef BSP_CAMERA_Init(void)
{
    Camera_StatusTypeDef status = CAMERA_ERROR;

    /* Set up the Camera */
    BSP_CAMERA_PwrUp();
    printf("[%7lld] Power on\n", t.elapsed_time().count()/1000);

    cam_rst = 0;
    wait_us(10000);
    cam_rst = 1;
    wait_us(10000);

    /* Read ID of Camera module via I2C */
    if(cam_checkId(0x7FA2, 0x2642) == CAMERA_OK)
    {
        printf("[%7lld] ID checked\n", t.elapsed_time().count()/1000);

        // camera_drv->Init(CameraHwAddress, Resolution);
        ov9655_Init();

        /* Set the RGB565 mode */
        // for (int i=0; i<sizeof(ov2640_rgb565_reg_tbl)/2; i++)
        // {
        // 	if (cam_cmd.write(0x60, ov2640_rgb565_reg_tbl[i], 2, false))
        // 	{
        // 		printf("[%7lld] Failure: setting format RGB565\n", t.elapsed_time().count()/1000);
        // 	}
        // }
        // printf("[%7lld] Format set to RGB565\n", t.elapsed_time().count()/1000);
        // for (int i=0; i<sizeof(ov2640_raw_reg_tbl)/2; i++)
        // {
        // 	if (cam_cmd.write(0x60, ov2640_raw_reg_tbl[i], 2, false))
        // 	{
        // 		printf("[%7lld] Failure: setting format RAW\n", t.elapsed_time().count()/1000);
        // 	}
        // }
        // printf("[%7lld] Format set to RAW\n", t.elapsed_time().count()/1000);
        /* Set the YUV422 mode */
        for (int i=0; i<sizeof(ov2640_yuv422_reg_tbl)/2; i++)
        {
            if (cam_cmd.write(0x60, ov2640_yuv422_reg_tbl[i], 2, false))
            {
                printf("[%7lld] Failure: setting format YUV422\n", t.elapsed_time().count()/1000);
            }
        }
        printf("[%7lld] Format set to YUV422\n", t.elapsed_time().count()/1000);
        for (int i=0; i<sizeof(ov2640_jpg_reg_tbl)/2; i++)
        {
            if (cam_cmd.write(0x60, ov2640_jpg_reg_tbl[i], 2, false))
            {
                printf("[%7lld] Failure: setting format JPEG\n", t.elapsed_time().count()/1000);
            }
        }
        printf("[%7lld] Format set to JPEG\n", t.elapsed_time().count()/1000);

        /* Return CAMERA_OK status */
        status = CAMERA_OK;
    }
    else
    {
        printf("[%7lld] ID failure\n", t.elapsed_time().count()/1000);

        /* Return CAMERA_NOT_SUPPORTED status */
        status = CAMERA_NOT_SUPPORTED;
    }

    return status;
}

void BSP_CAMERA_PwrUp(void)
{
	/* De-assert the camera POWER_DOWN pin (active high) */
	cam_pwr = cam_pwrOn;

	wait_us(3000);     /* POWER_DOWN de-asserted during 3ms */
}

Camera_StatusTypeDef cam_checkId(uint16_t m, uint16_t p)
{
	uint16_t mid = 0, pid = 0; // manufacture ID, p ID

	char mid_addr[2] = {0x1C, 0x1D}, mid_buffer[2], 
		 pid_addr[2] = {0x0A, 0x0B}, pid_buffer[2];
	
	cam_cmd.write(0x60, &mid_addr[0], 1, false);
	cam_cmd.read(0x61, &mid_buffer[0], 1, false);
	// printf("[%7lld] Debug buffer: %x\n", t.elapsed_time().count()/1000, mid_buffer[0]);
	cam_cmd.write(0x60, &mid_addr[1], 1, false);
	cam_cmd.read(0x61, &mid_buffer[1], 1, false);
	// printf("[%7lld] Debug buffer: %x\n", t.elapsed_time().count()/1000, mid_buffer[1]);
	mid = (mid_buffer[0] << 8) + mid_buffer[1];
	// printf("[%7lld] Obtained MID: %x\n", t.elapsed_time().count()/1000, mid);
	// should be 0x7FA2

	cam_cmd.write(0x60, &pid_addr[0], 1, false);
	cam_cmd.read(0x61, &pid_buffer[0], 1, false);
	// printf("[%7lld] Debug buffer: %x\n", t.elapsed_time().count()/1000, pid_buffer[0]);
	cam_cmd.write(0x60, &pid_addr[1], 1, false);
	cam_cmd.read(0x61, &pid_buffer[1], 1, false);
	// printf("[%7lld] Debug buffer: %x\n", t.elapsed_time().count()/1000, pid_buffer[1]);
	pid = (pid_buffer[0] << 8) + pid_buffer[1];
	// printf("[%7lld] Obtained PID: %x\n", t.elapsed_time().count()/1000, pid);
	// should be 0x2642

	if (mid != m || pid != p)
	{
		printf("[%7lld] MID=%4x, PID=%4x (expected: 0x7FA2 and 0x2642)\n", t.elapsed_time().count()/1000, mid, pid);
		return CAMERA_NOT_SUPPORTED;
	}
	else
	{
		return CAMERA_OK;
	}
}

void ov9655_Init(void)
{
	uint32_t index;

	char cam_cmd_wrbuf_sensor[2] = {0xFF, 0x01};
	cam_cmd.write(0x60, cam_cmd_wrbuf_sensor, 2, false);
	wait_us(200000);
	char cam_cmd_wrbuf_reset[2] = {0x12, 0x80};
	cam_cmd.write(0x60, cam_cmd_wrbuf_reset, 2, false);
	wait_us(200000);

	/* Initialize OV9655 */
	for(index=0; index<(sizeof(ov2640_sxga_init_reg_tbl)/2); index++)
	{
		// CAMERA_IO_Write(DeviceAddr, OV9655_QQVGA[index][0], OV9655_QQVGA[index][1]);
		// CAMERA_Delay(2);
		cam_cmd.write(0x60, ov2640_sxga_init_reg_tbl[index], 2, false);
		wait_us(2000);
	}

}

#endif