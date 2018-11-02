
# include "SdlWidget.hh"

namespace sdl {
  namespace core {

    SdlWidget::SdlWidget(const std::string& name,
                         const Boxf& area,
                         SdlWidget* parent,
                         const SDL_Color& color):
      m_name(name),
      m_parent(parent),
      m_area(area),
      m_background(color),
      m_propsLocker(),

      m_dirty(true),
      m_content(nullptr),
      m_drawingLocker()
    {}

    SDL_Texture*
    SdlWidget::draw(SDL_Renderer* renderer) {
      std::lock_guard<std::mutex> guard(m_drawingLocker);

      // Repaint if needed.
      if (hasChanged()) {
        clearTexture();


      }

      // Return the built-in texture.
      return m_content;
    }

  }
}
