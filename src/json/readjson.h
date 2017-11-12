#ifndef READFILE_H
#define READFILE_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "json.h"

using namespace std;
using json = nlohmann::json;

json readFile(const string &fileName);

#endif
