#include "imageUtils.h"
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <limits>
#include <cstring>
#include <stdexcept>
#include <array>
#include <algorithm>

uint16_t ntohl16(uint16_t num)
{
	uint8_t *ptr = reinterpret_cast<uint8_t*>(&num);
	return ((uint16_t)ptr[0] << 8) | ptr[1];
}

uint32_t ntohl32(uint32_t num)
{
	uint8_t *data = reinterpret_cast<uint8_t*>(&num);
    return ((uint32_t) data[3] << 0)
         | ((uint32_t) data[2] << 8)
         | ((uint32_t) data[1] << 16)
         | ((uint32_t) data[0] << 24);
}

namespace fs = std::filesystem;
constexpr auto MAX_SIZE = std::numeric_limits<int>::max();
std::tuple<int, int> ImageUtils::getPNGSize(const char* u8StringPath)
{
	std::ifstream imageFileStream{ fs::u8path(u8StringPath), std::ios::binary };
	std::uint32_t width, height;
	imageFileStream.seekg(16);
	imageFileStream.read((char *)&width, 4);
    imageFileStream.read((char *)&height, 4);

    width = ntohl32(width);
    height = ntohl32(height);
	if (width > MAX_SIZE || height > MAX_SIZE)
		throw std::runtime_error("The size of the image is too large.");
	return { width, height };
}

std::tuple<int, int> ImageUtils::getJPEGSize(const char* u8StringPath)
{
	std::ifstream imageFileStream{ fs::u8path(u8StringPath), std::ios::binary };
	std::uint16_t width = 0, height = 0;
	imageFileStream.seekg(2);
	while (imageFileStream)
	{
		uint8_t mark;
		uint8_t type;
		uint16_t length;
		imageFileStream.read(reinterpret_cast<char*>(&mark), sizeof(mark));
		imageFileStream.read(reinterpret_cast<char*>(&type), sizeof(type));
		imageFileStream.read(reinterpret_cast<char*>(&length), sizeof(length));
		if (mark != 0xFF)
			throw std::runtime_error("Invalid JPEG format!");
		if (type == 0xC0 || type == 0xC1 || type == 0xC2)
		{
			imageFileStream.seekg(1, std::ios_base::cur);
			imageFileStream.read(reinterpret_cast<char*>(&height), sizeof(height));
			imageFileStream.read(reinterpret_cast<char*>(&width), sizeof(width));
			height = ntohl16(height);
			width = ntohl16(width);
			break;
		}
		length = ntohl16(length);
		imageFileStream.seekg(length - 2, std::ios_base::cur);
	}
	if (width == 0 || height == 0)
		throw std::runtime_error("JPEG size not found!");
	return { width, height };
}

std::tuple<int, int> ImageUtils::getImageSize(const char* u8StringPath)
{
	if (ImageUtils::isPNGFile(u8StringPath))
		return ImageUtils::getPNGSize(u8StringPath);
	else if (ImageUtils::isJPGFile(u8StringPath))
		return ImageUtils::getJPEGSize(u8StringPath);
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
	size_t length = imageFileStream.tellg();
	imageFileStream.seekg(length - 2, std::ios_base::beg);
	imageFileStream.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
	if (!std::equal(JPGSign2.begin(), JPGSign2.end(), buffer.begin()))
		return false;
	return true;
}
