#include "mbed.h"
#include "include/camera/OV2640.hpp"
#include "mbed-os/storage/blockdevice/COMPONENT_I2CEE/include/I2CEE/I2CEEBlockDevice.h"
#include <chrono>
using namespace std::chrono;

/* 
 * GPIO Mapping
 * 
 * (GPIOA)
 * PA_0: T_CD0E, PA_1: T_CD1D, PA_2: T_CD1C, PA_4: OV2640_HSYNC, PA_6: OV2640_PCLK, PA_8: OV2640_RESET
 * 
 * (GPIOB)
 * PB_0: T_CD0D, PB_1: OV2640_POWER, PB_7: OV2640_VSYNC, PB_8: OV2640_I2C_SCL, PB_9: OV2640_I2C_SDA, PB_10: T_CD0A, PB_11: T_CD0B, PB_14: LED3
 * 
 * (GPIOC)
 * PC_2: T_CD1E, PC_6: OV2640_D0, PC_7: OV2640_D1, PC_8: OV2640_D2, PC_9: OV2640_D3
 * 
 * (GPIOD)
 * PD_3: OV2640_D5, PD_8: T_CD1A, PD_9: T_CD1B
 * 
 * (GPIOE)
 * PE_0: T_CD0C, PE_4: OV2640_D4, PE_5: OV2640_D6, PE_6: OV2640_D7, PE_7: T_CDG1, PE_8: T_CDR1, PE_10: T_R0, PE_12: T_G0, PE_13: T_CD1G, PE_14: T_CD0G, PE_15: T_CD0F
 * 
 * (GPIOF)
 * PF_15: T_CD1F
 */

// BufferedSerial pc(USBTX, USBRX, 400000);
BufferedSerial pc(USBTX, USBRX, 400000);
Timer t;
Timer clk;

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
OV2640 camera2(
    PB_1, PA_8,
    PB_9, PB_8, // I2C1
    PB_7, PA_4, PA_6,
    PC_6, PC_7, PC_8, PC_9, PE_4, PD_3, PE_5, PE_6
);
OV2640 camera3(
    PB_1, PA_8,
    PB_9, PB_8, // I2C1
    PB_7, PA_4, PA_6,
    PC_6, PC_7, PC_8, PC_9, PE_4, PD_3, PE_5, PE_6
);
OV2640 camera4(
    PB_1, PA_8,
    PB_9, PB_8, // I2C1
    PB_7, PA_4, PA_6,
    PC_6, PC_7, PC_8, PC_9, PE_4, PD_3, PE_5, PE_6
);
OV2640* cameraList[] = {&camera1, &camera2, &camera3, &camera4};

DigitalOut flash(LED3);

DCMI_HandleTypeDef hdcmi;
DMA_HandleTypeDef hdma_dcmi;

#define CAM_DIM_W 160
#define CAM_DIM_H 120

uint8_t captureBuffer[CAM_DIM_W * CAM_DIM_H * 2] = {0};
// uint32_t captureBuffer32[CAM_DIM_W * CAM_DIM_H / 2] = {0};

/* 5611AH/AS ED_CP BA_FG
 * DP is not connected
 */
/* CountDown and R/G light */
// ABCDEFG
BusOut t_cd0(PB_10, PB_11, PE_0, PB_0, PA_0, PE_15, PE_14);
DigitalOut t_r0(PE_10);
DigitalOut t_g0(PE_12);
BusOut t_cd1(PD_8, PD_9, PA_2, PA_1, PC_2, PF_15, PE_13);
DigitalOut t_r1(PE_8);
DigitalOut t_g1(PE_7);
BusOut t_cd2(PD_15, PF_12, PB_4, PB_3, PB_5, PD_14, PA_7);
DigitalOut t_r2(PF_13);
DigitalOut t_g2(PE_9);
BusOut t_cd3(PD_5, PD_4, PC_3, PC_0, PA_3, PD_6, PD_7);
DigitalOut t_r3(PC_1);
DigitalOut t_g3(PC_4);

BusOut* t_cdList[] = {&t_cd0, &t_cd1, &t_cd2, &t_cd3};
DigitalOut *t_rList[] = {&t_r0, &t_r1, &t_r2, &t_r3};
DigitalOut *t_gList[] = {&t_g0, &t_g1, &t_g2, &t_g3};

#define IDLE_COUNTDOWN_TIME 10
#define MAX_CONTINUOUS_TIME 100


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

