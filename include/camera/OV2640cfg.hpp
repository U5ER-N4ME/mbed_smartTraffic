#ifndef MBED_3RD_OV2640CFG_HPP
#define MBED_3RD_OV2640CFG_HPP

/* Initialization sequence for UXGA resolution (1600x1200)*/
const char OV2640_UXGA[][2]=
{
	0xff, 0x00,
	0x2c, 0xff,
	0x2e, 0xdf,
	0xff, 0x01,
	0x3c, 0x32,
	0x11, 0x00,
	0x09, 0x02,
	0x04, 0xD8,	//水平垂直翻转
	0x13, 0xe5,
	0x14, 0x48,
	0x2c, 0x0c,
	0x33, 0x78,
	0x3a, 0x33,
	0x3b, 0xfB,
	0x3e, 0x00,
	0x43, 0x11,
	0x16, 0x10,
	0x4a, 0x81,
	0x21, 0x99,
	0x24, 0x40,
	0x25, 0x38,
	0x26, 0x82,
	0x5c, 0x00,
	0x63, 0x00,
	0x46, 0x3f,
	0x0c, 0x3c,
	0x61, 0x70,
	0x62, 0x80,
	0x7c, 0x05,
	0x20, 0x80,
	0x28, 0x30,
	0x6c, 0x00,
	0x6d, 0x80,
	0x6e, 0x00,
	0x70, 0x02,
	0x71, 0x94,
	0x73, 0xc1,
	0x3d, 0x34,
	0x5a, 0x57,
	0x12, 0x00,
	0x11, 0x00,//0x00，15帧 0x80，30帧
	0x17, 0x11,
	0x18, 0x75,
	0x19, 0x01,
	0x1a, 0x97,
	0x32, 0x36,
	0x03, 0x0f,
	0x37, 0x40,
	0x4f, 0xbb,
	0x50, 0x9c,
	0x5a, 0x57,
	0x6d, 0x80,
	0x6d, 0x38,
	0x39, 0x02,
	0x35, 0x88,
	0x22, 0x0a,
	0x37, 0x40,
	0x23, 0x00,
	0x34, 0xa0,
	0x36, 0x1a,
	0x06, 0x02,
	0x07, 0xc0,
	0x0d, 0xb7,
	0x0e, 0x01,
	0x4c, 0x00,
	0xff, 0x00,
	0xe5, 0x7f,
	0xf9, 0xc0,
	0x41, 0x24,
	0xe0, 0x14,
	0x76, 0xff,
	0x33, 0xa0,
	0x42, 0x20,
	0x43, 0x18,
	0x4c, 0x00,
	0x87, 0xd0,
	0x88, 0x3f,
	0xd7, 0x03,
	0xd9, 0x10,
	0xd3, 0x82,
	0xc8, 0x08,
	0xc9, 0x80,
	0x7d, 0x00,
	0x7c, 0x03,
	0x7d, 0x48,
	0x7c, 0x08,
	0x7d, 0x20,
	0x7d, 0x10,
	0x7d, 0x0e,
	0x90, 0x00,
	0x91, 0x0e,
	0x91, 0x1a,
	0x91, 0x31,
	0x91, 0x5a,
	0x91, 0x69,
	0x91, 0x75,
	0x91, 0x7e,
	0x91, 0x88,
	0x91, 0x8f,
	0x91, 0x96,
	0x91, 0xa3,
	0x91, 0xaf,
	0x91, 0xc4,
	0x91, 0xd7,
	0x91, 0xe8,
	0x91, 0x20,
	0x92, 0x00,
	0x93, 0x06,
	0x93, 0xe3,
	0x93, 0x02,
	0x93, 0x02,
	0x93, 0x00,
	0x93, 0x04,
	0x93, 0x00,
	0x93, 0x03,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x96, 0x00,
	0x97, 0x08,
	0x97, 0x19,
	0x97, 0x02,
	0x97, 0x0c,
	0x97, 0x24,
	0x97, 0x30,
	0x97, 0x28,
	0x97, 0x26,
	0x97, 0x02,
	0x97, 0x98,
	0x97, 0x80,
	0x97, 0x00,
	0x97, 0x00,
	0xc3, 0xef,
	0xff, 0x00,
	0xba, 0xdc,
	0xbb, 0x08,
	0xb6, 0x24,
	0xb8, 0x33,
	0xb7, 0x20,
	0xb9, 0x30,
	0xb3, 0xb4,
	0xb4, 0xca,
	0xb5, 0x43,
	0xb0, 0x5c,
	0xb1, 0x4f,
	0xb2, 0x06,
	0xc7, 0x00,
	0xc6, 0x51,
	0xc5, 0x11,
	0xc4, 0x9c,
	0xbf, 0x00,
	0xbc, 0x64,
	0xa6, 0x00,
	0xa7, 0x1e,
	0xa7, 0x6b,
	0xa7, 0x47,
	0xa7, 0x33,
	0xa7, 0x00,
	0xa7, 0x23,
	0xa7, 0x2e,
	0xa7, 0x85,
	0xa7, 0x42,
	0xa7, 0x33,
	0xa7, 0x00,
	0xa7, 0x23,
	0xa7, 0x1b,
	0xa7, 0x74,
	0xa7, 0x42,
	0xa7, 0x33,
	0xa7, 0x00,
	0xa7, 0x23,
	0xc0, 0xc8,
	0xc1, 0x96,
	0x8c, 0x00,
	0x86, 0x3d,
	0x50, 0x92,
	0x51, 0x90,
	0x52, 0x2c,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x88,
	0x5a, 0x50,
	0x5b, 0x3c,
	0x5c, 0x00,
	0xd3, 0x08,
	0x7f, 0x00,
	0xda, 0x00,
	0xe5, 0x1f,
	0xe1, 0x67,
	0xe0, 0x00,
	0xdd, 0x7f,
	0x05, 0x00,
	0xff, 0x00,
	0xe0, 0x04,
	0xc0, 0xc8,
	0xc1, 0x96,
	0x86, 0x3d,
	0x50, 0x92,
	0x51, 0x90,
	0x52, 0x2c,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x88,
	0x57, 0x00,
	0x5a, 0x50,
	0x5b, 0x3c,
	0x5c, 0x00,
	0xd3, 0x04,//系统时钟
	0xe0, 0x00,
	0xFF, 0x00,
	0x05, 0x00,
	0xDA, 0x08,
	0xda, 0x09,
	0x98, 0x00,
	0x99, 0x00,
	0x00, 0x00,

	//  0xff, 0x00,
	//  0xe0, 0x04,
	//  0xc0, 0xc8,
	//  0xc1, 0x96,
	//  0x86, 0x35,
	//  0x50, 0x80,//必须配置这个寄存器控制时钟
	//  0x51, 0x90,
	//  0x52, 0x2c,
	//  0x53, 0x00,
	//  0x54, 0x00,
	//  0x55, 0x88,
	//  0x57, 0x00,
	//  0x5a, 0x78,//480
	//  0x5b, 0x44,//272
	//  0x5c, 0x00,
	//  0xd3, 0x04,
	//  0xe0, 0x00,

};

