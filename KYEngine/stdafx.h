///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <windows.h>

//{@	STL
#include <vector>
#include <list>
#include <array>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
//@}

#pragma warning(disable:4201)

//{@	boost
#include "boost/assert.hpp"
#include "boost/noncopyable.hpp"
//@}

//{@
#include "Common/BaseTypes.h"
#include "Common/CommonUtils.h"
//@}