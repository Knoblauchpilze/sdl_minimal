
# include "Content.hh"

namespace sdl {
  namespace minimal {

    Content::Content(const std::string& name,
                     const utils::Sizef& sizeHint,
                     const core::engine::Color& color):
      sdl::core::SdlWidget(name, sizeHint, nullptr, color)
    {
      // Empty implementation.
    }

  }
}
