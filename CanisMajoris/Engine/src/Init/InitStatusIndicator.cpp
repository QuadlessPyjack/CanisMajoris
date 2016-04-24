////////////////////////////////////////////////////////////////////////////////////////////////
//! \brief   Engine Init Status Indicator - Canis Majoris Init
//! \author  Bogdan Vitel
//! \details What is this? The result of 48hrs of Global Games Jam 2016
//! \date    31/01/2016
//! \todo    this should probably be a singleton and tied into the event system...EVENTually
//////////////////////////////////////////////////
#include <SDL.h>

#include <Init/InitStatusIndicator.h>
#include <Utils/Constants.h>
#include <time.h>

namespace Core {
namespace Init {

	StatusIndicator *StatusIndicator::m_indicator = nullptr;
	StatusIndicator::StatusIndicator()
	: m_frame_delta(clock())
	, m_screen(SDL_GetVideoSurface())
	{
		// when the font loader is remade into a singleton, do init symbols initialization here
	}

	StatusIndicator::~StatusIndicator()
	{
		delete m_indicator;
		m_indicator = nullptr;
	}

	StatusIndicator& StatusIndicator::GetInstance()
	{
		if (m_indicator == nullptr)
		{
			m_indicator = new StatusIndicator();
			return *m_indicator;
		}
		return *m_indicator;
	}

	void StatusIndicator::LoadInitSymbols(std::vector<Game::Entities::UIObject> initSymbols)
	{
		m_initSymbols = initSymbols;
		for (int index = 0; index < m_initSymbols.size(); ++index)
		{
			m_initSymbols[index].setPosition(Math::Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		}
	}

	void StatusIndicator::DisplayStartupSplash()
	{
		if (m_initSymbols.size() == 0)
		{
			return;
		}
		m_initSymbols[0].setPosition(Math::Vector2(600.0f, 200.0f));
		m_initSymbols[0].Draw(Colour::Green);
		SDL_Flip(m_screen);
		SDL_Delay(1000);

		clearScreen();
	}

	void StatusIndicator::DisplayPercentage(int percentage)
	{
		if (m_initSymbols.size() == 0)
		{
			return;
		}
	}

	void StatusIndicator::DisplayProgressSpinner()
	{
		if (m_initSymbols.size() == 0)
		{
			return;
		}
		m_frame_delta = (double)clock() - m_frame_delta;
		m_initSymbols[1].Rotate(Vector3(0.0f, 0.0f, 0.15f) * m_frame_delta);
		m_initSymbols[1].Draw();

		clearScreen();
	}

	void StatusIndicator::DisplayGuruMeditation()
	{
		if (m_initSymbols.size() == 0)
		{
			return;
		}

		m_initSymbols[2].Draw(Colour::Red);
		SDL_Flip(m_screen);
		SDL_Delay(1000);

		clearScreen();
	}

	void StatusIndicator::clearScreen()
	{
		SDL_Flip(m_screen);
		SDL_FillRect(m_screen, nullptr, 0x000000);
	}
}
}