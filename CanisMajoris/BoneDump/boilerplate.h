#include <string>

namespace Core      {
namespace Renderer  {
namespace CoreUtils {
	class Vertex;
}
}
}


const std::string ABOUT("BoneDump - OBJ Bone Dumping Utility \n"
                        "Author: Bogdan Vitel, Canis Majoris 2015\n"
                        "Dumps all bone coordinates in C++ / C# compatible code \n"
                        );

const std::string INVALID_PARAM_MESSAGE("Unknown parameter - ");

struct flags
{
	const char* CS_OUTPUT = "-cs";
	const char* H_OUTPUT = "-header";
	const char* LOG = "-log";
} SUPPORTED_FLAGS;