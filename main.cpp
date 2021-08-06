#include "mbed.h"
#include "include/camera/OV2640.hpp"
#include "mbed-os/storage/blockdevice/COMPONENT_I2CEE/include/I2CEE/I2CEEBlockDevice.h"

BufferedSerial pc(USBTX, USBRX, 115200);
Timer t;

/*  HW_PWR, HW_RST,
    I2C_SDA, I2C_SCL
    VSYNC, HSYNC, PCLK, 
    D0~D7 */
OV2640 camera1(
    PB_1, PA_8,
    PB_9, PB_8, // I2C1
    // PB_7, PA_5, PA_6,
    PB_7, PA_4, PA_6,
    // PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7
    PC_6, PC_7, PC_8, PC_9, PE_4, PD_3, PE_5, PE_6
);
DigitalOut flash(LED3);

DCMI_HandleTypeDef hdcmi;
DMA_HandleTypeDef hdma_dcmi;

#define CAM_DIM_W 16
#define CAM_DIM_H 12

uint8_t captureBuffer[CAM_DIM_W * CAM_DIM_H * 2] = {0};
uint32_t captureBuffer32[CAM_DIM_W * CAM_DIM_H * 2] = {0};

void MX_DMA_Init(void)
{
    /* DMA controller clock enable */
    __HAL_RCC_DMAMUX1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    // HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

void MX_DCMI_Init(void)
{
    hdcmi.Instance = DCMI;
    hdcmi.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
    hdcmi.Init.PCKPolarity = DCMI_PCKPOLARITY_RISING;
    hdcmi.Init.VSPolarity = DCMI_VSPOLARITY_LOW;
    hdcmi.Init.HSPolarity = DCMI_HSPOLARITY_LOW;
    hdcmi.Init.CaptureRate = DCMI_CR_ALL_FRAME;
    hdcmi.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
    hdcmi.Init.JPEGMode = DCMI_JPEG_DISABLE;
    hdcmi.Init.ByteSelectMode = DCMI_BSM_ALL;
    hdcmi.Init.ByteSelectStart = DCMI_OEBS_ODD;
    hdcmi.Init.LineSelectMode = DCMI_LSM_ALL;
    hdcmi.Init.LineSelectStart = DCMI_OELS_ODD;
    HAL_DCMI_Init(&hdcmi) == HAL_OK ? 
        printf("[%7lld] DCMI inited\n", t.elapsed_time().count()/1000):
        printf("[%7lld] DCMI init fail\n", t.elapsed_time().count()/1000);
}

void HAL_DCMI_MspInit(DCMI_HandleTypeDef* dcmiHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(dcmiHandle->Instance==DCMI)
    {
        /* DCMI clock enable */
        __HAL_RCC_DCMI_CLK_ENABLE();

        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**DCMI GPIO Configuration
        PE4     ------> DCMI_D4
        PE5     ------> DCMI_D6
        PE6     ------> DCMI_D7
        PA4     ------> DCMI_HSYNC
        PA6     ------> DCMI_PIXCLK
        PC6     ------> DCMI_D0
        PC7     ------> DCMI_D1
        PC8     ------> DCMI_D2
        PC9     ------> DCMI_D3
        PD3     ------> DCMI_D5
        PB7     ------> DCMI_VSYNC
        */
        GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_DCMI;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_DCMI;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_DCMI;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_DCMI;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_DCMI;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_DCMI;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_DCMI;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* DCMI DMA Init */
        /* DCMI Init */
        hdma_dcmi.Instance = DMA1_Channel1;
        hdma_dcmi.Init.Request = DMA_REQUEST_DCMI;
        hdma_dcmi.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_dcmi.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_dcmi.Init.MemInc = DMA_MINC_ENABLE;
        hdma_dcmi.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
        hdma_dcmi.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_dcmi.Init.Mode = DMA_CIRCULAR;
        hdma_dcmi.Init.Priority = DMA_PRIORITY_VERY_HIGH;
        HAL_DMA_Init(&hdma_dcmi) == HAL_OK ? 
            printf("[%7lld] DMA inited\n", t.elapsed_time().count()/1000):
            printf("[%7lld] DMA init fail\n", t.elapsed_time().count()/1000);

        __HAL_LINKDMA(dcmiHandle,DMA_Handle,hdma_dcmi);

        /* DCMI interrupt Init */
        //    HAL_NVIC_SetPriority(DCMI_IRQn, 0, 0);
        //    HAL_NVIC_EnableIRQ(DCMI_IRQn);
    }
}

void DMA1_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_dcmi);
}

