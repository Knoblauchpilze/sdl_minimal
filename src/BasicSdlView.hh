#ifndef    BASICSDLVIEW_HH
# define   BASICSDLVIEW_HH

# include <memory>
# include <vector>
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {

    class BasicSdlView {
      public:

        explicit
        BasicSdlView(const std::string& title,
                     const std::string& icon,
                     const int& width = 640,
                     const int& height = 480,
                     const float& framerate = 60.0f);

        virtual ~BasicSdlView();

        int
        getWidth() const;

        int
        getHeight() const;

        const std::string&
        getTitle() const noexcept;

        void
        setIcon(const std::string& icon);

      private:

        void
        initializeSdlLib() const;

        void
        createWindow(const int& width, const int& height);

      private:

        std::string m_title;
        std::string m_icon;
        float m_framerate;
        float m_frameDuration;
        SDL_Window* m_screen;
    };

    using BasicSdlViewShPtr = std::shared_ptr<BasicSdlView>;
  }
}

#include "BasicSdlView.hxx"

#endif    /* BASICSDLVIEW_HH */
