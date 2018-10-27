#ifndef ARGUMENTSEXCEPTION_H
#define ARGUMENTSEXCEPTION_H

#include <stdexcept>
#include <string>

namespace ogame {
  namespace app {

    class ArgumentsException: public std::exception
    {
      public:

        ArgumentsException(const std::string& cause);

        virtual ~ArgumentsException();

        const char* what() const throw() override;

      protected:

      private:

        std::string m_cause;
    };

  }
}

#endif // ARGUMENTSEXCEPTION_H
