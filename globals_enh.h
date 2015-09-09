#ifndef GLOBALS_ENH_H
#define GLOBALS_ENH_H

#define D_QUANTIZATION_RANGE_3D		300 //160 /* It's related to the range data, sigmas, etc */
#define D_QUANTIZATION_RANGE_2D		50 //16
#define D_BG_THRESHOLD				128 // Background threshold // Originally 128, then shifted to 15, then back to 128
#define D_CHANNEL_GRAY				150 // Just used for display colours
#define D_CHANNEL_R					255
#define D_CHANNEL_G					128
#define D_CHANNEL_B					0
#define D_KERNEL_SIZE               25
#define MLF_APP_MAX_DISTANCE		20000   //20000	 // IEE ToF Max Dist: 20000
#define MLF_APP_2D_RANGE			256
#define MLF_APP_INTENSITY_RANGE		4096 /*define type size of image*/
#define MLF_BackGround_Counter      1

// FGa, from previous tool
extern int D_Fusion_ScaleFactor;   // Scale factor: 3x
extern int D_Fusion_2D_3D_2DW; // By default we booked the maximum memory, considering VGA Res
extern int D_Fusion_2D_3D_2DH;
extern int D_Fusion_2D_3D_2DSIZE;
extern int D_Fusion_2D_3D_2DSIZE_RGB;

extern int D_Fusion_2D_3D_Spatial_downsample_rate; // Default downsampling rate, can be [0,4] but I set it to 0 in order to book enough memory
extern int D_Fusion_2D_3D_2DW_DS;
extern int D_Fusion_2D_3D_2DH_DS;
extern int D_Fusion_2D_3D_2DSIZE_DS;

extern int D_MEM_s32_DS;
extern int D_MEM_u16_DS;
extern int D_MEM_u08_DS;
extern int D_MEM_s32;
extern int D_MEM_u16;
extern int D_MEM_u08;
extern int D_MEM_RGB_u08;

extern int D_Fusion_2D_3D_MEM_SIZE; // Totally required memory


#endif
