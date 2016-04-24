////////////////////////////////////////////////////////////////////////////////////////////////
//! \brief   FontLoader - Canis Majoris Init
//! \author  Bogdan Vitel
//! \details Handles font loading and initialization
//! \date    31/01/2016
//! \todo    this MUST be a SINGLETON or else all that mesh data could go to hell
//////////////////////////////////////////////////
#include<Init/FontLoader.h>
#include<Init/InitStatusIndicator.h>

namespace Core {
namespace Init {

	FontLoader::FontLoader()
	: m_fontModel(DEFAULT_FONT_MODEL_FILENAME)
	, m_engineGlyphsModel(DEFAULT_ENGINE_SYMBOLS_FILENAME)
	{
		generateFontObjects(DEFAULT_FONT_NAME);
		generateFontObjects(DEFAULT_ENGINE_SYMBOLS_NAME, true);
	}

	FontLoader::FontLoader(std::string fontModelFilename)
	: m_fontModel(fontModelFilename)
	, m_engineGlyphsModel(DEFAULT_ENGINE_SYMBOLS_FILENAME)
	{
		generateFontObjects(fontModelFilename);
		generateFontObjects(DEFAULT_ENGINE_SYMBOLS_NAME);
	}

	bool FontLoader::LoadFontModelFile(std::string fontModelFilename)
	{
		m_fontModel.Load(fontModelFilename);
		if (fontModelFilename == DEFAULT_ENGINE_SYMBOLS_NAME)
		{
			generateFontObjects(DEFAULT_ENGINE_SYMBOLS_NAME, true);
		}

		return m_fontModel.IsValid();
	}

	std::list<Game::Entities::UIObject> FontLoader::GetFont(std::string fontName)
	{
		FontMap::const_iterator it;
		for (it = m_fontMap.begin(); it != m_fontMap.end(); ++it)
		{
			if (it->first == fontName)
			{
				return it->second;
			}
		}
		// requested font wasn't found, send the default one instead
		return m_fontMap.at(DEFAULT_FONT_NAME);
	}

	void FontLoader::generateFontObjects(std::string fontName, bool shouldLoadGlyphs)
	{
			MeshContainer tempMeshStorage;
			if (!shouldLoadGlyphs)
			{
				if (!m_fontModel.IsValid())
				{
					return;
				}
				tempMeshStorage = m_fontModel.ExtractMeshData(m_fontVertexPool);
			}
			else
			{
				int fontArrayLength = m_fontArray.size();
				std::list<Game::Entities::UIObject>::const_iterator it;
				it = m_fontArray.end();
				--it;
				std::vector<Game::Entities::UIObject> loadSymbols;
				loadSymbols.push_back(*it);
				loadSymbols.push_back(*(--it));
				loadSymbols.push_back(*(--it));

				StatusIndicator::GetInstance().LoadInitSymbols(loadSymbols);
				StatusIndicator::GetInstance().DisplayStartupSplash();
				if (!m_engineGlyphsModel.IsValid())
				{
					StatusIndicator::GetInstance().DisplayGuruMeditation();
					return;
				}
				tempMeshStorage = m_engineGlyphsModel.ExtractMeshData(m_glyphsVertexPool);
			}

			for (int tempMeshIndex = 0; tempMeshIndex < tempMeshStorage.length(); ++tempMeshIndex)
			{
				m_fontMeshes.AddMesh(tempMeshStorage.GetMesh(tempMeshIndex));
			}

			// cycle only through the newly added glyphs and build the UI font
			// AddMesh uses push_back behind the scenes, hence why we iterate on 0-length and not the other way around
			for (int meshIndex = 0; meshIndex < tempMeshStorage.length(); ++meshIndex)
			{
				Game::Entities::UIObject charObject;
				charObject.SetMesh(m_fontMeshes.GetMesh(meshIndex));
				m_fontArray.push_back(charObject);
			}
			FontPair newFontPair(fontName, m_fontArray);
			m_fontMap.insert(newFontPair);
	}
} // namespace Init
} // namespace Core