void DCMI_IRQHandler(void)
{
    HAL_DCMI_IRQHandler(&hdcmi);
}

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    // while (true)
    // {
    //     flash = !flash;
    //     wait_us(100000);
    // }
    // HAL_UART_Transmit(&huart5, captureBuffer, CAM_DIM_W * CAM_DIM_H * 2, 1000);
}

int main(void)
{
    HAL_Init();
    
    t.start();
    pc.sync();
    printf("[%7lld] Start\n", t.elapsed_time().count()/1000);

    MX_DMA_Init();
    MX_DCMI_Init();

    __HAL_DCMI_DISABLE_IT(&hdcmi, DCMI_IT_LINE | DCMI_IT_VSYNC);
    // __HAL_DCMI_DISABLE_IT(&hdcmi, DCMI_IT_LINE | DCMI_IT_VSYNC | DCMI_IT_ERR | DCMI_IT_FRAME | DCMI_IT_OVR | DCMI_IT_OVF);
    // __HAL_DMA_DISABLE_IT(&hdma_dcmi, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE);

    camera1.powerStateSet(CAMERA_PWR_ON) == CAMERA_OK ? 
        printf("[%7lld] Power on\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Power on fail\n", t.elapsed_time().count()/1000);

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

    camera1.outputResolutionSet(OV2640_ADDRESS, CAM_DIM_W, CAM_DIM_H) == CAMERA_OK ? 
        printf("[%7lld] Output resolution set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output resolution set fail\n", t.elapsed_time().count()/1000);

    /* set FPS */
    camera1.captureFrameRateSet(OV2640_ADDRESS, 0x3F) == CAMERA_OK ? 
        printf("[%7lld] Capture frame rate set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Capture frame rate fail\n", t.elapsed_time().count()/1000);

    camera1.outputClockFreqSet(OV2640_ADDRESS, 0x7F) == CAMERA_OK ? 
        printf("[%7lld] Output frequency set\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Output frequency set fail\n", t.elapsed_time().count()/1000);

    ThisThread::sleep_for(1s);

    HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t)captureBuffer32, CAM_DIM_W * CAM_DIM_H * 2) == HAL_OK ? 
        printf("[%7lld] DCMI started\n", t.elapsed_time().count()/1000):
        printf("[%7lld] DCMI start fail\n", t.elapsed_time().count()/1000);

    while (true)
    {
        flash = !flash;

        // for (int i=0; i<CAM_DIM_W*CAM_DIM_H*2; i+=2)
        // {
        //     // printf("%02X ", cap[i]);
        //     printf("%02X %02X %02X FF ", (
        //         captureBuffer[i]&0x1F)<<3, 
        //         (captureBuffer[i+1]&0x07)<<5 | (captureBuffer[i]&0xE0)>>3, 
        //         captureBuffer[i+1]&0xF8);
        // }
        for (int i=0; i<CAM_DIM_W*CAM_DIM_H/2; i++)
        {
            printf("%08X ", captureBuffer32[i]);
        }
        // for (int i=0; i<CAM_DIM_W*CAM_DIM_H/2; i++)
        // {
        //     uint8_t outTmp[4];
        //     outTmp[0] = (captureBuffer32[i] & 0xFF000000)>>24;
        //     outTmp[0] = (captureBuffer32[i] & 0x00FF0000)>>16;
        //     outTmp[0] = (captureBuffer32[i] & 0x0000FF00)>>8;
        //     outTmp[0] = (captureBuffer32[i] & 0x000000FF)>>0;
        //     printf("%02X %02X %02X FF %02X %02X %02X FF ", 
        //         (outTmp[0]&0x1F)<<3, 
        //         (outTmp[1]&0x07)<<5 | (outTmp[0]&0xE0)>>3, 
        //         outTmp[1]&0xF8,
        //         (outTmp[2]&0x1F)<<3, 
        //         (outTmp[3]&0x07)<<5 | (outTmp[2]&0xE0)>>3, 
        //         outTmp[3]&0xF8
        //     );
        // }
        printf("\n");

        ThisThread::sleep_for(1s);
    }
}











#ifdef EMU

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

#endif