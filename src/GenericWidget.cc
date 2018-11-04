
# include "GenericWidget.hh"

namespace sdl {
  namespace minimal {

    GenericWidget::GenericWidget(const std::string& name,
                                 const sdl::core::Boxf& area,
                                 const SDL_Color& backgroundColor):
      sdl::core::SdlWidget(name, area, nullptr, backgroundColor)
    {}

  }
}
