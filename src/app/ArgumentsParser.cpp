
#include <algorithm>

#include "ArgumentsParser.h"
#include "ArgumentsException.h"

namespace ogame {
  namespace app {

    ArgumentsParser::ArgumentsParser(const std::string& appName, const int& argumentsCount, char* arguments[]):
      m_appName(appName),
      m_arguments(),
      m_mandatoryArguments(),
      m_optionalArguments(),
      m_options()
    {
      copyArgumentsToLocal(argumentsCount, arguments);
    }

    ArgumentsParser::~ArgumentsParser()
    {
      //dtor
    }

    void ArgumentsParser::addOption(const std::string& name, const bool mandatory, const bool valued) {
      if (name.empty()) {
        throw ArgumentsException(std::string("Cannot add invalid unnamed option to parser"));
      }

      const std::string optionName = (
        name[0] == '-' ? name :
        (name.length() < 2 ? "-" + name :
                             "--" + name
        )
      );

      if (mandatory) {
        m_mandatoryArguments[optionName] = valued;
      }
      else {
        m_optionalArguments[optionName] = valued;
      }
    }

    void ArgumentsParser::parseArguments() {
      const bool allSet = checkMandatory();
      if (!allSet) {
        throw ArgumentsException("Missing mandatory option in provided arguments");
      }

      unsigned indexArgument = 0u;
      while (indexArgument < m_arguments.size()) {
        std::unordered_map<std::string, bool>::const_iterator mandatory = m_mandatoryArguments.find(m_arguments[indexArgument]);
        if (mandatory != m_mandatoryArguments.cend()) {
          if (mandatory->second) {
            if (indexArgument >= m_arguments.size() - 1) {
              throw ArgumentsException("Missing value for mandatory parameter " + mandatory->first);
            }
            else {
              m_options[mandatory->first] = m_arguments[indexArgument + 1];
              ++indexArgument;
            }
          }
          else {
            m_options[mandatory->first] = "true";
          }
        }
        std::unordered_map<std::string, bool>::const_iterator optional = m_optionalArguments.find(m_arguments[indexArgument]);
        if (optional != m_optionalArguments.cend()) {
          if (optional->second) {
            if (indexArgument >= m_arguments.size() - 1) {
              throw ArgumentsException("Missing value for optional parameter " + optional->first);
            }
            else {
              m_options[optional->first] = m_arguments[indexArgument + 1];
              ++indexArgument;
            }
          }
          else {
            m_options[optional->first] = "true";
          }
        }
        ++indexArgument;
      }

    }

    void ArgumentsParser::displayUsage(std::ostream& stream) const{
      stream << "Usage:" << std::endl << m_appName << " ";

      int count = m_mandatoryArguments.size();
      int value = 0;
      std::for_each(m_mandatoryArguments.cbegin(), m_mandatoryArguments.cend(),
        [this, count, &value, &stream](const std::pair<std::string, bool>& option) {
          stream << option.first;
          if (option.second) {
            stream << " value";
          }
          ++value;
          if (value < count || m_optionalArguments.size() > 0) {
            stream << " ";
          }
        }
      );

      count = m_optionalArguments.size();
      value = 0;
      std::for_each(m_optionalArguments.cbegin(), m_optionalArguments.cend(),
        [this, count, &value, &stream](const std::pair<std::string, bool>& option) {
          stream << "[" << option.first;
          if (option.second) {
            stream << " value";
          }
          stream << "]";
          ++value;
          if (value < count) {
            stream << " ";
          }
        }
      );
      stream << std::endl;
    }

    bool ArgumentsParser::hasOption(const std::string& name) const {
      return m_options.find(name) != m_options.cend();
    }

    bool ArgumentsParser::isOptionValued(const std::string& name) {
      std::unordered_map<std::string, bool>::const_iterator option = m_mandatoryArguments.find(name);
      if (option != m_mandatoryArguments.cend()) {
        return option->second;
      }
      option = m_optionalArguments.find(name);
      if (option != m_optionalArguments.cend()) {
        return option->second;
      }

      throw ArgumentsException("Cannot return valued status for unknown option \"" + name + "\"");
    }

    const std::string& ArgumentsParser::getOptionValue(const std::string& name) const {
      std::unordered_map<std::string, std::string>::const_iterator option = m_options.find(name);
      if (option == m_options.cend()) {
        throw ArgumentsException("Cannot retrieve value for unfilled option \"" + name + "\"");
      }
      return option->second;
    }

    void ArgumentsParser::copyArgumentsToLocal(const int& argumentsCount, char* arguments[]) {
      for (int indexArgument = 0 ; indexArgument < argumentsCount ; ++indexArgument) {
        m_arguments.push_back(arguments[indexArgument]);
      }
    }

    bool ArgumentsParser::checkMandatory() const {
      bool valid = true;
      std::for_each(m_mandatoryArguments.cbegin(), m_mandatoryArguments.cend(),
        [this, &valid](const std::pair<std::string, bool>& option) {
          std::vector<std::string>::const_iterator filledOption = m_arguments.cbegin();
          while (filledOption != m_arguments.cend() && *filledOption != option.first) {
            ++filledOption;
          }

          if (filledOption == m_arguments.cend()) {
            valid = false;
          }
        }
      );
      return valid;
    }

  }
}