/* Initialization sequence for SXGA resolution (1600*1200 ? 1280x1024)*/
const char ov2640_sxga_init_reg_tbl[][2]= 
{   
	{0xff, 0x00},
	{0x2c, 0xff},
	{0x2e, 0xdf},
	{0xff, 0x01},
	{0x3c, 0x32},
	//
	{0x11, 0x00}, // 0 0 00000: internal freq doubler OFF, clock divided by 1
	{0x09, 0x02}, // 000 0 0 0 10: normal mode, output drive 2x capability
	{0x04, 0xD8}, // 1 1 0 1 1 0 00: H mirror, V flip, 水平镜像,垂直翻转
	{0x13, 0xe5}, // 11 1 00 1 0 1: min exposure time 1/120s, AGC auto ctrl, auto exposure
	{0x14, 0x48}, // 010 01000: AGC 8x gain
	{0x2c, 0x0c},
	{0x33, 0x78},
	{0x3a, 0x33},
	{0x3b, 0xfB},
	//
	{0x3e, 0x00},
	{0x43, 0x11},
	{0x16, 0x10},
	//
	{0x39, 0x92},
	//
	{0x35, 0xda},
	{0x22, 0x1a},
	{0x37, 0xc3},
	{0x23, 0x00},
	{0x34, 0xc0}, // 
	{0x36, 0x1a},
	{0x06, 0x88},
	{0x07, 0xc0},
	{0x0d, 0x87}, // 10000 1 11: pwr-down, output remain
	{0x0e, 0x41},
	{0x4c, 0x00},
	
	{0x48, 0x00},
	{0x5B, 0x00},
	{0x42, 0x03},
	//
	{0x4a, 0x81},
	{0x21, 0x99},
	//
	{0x24, 0x40},
	{0x25, 0x38},
	{0x26, 0x82},
	{0x5c, 0x00},
	{0x63, 0x00},
	{0x46, 0x00}, // frame length adjustment
	{0x0c, 0x3c}, // 00111 1 0 0: 50 Hz banding, enable video output
	//
	{0x61, 0x70},
	{0x62, 0x80},
	{0x7c, 0x05},
	//
	{0x20, 0x80},
	{0x28, 0x30},
	{0x6c, 0x00},
	{0x6d, 0x80},
	{0x6e, 0x00},
	{0x70, 0x02},
	{0x71, 0x94},
	{0x73, 0xc1}, 
	{0x3d, 0x34}, 
	{0x5a, 0x57},
	//
	{0x12, 0x00},//UXGA 1600*1200
	
	{0x17, 0x11},
	{0x18, 0x75},
	{0x19, 0x01},
	{0x1a, 0x97},
	{0x32, 0x36}, // 00 110 110: PCLK freq no effect
	{0x03, 0x0f}, // 00 00 11 11: no dummy frame
	{0x37, 0x40},
	// 
	{0x4f, 0xca},
	{0x50, 0xa8},
	{0x5a, 0x23},
	{0x6d, 0x00},
	{0x6d, 0x38},
	//
	{0xff, 0x00},
	{0xe5, 0x7f},
	{0xf9, 0xc0}, // 1 1 0 0 0 0 0 0: microcontroller rst
	{0x41, 0x24},
	{0xe0, 0x14}, // 0 0 0 1 0 1 0 0: reset jpeg+dvp
	{0x76, 0xff},
	{0x33, 0xa0},
	{0x42, 0x20},
	{0x43, 0x18},
	{0x4c, 0x00},
	{0x87, 0xd5},
	{0x88, 0x3f},
	{0xd7, 0x03},
	{0xd9, 0x10},
	{0xd3, 0x82}, // 1 0000010: DVP auto, PCLK divided by 2
	//
	{0xc8, 0x08},
	{0xc9, 0x80},
	//
	{0x7c, 0x00},
	{0x7d, 0x00},
	{0x7c, 0x03},
	{0x7d, 0x48},
	{0x7d, 0x48},
	{0x7c, 0x08},
	{0x7d, 0x20},
	{0x7d, 0x10},
	{0x7d, 0x0e},
	//
	{0x90, 0x00},
	{0x91, 0x0e},
	{0x91, 0x1a},
	{0x91, 0x31},
	{0x91, 0x5a},
	{0x91, 0x69},
	{0x91, 0x75},
	{0x91, 0x7e},
	{0x91, 0x88},
	{0x91, 0x8f},
	{0x91, 0x96},
	{0x91, 0xa3},
	{0x91, 0xaf},
	{0x91, 0xc4},
	{0x91, 0xd7},
	{0x91, 0xe8},
	{0x91, 0x20},
	//
	{0x92, 0x00},
	{0x93, 0x06},
	{0x93, 0xe3},
	{0x93, 0x05},
	{0x93, 0x05},
	{0x93, 0x00},
	{0x93, 0x04},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	//
	{0x96, 0x00},
	{0x97, 0x08},
	{0x97, 0x19},
	{0x97, 0x02},
	{0x97, 0x0c},
	{0x97, 0x24},
	{0x97, 0x30},
	{0x97, 0x28},
	{0x97, 0x26},
	{0x97, 0x02},
	{0x97, 0x98},
	{0x97, 0x80},
	{0x97, 0x00},
	{0x97, 0x00},
	//
	{0xc3, 0xef}, // enable: cip, dmy, raw_gma, awb, awb_gain, lenc, pre
	
	{0xa4, 0x00},
	{0xa8, 0x00},
	{0xc5, 0x11},
	{0xc6, 0x51},
	{0xbf, 0x80},
	{0xc7, 0x10},
	{0xb6, 0x66},
	{0xb8, 0xA5},
	{0xb7, 0x64},
	{0xb9, 0x7C},
	{0xb3, 0xaf},
	{0xb4, 0x97},
	{0xb5, 0xFF},
	{0xb0, 0xC5},
	{0xb1, 0x94},
	{0xb2, 0x0f},
	{0xc4, 0x5c},
	//
	{0xc0, 0xc8}, // hsize[10:3]
	{0xc1, 0x96}, // vsize[10:3]
	{0x8c, 0x00}, // hsize[11], hsize[2:0], vsize[2:0]
	{0x86, 0x3d}, // enable dcw, sde, uv_adj, uv_avg, cmx
	{0x50, 0x00}, 
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	
	{0x5a, 0x90},
	{0x5b, 0x2C},
	{0x5c, 0x05},
	
	{0xd3, 0x02}, //auto设置要小心
	//
	{0xc3, 0xed}, // 1 1 1 0 1 1 0 1: enable: cip, dmy, raw_gma, awb, awb_gain, pre
	{0x7f, 0x00},
	
	{0xda, 0x09}, // 0 0 0 0 10 0 1: non-compressed (jpeg), RGB565, YUYV
	
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{0x05, 0x00}, // DSP
};  

