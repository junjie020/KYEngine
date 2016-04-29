///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#endif //_WIN32
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

#ifdef _WIN32
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;

#endif //_WIN32
//@}

#pragma warning(disable:4201)

#include "Common/BaseDef.h"

#include "glm/glm.hpp"

//{@	boost
#include "boost/assert.hpp"
#include "boost/noncopyable.hpp"
//@}

//{@
#include "Common/BaseTypes.h"
#include "Common/CommonUtils.h"
//@}