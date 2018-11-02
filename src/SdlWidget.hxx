#ifndef    SDLWIDGET_HXX
# define   SDLWIDGET_HXX

# include "SdlWidget.hh"
# include "SdlException.hh"

namespace sdl {
  namespace core {

    inline
    SdlWidget::~SdlWidget() {
      clearTexture();
    }

    inline
    const std::string&
    SdlWidget::getName() const noexcept {
      return m_name;
    }

    inline
    const Boxf&
    SdlWidget::getRenderingArea() const noexcept {
      std::lock_guard<std::mutex> guard(m_propsLocker);
      return m_area;
    }

    inline
    void
    SdlWidget::setRenderingArea(const Boxf& area) noexcept {
      std::lock_guard<std::mutex> guard(m_propsLocker);
      m_area = area;
    }

    inline
    void
    SdlWidget::setBackgroundColor(const SDL_Color& color) noexcept {
      std::lock_guard<std::mutex> guard(m_propsLocker);
      m_background = color;
    }

    inline
    bool
    SdlWidget::hasChanged() const noexcept {
      return m_dirty;
    }

    inline
    void
    SdlWidget::clearTexture() {
      std::lock_guard<std::mutex> guard(m_drawingLocker);
      if (m_content != nullptr) {
        SDL_DestroyTexture(m_content);
      }
    }

    inline
    SDL_Texture*
    SdlWidget::createContentPrivate(SDL_Renderer* renderer) const {
      const SDL_Rect areaAsRect = m_area.toSDLRect();

      SDL_Texture* content = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        areaAsRect.w,
        areaAsRect.h
      );

      if (content == nullptr) {
        throw SdlException(std::string("Could not create content for widget \"") + getName() + "\" (err: \"" + SDL_GetError() + "\")");
      }

      SDL_SetRenderTarget(renderer, content);
      SDL_SetRenderDrawColor(renderer, m_background.r, m_background.g, m_background.b, m_background.a);
      SDL_RenderClear(renderer);
    }

  }
}

#endif    /* SDLWIDGET_HXX */
