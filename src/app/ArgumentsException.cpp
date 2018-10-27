
#include "ArgumentsException.h"

namespace ogame {
  namespace app {

    ArgumentsException::ArgumentsException(const std::string& cause):
    std::exception(),
      m_cause(cause)
    {
      //ctor
    }

    ArgumentsException::~ArgumentsException()
    {
      //dtor
    }

    const char* ArgumentsException::what() const throw() {
      return m_cause.c_str();
    }

  }
}
