// This class provide references to resources

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <vector>
#include <list>
#include "InternalResource.h"
#include "ResourceHandle.h"
#include "../Graphics/Fonts/FontProperties.h"

class cResourceManager
{
	public:
		void Init( unsigned luiMaxSize );
		void Deinit();
		cResourceHandle FindResource( std::string lacNameID );
		void UnloadResource( cResourceHandle * lpHandle );
		cResourceHandle LoadResource( std::string lacNameID, const std::string &lacFile );
		cResourceHandle LoadResource( std::string lacNameID, void * lpMemoryData, int luiTypeID );
		cResourceHandle cResourceManager::LoadResource( const std::string &lacFile );
	protected:
		std::vector<cInternalResource> maResources;
		std::list<unsigned> mFreeResourceSlot;
		int muiNextKey;
		unsigned muiMaxSize;
		cResource * GetResource( cResourceHandle *lpHandle );
		friend class cResourceHandle;
		cFontProperties mProperties;
		cResourceHandle AddResourceToPool( cResource * lpResource );
		// Implementation of this methods will be placed in the child classes
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile ) { return NULL; };
		virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID ) { return NULL; }
};
#endif