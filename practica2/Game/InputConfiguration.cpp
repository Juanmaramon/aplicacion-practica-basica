#include "InputConfiguration.h"
#include "../Input/InputManager.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE },
	{ -1, -1, -1} // End of the table (Marca el final de la tabla)
};