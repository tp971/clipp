#ifndef CLIPP_CLI_H_INCLUDED
#define CLIPP_CLI_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <stdexcept>

namespace clipp
{
    class CLIException : public std::runtime_error
    {
    public:
        CLIException(std::string desc)
            :runtime_error(desc)
        {}
    };

    /** @brief Identifies a command line option */
    typedef int CLIOpt;
    
    /** @brief Identifies a non-option argument */
    const CLIOpt CLINonOpt = 0;

    /** @brief Represents a command line argument */
    struct CLIArg
    {
        /** @brief The corresponding command line option.
            It this is a command line option, its value is a CLIOpt returned by
            the corresponding CLIParser.addOpt. If this is a non-option argument,
            it is CLINonOpt.
        */
        CLIOpt opt;

        /** @brief String for non-option arguments */
        std::string str;

        /** @brief Short option (e.g. 'a' for -a) */
        char shortopt;

        /** @brief Long option (e.g. "all" for --all) */
        std::string longopt;

        /** @brief Number of parameters for option */
        int nparams;

        /** @brief Parameters for option */
        std::vector<std::string> params;

        CLIArg();
        CLIArg(std::string str);
        CLIArg(CLIOpt opt, char shortopt, std::string longopt, int nparams);
    };

    class CLIParser
    {
    private:
        CLIOpt opt_next;
        std::map<char, CLIArg> opts_short;
        std::map<std::string, CLIArg> opts_long;

    public:
        /** @brief Constructor */
        CLIParser();

        /** @brief Add an option with short and long option.
            @param shortopt Character for short option (e.g. 'a' for option -a)
                Does not add a short option if shortopt == 0
            @param longopt Character for long option (e.g. "all" for option --all)
                Does not add a long option if longopt == ""
            @param nparams Number of expected parameters for that option
            @returns a unique identifier for the given option
        */
        CLIOpt addOpt(char shortopt, std::string longopt, int nparams = 0);

        /** @brief Add a short option.
            @param shortopt Character for short option (e.g. 'a' for option -a)
                Does not add a short option if shortopt == 0
            @param nparams Number of expected parameters for that option
            @returns a unique identifier for the given option
        */
        CLIOpt addOpt(char shortopt, int nparams = 0);

        /** @brief Add a long option.
            @param longopt Character for long option (e.g. "all" for option --all)
                Does not add a long option if longopt == ""
            @param nparams Number of expected parameters for that option
            @returns a unique identifier for the given option
        */
        CLIOpt addOpt(std::string longopt, int nparams = 0);

        /** @brief Parses command line options.
            @param argc argc of main function
            @param argc argv of main function
            @param offset first element of argv to parse (default: 1)
            @throws CLIException if there is an unknown option or missing parameter.
        */
        std::vector<CLIArg> parse(int argc, char** argv, int offset = 1);
    };
}

#endif //CLIPP_CLI_H_INCLUDED
