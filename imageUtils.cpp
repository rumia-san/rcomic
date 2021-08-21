#include "imageUtils.h"
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <limits>
#include <cstring>
#include <stdexcept>
#include <array>
#include <algorithm>

uint32_t ntohl(uint32_t const net) {
    uint8_t data[4] = {};
    memcpy(&data, &net, sizeof(data));

    return ((uint32_t) data[3] << 0)
         | ((uint32_t) data[2] << 8)
         | ((uint32_t) data[1] << 16)
         | ((uint32_t) data[0] << 24);
}

namespace fs = std::filesystem;
constexpr auto MAX_SIZE = std::numeric_limits<int>::max();
std::tuple<int, int> ImageUtils::getPNGSize(const char* u8StringPath)
{
	std::ifstream imageFileStream{ fs::u8path(u8StringPath) };
	std::uint32_t width, height;
	imageFileStream.seekg(16);
	imageFileStream.read((char *)&width, 4);
    imageFileStream.read((char *)&height, 4);

    width = ntohl(width);
    height = ntohl(height);
	if (width > MAX_SIZE || height > MAX_SIZE)
		throw std::runtime_error("The size of the image is too large.");
	return { width, height };
}

std::tuple<int, int> ImageUtils::getJPEGSize(const char* u8StringPath)
{
	std::ifstream imageFileStream{ fs::u8path(u8StringPath) };
	std::uint32_t width, height;
	return { width, height };
}

std::tuple<int, int> ImageUtils::getImageSize(const char* u8StringPath)
{
	if (ImageUtils::isPNGFile(u8StringPath))
		return ImageUtils::getPNGSize(u8StringPath);
	else if (ImageUtils::isJPGFile(u8StringPath))
		throw std::runtime_error("Unsupported JPG");
	throw std::runtime_error("Unsupported format");
}

bool ImageUtils::isPNGFile(const char* u8StringPath)
{
	std::ifstream imageFileStream{ fs::u8path(u8StringPath), std::ios::binary };
	const std::array<uint8_t, 8> PNGSign{ 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
	std::array<uint8_t, 8> buffer;
	static_assert(sizeof(uint8_t) == sizeof(char));
	imageFileStream.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
	return std::equal(PNGSign.begin(), PNGSign.end(), buffer.begin());
}

bool ImageUtils::isJPGFile(const char* u8StringPath)
{
	std::ifstream imageFileStream{ fs::u8path(u8StringPath), std::ios::binary };
	const std::array<uint8_t, 2> JPGSign1{ 0xFF, 0xD8 };
	const std::array<uint8_t, 2> JPGSign2{ 0xFF, 0xD9 };
	std::array<uint8_t, 2> buffer;
	static_assert(sizeof(uint8_t) == sizeof(char));
	imageFileStream.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
	if (!std::equal(JPGSign1.begin(), JPGSign1.end(), buffer.begin()))
		return false;
	imageFileStream.seekg(0, std::ios_base::end);
	int length = imageFileStream.tellg();
	imageFileStream.seekg(length - 2, std::ios_base::beg);
	imageFileStream.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
	if (!std::equal(JPGSign2.begin(), JPGSign2.end(), buffer.begin()))
		return false;
	return true;
}
