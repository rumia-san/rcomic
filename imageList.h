#include "image.h"
#include <list>

class ImageList
{
public:
	ImageList();
	~ImageList();
	void addImage(const char* imagePath);
	void blitTo(SDL_Surface* surface);
	void moveX(int distance);
	void moveY(int distance);

private:
	std::list<Image> mList;
};

