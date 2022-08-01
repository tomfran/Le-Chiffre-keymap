MCU = atmega32u4
BOOTLOADER = atmel-dfu

SRC += swapper.c

BOOTMAGIC_ENABLE 	= yes
MOUSEKEY_ENABLE 	= no
EXTRAKEY_ENABLE 	= yes       
NKRO_ENABLE 		= yes           
RGBLIGHT_ENABLE 	= no        
ENCODER_ENABLE 		= yes
OLED_ENABLE 		= yes
RGB_MATRIX_ENABLE 	= no
RGB_MATRIX_DRIVER 	= WS2812
LTO_ENABLE 			= yes
WPM_ENABLE 			= no