/* Initialization sequence for SVGA resolution (800x600)*/
const char ov2640_svga_init_reg_tbl[][2]= 
{
	0xff, 0x00,
	0x2c, 0xff,
	0x2e, 0xdf,
	0xff, 0x01,
	0x3c, 0x32,
	//
	0x11, 0x00,
	0x09, 0x02,
	0x04, 0xD8,//水平镜像,垂直翻转
	0x13, 0xe5,
	0x14, 0x48,
	0x2c, 0x0c,
	0x33, 0x78,
	0x3a, 0x33,
	0x3b, 0xfB,
	//
	0x3e, 0x00,
	0x43, 0x11,
	0x16, 0x10,
	//
	0x39, 0x92,
	//
	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0x48, 0x00,
	0x5B, 0x00,
	0x42, 0x03,
	//
	0x4a, 0x81,
	0x21, 0x99,
	//
	0x24, 0x40,
	0x25, 0x38,
	0x26, 0x82,
	0x5c, 0x00,
	0x63, 0x00,
	0x46, 0x22,
	0x0c, 0x3c,
	//
	0x61, 0x70,
	0x62, 0x80,
	0x7c, 0x05,
	//
	0x20, 0x80,
	0x28, 0x30,
	0x6c, 0x00,
	0x6d, 0x80,
	0x6e, 0x00,
	0x70, 0x02,
	0x71, 0x94,
	0x73, 0xc1,
	
	0x3d, 0x34, 
	0x5a, 0x57,
	//根据分辨率不同而设置
	0x12, 0x40,//SVGA 800*600
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x37, 0xc0,
	//
	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x3d, 0x38,
	//
	0xff, 0x00,
	0xe5, 0x7f,
	0xf9, 0xc0,
	0x41, 0x24,
	0xe0, 0x14,
	0x76, 0xff,
	0x33, 0xa0,
	0x42, 0x20,
	0x43, 0x18,
	0x4c, 0x00,
	0x87, 0xd5,
	0x88, 0x3f,
	0xd7, 0x03,
	0xd9, 0x10,
	0xd3, 0x82,
	//
	0xc8, 0x08,
	0xc9, 0x80,
	//
	0x7c, 0x00,
	0x7d, 0x00,
	0x7c, 0x03,
	0x7d, 0x48,
	0x7d, 0x48,
	0x7c, 0x08,
	0x7d, 0x20,
	0x7d, 0x10,
	0x7d, 0x0e,
	//
	0x90, 0x00,
	0x91, 0x0e,
	0x91, 0x1a,
	0x91, 0x31,
	0x91, 0x5a,
	0x91, 0x69,
	0x91, 0x75,
	0x91, 0x7e,
	0x91, 0x88,
	0x91, 0x8f,
	0x91, 0x96,
	0x91, 0xa3,
	0x91, 0xaf,
	0x91, 0xc4,
	0x91, 0xd7,
	0x91, 0xe8,
	0x91, 0x20,
	//
	0x92, 0x00,
	0x93, 0x06,
	0x93, 0xe3,
	0x93, 0x05,
	0x93, 0x05,
	0x93, 0x00,
	0x93, 0x04,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	//
	0x96, 0x00,
	0x97, 0x08,
	0x97, 0x19,
	0x97, 0x02,
	0x97, 0x0c,
	0x97, 0x24,
	0x97, 0x30,
	0x97, 0x28,
	0x97, 0x26,
	0x97, 0x02,
	0x97, 0x98,
	0x97, 0x80,
	0x97, 0x00,
	0x97, 0x00,
	//
	0xc3, 0xed,
	0xa4, 0x00,
	0xa8, 0x00,
	0xc5, 0x11,
	0xc6, 0x51,
	0xbf, 0x80,
	0xc7, 0x10,
	0xb6, 0x66,
	0xb8, 0xA5,
	0xb7, 0x64,
	0xb9, 0x7C,
	0xb3, 0xaf,
	0xb4, 0x97,
	0xb5, 0xFF,
	0xb0, 0xC5,
	0xb1, 0x94,
	0xb2, 0x0f,
	0xc4, 0x5c,
	//根据分辨率不同而设置
	0xc0, 0x64,
	0xc1, 0x4B,
	0x8c, 0x00,
	0x86, 0x3D,
	0x50, 0x00,
	0x51, 0xC8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x5a, 0xC8,
	0x5b, 0x96,
	0x5c, 0x00,
	
	0xd3, 0x02,//auto设置要小心
	//
	0xc3, 0xed,
	0x7f, 0x00,
	
	0xda, 0x09,
	
	0xe5, 0x1f,
	0xe1, 0x67,
	0xe0, 0x00,
	0xdd, 0x7f,
	0x05, 0x00,
};

