#include "OpenGLTexture.h"
#include <glad/glad.h>

OpenGLTexture::OpenGLTexture() : id(0), width(0), height(0), bpp(0)
{
}

void OpenGLTexture::load(std::string path)
{

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	stbi_set_flip_vertically_on_load(1);

	unsigned char *buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	//~

	glBindTexture(GL_TEXTURE_2D, 0);

	if (buffer == nullptr)
	{
		std::cout << "stbi_failure_reason()\n";
		std::cout << stbi_failure_reason() << "\n";
	}
	if (buffer)
		stbi_image_free(buffer);
}

void OpenGLTexture::setData(int _width, int _height, unsigned char *buffer)
{

	glDeleteTextures(1, &id);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);

	glBindTexture(GL_TEXTURE_2D, 0);

	//~ std::cout << "__ setting texture data : " << _width << "/" << _height  << "\n";
}

void OpenGLTexture::bind(unsigned int slot)
{
	// glActiveTexture(GL_TEXTURE0 + slot);
	// glBindTexture(GL_TEXTURE_2D, id);
	glBindTextureUnit(slot, id);
}

// void OpenGLTexture::unbind(unsigned int slot)
// {
// 	glActiveTexture(GL_TEXTURE0 + slot);
// 	glBindTexture(GL_TEXTURE_2D, 0);
// }

OpenGLTexture::~OpenGLTexture()
{

	glDeleteTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, 0);
}
