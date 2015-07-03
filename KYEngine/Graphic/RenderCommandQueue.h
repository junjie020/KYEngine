#ifndef _RENDERCOMMANDQUEUE_H_
#define _RENDERCOMMANDQUEUE_H_

#include "boost/noncopyable.hpp"
namespace KY
{
	class RenderOperation;

    class RenderCommandQueue : public noncopyable
    {
    public:
    	~RenderCommandQueue();
		
		void Push(const RenderOperation &ro);
		RenderOperation* Pop();

    private:
		typedef std::list<RenderOperation*>	ROList;

		ROList	mROList;

    };
}
#endif // _RENDERCOMMANDQUEUE_H_