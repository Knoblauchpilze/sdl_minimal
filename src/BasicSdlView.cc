
# include "BasicSdlView.hh"

namespace sdl {
  namespace core {

    BasicSdlView::BasicSdlView(const std::string& title,
                               const std::string& icon,
                               const int& width,
                               const int& height,
                               const float& framerate):
      m_title(title),
      m_icon(),
      m_framerate(std::max(0.1f, framerate)),
      m_frameDuration(1000.0f / m_framerate),
      m_screen(nullptr)
    {
      createWindow(width, height);
      setIcon(icon);
    }

    void
    BasicSdlView::createWindow(const int& width, const int& height) {
      // Initialize sdl lib.
      initializeSdlLib();

      // Create the main renderer.
      m_screen = SDL_CreateWindow(
        getTitle().c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
      );
      if (m_screen == nullptr) {
        throw SdlException(std::string("Could not create main window \"") + getTitle() + "\" (err: \"" + SDL_GetError() + "\")");
      }
    }

  }
}
