#include "readjson.h"

json readFile(const string &fileName)
{

  ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

  ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, ios::beg);

  vector<char> bytes(fileSize);
  ifs.read(&bytes[0], fileSize);

  return json::parse(string(&bytes[0], fileSize));

}
