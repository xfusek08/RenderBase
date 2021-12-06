
#include <RenderBase/gl/Texture3D.h>
#include <RenderBase/logging.h>

using namespace rb::gl;

Texture3D::Texture3D()
{
    glCreateTextures(GL_TEXTURE_3D, 1, &glId);
    RB_INFO("Texture3D " << glId << " created.");
}

Texture3D::~Texture3D()
{
    glDeleteTextures(1, &glId);
    RB_INFO("Texture3D " << glId << " deleted.");
}
