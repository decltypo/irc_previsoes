#include "aux.hpp"

std::vector<std::string> split(const std::string& str, const std::string& delimiter)
{
  size_t pos = 0, lpos=0;

  std::string token;
  std::vector<std::string> ret;

  if((pos = str.find(delimiter,lpos))!=std::string::npos)
  {
    do
    {
      ret.push_back(str.substr(lpos,pos-lpos));
      lpos=pos+delimiter.length();
    }
    while ((pos = str.find(delimiter,lpos)) != std::string::npos );
  }

  ret.push_back(str.substr(lpos,str.length()-lpos));

  return ret;
}

std::string lcase(const std::string &s)
{
  std::string ret=s;
  std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
  return ret;
}