/* Initialization sequence for 480x272 resolution */
const char OV2640_480x272[][2]=
{
	{0xff, 0x00},  /* Device control register list Table 12 */
	{0x2c, 0xff},  /* Reserved                              */
	{0x2e, 0xdf},  /* Reserved                              */
	{0xff, 0x01},  /* Device control register list Table 13 */
	{0x3c, 0x32},  /* Reserved                              */
	{0x11, 0x00},  /* Clock Rate Control                    */
	{0x09, 0x02},  /* Common control 2                      */
	{0x04, 0xA8},  /* Mirror                                */
	{0x13, 0xe5},  /* Common control 8                      */
	{0x14, 0x48},  /* Common control 9                      */
	{0x2c, 0x0c},  /* Reserved                              */
	{0x33, 0x78},  /* Reserved                              */
	{0x3a, 0x33},  /* Reserved                              */
	{0x3b, 0xfB},  /* Reserved                              */
	{0x3e, 0x00},  /* Reserved                              */
	{0x43, 0x11},  /* Reserved                              */
	{0x16, 0x10},  /* Reserved                              */
	{0x4a, 0x81},  /* Reserved                              */
	{0x21, 0x99},  /* Reserved                              */
	{0x24, 0x40},  /* Luminance signal High range           */
	{0x25, 0x38},  /* Luminance signal low range            */
	{0x26, 0x82},  /*                                       */
	{0x5c, 0x00},  /* Reserved                              */
	{0x63, 0x00},  /* Reserved                              */
	{0x46, 0x3f},  /* Frame length adjustment               */
	{0x0c, 0x3c},  /* Common control 3                      */
	{0x61, 0x70},  /* Histogram algo low level              */
	{0x62, 0x80},  /* Histogram algo high level             */
	{0x7c, 0x05},  /* Reserved                              */
	{0x20, 0x80},  /* Reserved                              */
	{0x28, 0x30},  /* Reserved                              */
	{0x6c, 0x00},  /* Reserved                              */
	{0x6d, 0x80},  /* Reserved                              */
	{0x6e, 0x00},  /* Reserved                              */
	{0x70, 0x02},  /* Reserved                              */
	{0x71, 0x94},  /* Reserved                              */
	{0x73, 0xc1},  /* Reserved                              */
	{0x3d, 0x34},  /* Reserved                              */
	{0x5a, 0x57},  /* Reserved                              */
	{0x12, 0x00},  /* Common control 7                      */
	{0x11, 0x00},  /* Clock Rate Control                   2*/
	{0x17, 0x11},  /* Horiz window start MSB 8bits          */
	{0x18, 0x75},  /* Horiz window end MSB 8bits            */
	{0x19, 0x01},  /* Vert window line start MSB 8bits      */
	{0x1a, 0x97},  /* Vert window line end MSB 8bits        */
	{0x32, 0x36},
	{0x03, 0x0f},
	{0x37, 0x40},
	{0x4f, 0xbb},
	{0x50, 0x9c},
	{0x5a, 0x57},
	{0x6d, 0x80},
	{0x6d, 0x38},
	{0x39, 0x02},
	{0x35, 0x88},
	{0x22, 0x0a},
	{0x37, 0x40},
	{0x23, 0x00},
	{0x34, 0xa0},
	{0x36, 0x1a},
	{0x06, 0x02},
	{0x07, 0xc0},
	{0x0d, 0xb7},
	{0x0e, 0x01},
	{0x4c, 0x00},
	{0xff, 0x00},
	{0xe5, 0x7f},
	{0xf9, 0xc0},
	{0x41, 0x24},
	{0xe0, 0x14},
	{0x76, 0xff},
	{0x33, 0xa0},
	{0x42, 0x20},
	{0x43, 0x18},
	{0x4c, 0x00},
	{0x87, 0xd0},
	{0x88, 0x3f},
	{0xd7, 0x03},
	{0xd9, 0x10},
	{0xd3, 0x82},
	{0xc8, 0x08},
	{0xc9, 0x80},
	{0x7d, 0x00},
	{0x7c, 0x03},
	{0x7d, 0x48},
	{0x7c, 0x08},
	{0x7d, 0x20},
	{0x7d, 0x10},
	{0x7d, 0x0e},
	{0x90, 0x00},
	{0x91, 0x0e},
	{0x91, 0x1a},
	{0x91, 0x31},
	{0x91, 0x5a},
	{0x91, 0x69},
	{0x91, 0x75},
	{0x91, 0x7e},
	{0x91, 0x88},
	{0x91, 0x8f},
	{0x91, 0x96},
	{0x91, 0xa3},
	{0x91, 0xaf},
	{0x91, 0xc4},
	{0x91, 0xd7},
	{0x91, 0xe8},
	{0x91, 0x20},
	{0x92, 0x00},
	{0x93, 0x06},
	{0x93, 0xe3},
	{0x93, 0x02},
	{0x93, 0x02},
	{0x93, 0x00},
	{0x93, 0x04},
	{0x93, 0x00},
	{0x93, 0x03},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x96, 0x00},
	{0x97, 0x08},
	{0x97, 0x19},
	{0x97, 0x02},
	{0x97, 0x0c},
	{0x97, 0x24},
	{0x97, 0x30},
	{0x97, 0x28},
	{0x97, 0x26},
	{0x97, 0x02},
	{0x97, 0x98},
	{0x97, 0x80},
	{0x97, 0x00},
	{0x97, 0x00},
	{0xc3, 0xef},
	{0xff, 0x00},
	{0xba, 0xdc},
	{0xbb, 0x08},
	{0xb6, 0x24},
	{0xb8, 0x33},
	{0xb7, 0x20},
	{0xb9, 0x30},
	{0xb3, 0xb4},
	{0xb4, 0xca},
	{0xb5, 0x43},
	{0xb0, 0x5c},
	{0xb1, 0x4f},
	{0xb2, 0x06},
	{0xc7, 0x00},
	{0xc6, 0x51},
	{0xc5, 0x11},
	{0xc4, 0x9c},
	{0xbf, 0x00},
	{0xbc, 0x64},
	{0xa6, 0x00},
	{0xa7, 0x1e},
	{0xa7, 0x6b},
	{0xa7, 0x47},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x2e},
	{0xa7, 0x85},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x1b},
	{0xa7, 0x74},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x8c, 0x00},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x5a, 0x50},
	{0x5b, 0x3c},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0x7f, 0x00},
	{0xda, 0x00},
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{0x05, 0x00},
	{0xff, 0x00},
	{0xe0, 0x04},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x57, 0x00},
	{0x5a, 0x50},
	{0x5b, 0x3c},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0xe0, 0x00},
	{0xFF, 0x00},
	{0x05, 0x00},
	{0xDA, 0x08},
	{0xda, 0x09},
	{0x98, 0x00},
	{0x99, 0x00},
	{0x00, 0x00},
	{0xff, 0x00},
	{0xe0, 0x04},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x86, 0x35},
	{0x50, 0x80},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x57, 0x00},
	{0x5a, 0x78},
	{0x5b, 0x44},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0xe0, 0x00},
};

