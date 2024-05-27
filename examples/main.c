#include "test.h"
#include "DEV_Config.h"
#include "LCD_1in44.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()
extern LCD_DIS sLCD_DIS;

void jeff_test(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in44_LCD);
    
    /* Module Init */
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
	LCD_SCAN_DIR LCD_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R
    /* LCD Init */
	printf("1.44inch LCD demo...\r\n");
	LCD_1in44_Init(LCD_ScanDir);
	LCD_1in44_Clear(WHITE);

    UWORD *BlackImage;
    UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // printf("size = %d\r\n",sizeof(BlackImage) / sizeof(UWORD));
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);
#if 0
    // /* GUI */
    // /*2.Drawing on the image*/
    printf("GUI Draw Line \r\n");
    Paint_DrawLine(2, 10, sLCD_DIS.LCD_Dis_Column - 1  , 10, RED,DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	Paint_DrawLine(1, 20, sLCD_DIS.LCD_Dis_Column, 20, RED,DOT_PIXEL_DFT, LINE_STYLE_DOTTED);

    printf("GUI Draw Rectangle \r\n");
	Paint_DrawRectangle(1,1,sLCD_DIS.LCD_Dis_Column,9,BLUE, DOT_PIXEL_DFT, LINE_STYLE_DOTTED);

    printf("GUI Draw Olympic Rings\r\n");
	uint16_t Cx1 = 40, Cy1 = 85, Cr = 12;
	uint16_t Cx2 = Cx1 + (2.5 * Cr), Cy2 = Cy1;
	uint16_t Cx3 = Cx1 + (5 * Cr), Cy3 = Cy1;
	uint16_t Cx4 = ( Cx1 + Cx2 )/2, Cy4 = Cy1 + Cr;
	uint16_t Cx5 = ( Cx2 + Cx3 )/2, Cy5 = Cy1 + Cr;

    Paint_DrawCircle( Cx1, Cy1, Cr, BLUE, DOT_PIXEL_DFT, DRAW_FILL_EMPTY);
	Paint_DrawCircle( Cx2, Cy2, Cr, BLACK, DOT_PIXEL_DFT, DRAW_FILL_EMPTY);
	Paint_DrawCircle( Cx3, Cy3, Cr, RED, DOT_PIXEL_DFT, DRAW_FILL_EMPTY);
	Paint_DrawCircle( Cx4, Cy4, Cr, YELLOW, DOT_PIXEL_DFT, DRAW_FILL_EMPTY);
	Paint_DrawCircle( Cx5, Cy5, Cr, GREEN, DOT_PIXEL_DFT, DRAW_FILL_EMPTY);

    printf("GUI Draw Realistic circles\r\n");
	Paint_DrawCircle(15, 110, 10, BRRED, DOT_PIXEL_DFT, DRAW_FILL_FULL);
	Paint_DrawCircle(sLCD_DIS.LCD_Dis_Column - 15, 110, 10, BRRED, DOT_PIXEL_DFT, DRAW_FILL_FULL);

    printf("GUI Display String \r\n");
	Paint_DrawString_EN(35,20,"WaveShare",&Font12,WHITE,BLUE);
	Paint_DrawString_EN(32,33,"Electronic",&Font12,WHITE,BLUE);
	Paint_DrawString_EN(28,45,"1.44inch TFTLCD",&Font8,RED,GRED);

	printf("GUI Display Nummber \r\n");
	Paint_DrawNum(28,55,1234567890,&Font12,WHITE,BLUE);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_1in44_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif

    // /* show bmp */
    printf("show bmp\r\n");
    GUI_ReadBmp("./pic/derbynet-128.bmp");

    Paint_DrawCharAlpha(64,64, 'M', &Font24, YELLOW, 0xffff, GREEN, 0x7fff);
    Paint_DrawCharAlpha(0,0, 'A', &Font24, RED, 0xffff, CYAN, 0x7fff);
    Paint_DrawCharAlpha(128 - 17, 128 - 24, 'Z', &Font24, BROWN, 0xffff, GRAY, 0x7fff);

    Paint_DrawStringAlpha(0, 128 - 24, "Hello", &Font24, WHITE, 0x7fff, BLUE, 0x7fff);
    Paint_DrawStringAlpha(0, 128 - 24 - 20, "Upload OK", &Font20, WHITE, 0x7fff, GREEN, 0x7fff);
    Paint_DrawStringAlpha(0, 128 - 24 - 20 - 20, "Upload OK", &Font20, GREEN, 0xffff, WHITE, 0xbfff);

    Paint_DrawStringAlpha(0, 128 - 24 - 20 * 3, "Upload ", &Font20, BLACK, 0xffff, WHITE, 0xbfff);
    Paint_DrawStringAlpha(Font20.Width * 7, 128 - 24 - 20 * 3, "OK", &Font20, BLACK, 0xffff, GREEN, 0xbfff);

    if (0) {
    for (int x = 0; x < 128; ++x) {
      for (int y = 0; y < 128; ++y) {
	UWORD color = Paint_GetPixel(x, y);
	char* color_name = "";
	switch (color) {
	case WHITE: color_name = "WHITE"; break;
	case BLACK: color_name = "BLACK"; break;
	case BLUE: color_name = "BLUE"; break;
	  // case BRED: color_name = "BRED"; break;
	  // case GRED: color_name = "GRED"; break;
	case GBLUE: color_name = "GBLUE"; break;
	case RED: color_name = "RED"; break;
	case MAGENTA: color_name = "MAGENTA"; break;
	case GREEN: color_name = "GREEN"; break;
	case CYAN: color_name = "CYAN"; break;
	case YELLOW: color_name = "YELLOW"; break;
	case BROWN: color_name = "BROWN"; break;
	case BRRED: color_name = "BRRED"; break;
	case GRAY: color_name = "GRAY"; break;
	case 32159: color_name = "background"; break;
	}	  
	printf("%d,%d %d red %d, green %d, blue %d %s\n", x, y, color,
	       ((color & 0xf800) >> 11),
	       ((color & 0x07e0) >> 5),
	       ((color & 0x001f)     ),
	       color_name
	       );
      }
    }
    }
    
    LCD_1in44_Display(BlackImage);
    DEV_Delay_ms(2000);
    
    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
	// DEV_ModuleExit();
}

int main()
{
  //   LCD_1in44_test();
  //    KEY_1in44_test();
  jeff_test();
    return 0;
}
