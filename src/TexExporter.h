#pragma once
#include <string>
#include <fstream>

enum class TexFormat : uint8_t 
{ 
	RGB_8 = 0,
	RGBA_8,
	DEPTH_COMPONENT_F32
};

class TexExporter
{
public:
	TexExporter(const std::string& filepath);
	~TexExporter();
	void Export(const void* data, uint32_t width, uint32_t height, TexFormat tf);
private:
	void Export_PPM(const void* data, uint32_t width, uint32_t height, TexFormat tf);

	std::fstream m_File;
	std::string m_Extension;
};