/* Initialization sequence for VGA resolution (640x480)*/
const char OV2640_VGA[][2]=
{
	{0xff, 0x00},  /* Device control register list Table 12 */
	{0x2c, 0xff},  /* Reserved                              */
	{0x2e, 0xdf},  /* Reserved                              */
	{0xff, 0x01},  /* Device control register list Table 13 */
	{0x3c, 0x32},  /* Reserved                              */
	{0x11, 0x00},  /* Clock Rate Control                    */
	{0x09, 0x02},  /* Common control 2                      */
	{0x04, 0xA8},  /* Mirror                                */
	{0x13, 0xe5},  /* Common control 8                      */
	{0x14, 0x48},  /* Common control 9                      */
	{0x2c, 0x0c},  /* Reserved                              */
	{0x33, 0x78},  /* Reserved                              */
	{0x3a, 0x33},  /* Reserved                              */
	{0x3b, 0xfB},  /* Reserved                              */
	{0x3e, 0x00},  /* Reserved                              */
	{0x43, 0x11},  /* Reserved                              */
	{0x16, 0x10},  /* Reserved                              */
	{0x4a, 0x81},  /* Reserved                              */
	{0x21, 0x99},  /* Reserved                              */
	{0x24, 0x40},  /* Luminance signal High range           */
	{0x25, 0x38},  /* Luminance signal low range            */
	{0x26, 0x82},  /*                                       */
	{0x5c, 0x00},  /* Reserved                              */
	{0x63, 0x00},  /* Reserved                              */
	{0x46, 0x3f},  /* Frame length adjustment               */
	{0x0c, 0x3c},  /* Common control 3                      */
	{0x61, 0x70},  /* Histogram algo low level              */
	{0x62, 0x80},  /* Histogram algo high level             */
	{0x7c, 0x05},  /* Reserved                              */
	{0x20, 0x80},  /* Reserved                              */
	{0x28, 0x30},  /* Reserved                              */
	{0x6c, 0x00},  /* Reserved                              */
	{0x6d, 0x80},  /* Reserved                              */
	{0x6e, 0x00},  /* Reserved                              */
	{0x70, 0x02},  /* Reserved                              */
	{0x71, 0x94},  /* Reserved                              */
	{0x73, 0xc1},  /* Reserved                              */
	{0x3d, 0x34},  /* Reserved                              */
	{0x5a, 0x57},  /* Reserved                              */
	{0x12, 0x00},  /* Common control 7                      */
	{0x11, 0x00},  /* Clock Rate Control                   2*/
	{0x17, 0x11},  /* Horiz window start MSB 8bits          */
	{0x18, 0x75},  /* Horiz window end MSB 8bits            */
	{0x19, 0x01},  /* Vert window line start MSB 8bits      */
	{0x1a, 0x97},  /* Vert window line end MSB 8bits        */
	{0x32, 0x36},
	{0x03, 0x0f},
	{0x37, 0x40},
	{0x4f, 0xbb},
	{0x50, 0x9c},
	{0x5a, 0x57},
	{0x6d, 0x80},
	{0x6d, 0x38},
	{0x39, 0x02},
	{0x35, 0x88},
	{0x22, 0x0a},
	{0x37, 0x40},
	{0x23, 0x00},
	{0x34, 0xa0},
	{0x36, 0x1a},
	{0x06, 0x02},
	{0x07, 0xc0},
	{0x0d, 0xb7},
	{0x0e, 0x01},
	{0x4c, 0x00},
	{0xff, 0x00},
	{0xe5, 0x7f},
	{0xf9, 0xc0},
	{0x41, 0x24},
	{0xe0, 0x14},
	{0x76, 0xff},
	{0x33, 0xa0},
	{0x42, 0x20},
	{0x43, 0x18},
	{0x4c, 0x00},
	{0x87, 0xd0},
	{0x88, 0x3f},
	{0xd7, 0x03},
	{0xd9, 0x10},
	{0xd3, 0x82},
	{0xc8, 0x08},
	{0xc9, 0x80},
	{0x7d, 0x00},
	{0x7c, 0x03},
	{0x7d, 0x48},
	{0x7c, 0x08},
	{0x7d, 0x20},
	{0x7d, 0x10},
	{0x7d, 0x0e},
	{0x90, 0x00},
	{0x91, 0x0e},
	{0x91, 0x1a},
	{0x91, 0x31},
	{0x91, 0x5a},
	{0x91, 0x69},
	{0x91, 0x75},
	{0x91, 0x7e},
	{0x91, 0x88},
	{0x91, 0x8f},
	{0x91, 0x96},
	{0x91, 0xa3},
	{0x91, 0xaf},
	{0x91, 0xc4},
	{0x91, 0xd7},
	{0x91, 0xe8},
	{0x91, 0x20},
	{0x92, 0x00},
	{0x93, 0x06},
	{0x93, 0xe3},
	{0x93, 0x02},
	{0x93, 0x02},
	{0x93, 0x00},
	{0x93, 0x04},
	{0x93, 0x00},
	{0x93, 0x03},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x96, 0x00},
	{0x97, 0x08},
	{0x97, 0x19},
	{0x97, 0x02},
	{0x97, 0x0c},
	{0x97, 0x24},
	{0x97, 0x30},
	{0x97, 0x28},
	{0x97, 0x26},
	{0x97, 0x02},
	{0x97, 0x98},
	{0x97, 0x80},
	{0x97, 0x00},
	{0x97, 0x00},
	{0xc3, 0xef},
	{0xff, 0x00},
	{0xba, 0xdc},
	{0xbb, 0x08},
	{0xb6, 0x24},
	{0xb8, 0x33},
	{0xb7, 0x20},
	{0xb9, 0x30},
	{0xb3, 0xb4},
	{0xb4, 0xca},
	{0xb5, 0x43},
	{0xb0, 0x5c},
	{0xb1, 0x4f},
	{0xb2, 0x06},
	{0xc7, 0x00},
	{0xc6, 0x51},
	{0xc5, 0x11},
	{0xc4, 0x9c},
	{0xbf, 0x00},
	{0xbc, 0x64},
	{0xa6, 0x00},
	{0xa7, 0x1e},
	{0xa7, 0x6b},
	{0xa7, 0x47},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x2e},
	{0xa7, 0x85},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x1b},
	{0xa7, 0x74},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x8c, 0x00},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x5a, 0x50},
	{0x5b, 0x3c},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0x7f, 0x00},
	{0xda, 0x00},
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{0x05, 0x00},
	{0xff, 0x00},
	{0xe0, 0x04},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x57, 0x00},
	{0x5a, 0x50},
	{0x5b, 0x3c},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0xe0, 0x00},
	{0xFF, 0x00},
	{0x05, 0x00},
	{0xDA, 0x08},
	{0xda, 0x09},
	{0x98, 0x00},
	{0x99, 0x00},
	{0x00, 0x00},
	{0xff, 0x00},
	{0xe0, 0x04},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x86, 0x3d},
	{0x50, 0x89},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x57, 0x00},
	{0x5a, 0xA0},
	{0x5b, 0x78},
	{0x5c, 0x00},
	{0xd3, 0x02},
	{0xe0, 0x00},
};

