#pragma once

#include "Common.hpp"
#include "rendering/ShaderProgram.hpp"

class TextRenderer {
 public:
  TextRenderer();
  virtual ~TextRenderer();

  virtual void InitRenderer(int fontSize);
  virtual void RenderText(const glm::vec3& pos, float size,
                          const glm::vec3& color, std::string text);

 protected:
  std::shared_ptr<ShaderProgram> m_shader;

  TTF_Font* m_font;
};
