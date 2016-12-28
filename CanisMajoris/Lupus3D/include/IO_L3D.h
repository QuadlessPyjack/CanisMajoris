#ifndef IO_L3D_H
#define IO_L3D_H
////////////////////////////////////////// 
//! \brief   IO_L3D_H - Canis Majoris Renderer
//! \author  Bogdan Vitel
//! \details L3D File Loader Header
//! \date    25/04/2016
//! \todo 
//////////////////////////////////////////
#include <string>
#include <vector>
#include <fstream>
#include <FileInfo.h>


#ifdef L3D_LIB_COMPILE
	#define L3D_LIB __declspec(dllexport)
#else
	#define L3D_LIB __declspec(dllimport)
#endif

class MeshContainer;

namespace Lupus3D {

			class L3D_LIB Model
			{
			public:
				Model();

				Model(std::string filePath);

				void Load(std::string filePath);
				void Save(std::string filePath);
				void AddMeshFile(FileInfo::MeshFile meshFile);
				void CreateBlankFile(string fileName);



				bool IsValid();

				std::vector<FileInfo::MeshParamsFile> GetMeshFiles();

			private:
				void createBlankFile(string fileName);
				void writeDescriptor(string fileName);
				void writeGeometryContent(FileInfo::MeshDataFile content[]);
				void writeMeshParameters(FileInfo::MeshParamsFile meshParams[]);
				void setGeometryBlockSize(uchar fileBlockEntry[], int geometricObjectCount, int& block_length);

				bool loadDescriptor(FileInfo::L3DFILE &fileMap);
				bool loadNBlock(FileInfo::L3DFILE &fileMap);
				bool loadGeometryContent(FileInfo::L3DFILE &fileMap, FileInfo::MeshDataFile content[]);
				bool loadMeshParameters(FileInfo::L3DFILE &fileMap);

				string m_filename;
				fstream m_l3d_file;
				std::vector<FileInfo::MeshFile> m_meshes;
				FileInfo::L3DFILE m_fileMap;

			};
}

#endif // IO_L3D_H