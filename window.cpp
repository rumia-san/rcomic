#include "window.h"
#include "SDL.h"
#include "image.h"
#include "imageList.h"
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
	SDL_DestroyWindow(mWindow);
}

void Window::update()
{
	SDL_UpdateWindowSurface(mWindow);
}

void Window::drawImage(Image& image)
{
	image.blitTo(SDL_GetWindowSurface(mWindow));
}

void Window::drawImage(ImageList& imageList)
{
	imageList.blitTo(SDL_GetWindowSurface(mWindow));
}

const SDL_PixelFormat* Window::getWindowPixelFormat()
{
	return SDL_GetWindowSurface(mWindow)->format;
}
