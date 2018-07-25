#include <unistd.h>

#include "cXbox360.h"

#define JS_EVENT_BUTTON 0x01	// button pressed/released
#define JS_EVENT_AXIS 0x02		// joystick moved
#define JS_EVENT_INIT 0x80		// initial state of device

struct jsEvent
{
	unsigned int time;
	short value;
	unsigned char type;
	unsigned char number;
};

enum
{
	XBOX360_B_A,
	XBOX360_B_B,
	XBOX360_B_X,
	XBOX360_B_Y,
	XBOX360_B_LB,
	XBOX360_B_RB,
	XBOX360_B_back,
	XBOX360_B_start,
	XBOX360_B_jDroit,
	XBOX360_B_jGauche
};
enum
{
	XBOX360_A_X1,
	XBOX360_A_Y1,
	XBOX360_A_X2,
	XBOX360_A_Y2,
	XBOX360_A_RT,
	XBOX360_A_LT,
	XBOX360_A_H,
	XBOX360_A_V,
};
static int readJoystickEvent ( struct jsEvent *jse, int joystick_fd )
{
	return ( read ( joystick_fd, jse, sizeof(*jse) ) == sizeof ( *jse ) );
}

int getStatus360 ( const int joystick, Xbox360Controller * const ctrl, bool init )
{
	struct jsEvent jse;

	if ( !joystick )
	{
		return ( __LINE__ );
	}

	while ( readJoystickEvent ( &jse, joystick ) )
	{
		if ( init )
		{
			jse.type &= ~JS_EVENT_INIT;
		}

		switch ( jse.type )
		{
			case JS_EVENT_INIT:
			{
				continue;
			}
			case JS_EVENT_AXIS:
			{
				switch ( jse.number )
				{
					case XBOX360_A_X1:
					{
						ctrl->X1 = jse.value;
						break;
					}
					case XBOX360_A_Y1:
					{
						ctrl->Y1 = jse.value;
						break;
					}
					case XBOX360_A_X2:
					{
						ctrl->X2 = jse.value;
						break;
					}
					case XBOX360_A_Y2:
					{
						ctrl->Y2 = jse.value;
						break;
					}
					case XBOX360_A_RT:
					{
						ctrl->RT = jse.value;
						break;
					}
					case XBOX360_A_LT:
					{
						ctrl->LT = jse.value;
						break;
					}
					case XBOX360_A_H:
					{
						ctrl->dl = ( jse.value < 0 );
						ctrl->dr = ( jse.value > 0 );
						break;
					}
					case XBOX360_A_V:
					{
						ctrl->du = ( jse.value < 0 );
						ctrl->dd = ( jse.value > 0 );
						break;
					}
				}
				break;
			}
			case JS_EVENT_BUTTON:
			{
				switch ( jse.number )
				{
					case XBOX360_B_A:
					{
						ctrl->A = jse.value;
						break;
					}
					case XBOX360_B_B:
					{
						ctrl->B = jse.value;
						break;
					}
					case XBOX360_B_X:
					{
						ctrl->X = jse.value;
						break;
					}
					case XBOX360_B_Y:
					{
						ctrl->Y = jse.value;
						break;
					}
					case XBOX360_B_LB:
					{
						ctrl->LB = jse.value;
						break;
					}
					case XBOX360_B_RB:
					{
						ctrl->RB = jse.value;
						break;
					}
					case XBOX360_B_back:
					{
						ctrl->back = jse.value;
						break;
					}
					case XBOX360_B_start:
					{
						ctrl->start = jse.value;
						break;
					}
					case XBOX360_B_jDroit:
					{
						ctrl->TR = jse.value;
						break;
					}
					case XBOX360_B_jGauche:
					{
						ctrl->TL = jse.value;
						break;
					}
				}
				break;
			}
		}
	}

	return ( 0 );
}

