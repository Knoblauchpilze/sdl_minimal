#ifndef    GENERICWIDGET_HH
# define   GENERICWIDGET_HH

# include <memory>
# include <sdl_core/SdlWidget.hh>

namespace sdl {
  namespace minimal {

    class GenericWidget: public sdl::core::SdlWidget {
      public:

        GenericWidget(const std::string& name,
                      const sdl::core::Boxf& area,
                      const SDL_Color& backgroundColor = SDL_Color{0, 0, 0, SDL_ALPHA_OPAQUE});

        ~GenericWidget() = default;
    };

    using GenericWidgetShPtr = std::shared_ptr<GenericWidget>;

  }
}

#endif    /* GENERICWIDGET_HH */
