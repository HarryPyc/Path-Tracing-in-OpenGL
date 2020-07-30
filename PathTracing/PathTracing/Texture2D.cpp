#include "Texture2D.h"
#include "LoadTexture.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
Texture2D::Texture2D(const std::string name, int w, int h, GLenum magFilter, GLenum minFilter, GLint internalFormat, GLint type, GLint wrap)
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, GL_RGBA, type, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    width = w;
    height = h;
    texture_name = name;
}
Texture2D::Texture2D(const std::string name, const std::string path)
{
    texture_id = LoadTexture(path.c_str());
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glBindTexture(GL_TEXTURE_2D, 0);
    texture_name = name;

}
void Texture2D::activate(GLuint program, GLuint textureLoc)
{
    glUseProgram(program);
    glActiveTexture(GL_TEXTURE0 + textureLoc);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    int tex_loc = glGetUniformLocation(program, texture_name.c_str());
    if (tex_loc != -1)
    {
        glUniform1i(tex_loc, textureLoc); // we bound our texture to texture unit 0
    }
}

void Texture2D::print(std::string name) {
    GLfloat* pixels = new GLfloat[width * height * 4];
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, pixels);
    //stbi_write_bmp(name.c_str(), width, height, 4, pixels);
    ofstream outFile(name);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for(int c = 0; c < 4; c++)
            outFile << *(pixels+4*(i*width+j)+c)<<" ";
        }
        outFile << "\n";
    }
    outFile.close();
    delete[] pixels;
}

void Texture2D::clear(glm::vec4 color) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glClearTexImage(texture_id, 0, GL_RGBA, GL_FLOAT, &color);
    glBindTexture(GL_TEXTURE_2D, 0);
}