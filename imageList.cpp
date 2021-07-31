#include "imageList.h"
#include "SDL.h"
#include <filesystem>
namespace fs = std::filesystem;


void ImageList::addImage(const char* path, SDL_Renderer* renderer)
{
	// SDL uses UTF8 encoding for the path
	fs::path p = fs::u8path(path);
	if (fs::is_directory(p)) {
		for (const auto& entry : fs::directory_iterator(p))
			addSingleImage(entry.path().u8string().c_str(), renderer);
	} else {
		addSingleImage(path, renderer);
	}
}

void ImageList::addSingleImage(const char* imagePath, SDL_Renderer* renderer)
{
	if (mList.empty())
	{
		mList.emplace_back(imagePath, renderer);
	}
	else
	{
		auto [lastX, lastY] = mList.back().getPosition();
		mList.emplace_back(imagePath, renderer);
		Image& newImage = mList.back();
		auto [thisW, thisH] = newImage.getSize();
		// move to the left side of last image
		newImage.moveTo(lastX - thisW, 0);
	}
}

void ImageList::blitTo(SDL_Surface* surface)
{
	for (auto&& image : mList)
	{
		image.blitTo(surface);
	}
}

void ImageList::moveX(int distance)
{
	for (auto&& image : mList)
	{
		image.moveX(distance);
	}
}

void ImageList::moveY(int distance)
{
	for (auto&& image : mList)
	{
		image.moveY(distance);
	}
}
