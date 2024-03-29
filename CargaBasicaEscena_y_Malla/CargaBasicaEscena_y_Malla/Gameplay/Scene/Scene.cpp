#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include "Scene.h"
#include "../../Graphics/Meshes/MeshManager.h"
#include "../../Graphics/Meshes/Mesh.h"
#include "../../Utility/ResourceHandle.h"
 
/*NOTA:
------------------
 CARGA DE ESCENA
------------------
La librer�a "assimp" es capaz de cargar un gran n�mero de formatos (3ds, md2, ...), 
es por ello que nos resultar� de mucha utilidad ya que podremos usar el formato 
que m�s se ajuste a nuestras necesidades.
Todos los formatos son distintos, por lo que Assimp al cargarlos, almacena toda la 
informaci�n en una estructura de escena que sirve para homogeneizar los datos. La 
ra�z de esa estructura es una clase llamada "aiScene" que representa la escena le�da desde 
el fichero. Para leer la escena es necesario utilizar una clase denominada "Importer", que 
como su nombre indica, se encarga de importar los datos y almacenarlos en la escena.
*/


//Inicializa una escena desde un fichero indicando su ruta.
bool cScene::Init( const std::string &lacNameID, const std::string &lacFile )
{
   macFile = lacFile;
   mbLoaded = false;
 
   // Create an instance of the Importer class
   Assimp::Importer lImporter;
 
   // Load the scene
   //Al cargar la escena se pasan una serie de par�metros que sirven para que se calculen
   // las coordenadas tangenciales, para asegurarnos que las mallas est�s compuestas por tri�ngulos 
   // y no por otro tipo de primitivas, para 
   // eliminar v�rtices duplicados y para dividir en distintas submallas aquellas mallas que 
   // est�n compuestas por m�s de un tipo de primitivas (tri�ngulos, pol�gonos,�). 
   const aiScene* lpScene = lImporter.ReadFile( lacFile.c_str(), 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);
 
   // If the import failed, report it
   if( !lpScene )
   {
      printf( lImporter.GetErrorString() );
      return false;
   }

   //Se extrae la informaci�n de la escena (en nuestro caso, se encargar� de 
   // extraer la informaci�n de las mallas).
   ProcessScene(lpScene);

   //La llamada a FreeScene se encarga de liberar la escena reci�n cargada. 
   //De todas formas, las escenas se liberan al eliminarse el importador.
   lImporter.FreeScene();
   mbLoaded = true;
   return true;
}

//M�todo que extrae la informaci�n de la escena (en nuestro caso, se encargar� de 
// extraer la informaci�n de las mallas).
void cScene::ProcessScene( const aiScene* lpScene )
{
	//La clase lpScene cuenta con un atributo llamado mNumMeshes que contiene el 
	// n�mero de meshes (mallas) que se encuentran en la escena y un array llamado mMeshes que 
	// contiene las meshes en s� mismas. Por lo tanto lo que haremos ser� acceder a todas esas 
	// mallas y cargarlas dentro de una clase cMesh que estar� gestionada por una clase 
	// cMeshManager (gestor de malla).
	for (unsigned luiIndex = 0;luiIndex < lpScene->mNumMeshes;++luiIndex)
	{
		char lacMeshName[512];
		//El nombre de una malla ser� el nombre del fichero de escena seguido 
		// del �ndice correspondiente a la malla:
		//Con la funci�n sprintf concatenamos macFile con luiIndex y lo guardamos en lacMeshName.
		sprintf( lacMeshName, "%s_%d", macFile.c_str(), luiIndex);

		cResourceHandle lHandle;
		
		//Como las mallas no est�n en ficheros sino que forman parte del fichero de escena,
		// nos vemos obligados a usar el prototipo de LoadResource (de cResourceManager (clase Padre de cMeshManager))
		// que a�ade un recurso desde MEMORIA.
		lHandle = cMeshManager::Get().LoadResource(lacMeshName, lpScene->mMeshes[luiIndex], 0);
		//Se a�ade la malla al vector de manejadores de mallas.
		mMeshList.push_back(lHandle);
	}
}

//M�todo que renderiza la escena recorriendo todas las mallas y llamando a los Render.
void cScene::Render()
{
   //Se recorre el vector de manejadores de malla accediendo (GetResource)
   // al recurso (malla en este caso) de cada manejador y se invoca el m�todo RenderMesh() para cada malla.
   for ( cResourceHandleListIt lpIt = mMeshList.begin(); lpIt != mMeshList.end(); ++lpIt )
   {
      ((cMesh *)lpIt->GetResource())->RenderMesh();
   }
}

//M�todo que libera la escena recorriendo todas las mallas y llamando a los Deinit.
void cScene::Deinit()
{   
   for ( cResourceHandleListIt lpIt = mMeshList.begin(); lpIt != mMeshList.end(); ++lpIt )
   {
      //Se recorre el vector de manejadores de malla accediendo (GetResource)
      // al recurso (malla en este caso) de cada manejador y se invoca el m�todo Deinit() para cada malla.
	  ((cMesh *)lpIt->GetResource())->Deinit();	  
   }
   mMeshList.clear();
}
