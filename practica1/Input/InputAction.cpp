#include "InputAction.h"

void cInputAction::Init( void )
{
	mfValue = 0.0f;
	mfTimePressed = 0.0f;
	mbIsPressed = false;
	mbWasPressed = false;
	mbBecomeReleased = false;
	mbBecomePressed = false;
}

void cInputAction::Update (float lfTimestep, float lfValue)
{
	mbWasPressed = mbIsPressed;
	mbIsPressed = (lfValue > 0.0f);
	if (mbIsPressed && mbWasPressed){
		mfTimePressed += lfTimestep;
	}else{
		mfTimePressed = 0;
	}
	mbBecomePressed = (mbIsPressed && !mbWasPressed );
	mbBecomeReleased = (mbWasPressed && !mbIsPressed );
	mfValue = lfValue;
}