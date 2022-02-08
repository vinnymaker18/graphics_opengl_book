#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string readShaderSource(string filePath)
{
  ifstream fin(filePath);
  ostringstream out;
  while (!fin.eof()) {
    string line;
    getline(fin, line);
    out << line << endl;
  }

  return out.str();
}
