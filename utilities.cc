#include <istream>
#include <string>
#include "Array.h"

//Divide una linea csv con delimitador c en un arreglo de strings
void _split(const string& s, const char c , Array<string>& v) 
{
    int i = 0;
    int j = s.find(c);

    if(j == -1)
      v.push_back(s);
    while (j >= 0) 
    {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j < 0) 
        {
          v.push_back(s.substr(i, s.length()));
      }
    }
}

//Elimina espacios y tabs desde el extremo derecho
void _right_trim(string & str)
{
  int len = str.length()-1;
  while(len >= 0 && (str[len] == ' ' || str[len] == '\t'))
  {
        str.resize(len);
        len = str.length()-1;
  }
}

//Se fija si la string sólo tiene espacios y tabs
bool _all_blanks_and_tabs(const string & str)
{
  int len = str.length();

  for(int i = 0; i < len; i++)
      if(str[i] != ' ' && str[i] != '\t')
        return false;
  return true;
}