#pragma once
struct SDL_Window;
struct SDL_Surface;
class Image;
class ImageList;

class Window
{
public:
	Window();
	~Window();
	void update();
	void drawImage(Image& image);
	void drawImage(ImageList& imageList);
private:
	SDL_Window* mWindow;
};
