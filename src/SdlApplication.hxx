#ifndef    SDLAPPLICATION_HXX
# define   SDLAPPLICATION_HXX

# include "SdlException.hh"
# include "SdlApplication.hh"

# include <iostream>

namespace sdl {
  namespace core {

    inline
    SdlApplication::~SdlApplication() {
      if (m_eventsHandler.isRunning()) {
        m_eventsHandler.stop();
      }

      if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
      }
    }

    inline
    int
    SdlApplication::getWidth() const {
      if (m_window == nullptr) {
        throw SdlException(std::string("Cannot retrieve height for invalid sdl window \"") + getTitle() + "\"");
      }

      int width = 0;
      SDL_GetWindowSize(m_window, &width, nullptr);
      return width;
    }

    inline
    int
    SdlApplication::getHeight() const {
      if (m_window == nullptr) {
        throw SdlException(std::string("Cannot retrieve height for invalid sdl window \"") + getTitle() + "\"");
      }

      int height = 0;
      SDL_GetWindowSize(m_window, nullptr, &height);
      return height;
    }

    inline
    const std::string&
    SdlApplication::getTitle() const noexcept {
      return m_title;
    }

    inline
    void
    SdlApplication::setIcon(const std::string& icon) {
      if (m_window == nullptr) {
        throw SdlException(std::string("Could not set icon for invalid sdl window"));
      }

      // Load this icon.
      SDL_Surface* iconAsSurface = SDL_LoadBMP(icon.c_str());
      if (iconAsSurface == nullptr) {
        throw SdlException(std::string("Could not load icon \"") + icon + "\" (err: \"" + SDL_GetError() + "\")");
      }

      SDL_SetWindowIcon(m_window, iconAsSurface);

      SDL_FreeSurface(iconAsSurface);
    }

    inline
    void
    SdlApplication::run() {
      // Start event handling.
      m_eventsHandler.run();

      // Start rendering.
      performRendering();
    }

    inline
    void
    SdlApplication::initializeSdlLib() const {
      if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        return;
      }

      int initStatus = SDL_Init(SDL_INIT_VIDEO);
      if (initStatus != 0) {
        throw SdlException(std::string("Could not initialize SDL library (err: \"") + SDL_GetError() + "\")");
      }
    }

    inline
    void
    SdlApplication::lock() {
      m_locker.lock();
    }

    inline
    void
    SdlApplication::unlock() {
      m_locker.unlock();
    }

    inline
    void
    SdlApplication::render() {
      const unsigned int startingRenderingTime = SDL_GetTicks();
      std::cout << "[APP] Performing rendering" << std::endl;

      SDL_RenderClear(m_renderer);
      SDL_RenderPresent(m_renderer);

      const unsigned int renderingDuration = SDL_GetTicks() - startingRenderingTime;

      if (renderingDuration > m_frameDuration) {
        std::cerr << "Frame took " << renderingDuration << "ms which is greater than the " << m_frameDuration << "ms authorized to maintain " << m_framerate << "fps" << std::endl;
      }
      else {
        const unsigned int remainingDuration = m_frameDuration - renderingDuration;
        if (remainingDuration > 3u) {
          SDL_Delay(remainingDuration);
        }
      }
    }

  }
}

#endif    /* SDLAPPLICATION_HXX */
