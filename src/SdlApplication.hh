#ifndef    SDLAPPLICATION_HH
# define   SDLAPPLICATION_HH

# include <memory>
# include <vector>
# include <mutex>
# include <SDL2/SDL.h>
# include "SdlEventHandler.hh"

namespace sdl {
  namespace core {

    class SdlApplication {
      public:

        explicit
        SdlApplication(const std::string& title,
                     const std::string& icon,
                     const int& width = 640,
                     const int& height = 480,
                     const float& framerate = 60.0f,
                     const float& eventFramerate = 30.0f);

        virtual ~SdlApplication();

        int
        getWidth() const;

        int
        getHeight() const;

        const std::string&
        getTitle() const noexcept;

        void
        setIcon(const std::string& icon);

        void
        run();

      private:

        void
        initializeSdlLib() const;

        void
        createWindow(const int& width, const int& height);

        void
        lock();

        void
        unlock();

        void
        performRendering();

        void
        render();

      private:

        std::string m_title;
        std::string m_icon;
        float m_framerate;
        float m_frameDuration;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SdlEventHandler m_eventsHandler;

        bool m_renderingRunning;
        std::mutex m_locker;
    };

    using BasicSdlWindowShPtr = std::shared_ptr<SdlApplication>;
  }
}

#include "SdlApplication.hxx"

#endif    /* SDLAPPLICATION_HH */