/* Initialization sequence for QVGA resolution (320x240) */
const char OV2640_QVGA[][2]=
{
	{0xff, 0x00},
	{0x2c, 0xff},
	{0x2e, 0xdf},
	{0xff, 0x01},
	{0x3c, 0x32},
	{0x11, 0x00},
	{0x09, 0x02},
	{0x04, 0xA8},
	{0x13, 0xe5},
	{0x14, 0x48},
	{0x2c, 0x0c},
	{0x33, 0x78},
	{0x3a, 0x33},
	{0x3b, 0xfB},
	{0x3e, 0x00},
	{0x43, 0x11},
	{0x16, 0x10},
	{0x4a, 0x81},
	{0x21, 0x99},
	{0x24, 0x40},
	{0x25, 0x38},
	{0x26, 0x82},
	{0x5c, 0x00},
	{0x63, 0x00},
	{0x46, 0x3f},
	{0x0c, 0x3c},
	{0x61, 0x70},
	{0x62, 0x80},
	{0x7c, 0x05},
	{0x20, 0x80},
	{0x28, 0x30},
	{0x6c, 0x00},
	{0x6d, 0x80},
	{0x6e, 0x00},
	{0x70, 0x02},
	{0x71, 0x94},
	{0x73, 0xc1},
	{0x3d, 0x34},
	{0x5a, 0x57},
	{0x12, 0x00},
	{0x11, 0x00},
	{0x17, 0x11},
	{0x18, 0x75},
	{0x19, 0x01},
	{0x1a, 0x97},
	{0x32, 0x36},
	{0x03, 0x0f},
	{0x37, 0x40},
	{0x4f, 0xbb},
	{0x50, 0x9c},
	{0x5a, 0x57},
	{0x6d, 0x80},
	{0x6d, 0x38},
	{0x39, 0x02},
	{0x35, 0x88},
	{0x22, 0x0a},
	{0x37, 0x40},
	{0x23, 0x00},
	{0x34, 0xa0},
	{0x36, 0x1a},
	{0x06, 0x02},
	{0x07, 0xc0},
	{0x0d, 0xb7},
	{0x0e, 0x01},
	{0x4c, 0x00},
	{0xff, 0x00},
	{0xe5, 0x7f},
	{0xf9, 0xc0},
	{0x41, 0x24},
	{0xe0, 0x14},
	{0x76, 0xff},
	{0x33, 0xa0},
	{0x42, 0x20},
	{0x43, 0x18},
	{0x4c, 0x00},
	{0x87, 0xd0},
	{0x88, 0x3f},
	{0xd7, 0x03},
	{0xd9, 0x10},
	{0xd3, 0x82},
	{0xc8, 0x08},
	{0xc9, 0x80},
	{0x7d, 0x00},
	{0x7c, 0x03},
	{0x7d, 0x48},
	{0x7c, 0x08},
	{0x7d, 0x20},
	{0x7d, 0x10},
	{0x7d, 0x0e},
	{0x90, 0x00},
	{0x91, 0x0e},
	{0x91, 0x1a},
	{0x91, 0x31},
	{0x91, 0x5a},
	{0x91, 0x69},
	{0x91, 0x75},
	{0x91, 0x7e},
	{0x91, 0x88},
	{0x91, 0x8f},
	{0x91, 0x96},
	{0x91, 0xa3},
	{0x91, 0xaf},
	{0x91, 0xc4},
	{0x91, 0xd7},
	{0x91, 0xe8},
	{0x91, 0x20},
	{0x92, 0x00},
	{0x93, 0x06},
	{0x93, 0xe3},
	{0x93, 0x02},
	{0x93, 0x02},
	{0x93, 0x00},
	{0x93, 0x04},
	{0x93, 0x00},
	{0x93, 0x03},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x96, 0x00},
	{0x97, 0x08},
	{0x97, 0x19},
	{0x97, 0x02},
	{0x97, 0x0c},
	{0x97, 0x24},
	{0x97, 0x30},
	{0x97, 0x28},
	{0x97, 0x26},
	{0x97, 0x02},
	{0x97, 0x98},
	{0x97, 0x80},
	{0x97, 0x00},
	{0x97, 0x00},
	{0xc3, 0xef},
	{0xff, 0x00},
	{0xba, 0xdc},
	{0xbb, 0x08},
	{0xb6, 0x24},
	{0xb8, 0x33},
	{0xb7, 0x20},
	{0xb9, 0x30},
	{0xb3, 0xb4},
	{0xb4, 0xca},
	{0xb5, 0x43},
	{0xb0, 0x5c},
	{0xb1, 0x4f},
	{0xb2, 0x06},
	{0xc7, 0x00},
	{0xc6, 0x51},
	{0xc5, 0x11},
	{0xc4, 0x9c},
	{0xbf, 0x00},
	{0xbc, 0x64},
	{0xa6, 0x00},
	{0xa7, 0x1e},
	{0xa7, 0x6b},
	{0xa7, 0x47},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x2e},
	{0xa7, 0x85},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x1b},
	{0xa7, 0x74},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x8c, 0x00},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x5a, 0x50},
	{0x5b, 0x3c},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0x7f, 0x00},
	{0xda, 0x00},
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{0x05, 0x00},
	{0xff, 0x00},
	{0xe0, 0x04},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x57, 0x00},
	{0x5a, 0x50},
	{0x5b, 0x3C},
	{0x5c, 0x00},
	{0xd3, 0x08},
	{0xe0, 0x00},
	{0xFF, 0x00},
	{0x05, 0x00},
	{0xDA, 0x08},
	{0xda, 0x09},
	{0x98, 0x00},
	{0x99, 0x00},
	{0x00, 0x00},
};

