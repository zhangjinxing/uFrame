/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDConf_1375_C4PR90_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE      (240)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (320)   /* Y-resolution of LCD, Logical coor. */

#define LCD_CONTROLLER 1375

#define LCD_READ_MEM(Off)            *((U16*)         (0xc00000+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,data)      *((U16*)         (0xc00000+(((U32)(Off))<<1)))=data
#define LCD_READ_REG(Off)            *((volatile U16*)(0xc1ffe0+(((U16)(Off))<<1)))
#define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0xc1ffe0+(((U16)(Off))<<1)))=data

#define LCD_BITSPERPIXEL (4)

#define LCD_SWAP_BYTE_ORDER 0

/*********************************************************************
*
*                   List of physical colors
*
**********************************************************************
*/

#define LCD_PHYSCOLORS  0x000000      /* 0000  black            */ \
                       ,0x000080      /* 0001  dark red         */ \
                       ,0x008000      /* 0010  dark green       */ \
                       ,0x008080      /* 0011  mustard          */ \
                       ,0x800000      /* 0100  dark blue        */ \
                       ,0x800080      /* 0101  purple           */ \
                       ,0x808000      /* 0110  dark turquoise   */ \
                       ,0xC0C0C0	    /* 1000  gray             */ \
                       ,0x808080      /* 0111  dark gray        */ \
                       ,0x0000ff      /* 1001  red              */ \
                       ,0x00FF00      /* 1010  green            */ \
                       ,0x00FFFF      /* 1011  yellow           */ \
                       ,0xFF0000      /* 1100  blue             */ \
                       ,0xFF00FF      /* 1101  pink (magenta)   */ \
                       ,0xFFFF00      /* 1110  cyan             */ \
											 ,0xFFFFFF      /* 1111  white            */

/*********************************************************************
*
*                   Define contents of registers
*
**********************************************************************
*/

#define LCD_REG0  (0)                                          /* Product code */

#define LCD_REG1  (0x23)                                       /* Mode reg 0.    0 for 4 bit mono LCD */            \
                                                               /*                1 for 8 bit mono LCD */            \
                                                               /*             0x23 for 8 bit color LCD */           \
                 |(1<<2)                                       /*             Mask FPSHIFT during h.non-display */

#define LCD_REG2 ((2<<6)                                       /* Mode reg 1: Bits per pixel 0:1, 1:2, 2:4, 3:8 */  \
                 |(1<<5)                                       /* High performance bit for accel. of CPU access */  \
                 |(1<<4)                                       /* Input clock divide */                             \
                 |(0<<3)                                       /* Display blank */                                  \
                 |(0<<2)                                       /* Frame repeat */                                   \
                 |(0<<1)                                       /* HW video invert enable */                         \
                 |(0<<0))                                      /* SW video invert */
                 
#define LCD_REG3                                               /* Mode reg 2. 0 for 4 bit mono LCD */               \
                  (0<<7)                                       /* LUT bypass */                                     \
                 |(0<<3)                                       /* LCDPWR override */                                \
                 |(0<<2)                                       /* hw power save enable */                           \
                 |(3<<0)                                       /* Software power save :3 = normal operation */

#define LCD_REG4 (LCD_YSIZE/8-1)                               /* horizontal panel size*/
#define LCD_REG5 ((LCD_XSIZE-1)&255)                           /* Vert. panel size, lsb */
#define LCD_REG6 ((LCD_XSIZE-1)>>8)                            /* Vert. panel size, msb */
#define LCD_REG7 (0)                                           /* FPLine start position (TFT only) */
#define LCD_REG8 (0)                                           /* H.non display period   (0 usually O.K.)*/
#define LCD_REG9 (0)                                           /* FPFrame start pos.    (TFT only) */
#define LCD_REGA (0)                                           /* v.non display period  */
#define LCD_REGB (0)                                           /* mod rate register     0: every frame */
#define LCD_REGC (LCD_XSIZE*LCD_BITSPERPIXEL/8-1)              /* Screen 1 start lsb    */
#define LCD_REGD (0)                                           /* Screen 1 start msb    */

#define LCD_REG11 (LCD_BITSPERPIXEL*(LCD_VXSIZE-LCD_XSIZE)/16) /* Memory Address offset (usually 0) */
#define LCD_REG12 LCD_REG5                                     /* Vert. screen 1 size, lsb */
#define LCD_REG13 LCD_REG6                                     /* Vert. screen 1 size, msb */

#define LCD_REG1B (0xc0)                                       /* swivel mode  */
#define LCD_REG1C (0x78)                                       /* bytes per line (stride, for swivel mode only)  */

/*********************************************************************
*
*                   Init sequence for 16 bit access
*
**********************************************************************
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif  

#define LCD_INIT_CONTROLLER()                                                                    \
        LCD_WRITE_REGLH(0x00>>1,LCD_REG0, LCD_REG1);                                             \
        LCD_WRITE_REGLH(0x02>>1,LCD_REG2, LCD_REG3);                                             \
        LCD_WRITE_REGLH(0x04>>1,LCD_REG4, LCD_REG5);                                             \
        LCD_WRITE_REGLH(0x06>>1,LCD_REG6, LCD_REG7);                                             \
        LCD_WRITE_REGLH(0x08>>1,LCD_REG8, LCD_REG9);                                             \
        LCD_WRITE_REGLH(0x0a>>1,LCD_REGA, LCD_REGB);                                             \
        LCD_WRITE_REGLH(0x0c>>1,LCD_REGC, LCD_REGD);                                             \
        LCD_WRITE_REG  (0x0e>>1,0x00);                 /* 0, screen 2 start l*/                  \
        LCD_WRITE_REGLH(0x10>>1,0x00,      LCD_REG11); /* mem adr. offset */                     \
        LCD_WRITE_REGLH(0x12>>1,LCD_REG12, LCD_REG13); /* screen 1 vsize */                      \
        LCD_WRITE_REGLH(0x1a>>1,0, LCD_REG1B);                                                   \
        LCD_WRITE_REGLH(0x1c>>1,LCD_REG1C, 0)

#endif /* LCDCONF_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
