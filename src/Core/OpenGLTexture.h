#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "pch.h"

class OpenGLTexture
{
public:
	OpenGLTexture();

	virtual ~OpenGLTexture();
	void load(std::string path);
	void setData(int width, int height, unsigned char *buffer);

	unsigned int getID() { return id; };
	int getWidth() { return width; };
	int getHeight() { return height; };
	int getBPP() { return bpp; };
	void bind(unsigned int slot);
	// virtual void unbind(unsigned int slot) override;

private:
	unsigned int id;
	int width, height, bpp;
};

#endif /* OPENGL_TEXTURE_H */
