#include <fstream>
#include <Utils/MeshContainer.h>

#include "boilerplate.h"

inline void generateContents(std::ofstream &outputFile, float scaleFactor, char flag[12], MeshContainer &container, int meshIndex)
{
	using namespace std;
	bool fireOnce = false;
	if (strcmp(flag, SUPPORTED_FLAGS.CS_OUTPUT) == 0)
	{
		cout << container.GetMesh(meshIndex)->GetID() << '\n';
		Vector3 v3 = container.GetMesh(meshIndex)->Location() * scaleFactor;
		outputFile << "Vector3 " << container.GetMesh(meshIndex)->GetID() << " = new Vector3" << v3 << ";\n";
	}

	if (strcmp(flag, SUPPORTED_FLAGS.H_OUTPUT) == 0)
	{
		cout << container.GetMesh(meshIndex)->GetID() << '\n';
		if (!fireOnce)
		{
			outputFile << "include <Utils/Math/Vector3.h> \n\n";
			fireOnce = true;
		}
		Vector3 v3 = container.GetMesh(meshIndex)->Location() * scaleFactor;
		outputFile << "Vector3 " << container.GetMesh(meshIndex)->GetID() << v3 << ";\n";
	}
}