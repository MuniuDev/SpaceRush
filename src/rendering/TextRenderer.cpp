#include "rendering/TextRenderer.hpp"
#include "rendering/Quad.hpp"

TextRenderer::TextRenderer() : m_font(nullptr) {}
TextRenderer::~TextRenderer() {}

void TextRenderer::InitRenderer(int fontSize) {
  m_font = TTF_OpenFont("res/OpenSans-Regular.ttf", fontSize);
  if (m_font == nullptr) {
    LOGE("Failed to load font! SDL_ttf Error: {}", TTF_GetError());
  }

  m_shader = std::make_shared<ShaderProgram>("res/text.vsh", "res/text.fsh");
  m_shader->RegisterUniform("u_transform");
  m_shader->RegisterUniform("u_uvScale");
}

SDL_Color toSDLColor(const glm::vec3& color) {
  SDL_Color sdlColor;
  sdlColor.r = static_cast<int>(glm::clamp(color.x, 0.f, 1.f) * 255);
  sdlColor.g = static_cast<int>(glm::clamp(color.y, 0.f, 1.f) * 255);
  sdlColor.b = static_cast<int>(glm::clamp(color.z, 0.f, 1.f) * 255);
  sdlColor.a = 255;
  return sdlColor;
}

void TextRenderer::RenderText(const glm::vec3& pos, float size,
                              const glm::vec3& color, std::string text) {
  if (!m_font) return;
  SDL_Color sdlColor = toSDLColor(color);

  SDL_Surface* originalSurface =
      TTF_RenderText_Blended(m_font, text.c_str(), sdlColor);

  int Mode = GL_RGB;
  if (originalSurface->format->BytesPerPixel == 4) {
    Mode = GL_RGBA;
  }

  int w = pow(2, ceil(log(originalSurface->w) / log(2)));
  int h = pow(2, ceil(log(originalSurface->h) / log(2)));

  SDL_Surface* textSurface = SDL_CreateRGBSurface(
      0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_BlitSurface(originalSurface, 0, textSurface, 0);

  GLuint textureID = 0;

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexImage2D(GL_TEXTURE_2D, 0, Mode, textSurface->w, textSurface->h, 0, Mode,
               GL_UNSIGNED_BYTE, textSurface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // draw
  glm::mat4 scale = glm::scale(
      glm::mat4(1.0f),
      glm::vec3(size * (float)originalSurface->w / (float)originalSurface->h,
                size, 1.f));
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), pos);
  glm::mat4 t = trans * scale;

  m_shader->BindProgram();
  m_shader->SetUniform("u_transform", t);
  m_shader->SetUniform("u_uvScale",
                       glm::vec2((float)originalSurface->w / (float)w,
                                 (float)originalSurface->h / (float)h));

  static Quad q;
  q.Render();

  glDeleteTextures(1, &TextureID);
  SDL_FreeSurface(originalSurface);
  SDL_FreeSurface(textSurface);
}
