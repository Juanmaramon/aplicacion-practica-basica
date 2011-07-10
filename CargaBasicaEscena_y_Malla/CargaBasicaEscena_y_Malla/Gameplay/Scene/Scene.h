/*Esta Clase implementa la interfaz cResource.
Esta clase es HIJA de cResource (PADRE) y por tanto heredar� de ella e 
implementa las funciones virtuales correspondientes. 
*/

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "../../Utility/Resource.h"
#include "../../Utility/ResourceHandle.h"


//Para poder a�adir el prototipo de la funci�n ProcessScene a la definici�n de esta clase es necesario 
// a�adir una declaraci�n forward de aiScene para poder referenciarla en dicha funci�n: 
struct aiScene;

class cScene : public cResource
{
   public:
      cScene()                               { mbLoaded = false; }
 
	  //Inicializa una escena desde un fichero indicando su ruta.
      virtual bool Init( const std::string &lacNameID, const std::string &lacFile );

	  //Libera la escena recorriendo todas las mallas y llamando a los Deinit.
	  virtual void Deinit();

      //Comprueba si la escena est� cargada.
      virtual bool IsLoaded()  { return mbLoaded; }

      void Update( float lfTimestep );

	  //Renderiza la escena recorriendo todas las mallas y llamando a los Render.
      void Render();

   private:  
	    
      //Extrae la informaci�n de la escena (en nuestro caso, se encargar� de 
      // extraer la informaci�n de las mallas).
	  void ProcessScene( const aiScene* lpScene );

	  //Cadena que almacena el nombre del fichero de escena.
      std::string macFile;

	  //Booleano que indica si la escena est� cargada o no.
      bool mbLoaded;

	  typedef std::vector<cResourceHandle> cResourceHandleList;
	  //Iterador para recorrer el vector de los manejadores de malla.
	  typedef cResourceHandleList::iterator cResourceHandleListIt;
	  //Vector (de tipo cResourceHandleList) que contendr� los manejadores de malla de la escena.
	  cResourceHandleList mMeshList;
};

#endif