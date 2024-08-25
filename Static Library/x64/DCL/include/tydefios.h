#pragma once
#include <iostream>
#include <fstream>
//--------------------
#include "dcl_defines.h"

DCL_BEGIN

typedef std::ostream ostream;
typedef std::istream istream;

typedef std::ifstream ifstream;
typedef std::ofstream ofstream;

typedef std::fstream fstream;
typedef std::stringstream stringstream;

typedef std::ios ios;

static ostream& cout = std::cout;
static istream& cin = std::cin;

DCL_END
