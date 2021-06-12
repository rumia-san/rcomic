#include "window.h"
#include "SDL.h"
#include "image.h"
#include <stdexcept>
#include <string>
Window::Window()
{
	mWindow = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (!mWindow) {
		using namespace std::string_literals;
		throw std::runtime_error("Failed to create window"s + SDL_GetError());
	}
		
}

Window::~Window()
{
	if (mWindow)
		SDL_DestroyWindow(mWindow);
}

void Window::update()
{
	SDL_UpdateWindowSurface(mWindow);
}

int Window::drawImage(Image& image)
{
	return image.blitTo(SDL_GetWindowSurface(mWindow));
}
