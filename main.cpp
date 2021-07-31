#include "window.h"
#include "image.h"
#include "imageList.h"
#include "SDL.h"
#include <stdexcept>
#include <string>
class RComic
{
public:
	RComic()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			using namespace std::string_literals;
			throw std::runtime_error("Unable to initialize SDL: %s"s + SDL_GetError());
		};
	}
	~RComic() { SDL_Quit(); }
	void eventLoop()
	{
		while (!mQuit)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) > 0)
			{
				switch (event.type)
				{
				case SDL_DROPFILE: {
					char* droppedFile = event.drop.file;
					mImage.addImage(droppedFile, mWindow.getRenderer());
					SDL_free(droppedFile);
					break;
				}
				case SDL_MOUSEWHEEL:
					handleMouseWheelEvent(event.wheel);
					break;
				case SDL_MOUSEBUTTONDOWN:
					handleMouseButtonEvent(event.button);
					break;
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}
			handleKeyboardInput();
			autoScroll();
			mWindow.clear();
			mWindow.drawImage(mImage);
			mWindow.update();
			SDL_Delay(1000/60);
		}
	}
	void run()
	{
		mWindow.drawImage(mImage);
		mWindow.update();
		eventLoop();
	}

private:
	Window mWindow;
	ImageList mImage;
	bool mQuit = false;
	bool mAutoScroll = false;
	int speed = 1;
	void handleMouseWheelEvent(SDL_MouseWheelEvent& e)
	{
		mImage.moveX(e.y * speed);
	}
	void handleMouseButtonEvent(SDL_MouseButtonEvent& e)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
			mAutoScroll = !mAutoScroll;
			break;
		}
	}
	void handleKeyboardInput()
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_LEFT])
			mImage.moveX(-speed);
		if (state[SDL_SCANCODE_RIGHT])
			mImage.moveX(speed);
		if (state[SDL_SCANCODE_UP])
			mImage.moveY(-speed);
		if (state[SDL_SCANCODE_DOWN])
			mImage.moveY(speed);
		if (state[SDL_SCANCODE_ESCAPE])
			mQuit = true;
	}
	void autoScroll()
	{
		if (mAutoScroll)
		{
			mImage.moveX(speed);
		}
	}
};

//Thanks to SDL2, we could create WIN32 GUI program without the WinMain entry function
int main(int argc, char* argv[])
{
	try
	{
		RComic rComic;
		rComic.run();
	}
	catch (const std::exception& e)
	{
		SDL_Log(e.what());
		return 1;
	}
	return 0;
}
