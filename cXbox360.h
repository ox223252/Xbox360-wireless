#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	int16_t X1;
	int16_t Y1;
	int16_t X2;
	int16_t Y2;
	uint8_t LT;
	uint8_t RT;
	int16_t du:1,
		dd:1,
		dl:1,
		dr:1,
		back:1,
		guide:1,
		start:1,
		TL:1,
		TR:1,
		A:1,
		B:1,
		X:1,
		Y:1,
		LB:1,
		RB:1;	
}
Xbox360Controller;

int getStatus360 ( const int joystick, Xbox360Controller * const ctrl, bool init );

#endif