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
#include <filesystem>
namespace fs = std::tr2::sys;
//@}

//{@	boost
#include "boost/assert.hpp"
#include "boost/noncopyable.hpp"
//@}

//{@
#include "Common/BaseTypes.h"
#include "Common/CommonUtils.h"
//@}