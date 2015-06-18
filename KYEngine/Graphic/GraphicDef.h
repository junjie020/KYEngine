#ifndef _GRAPHICDEF_H_
#define _GRAPHICDEF_H_

namespace KY
{
	struct GraphicInitParam
	{
		uint32 width, height;
		uint32 featureLevel;
		struct SampleDesc
		{
			uint32 count;
			uint32 level;
		};
		SampleDesc sampleDesc;
		HWND hwnd;
	};
}
#endif // _GRAPHICDEF_H_