#include "rendering/TextRenderer.hpp"
#include "rendering/Quad.hpp"

TextRenderer::TextRenderer() : m_font(nullptr) {}
TextRenderer::~TextRenderer() {
  if (m_font) TTF_CloseFont(m_font);
}

void TextRenderer::InitRenderer(int fontSize) {
  m_font = TTF_OpenFont("res/OpenSans-Regular.ttf", fontSize);
  if (m_font == nullptr) {
    LOGE("Failed to load font! SDL_ttf Error: {}", TTF_GetError());
    return;
  }

  m_shader = std::make_shared<ShaderProgram>("res/text.vsh", "res/text.fsh");
  m_shader->RegisterUniform("u_transform");
  m_shader->RegisterUniform("u_uvScale");
}

void TextRenderer::RenderText(const glm::vec3& pos, float size,
                              const glm::vec3& color, std::string text) {
  if (!m_font) {
    LOGE("Cannot draw. Font is NULL!");
    return;
  }

  // convert color to SDL_Color
  SDL_Color sdlColor;
  sdlColor.r = static_cast<int>(glm::clamp(color.z, 0.f, 1.f) * 255);
  sdlColor.g = static_cast<int>(glm::clamp(color.y, 0.f, 1.f) * 255);
  sdlColor.b = static_cast<int>(glm::clamp(color.x, 0.f, 1.f) * 255);
  sdlColor.a = 255;

  // generate font surface
  SDL_Surface* origSurf =
      TTF_RenderText_Blended(m_font, text.c_str(), sdlColor);

  // find neares power of 2 from width and height
  int w = pow(2, ceil(log(origSurf->w) / log(2)));
  int h = pow(2, ceil(log(origSurf->h) / log(2)));

  // create properely sized surface, and copy data to it
  SDL_Surface* textSurf = SDL_CreateRGBSurface(
      0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_BlitSurface(origSurf, 0, textSurf, 0);

  // Set texture mode
  int Mode = GL_RGB;
  if (origSurf->format->BytesPerPixel == 4) {
    Mode = GL_RGBA;
  }

  // create and populate OpenGL texture
  GLuint textureID = 0;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, Mode, textSurf->w, textSurf->h, 0, Mode,
               GL_UNSIGNED_BYTE, textSurf->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // draw the texture on screen
  glm::mat4 scale = glm::scale(
      glm::mat4(1.0f), glm::vec3(size * static_cast<float>(origSurf->w) /
                                     static_cast<float>(origSurf->h),
                                 size, 1.f));
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), pos);
  glm::mat4 t = trans * scale;

  m_shader->BindProgram();
  m_shader->SetUniform("u_transform", t);
  m_shader->SetUniform(
      "u_uvScale",
      glm::vec2(static_cast<float>(origSurf->w) / static_cast<float>(w),
                static_cast<float>(origSurf->h) / static_cast<float>(h)));
  static Quad q;
  q.Render();

  // free the resources
  glDeleteTextures(1, &textureID);
  SDL_FreeSurface(origSurf);
  SDL_FreeSurface(textSurf);
}