void _debug(OV2640* camPtr)
{
    camPtr->powerStateSet(CAMERA_PWR_ON) == CAMERA_OK ? 
        printf("[%7lld] Power on\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Power on fail\n", t.elapsed_time().count()/1000);
    
    printf("\n");
    camPtr->SCCB_WR_Reg(0xFF, 0x00);
    for (int i=0; i<0x100; i++)
    {
        char readBuf = 0;
        readBuf = camPtr->SCCB_RD_Reg(i);
        printf("[%02X]%02X", i, readBuf);
        wait_us(10);
    }
    printf("\n");
    camPtr->SCCB_WR_Reg(0xFF, 0x01);
    for (int i=0; i<0x100; i++)
    {
        char readBuf = 0;
        readBuf = camPtr->SCCB_RD_Reg(i);
        printf("[%02X]%02X", i, readBuf);
        wait_us(10);
    }
    printf("\n\n");

    camPtr->powerStateSet(CAMERA_PWR_OFF) == CAMERA_OK ? 
        printf("[%7lld] Power off\n", t.elapsed_time().count()/1000):
        printf("[%7lld] Power off fail\n", t.elapsed_time().count()/1000);
}

void dcmiInit(void)
{
    HAL_Init();

    MX_DMA_Init();
    MX_DCMI_Init();

    __HAL_DCMI_DISABLE_IT(&hdcmi, DCMI_IT_LINE | DCMI_IT_VSYNC);
    // __HAL_DCMI_DISABLE_IT(&hdcmi, DCMI_IT_LINE | DCMI_IT_VSYNC | DCMI_IT_ERR | DCMI_IT_FRAME | DCMI_IT_OVR | DCMI_IT_OVF);
    // __HAL_DMA_DISABLE_IT(&hdma_dcmi, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE);

}

