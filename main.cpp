#include "window.h"
#include "image.h"
#include "SDL.h"

class RComic
{
public:
	RComic() {}
	~RComic() {}
	void eventLoop()
	{
		while (!mQuit)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) > 0)
			{
				switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					handleMouseEvent(event.button);
					break;
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}
			handleKeyboardInput();
			autoScroll();
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
	Image mImage{ "D:\\developer\\rcomic\\test.bmp" };
	bool mQuit = false;
	bool mAutoScroll = false;
	unsigned int speed = 1;
	void handleMouseEvent(SDL_MouseButtonEvent& b)
	{
		switch (b.button)
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

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	};
	int exitCode = 0;
	try
	{
		RComic rComic;
		rComic.run();
	}
	catch (const std::exception& e)
	{
		SDL_Log(e.what());
		exitCode = 1;
	}
	SDL_Quit();
	return exitCode;
}