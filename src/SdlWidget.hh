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
                  SdlWidget* parent = nullptr,
                  const SDL_Color& backgroundColor = SDL_Color{0, 0, 0, SDL_ALPHA_OPAQUE});

        virtual ~SdlWidget();

        const std::string&
        getName() const noexcept;

        const Boxf&
        getRenderingArea() const noexcept;

        void
        setRenderingArea(const Boxf& area) noexcept;

        void
        setBackgroundColor(const SDL_Color& color) noexcept;

        virtual SDL_Texture*
        draw(SDL_Renderer* renderer);

      protected:

        // We assume that this widget is already locked when we enter this method.
        virtual bool
        hasChanged() const noexcept;

        virtual SDL_Texture*
        createContentPrivate(SDL_Renderer* renderer) const;

      private:

        void
        clearTexture();

      private:

        std::string m_name;

        SdlWidget* m_parent;
        Boxf m_area;
        SDL_Color m_background;
        mutable std::mutex m_propsLocker;

        bool m_dirty;
        SDL_Texture* m_content;
        std::mutex m_drawingLocker;
    };

  }
}

# include "SdlWidget.hxx"

#endif    /* SDLWIDGET_HH */
