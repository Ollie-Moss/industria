#include "Texture.hpp"
#include <glm/common.hpp>

Texture2D::Texture2D()
	: Width(0), Height(0), Internal_Format(GL_RGBA), Image_Format(GL_RGBA),
	  Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_NEAREST),
	  Filter_Max(GL_NEAREST) {
	glGenTextures(1, &this->ID);
}

void Texture2D::Generate(unsigned int width, unsigned int height,
						 unsigned char *data) {
	this->Width = width;
	this->Height = height;

	if (data != nullptr) {
		this->textureData = std::vector<unsigned char>(data, data + (width * height * 4));
	}

	// create Texture
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0,
				 this->Image_Format, GL_UNSIGNED_BYTE, data);
	// set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec4 Texture2D::GetPixel(glm::vec2 texCoord) const {
	int x = static_cast<int>(texCoord.x * Width);
	int y = static_cast<int>(texCoord.y * Height);

	x = glm::clamp<int>(x, 0, Width - 1);
	y = glm::clamp<int>(y, 0, Height - 1);

	int index = (y * Width + x) * 4;

	return glm::vec4(textureData[index] / 255.0f, textureData[index + 1] / 255.0f, textureData[index + 2] / 255.0f, textureData[index + 3] / 255.0f);
}

void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, this->ID); }
