#ifndef FONT_LOADER_H
#define FONT_LOADER_H
////////////////////////////////////////////////////////////////////////////////////////////////
//! \brief   FontLoader - Canis Majoris Init
//! \author  Bogdan Vitel
//! \details Handles font loading and initialization
//! \date    31/01/2016
//! \todo    this really needs to be a SINGLETON or else all that mesh data could go to hell
//////////////////////////////////////////////////
#include <FileIO/OBJImpex/Reader/IO_OBJLoader.h>
#include <Entities/UIObject.h>
#include <Utils/Constants.h>

#include <vector>
#include <map>
#include <list>

namespace Core {
namespace Init {
	class FontLoader
	{
	public:
		FontLoader();
		FontLoader(std::string fontModelFilename);
		bool LoadFontModelFile(std::string fontModelFilename);

		std::list<Game::Entities::UIObject> GetFont(std::string fontName);


	private:
		IO::ModelFile m_fontModel;
		IO::ModelFile m_engineGlyphsModel;
		std::list<Game::Entities::UIObject> m_fontArray;
		std::vector<Core::Renderer::CoreUtils::Vertex*> m_fontVertexPool;
		std::vector<Core::Renderer::CoreUtils::Vertex*> m_glyphsVertexPool;
		MeshContainer m_fontMeshes;

		typedef std::pair<std::string, std::list<Game::Entities::UIObject>> FontPair;
		typedef std::map<std::string, std::list<Game::Entities::UIObject>> FontMap;
		FontMap m_fontMap;

		void generateFontObjects(std::string fontName = "FONT_", bool shouldLoadGlyphs = false);
	};
} // namespace Init
} // namespace Core

#endif // FONT_LOADER_H