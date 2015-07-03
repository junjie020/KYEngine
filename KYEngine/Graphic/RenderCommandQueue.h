#ifndef _RENDERCOMMANDQUEUE_H_
#define _RENDERCOMMANDQUEUE_H_

#include "boost/noncopyable.hpp"
namespace KY
{
	class RenderOperation;

    class RenderCommandQueue : public boost::noncopyable
    {
    public:
    	~RenderCommandQueue();
		
		void Push(const RenderOperation *ro);
		const RenderOperation* Pop();

    private:
		typedef std::list<const RenderOperation*>	ROList;

		ROList	mROList;

    };
}
#endif // _RENDERCOMMANDQUEUE_H_