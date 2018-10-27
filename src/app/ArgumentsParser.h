#ifndef ARGUMENTSPARSER_H
#define ARGUMENTSPARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <ostream>

namespace ogame {
  namespace app{

    class ArgumentsParser
    {
      public:

        ArgumentsParser(const std::string& appName, const int& argumentsCount, char* arguments[]);

        virtual ~ArgumentsParser();

        void addOption(const std::string& name, const bool mandatory, const bool valued);

        void parseArguments();

        void displayUsage(std::ostream& stream) const;

        bool hasOption(const std::string& name) const;

        bool isOptionValued(const std::string& name);

        const std::string& getOptionValue(const std::string& name) const;

      protected:

        void copyArgumentsToLocal(const int& argumentsCount, char* arguments[]);

        bool checkMandatory() const;

      private:

        std::string m_appName;
        std::vector<std::string> m_arguments;
        std::unordered_map<std::string, bool> m_mandatoryArguments;
        std::unordered_map<std::string, bool> m_optionalArguments;

        std::unordered_map<std::string, std::string> m_options;
    };

  }
}

#endif // ARGUMENTSPARSER_H
