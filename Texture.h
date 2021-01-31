#pragma once

struct Texture {
	const char* path;
	const int id;
	const int width, height;
	Texture() = default;
	Texture(const int p_id, const char* p_path, const int p_width, const int p_height) : id(p_id), path(p_path), width(p_width), height(p_height) {}
	Texture(const int p_id, const char* p_path, const int p_side) : id(p_id), path(p_path), width(p_side), height(p_side) {}
	Texture(const int p_id, const char* p_path) : id(p_id), path(p_path), width(NULL), height(NULL) {}
};