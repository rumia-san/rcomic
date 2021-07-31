#include "window.h"
#include "SDL.h"
#include "image.h"
#include "imageList.h"
#include <stdexcept>
#include <string>

using namespace std::string_literals;
Window::Window()
{
	mWindow = SDL_CreateWindow("RComic",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
		SDL_WINDOW_RESIZABLE);
	if (!mWindow) {
		throw std::runtime_error("Failed to create window"s + SDL_GetError());
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		throw std::runtime_error("Failed to create window renderer"s + SDL_GetError());
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void Window::update()
{
	SDL_RenderPresent(mRenderer);
}

void Window::clear()
{
	SDL_RenderClear(mRenderer);
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

SDL_Renderer* Window::getRenderer()
{
	return mRenderer;
}
