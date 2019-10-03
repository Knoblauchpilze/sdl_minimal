#ifndef    CONTENT_HH
# define   CONTENT_HH

# include <maths_utils/Box.hh>
# include <sdl_core/SdlWidget.hh>

namespace sdl {
  namespace minimal {

    class Content: public sdl::core::SdlWidget {
      public:

        Content(const std::string& name,
                const utils::Sizef& sizeHint = utils::Sizef(),
                const core::engine::Color& color = core::engine::Color());

        ~Content() = default;
    };

  }
}

#endif    /* CONTENT_HH */
