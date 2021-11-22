#define NO_DEBUG_LOG

#include <RenderBase/gl/Shader.h>

#include <RenderBase/tools/util.h>

#include <RenderBase/logging.h>
#include <RenderBase/asserts.h>

#include <fstream>
#include <iterator>

using namespace std;
using namespace rb::gl;

string resolveSourceCode(string source, const vector<string>& defines) {
    stringstream sourceCode;
    ifstream stream(source);
    if (stream.good()) {
        string line;
        while (getline(stream, line)) {
            sourceCode << line << "\n";
            if (line.find("#version") != string::npos) {
                sourceCode << rb::implode(
                    rb::map(defines, [](string s) {
                        return "#define " + s + "\n";
                    })
                ) << "\n";
                break;
            }
        }
        sourceCode << string(
            std::istream_iterator<char>(stream >> std::noskipws),
            std::istream_iterator<char>()
        );
    } else {
        sourceCode << source;
    }
    RB_DEBUG("final source:\n" << sourceCode.str());
    return sourceCode.str();
}

Shader::Shader(GLenum type, std::string source, const vector<string>& defines)
{
    this->type = type;
    source = resolveSourceCode(source, defines);

    // Compile
    glId = glCreateShader(this->type);
    char const* rawSource = source.c_str();
    glShaderSource(glId, 1, &rawSource, nullptr);
    glCompileShader(glId);
    
    // assert failed compilation
    #ifndef NO_ASSERT
        GLint status;
        glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            GLint errLen = 0;
            glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &errLen);
            auto errorMessage = std::string(" ", errLen);
            glGetShaderInfoLog(glId, errorMessage.size(), &errLen, (char*)errorMessage.data());
            RB_ASSERT_MSG(false, "Shader compilation error:\n" + errorMessage);
        }
    #endif
    
    RB_INFO("Shader " << glId << " created.");
}

Shader::~Shader()
{
    glDeleteShader(glId);
    RB_INFO("Shader " << glId << " deleted.");
}
