/*Esta Clase (malla) implementa la interfaz cResource.
Esta clase es HIJA de cResource (PADRE) y por tanto heredar� de ella e 
implementa las funciones virtuales correspondientes. 

Se encarga de cargar la malla desde la estructura (aiMesh) que nos proporciona 
la librer�a Assimp para posteriormente almacenar la informaci�n de mallas en la 
tarjeta gr�fica (mirar m�todo cMesh::Init).
*/


#ifndef MESH_H
#define MESH_H
 
#include <string>
#include "../../Utility/Resource.h"
 
//En la funci�n "cMesh::Init" se hace referencia a la estructura aiMesh, por eso es necesario
// a�adir una declaraci�n forward de dicha clase:
struct aiMesh;
 
class cMesh : public cResource
{
   public:
      cMesh()                         { mbLoaded = false; }
 
      //Inicializa una malla desde Memoria.
	  virtual bool Init( const std::string &lacNameID, void * lpMemoryData, int luiTypeID );
      
	  //Libera los bufferes que se crean en el m�todo Init.
	  virtual void Deinit();

      //Comprueba si la malla est� cargada.
	  virtual bool IsLoaded()  { return mbLoaded; }
      
      //Renderiza la malla.	  
	  void RenderMesh();
   
	private:
		
      //Almacena el n�mero de �ndices que contiene la malla y que se necesita
	  // para poder renderizar.
	  unsigned muiIndexCount;

	  //Booleano que indica si la malla est� cargada o no.
      bool mbLoaded;

	  //Buffer de v�rtices (posiciones).
	  unsigned int mVboVertices;

	  //Buffer de normales.
	  unsigned int mVboNormals;

	  //Buffer de texturas.
	  unsigned int mVboTexture;

	  //Buffer de �ndices.
	  unsigned int mVboIndex;

	  //Booleano que indique si la malla cuenta o no con normales.
	  bool mbHasNormals;

};
#endif