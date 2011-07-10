#include "MeshManager.h"
#include "Mesh.h"

//M�todo que carga la malla espec�fica desde MEMORIA.
cResource * cMeshManager::LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID )
{   
   //Se crea una instancia de cMesh y llama a su funci�n Init con los par�metros asociados. 
   //Si la funci�n devuelve error, libera la memoria y devuelve NULL. De lo contrario, construye la 
   // malla (mesh) y devuelve el recurso (malla en este caso).	
   cMesh * lpMesh = new cMesh();
   if (!lpMesh->Init( lacNameID, lpMemoryData, luiTypeID ))
   {
      delete lpMesh;
      return NULL;
   }
   return lpMesh;
}