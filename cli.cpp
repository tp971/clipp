#include "cli.h"

using namespace std;
using namespace clipp;

CLIArg::CLIArg()
{}

CLIArg::CLIArg(std::string str)
    :opt(CLINonOpt), str(str)
{}

CLIArg::CLIArg(CLIOpt opt, char shortopt, std::string longopt, int nparams)
    :opt(opt), longopt(longopt), shortopt(shortopt), nparams(nparams)
{}

CLIParser::CLIParser()
    :opt_next(1)
{}

CLIOpt CLIParser::addOpt(char shortopt, string longopt, int nparams)
{
    CLIArg arg(opt_next++, shortopt, longopt, nparams);
    if(shortopt != 0)
    {
        if(opts_short.count(shortopt))
            throw runtime_error("short option already exists");
        opts_short[shortopt] = arg;
    }
    if(longopt != "")
    {
        if(opts_long.count(longopt))
            throw runtime_error("long option already exists");
        opts_long[longopt] = arg;
    }
    return arg.opt;
}

CLIOpt CLIParser::addOpt(char shortopt, int nparams)
{ return addOpt(shortopt, "", nparams); }

CLIOpt CLIParser::addOpt(string longopt, int nparams)
{ return addOpt(0, longopt, nparams); }

vector<CLIArg> CLIParser::parse(int argc, char** argv, int offset)
{
    vector<CLIArg> res;
    for(int i = offset; i < argc; i++)
    {
        string next = argv[i];
        if(next == "--")
            for(i++; i < argc; i++)
                res.emplace_back(string(argv[i]));
        else if(next == "-")
            res.emplace_back(next);
        else if(next.size() >= 2 && next.substr(0, 2) == "--")
        {
            if(!opts_long.count(next.substr(2)))
                throw CLIException("unknown option: " + next);
            CLIArg opt = opts_long[next.substr(2)];
            for(int j = 0; j < opt.nparams; j++)
                if(++i < argc)
                    opt.params.push_back(argv[i]);
                else
                    throw CLIException("missing argument to option " + next);
            res.push_back(opt);
        }
        else if(next.size() >= 1 && next[0] == '-')
        {
            for(size_t j = 1; j < next.size(); j++)
            {
                char next2 = next[j];
                if(!opts_short.count(next2))
                    throw CLIException(string("unknown option: -") + next2);
                CLIArg opt = opts_short[next2];
                if(opt.nparams)
                {
                    if(++j < next.size())
                    {
                        opt.params.push_back(next.substr(j));
                        j = next.size();
                    }
                    for(int k = opt.params.size(); k < opt.nparams; k++)
                        if(++i < argc)
                            opt.params.push_back(argv[i]);
                        else
                            throw CLIException(string("missing argument to option -") + next2);
                }
                res.push_back(opt);
            }
        }
        else
            res.emplace_back(next);
    }
    return res;
}
