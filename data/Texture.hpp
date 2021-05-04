#pragma once

struct Texture {
	static unsigned char freeID;
	const char* path;
	const unsigned char id;
	const int width, height;
	Texture() = default;
	Texture(const char* p_path, const int p_width, const int p_height) : id(freeID++), path(p_path), width(p_width), height(p_height) {}
	Texture(const char* p_path, const int p_side) : id(freeID++), path(p_path), width(p_side), height(p_side) {}
	Texture(const char* p_path) : id(freeID++), path(p_path), width(0), height(0) {}
};