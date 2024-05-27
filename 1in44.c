#include "DEV_Config.h"
#include "LCD_1in44.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <getopt.h>
#include <signal.h>     //signal()
extern LCD_DIS sLCD_DIS;

struct Line {
  char* text;
  UWORD bg_color;
  UWORD bg_alpha;
};

UWORD ConvertColor(ulong color) {
  uint red = (((color & 0xff0000) >> 16) * 0x1f) / 0xff;
  uint green = (((color & 0xff00) >>  8) * 0x3f) / 0xff;
  uint blue = ((color & 0xff) * 0x1f) / 0xff;
  return ((red & 0x1f) << 11) | ((green & 0x3f) << 5) | (blue & 0x1f);
}

int main (int argc, char **argv) {
  signal(SIGINT, Handler_1in44_LCD);  // Exception handling:ctrl + c
    
  if(DEV_ModuleInit() != 0){
    DEV_ModuleExit();
    exit(0);
  }
  LCD_SCAN_DIR LCD_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R

  LCD_1in44_Init(LCD_ScanDir);
  LCD_1in44_Clear(WHITE);

  int c;
  struct Line lines[10];
  // *lines = 0;

  int nlines = 0;
  UWORD bg_color = WHITE;
  UWORD bg_alpha = 0xffff;
  
  while (1) {
    static struct option long_options[] =
      {
	{"text",   required_argument, 0, 't'},
	{"background", required_argument, 0, 'b'},
	{"alpha", required_argument, 0, 'a'},
	{0, 0, 0, 0}
      };

    /* getopt_long stores the option index here. */
    int option_index = 0;
    c = getopt_long (argc, argv, "b:t:c:a:",
		     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c) {
    case 0:
      printf("option %s\n", long_options[option_index].name);
      break;
    case 'b':  // background color
      bg_color = ConvertColor(strtol(optarg, NULL, 16));
      break;
    case 'a':  // alpha for background
      bg_alpha = strtol(optarg, NULL, 16);
      break;
    case 't':  // text
      lines[nlines].text = optarg;
      lines[nlines].bg_color = bg_color;
      lines[nlines].bg_alpha = bg_alpha;
      ++nlines;
      break;
    }
  }

  UWORD *BlackImage;
  UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;

  if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    exit(0);
  }

  Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, WHITE, 16);
  Paint_Clear(WHITE);

  if (optind >= argc) {
    printf("Usage: --color -alpha --text  (128x128 bitmap)\n");
    exit(1);
  }

  GUI_ReadBmp(argv[optind]);

  sFONT* font = &Font20;
  for (int i = 0; i < nlines; ++i) {
    int width = font->Width * strlen(lines[i].text);
    Paint_DrawStringAlpha((LCD_WIDTH - width) / 2, LCD_HEIGHT - font->Height * (i + 1), lines[i].text,
			  font, BLACK, 0xffff, lines[i].bg_color, lines[i].bg_alpha);
  }

  LCD_1in44_Display(BlackImage);
  // DEV_Delay_ms(2000);
    
  free(BlackImage);
  BlackImage = NULL;

  return 0;
}
