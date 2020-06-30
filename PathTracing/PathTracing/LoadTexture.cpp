#include "LoadTexture.h"
#include "FreeImage.h"


GLuint LoadTexture(const std::string& fname)
{
   GLuint tex_id;

   FIBITMAP* tempImg = FreeImage_Load(FreeImage_GetFileType(fname.c_str(), 0), fname.c_str());
   FIBITMAP* img = FreeImage_ConvertTo32Bits(tempImg);

   FreeImage_Unload(tempImg);

   GLuint w = FreeImage_GetWidth(img);
   GLuint h = FreeImage_GetHeight(img);
   GLuint scanW = FreeImage_GetPitch(img);

   GLubyte* byteImg = new GLubyte[h*scanW];
   FreeImage_ConvertToRawBits(byteImg, img, scanW, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);
   FreeImage_Unload(img);

   glGenTextures(1, &tex_id);
   glBindTexture(GL_TEXTURE_2D, tex_id);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, byteImg);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   delete byteImg;

   return tex_id;
}

GLuint LoadCube(const std::string& fname)
{

   GLuint tex_id;
   const std::string faces[6] = { "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" };

   glGenTextures(1, &tex_id);
   glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);
   glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   for (int i = 0; i<6; i++)
   {
      std::string cube_face = fname + "\\" + faces[i];
      FIBITMAP* tempImg = FreeImage_Load(FreeImage_GetFileType(cube_face.c_str(), 0), cube_face.c_str());
      FIBITMAP* img = FreeImage_ConvertTo32Bits(tempImg);

      FreeImage_Unload(tempImg);

      GLuint w = FreeImage_GetWidth(img);
      GLuint h = FreeImage_GetHeight(img);
      GLuint scanW = FreeImage_GetPitch(img);

      GLubyte* byteImg = new GLubyte[h*scanW];
      FreeImage_ConvertToRawBits(byteImg, img, scanW, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE); //last arg FALSE set origin of the texture to the lower left
      FreeImage_Unload(img);

      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, byteImg);

      delete byteImg;
   }
   glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
   glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
   return tex_id;
}