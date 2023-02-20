#include "TexExporter.h"
#include <iostream>

TexExporter::TexExporter(const std::string& filepath)
{
	m_File.open(filepath.c_str(), std::ios::out);
	m_Extension = filepath.substr(filepath.find_last_of('.'));
}

TexExporter::~TexExporter()
{
	m_File.close();
}

void TexExporter::Export(const void* data, uint32_t width, uint32_t height, TexFormat tf)
{
	static_assert(sizeof(float) == 4, "Currently not supporting native 64-bit floats");

	if (m_Extension != ".ppm")
	{
		std::cout << "Only PPM file format is supported for the time being" << std::endl;
		return;
	}

	Export_PPM(data, width, height, tf);
}

void TexExporter::Export_PPM(const void* data, uint32_t width, uint32_t height, TexFormat tf)
{
	//Header
	m_File << "P3\n";
	m_File << std::to_string(width) << " " << std::to_string(height) << "\n";
	//64 level of colors per channel
	m_File << "255\n";

	//Initializing pointers that will be used depending on the texture format
	const uint8_t* u8_data = static_cast<const uint8_t*>(data);
	const float* f32_data = static_cast<const float*>(data);

	switch (tf)
	{
	case TexFormat::RGB_8:

		for (uint32_t i = 0; i < height; i++)
		{
			for (uint32_t j = 0; j < width; j++)
			{
				std::string vals[3];
				for (int k = 0; k < 3; k++)
				{
					uint32_t index = i * (width * 3) + (j * 3) + k;
					vals[k] = std::to_string(static_cast<uint32_t>(u8_data[index]));
				}

				m_File << vals[0] << " " << vals[1] << " " << vals[2] << "\n";
			}
		}

		break;
	case TexFormat::RGBA_8:
		//Alpha channel gets ignored
		for (uint32_t i = 0; i < height; i++)
		{
			for (uint32_t j = 0; j < width; j++)
			{
				std::string vals[3];
				for (int k = 0; k < 3; k++)
				{
					uint32_t index = i * (width * 4) + (j * 4) + k;
					vals[k] = std::to_string(static_cast<uint32_t>(u8_data[index]));
				}

				m_File << vals[0] << " " << vals[1] << " " << vals[2] << "\n";
			}
		}

		break;
	case TexFormat::DEPTH_COMPONENT_F32:

		for (uint32_t i = 0; i < height; i++)
		{
			for (uint32_t j = 0; j < width; j++)
			{
				uint32_t val = static_cast<uint32_t>(f32_data[i * width + j] * 255.0f);
				std::string str = std::to_string(val);
				m_File << str << " " << str << " " << str << "  ";
			}
			m_File << "\n";
		}

		break;
	};
}
