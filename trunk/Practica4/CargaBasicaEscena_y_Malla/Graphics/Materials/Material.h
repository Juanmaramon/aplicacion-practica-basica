// Class to obtain data of resource files

#ifndef Material_H
#define Material_H

#include "..\..\Utility\Resource.h"
#include "..\..\Utility\ResourceHandle.h"

class cMaterial : public cResource
{
	public:
		cMaterial() { mbLoaded = false; }
		virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int liDataType );
		virtual void Deinit();
		virtual bool IsLoaded() { return mbLoaded; }
		void SetMaterial();
	private:
		cResourceHandle mDiffuseTexture;
		bool mbLoaded;
};

#endif