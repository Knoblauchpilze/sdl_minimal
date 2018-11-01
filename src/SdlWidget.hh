#ifndef    SDLWIDGET_HH
# define   SDLWIDGET_HH

# include <mutex>
# include "Box.hh"
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {

    using Boxf = sdl::utils::Box<float>;

    class SdlWidget {
      public:

        SdlWidget(const std::string& name,
                  const Boxf& area,
                  const bool transparent = true,
                  SdlWidget* parent = nullptr);

        virtual ~SdlWidget();

        const std::string&
        getName() const noexcept;

        const Boxf&
        getRenderingArea() const noexcept;

        void
        setRenderingArea(const Boxf& area) noexcept;

        virtual SDL_Texture*
        draw() = 0;

      private:

        std::string m_name;

        SdlWidget* m_parent;
        Boxf m_area;
        mutable std::mutex m_drawingLocker;
    };

  }
}

# include "SdlWidget.hxx"

#endif    /* SDLWIDGET_HH */
