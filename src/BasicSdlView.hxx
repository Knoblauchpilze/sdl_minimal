#ifndef    BASICSDLVIEW_HXX
# define   BASICSDLVIEW_HXX

# include "SdlException.hh"
# include "BasicSdlView.hh"

namespace sdl {
  namespace core {

    inline
    BasicSdlView::~BasicSdlView() {
      if (m_screen != nullptr) {
        SDL_DestroyWindow(m_screen);
      }
    }

    inline
    int
    BasicSdlView::getWidth() const {
      if (m_screen == nullptr) {
        throw SdlException(std::string("Cannot retrieve height for invalid sdl window \"") + getTitle() + "\"");
      }

      int width = 0;
      SDL_GetWindowSize(m_screen, &width, nullptr);
      return width;
    }

    inline
    int
    BasicSdlView::getHeight() const {
      if (m_screen == nullptr) {
        throw SdlException(std::string("Cannot retrieve height for invalid sdl window \"") + getTitle() + "\"");
      }

      int height = 0;
      SDL_GetWindowSize(m_screen, nullptr, &height);
      return height;
    }

    inline
    const std::string&
    BasicSdlView::getTitle() const noexcept {
      return m_title;
    }

    inline
    void
    BasicSdlView::setIcon(const std::string& icon) {
      if (m_screen == nullptr) {
        throw SdlException(std::string("Could not set icon for invalid sdl window"));
      }

      // Load this icon.
      SDL_Surface* iconAsSurface = SDL_LoadBMP(icon.c_str());
      if (iconAsSurface == nullptr) {
        throw SdlException(std::string("Could not load icon \"") + icon + "\" (err: \"" + SDL_GetError() + "\")");
      }

      SDL_SetWindowIcon(m_screen, iconAsSurface);

      SDL_FreeSurface(iconAsSurface);
    }

    inline
    void
    BasicSdlView::initializeSdlLib() const {
      if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        return;
      }

      int initStatus = SDL_Init(SDL_INIT_VIDEO);
      if (initStatus == 0) {
        throw SdlException(std::string("Could not initialize SDL library (err: \"") + SDL_GetError() + "\")");
      }
    }

  }
}

#endif    /* BASICSDLVIEW_HH */
