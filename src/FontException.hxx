#ifndef    FONTEXCEPTION_HXX
# define   FONTEXCEPTION_HXX

# include "FontException.hh"

namespace sdl {
  namespace core {

    inline
    FontException::FontException(const std::string& cause):
      SdlException(cause)
    {}

  }
}

#endif    /* FONTEXCEPTION_HXX */