/* Initialization sequence for QQVGA resolution (160x120) */
const char OV2640_QQVGA[][2]=
{
	{0xff, 0x00}, //Register 0xFF controls which set is accessible.
	{0x2c, 0xff},
	{0x2e, 0xdf},
	{0xff, 0x01},
	{0x3c, 0x32},
	{0x11, 0x00},
	{0x09, 0x02},
	{0x04, 0xA8},
	{0x13, 0xe5},
	{0x14, 0x48},
	{0x2c, 0x0c},
	{0x33, 0x78},
	{0x3a, 0x33},
	{0x3b, 0xfB},
	{0x3e, 0x00},
	{0x43, 0x11},
	{0x16, 0x10},
	{0x4a, 0x81},
	{0x21, 0x99},
	{0x24, 0x40},
	{0x25, 0x38},
	{0x26, 0x82},
	{0x5c, 0x00},
	{0x63, 0x00},
	{0x46, 0x3f},
	{0x0c, 0x3c},
	{0x61, 0x70},
	{0x62, 0x80},
	{0x7c, 0x05},
	{0x20, 0x80},
	{0x28, 0x30},
	{0x6c, 0x00},
	{0x6d, 0x80},
	{0x6e, 0x00},
	{0x70, 0x02},
	{0x71, 0x94},
	{0x73, 0xc1},
	{0x3d, 0x34},
	{0x5a, 0x57},
	{0x12, 0x00},
	{0x11, 0x00},
	{0x17, 0x11},
	{0x18, 0x75},
	{0x19, 0x01},
	{0x1a, 0x97},
	{0x32, 0x36},
	{0x03, 0x0f},
	{0x37, 0x40},
	{0x4f, 0xbb},
	{0x50, 0x9c},
	{0x5a, 0x57},
	{0x6d, 0x80},
	{0x6d, 0x38},
	{0x39, 0x02},
	{0x35, 0x88},
	{0x22, 0x0a},
	{0x37, 0x40},
	{0x23, 0x00},
	{0x34, 0xa0},
	{0x36, 0x1a},
	{0x06, 0x02},
	{0x07, 0xc0},
	{0x0d, 0xb7},
	{0x0e, 0x01},
	{0x4c, 0x00},
	{0xff, 0x00},
	{0xe5, 0x7f},
	{0xf9, 0xc0},
	{0x41, 0x24},
	{0xe0, 0x14},
	{0x76, 0xff},
	{0x33, 0xa0},
	{0x42, 0x20},
	{0x43, 0x18},
	{0x4c, 0x00},
	{0x87, 0xd0},
	{0x88, 0x3f},
	{0xd7, 0x03},
	{0xd9, 0x10},
	{0xd3, 0x82},
	{0xc8, 0x08},
	{0xc9, 0x80},
	{0x7d, 0x00},
	{0x7c, 0x03},
	{0x7d, 0x48},
	{0x7c, 0x08},
	{0x7d, 0x20},
	{0x7d, 0x10},
	{0x7d, 0x0e},
	{0x90, 0x00},
	{0x91, 0x0e},
	{0x91, 0x1a},
	{0x91, 0x31},
	{0x91, 0x5a},
	{0x91, 0x69},
	{0x91, 0x75},
	{0x91, 0x7e},
	{0x91, 0x88},
	{0x91, 0x8f},
	{0x91, 0x96},
	{0x91, 0xa3},
	{0x91, 0xaf},
	{0x91, 0xc4},
	{0x91, 0xd7},
	{0x91, 0xe8},
	{0x91, 0x20},
	{0x92, 0x00},
	{0x93, 0x06},
	{0x93, 0xe3},
	{0x93, 0x02},
	{0x93, 0x02},
	{0x93, 0x00},
	{0x93, 0x04},
	{0x93, 0x00},
	{0x93, 0x03},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x93, 0x00},
	{0x96, 0x00},
	{0x97, 0x08},
	{0x97, 0x19},
	{0x97, 0x02},
	{0x97, 0x0c},
	{0x97, 0x24},
	{0x97, 0x30},
	{0x97, 0x28},
	{0x97, 0x26},
	{0x97, 0x02},
	{0x97, 0x98},
	{0x97, 0x80},
	{0x97, 0x00},
	{0x97, 0x00},
	{0xc3, 0xef},
	{0xff, 0x00},
	{0xba, 0xdc},
	{0xbb, 0x08},
	{0xb6, 0x24},
	{0xb8, 0x33},
	{0xb7, 0x20},
	{0xb9, 0x30},
	{0xb3, 0xb4},
	{0xb4, 0xca},
	{0xb5, 0x43},
	{0xb0, 0x5c},
	{0xb1, 0x4f},
	{0xb2, 0x06},
	{0xc7, 0x00},
	{0xc6, 0x51},
	{0xc5, 0x11},
	{0xc4, 0x9c},
	{0xbf, 0x00},
	{0xbc, 0x64},
	{0xa6, 0x00},
	{0xa7, 0x1e},
	{0xa7, 0x6b},
	{0xa7, 0x47},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x2e},
	{0xa7, 0x85},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xa7, 0x1b},
	{0xa7, 0x74},
	{0xa7, 0x42},
	{0xa7, 0x33},
	{0xa7, 0x00},
	{0xa7, 0x23},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x8c, 0x00},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x5a, 0x50},
	{0x5b, 0x3c},
	{0x5c, 0x00},
	{0xd3, 0x04},
	{0x7f, 0x00},
	{0xda, 0x00},
	{0xe5, 0x1f},
	{0xe1, 0x67},
	{0xe0, 0x00},
	{0xdd, 0x7f},
	{0x05, 0x00},
	{0xff, 0x00},
	{0xe0, 0x04},
	{0xc0, 0xc8},
	{0xc1, 0x96},
	{0x86, 0x3d},
	{0x50, 0x92},
	{0x51, 0x90},
	{0x52, 0x2c},
	{0x53, 0x00},
	{0x54, 0x00},
	{0x55, 0x88},
	{0x57, 0x00},
	{0x5a, 0x28}, 
	{0x5b, 0x1E}, 
	{0x5c, 0x00},
	{0xd3, 0x08},
	{0xe0, 0x00},
	{0xFF, 0x00},
	{0x05, 0x00},
	{0xDA, 0x08},
	{0xda, 0x09},
	{0x98, 0x00},
	{0x99, 0x00},
	{0x00, 0x00},
};

const char ov2640_rgb565_reg_tbl[][2]=
{
	0xFF, 0x00,
	0xDA, 0x09,	// RGB565, Low bit first
	0xD7, 0x03, // ?
	0xDF, 0x02, // ?
	0x33, 0xa0, // ?
	0x3C, 0x00, // ?
	0xE1, 0x67  // ?
};

const char ov2640_yuv422_reg_tbl[][2]= 
{
	0xFF, 0x00, 
	// 0xDA, 0x10, // YUV422, JPEG compressed
	0xDA, 0x00, // YUV422, raw
	0xD7, 0x03,
	0xDF, 0x00,
	0x33, 0x80,
	0x3C, 0x40,
	0xE1, 0x77,
	0x00, 0x00,
};

const char ov2640_raw_reg_tbl[][2]=
{
	0xFF, 0x01, 
	0xE0, 0x00,
	0xE1, 0x00,
	0xE5, 0x00,
	0xD7, 0x00, 
	0xDA, 0x00, // raw, YUV422, high bit first
	0xE0, 0x00, 
};

const char ov2640_jpg_reg_tbl[][2]= 
{
	0xFF, 0x01, 
	0xE0, 0x14, // reset JPEG and DVP
	0xE1, 0x77, //
	0xE5, 0x1F,
	0xD7, 0x03,
	0xDA, 0x10, // JPEG
	0xE0, 0x00, 
};

