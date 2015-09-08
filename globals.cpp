#include "globals.h"

// FGa, from previous tool
int D_Fusion_ScaleFactor = 3;   // Scale factor: 8x
int D_Fusion_2D_3D_2DW = 640; // By default we booked the maximum memory, considering VGA Res
int D_Fusion_2D_3D_2DH = 480;
int D_Fusion_2D_3D_2DSIZE;
int D_Fusion_2D_3D_2DSIZE_RGB;

int D_Fusion_2D_3D_Spatial_downsample_rate; // Default downsampling rate, can be [0,4] but I set it to 0 in order to book enough memory
int D_Fusion_2D_3D_2DW_DS;
int D_Fusion_2D_3D_2DH_DS;
int D_Fusion_2D_3D_2DSIZE_DS;

int D_MEM_s32_DS;
int D_MEM_u16_DS;
int D_MEM_u08_DS;
int D_MEM_s32;
int D_MEM_u16;
int D_MEM_u08;
int D_MEM_RGB_u08;

int D_Fusion_2D_3D_MEM_SIZE; // Totally required memory
