#ifndef INIT_INDICATOR_H
#define INIT_INDICATOR_H
////////////////////////////////////////////////////////////////////////////////////////////////
//! \brief   Engine Init Status Indicator - Canis Majoris Init
//! \author  Bogdan Vitel
//! \details What is this? The result of 48hrs of Global Games Jam 2016
//! \date    31/01/2016
//! \todo    this should probably be a singleton and tied into the event system...EVENTually
//////////////////////////////////////////////////
#include <vector>
#include <Entities/UIObject.h>

struct SDL_Surface;

namespace Core {
namespace Init {
	
	class CM_ENGINE_API StatusIndicator
	{
	public:
		~StatusIndicator();

		static StatusIndicator &GetInstance();

		void LoadInitSymbols(std::vector<Game::Entities::UIObject> initSymbols);

		void DisplayStartupSplash();
		void DisplayPercentage(int percentage);
		void DisplayProgressSpinner();
		void DisplayGuruMeditation();

	private:
		StatusIndicator();
		static StatusIndicator *m_indicator;
		double m_frame_delta;
		std::vector<Game::Entities::UIObject> m_initSymbols;
		void clearScreen();
		SDL_Surface *m_screen;
	};

} // namespace Init
} // namespace Core

#endif