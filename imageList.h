#include "image.h"
#include <list>

struct SDL_PixelFormat;

class ImageList
{
public:
	ImageList() = default;
	~ImageList() = default;
	void addImage(const char* imagePath);
	void addSingleImage(const char* imagePath);
	void blitTo(SDL_Surface* surface);
	void moveX(int distance);
	void moveY(int distance);

private:
	std::list<Image> mList;
};

