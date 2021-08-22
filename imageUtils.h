#pragma once
#include <tuple>
namespace ImageUtils
{
	std::tuple<int, int> getPNGSize(const char *u8StringPath);
	std::tuple<int, int> getJPEGSize(const char* u8StringPath);
	std::tuple<int, int> getGIFSize(const char* u8StringPath);
	std::tuple<int, int> getImageSize(const char* u8StringPath);
	bool isPNGFile(const char* u8StringPath);
	bool isJPGFile(const char* u8StringPath);
	bool isGIFFile(const char* u8StringPath);
}