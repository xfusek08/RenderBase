
#include <RenderBase/gl/Texture3D.h>

using namespace rb::gl;

Texture3D::Texture3D(uint32 width, uint32 height, uint32 depth) : width(width), height(height), depth(depth)
{
    glCreateTextures(GL_TEXTURE_3D, 1, &glId);
    
    //nastaveni parametru textury
    
    // default filtering
    glTextureParameteri(glId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(glId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // default wrapping
    glTextureParameteri(glId, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTextureParameteri(glId, GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTextureParameteri(glId, GL_TEXTURE_WRAP_R, GL_NEAREST);
}

Texture3D::~Texture3D()
{
    glDeleteTextures(1, &glId);
}

void Texture3D::loadData(GLenum format, GLenum type, void *data)
{
    glBindTexture(GL_TEXTURE_3D, glId);
    // glTexImage3D(GL_TEXTURE_3D, 0, format, width, height, depth, 0, type, data);
}
