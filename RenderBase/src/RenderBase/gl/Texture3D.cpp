
#include <RenderBase/gl/Texture3D.h>

using namespace rb::gl;

Texture3D::Texture3D()
{
    glCreateTextures(GL_TEXTURE_3D, 1, &glId);
}

Texture3D::~Texture3D()
{
    glDeleteTextures(1, &glId);
}