const char OV2640_JPEG_INIT[][2]=
{
	0xff, 0x00,
	0x2c, 0xff,
	0x2e, 0xdf,
	0xff, 0x01,
	0x3c, 0x32,
	0x11, 0x30,
	0x09, 0x02,
	0x04, 0x28,
	0x13, 0xe5,
	0x14, 0x48,
	0x2c, 0x0c,
	0x33, 0x78,
	0x3a, 0x33,
	0x3b, 0xfB,
	0x3e, 0x00,
	0x43, 0x11,
	0x16, 0x10,
	0x39, 0x92,
	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0x48, 0x00,
	0x5B, 0x00,
	0x42, 0x03,
	0x4a, 0x81,
	0x21, 0x99,
	0x24, 0x40,
	0x25, 0x38,
	0x26, 0x82,
	0x5c, 0x00,
	0x63, 0x00,
	0x61, 0x70,
	0x62, 0x80,
	0x7c, 0x05,
	0x20, 0x80,
	0x28, 0x30,
	0x6c, 0x00,
	0x6d, 0x80,
	0x6e, 0x00,
	0x70, 0x02,
	0x71, 0x94,
	0x73, 0xc1,
	0x12, 0x40,
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x37, 0xc0,
	0x4f, 0x60,
	0x50, 0xa8,
	0x6d, 0x00,
	0x3d, 0x38,
	0x46, 0x3f,
	0x4f, 0x60,
	0x0c, 0x3c,
	0xff, 0x00,
	0xe5, 0x7f,
	0xf9, 0xc0,
	0x41, 0x24,
	0xe0, 0x14,
	0x76, 0xff,
	0x33, 0xa0,
	0x42, 0x20,
	0x43, 0x18,
	0x4c, 0x00,
	0x87, 0xd5,
	0x88, 0x3f,
	0xd7, 0x03,
	0xd9, 0x10,
	0xd3, 0x82,
	0xc8, 0x08,
	0xc9, 0x80,
	0x7c, 0x00,
	0x7d, 0x00,
	0x7c, 0x03,
	0x7d, 0x48,
	0x7d, 0x48,
	0x7c, 0x08,
	0x7d, 0x20,
	0x7d, 0x10,
	0x7d, 0x0e,
	0x90, 0x00,
	0x91, 0x0e,
	0x91, 0x1a,
	0x91, 0x31,
	0x91, 0x5a,
	0x91, 0x69,
	0x91, 0x75,
	0x91, 0x7e,
	0x91, 0x88,
	0x91, 0x8f,
	0x91, 0x96,
	0x91, 0xa3,
	0x91, 0xaf,
	0x91, 0xc4,
	0x91, 0xd7,
	0x91, 0xe8,
	0x91, 0x20,
	0x92, 0x00,
	0x93, 0x06,
	0x93, 0xe3,
	0x93, 0x05,
	0x93, 0x05,
	0x93, 0x00,
	0x93, 0x04,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x93, 0x00,
	0x96, 0x00,
	0x97, 0x08,
	0x97, 0x19,
	0x97, 0x02,
	0x97, 0x0c,
	0x97, 0x24,
	0x97, 0x30,
	0x97, 0x28,
	0x97, 0x26,
	0x97, 0x02,
	0x97, 0x98,
	0x97, 0x80,
	0x97, 0x00,
	0x97, 0x00,
	0xc3, 0xed,
	0xa4, 0x00,
	0xa8, 0x00,
	0xc5, 0x11,
	0xc6, 0x51,
	0xbf, 0x80,
	0xc7, 0x10,
	0xb6, 0x66,
	0xb8, 0xA5,
	0xb7, 0x64,
	0xb9, 0x7C,
	0xb3, 0xaf,
	0xb4, 0x97,
	0xb5, 0xFF,
	0xb0, 0xC5,
	0xb1, 0x94,
	0xb2, 0x0f,
	0xc4, 0x5c,
	0xc0, 0x64,
	0xc1, 0x4B,
	0x8c, 0x00,
	0x86, 0x3D,
	0x50, 0x00,
	0x51, 0xC8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x5a, 0xC8,
	0x5b, 0x96,
	0x5c, 0x00,
	0xd3, 0x7f,
	0xc3, 0xed,
	0x7f, 0x00,
	0xda, 0x00,
	0xe5, 0x1f,
	0xe1, 0x67,
	0xe0, 0x00,
	0xdd, 0x7f,
	0x05, 0x00,

	0x12, 0x40,
	0xd3, 0x7f,
	0xc0, 0x16,
	0xC1, 0x12,
	0x8c, 0x00,
	0x86, 0x3d,
	0x50, 0x00,
	0x51, 0x2C,
	0x52, 0x24,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x5A, 0x2c,
	0x5b, 0x24,
	0x5c, 0x00,
};

const char OV2640_YUV422[][2]= 
{
	0xFF, 0x00,
	0x05, 0x00,
	0xDA, 0x10,
	0xD7, 0x03,
	0xDF, 0x00,
	0x33, 0x80,
	0x3C, 0x40,
	0xe1, 0x77,
	0x00, 0x00,
};

const char OV2640_JPEG[][2]=
{
	0xe0, 0x14,
	0xe1, 0x77,
	0xe5, 0x1f,
	0xd7, 0x03,
	0xda, 0x10,
	0xe0, 0x00,
	0xFF, 0x01,
	0x04, 0x08,
};

/* JPG 160x120 */
const char OV2640_160x120_JPEG[][2]=
{
	0xff, 0x01,
	0x12, 0x40,
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x39, 0x12,
	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0xff, 0x00,
	0xe0, 0x04,
	0xc0, 0x64,
	0xc1, 0x4b,
	0x86, 0x35,
	0x50, 0x92,
	0x51, 0xc8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x57, 0x00,
	0x5a, 0x28,
	0x5b, 0x1e,
	0x5c, 0x00,
	0xe0, 0x00,
};

/* JPG, 0x176x144 */
const char OV2640_176x144_JPEG[][2]=
{
	0xff, 0x01,
	0x12, 0x40,
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x39, 0x12,
	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0xff, 0x00,
	0xe0, 0x04,
	0xc0, 0x64,
	0xc1, 0x4b,
	0x86, 0x35,
	0x50, 0x92,
	0x51, 0xc8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x57, 0x00,
	0x5a, 0x2c,
	0x5b, 0x24,
	0x5c, 0x00,
	0xe0, 0x00,
};

/* JPG 320x240 */
const char OV2640_320x240_JPEG[][2]=
{
	0xff, 0x01,
	0x12, 0x40,
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x39, 0x12,
	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0xff, 0x00,
	0xe0, 0x04,
	0xc0, 0x64,
	0xc1, 0x4b,
	0x86, 0x35,
	0x50, 0x89,
	0x51, 0xc8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x57, 0x00,
	0x5a, 0x50,
	0x5b, 0x3c,
	0x5c, 0x00,
	0xe0, 0x00,
};

/* JPG 352x288 */
const char OV2640_352x288_JPEG[][2]=
{
	0xff, 0x01,
	0x12, 0x40,
	0x17, 0x11,
	0x18, 0x43,
	0x19, 0x00,
	0x1a, 0x4b,
	0x32, 0x09,
	0x4f, 0xca,
	0x50, 0xa8,
	0x5a, 0x23,
	0x6d, 0x00,
	0x39, 0x12,
	0x35, 0xda,
	0x22, 0x1a,
	0x37, 0xc3,
	0x23, 0x00,
	0x34, 0xc0,
	0x36, 0x1a,
	0x06, 0x88,
	0x07, 0xc0,
	0x0d, 0x87,
	0x0e, 0x41,
	0x4c, 0x00,
	0xff, 0x00,
	0xe0, 0x04,
	0xc0, 0x64,
	0xc1, 0x4b,
	0x86, 0x35,
	0x50, 0x89,
	0x51, 0xc8,
	0x52, 0x96,
	0x53, 0x00,
	0x54, 0x00,
	0x55, 0x00,
	0x57, 0x00,
	0x5a, 0x58,
	0x5b, 0x48,
	0x5c, 0x00,
	0xe0, 0x00,
};

#endif