#include "TexExporter.h"

TexExporter::TexExporter(const std::string& filepath)
{
	m_File.open(filepath.c_str(), std::ios::out);
}

TexExporter::~TexExporter()
{
	m_File.close();
}

void TexExporter::Export(const float* data, uint32_t width, uint32_t height, TexFormat tf)
{
	//Header
	m_File << "P3\n";
	m_File << std::to_string(width) << " " << std::to_string(height) << "\n";
	//64 level of colors per channel
	m_File << "64\n";

	switch (tf)
	{
	case TexFormat::RGBA:
		//TODO
		break;
	case TexFormat::DEPTH_COMPONENT:
		for (uint32_t i = 0; i < height; i++)
		{
			for (uint32_t j = 0; j < width; j++)
			{
				std::string val = std::to_string(data[height * i + width]);
				m_File << val << " " << val << " " << val << "  ";
			}
			m_File << "\n";
		}

		break;
	};
}