void cameraInit(OV2640* camPtr)
{
    camPtr->powerStateSet(CAMERA_PWR_ON) == CAMERA_OK ? 
        printf("[%7lld] Power on\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Power on fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    camPtr->hwReset() == CAMERA_OK ? 
        printf("[%7lld] Hardware reset\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Hardware reset fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    camPtr->idCheck(OV2640_ADDRESS, 0x7FA2, 0x2642) == CAMERA_OK ? 
        printf("[%7lld] ID checked\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] ID check fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());
    
    camPtr->swReset(OV2640_ADDRESS) == CAMERA_OK ? 
        printf("[%7lld] Software Reset\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Software reset fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    camPtr->init(OV2640_ADDRESS, CAMERA_RES_SXGA) == CAMERA_OK ? 
        printf("[%7lld] Inited\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Init fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    // camPtr->outputFormatSet(OV2640_ADDRESS, CAMERA_FMT_RGB565) == CAMERA_OK ? 
    camPtr->outputFormatSet(OV2640_ADDRESS, CAMERA_FMT_RGB565) == CAMERA_OK ? 
        printf("[%7lld] Output format set\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Output format set fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());
    
    // sensor resolution
    camPtr->imageSizeSet(OV2640_ADDRESS, 1600, 1200) == CAMERA_OK ? 
        printf("[%7lld] Output resolution set\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Output resolution set fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());
    camPtr->windowSet(OV2640_ADDRESS, 0, 0, 1600, 1200);
    camPtr->imageWinSet(OV2640_ADDRESS, 400, 300, 1200, 900);
    
    camPtr->outputResolutionSet(OV2640_ADDRESS, CAM_DIM_W*2, CAM_DIM_H*2) == CAMERA_OK ? 
        printf("[%7lld] Output resolution set\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Output resolution set fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    camPtr->outputClockFreqSet(OV2640_ADDRESS, 0x07) == CAMERA_OK ? 
        printf("[%7lld] Output frequency set\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Output frequency set fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    camPtr->captureFrameRateSet(0x60, 0x03) == CAMERA_OK ? 
        printf("[%7lld] Output frequency set\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Output frequency set fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());


    // camPtr->lightModeSet(3);
    // camPtr->colorSaturationSet(2);
    // camPtr->brightnessSet(2);
    // camPtr->contrastSet(2);
    // camPtr->autoExposureSet(2);

    // camPtr->specialEffectSet(0);

    camPtr->colorBarSet(OV2640_ADDRESS, false) == CAMERA_OK ? 
        printf("[%7lld] Color bar set\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Color bar set fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    camPtr->powerStateSet(CAMERA_PWR_OFF) == CAMERA_OK ? 
        printf("[%7lld] Power off\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
        printf("[%7lld] Power off fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());
}

/**
 * @brief display a single number on a seven-segment display
 * 
 * @param sevenSeg BusOut that will display number
 * @param number the number that will be shown
 */
void dispNum(BusOut* sevenSeg, uint8_t number)
{
	/*
					 GFE DCBA
		0	0x3F	0011 1111
		1	0x06	0000 0110
		2	0x5B	0101 1011
		3	0x4F	0100 1111
		4	0x66	0110 0110
		5	0x6D	0110 1101
		6	0x7D	0111 1101
		7	0x07	0000 0111
		8	0x7F	0111 1111
		9	0x6F	0110 1111
	*/
	switch(number)
	{
		case 0: *sevenSeg = 0x3F; break;
		case 1: *sevenSeg = 0x06; break;
		case 2: *sevenSeg = 0x5B; break;
		case 3: *sevenSeg = 0x4F; break;
		case 4: *sevenSeg = 0x66; break;
		case 5: *sevenSeg = 0x6D; break;
		case 6: *sevenSeg = 0x7D; break;
		case 7: *sevenSeg = 0x07; break;
		case 8: *sevenSeg = 0x7F; break;
		case 9: *sevenSeg = 0x6F; break;
        case 255: *sevenSeg = 0x00; break; // clear display
	}

}

void change(uint8_t current, uint8_t next)
{
    if (current>=0 && current<=3 && next>=0 && next<=3)
    {
        if (current != next)
        {
            // 3
            dispNum(t_cdList[current], 3);
            dispNum(t_cdList[next], 3);
            *t_gList[current] = 0;
            ThisThread::sleep_for(500ms);
            *t_gList[current] = 1;
            ThisThread::sleep_for(500ms);
            // 2
            dispNum(t_cdList[current], 2);
            dispNum(t_cdList[next], 2);
            *t_gList[current] = 0;
            ThisThread::sleep_for(500ms);
            *t_gList[current] = 1;
            ThisThread::sleep_for(500ms);
            // 1
            dispNum(t_cdList[current], 1);
            dispNum(t_cdList[next], 1);
            *t_gList[current] = 0;
            ThisThread::sleep_for(500ms);
            *t_gList[current] = 1;
            ThisThread::sleep_for(500ms);

            // move to next road
            dispNum(t_cdList[current], 255);
            dispNum(t_cdList[next], 255);
            for (uint8_t i=0; i<4; i++)
            {
                *t_rList[i] = 1;
                *t_gList[i] = 0;
            }
            *t_rList[next] = 0;
            *t_gList[next] = 1;
        }
        else
        {
            // do nothing
        }
    }
    else
    {

    }
    
}


int main(void)
{
    t.start();
    clk.start();
    pc.sync();
    printf("[%7lld] Start\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    dcmiInit();
    cameraInit(&camera1);

    // _debug(&camera1);
    ThisThread::sleep_for(1s); 

    // HAL_DCMI_ConfigCrop(&hdcmi, 48, 36, 48, 36);
    // HAL_DCMI_ConfigCrop(&hdcmi, 12, 9, 12, 9);
    // HAL_DCMI_EnableCrop(&hdcmi);

    // camera1.powerStateSet(CAMERA_PWR_ON) == CAMERA_OK ? 
    //     printf("[%7lld] Power on\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
    //     printf("[%7lld] Power on fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

    uint8_t last = 3;
    uint8_t now = 0;
    float cond[4]={0.0, 0.0, 0.0, 0.0};
    change(last, now);

    while (true)
    {
        clk.reset();
        flash = !flash;

        for (int i=0; i<4; i++)
        {
            cameraList[i]->powerStateSet(CAMERA_PWR_ON) == CAMERA_OK ? 
            printf("[%7lld] Power on\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
            printf("[%7lld] Power on fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

            cameraList[i]->abandonFrames(1);
            /* Start DCMI-DMA transfer */
            //                         capture mode          buffer for storage         dimension(in uint32_t)
            HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)captureBuffer, CAM_DIM_W * CAM_DIM_H * 2) == HAL_OK ? 
                printf("[%7lld] DCMI started\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
                printf("[%7lld] DCMI start fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            cameraList[i]->abandonFrames(10);
            HAL_DCMI_Stop(&hdcmi) == HAL_OK ? 
                printf("[%7lld] DCMI stopped\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
                printf("[%7lld] DCMI stop fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

            cameraList[i]->powerStateSet(CAMERA_PWR_OFF) == CAMERA_OK ? 
                printf("[%7lld] Power off\n", duration_cast<milliseconds>(t.elapsed_time()).count()):
                printf("[%7lld] Power off fail\n", duration_cast<milliseconds>(t.elapsed_time()).count());

            /* TODO: img process */
            
            ThisThread::sleep_for(500ms);
        }
        
        // obtained picture should be 4 frames in a line (use CAM_DIM_W*2 x CAM_DIM_H/2 to demonstrate)
        // for (int i=0; i<CAM_DIM_H/2; i++)
        // {
        //     for (int j=0; j<CAM_DIM_W; j+=2)
        //     {
        //         printf("%02X%02X", captureBuffer[i*CAM_DIM_W*2+j], captureBuffer[i*CAM_DIM_W*2+j+1]); // RGB565
        //         // printf("%02X%02X%02XFF",
        //         //     (captureBuffer[i*CAM_DIM_W*2+j]  &0x1F)<<3,                                            // R
        //         //     (captureBuffer[i*CAM_DIM_W*2+j+1]&0x07)<<5 | (captureBuffer[i*CAM_DIM_W*2+j]&0xE0)>>3, // G
        //         //      captureBuffer[i*CAM_DIM_W*2+j+1]&0xF8                                                 // B
        //         // );
        //         // printf("%02X%02X%02XFF",
        //         //     /*R*/ captureBuffer[i*CAM_DIM_W*2+j  ]&0xF8,
        //         //     /*G*/(captureBuffer[i*CAM_DIM_W*2+j  ]&0x07)<<5 | (captureBuffer[i*CAM_DIM_W*2+j+1]&0xE0)>>3,
        //         //     /*B*/(captureBuffer[i*CAM_DIM_W*2+j+1]&0x1F)<<3
        //         // );
        //     }
        // }
        // for (int i=0; i<CAM_DIM_W*CAM_DIM_H*2; i+=2)
        // {
        //     printf("%02X%02X", captureBuffer[i], captureBuffer[i+1]);
        //     // printf("%02X%02X%02XFF",
        //     //      captureBuffer[i  ]&0xF8,                                    // R
        //     //     (captureBuffer[i  ]&0x07)<<5 | (captureBuffer[i+1]&0xE0)>>3, // G
        //     //     (captureBuffer[i+1]&0x1F)<<3                                 // B
        //     // );
        // }
        // for (int i=0; i<CAM_DIM_W*CAM_DIM_H/2; i++)
        // {
        //     // printf("%02X%02X%02XFF%02X%02X%02XFF", 
        //     //     (captureBuffer32[i]&0x001F0000)>>16<<3,                                          // R
        //     //     (captureBuffer32[i]&0x07000000)>>24<<5 | (captureBuffer32[i]&0x00E00000)>>16>>3, // G
        //     //      captureBuffer32[i]&0xF8000000 >>24,                                             // B
        //     //     (captureBuffer32[i]&0x0000001F)<<3,
        //     //     (captureBuffer32[i]&0x00000700)>>8<<5 | (captureBuffer32[i]&0x000000E0)>>3, 
        //     //      captureBuffer32[i]&0x0000F800 >>8
        //     // );
        //     // printf("%02X%02X%02XFF%02X%02X%02XFF", 
        //     //      captureBuffer32[i]&0xF8000000 >>24,                                          // R
        //     //     (captureBuffer32[i]&0x07000000)>>24<<2 | (captureBuffer32[i]&0x00E00000)>>16, // G
        //     //     (captureBuffer32[i]&0x001F0000)>>16<<3,                                       // B
        //     //      captureBuffer32[i]&0x0000F800 >>8,
        //     //     (captureBuffer32[i]&0x00000700)>>8<<2 | (captureBuffer32[i]&0x000000E0),
        //     //     (captureBuffer32[i]&0x0000001F)<<3
        //     // );
        // }
        // printf("\n\n");

        while (duration_cast<seconds>(clk.elapsed_time()).count() < IDLE_COUNTDOWN_TIME - 3);

        for (uint8_t i=0; i<4; i++)
        {
            srand(duration_cast<microseconds>(t.elapsed_time()).count());
            cond[i] = rand() / (float)RAND_MAX * 10;
        }
        printf("[%7lld] %.6f %.6f %.6f %.6f\n", duration_cast<milliseconds>(t.elapsed_time()).count(), cond[0], cond[1], cond[2], cond[3]);

        last = now;
        float max = cond[0];
        uint8_t max_id = 0;
        for (uint8_t i=1; i<4; i++)
        {
            if (cond[i] >= max)
            {
                max = cond[i];
                max_id = i;
            }
        }
        now = max_id;

        printf("[%7lld] prev: %d, next: %d\n", duration_cast<milliseconds>(t.elapsed_time()).count(), last, now);
        change(last, now);

        // ThisThread::sleep_for(2s);
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