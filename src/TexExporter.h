#pragma once
#include <string>
#include <fstream>

enum class TexFormat : uint8_t { RGBA = 0, DEPTH_COMPONENT };

class TexExporter
{
public:
	TexExporter(const std::string& filepath);
	~TexExporter();
	void Export(const float* data, uint32_t width, uint32_t height, TexFormat tf);
private:
	std::fstream m_File;
};