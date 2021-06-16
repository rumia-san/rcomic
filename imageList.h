#include "image.h"
#include <list>

struct SDL_PixelFormat;

class ImageList
{
public:
	ImageList(const SDL_PixelFormat* fmt);
	~ImageList();
	void addImage(const char* imagePath);
	void addSingleImage(const char* imagePath);
	void blitTo(SDL_Surface* surface);
	void moveX(int distance);
	void moveY(int distance);

private:
	std::list<Image> mList;
	const SDL_PixelFormat* pixelFormat;
};

