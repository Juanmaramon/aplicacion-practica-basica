#include <windows.h>
#include <iostream>
#include <sstream>
#include "InputManager.h"
#include "../Window/Window.h"

void cInputManager::Init( const tActionMapping laActionMapping[], unsigned luiActionCount )
{
	// Initializing the OIS library
	OIS::ParamList pl;

	std::ostringstream wnd;
	wnd << (size_t)cWindow::Get().GetHWND();

	pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));

	//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
	pl.insert(std::make_pair(std::string("w32_mouse"),
	std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"),
	std::string("DISCL_NONEXCLUSIVE")));

	//This never returns null.. it will raise an exception on errors
	mpOISInputManager = OIS::InputManager::createInputSystem(pl);

	//Lets enable all addons that were compiled in:
	mpOISInputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);

	// Initializing the devices
	cGenericDevice * lpKeyboard = new cKeyboard;
	lpKeyboard->Init();

	// This needs to match with the enum eDevices.
	// eKeyboard = 0 -> Keyboard in the index 0 of the vector
	mDevices.push_back(lpKeyboard);

	// Initializing the actions vector
	mActions.resize( luiActionCount );

	// Initializing the Mapping structure
	mMapped.resize( luiActionCount );

	int liIndex = 0;
	while ( laActionMapping[ liIndex ].miAction >= 0 )
	{
		cInputEntry lEntry;
		lEntry.muiDevice = laActionMapping[ liIndex ].miDevice;
		lEntry.muiChannel = laActionMapping[ liIndex ].miChannel;
		mMapped[ laActionMapping[ liIndex ].miAction ].push_back(lEntry);
		++liIndex;
	}
}

float cInputManager::Check(int liDevice, int liChannel) {
	if (mDevices[liDevice] != NULL && mDevices[liDevice]->IsValid() )
		return (mDevices[liDevice]->Check(liChannel));

	return 0.0f;
}


void cInputManager::Update(const float &lfTimestep)
{
	// Update the devices
	int liSize = mDevices.size();
	for (int liDeviceId = 0; liDeviceId < liSize; ++liDeviceId){
		if (mDevices[liDeviceId] != NULL)
			mDevices[liDeviceId]->Update();
	}

	// For each action
	liSize = mMapped.size();
	for (int lActionId = 0; lActionId < liSize; ++lActionId){
		// For each map
		int liMapSize = mMapped[lActionId].size();
		float lfValue = 0.0f;
		for (int liMapId = 0; liMapId < liMapSize; ++liMapId){
			// Calculate the value of the input
			const cInputEntry& lEntry = mMapped[lActionId][liMapId];
			lfValue += Check(lEntry.muiDevice, lEntry.muiChannel);
		}
		// Set the value in the action
		mActions[lActionId].Update(lfTimestep, lfValue);
	}
};

void cInputManager::Deinit(){
	// Deinit devices
	for (unsigned luiIndex = 0; luiIndex < mDevices.size(); ++luiIndex){
		mDevices[luiIndex]->Deinit();
		delete mDevices[luiIndex];
	}

	mDevices.resize(0);
	mActions.resize(0);
	mMapped.resize(0);
	if( mpOISInputManager ){
		OIS::InputManager::destroyInputSystem(mpOISInputManager);
		mpOISInputManager = NULL;
	}
}
