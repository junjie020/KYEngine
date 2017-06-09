#ifndef _RENDERCOMMANDQUEUE_H_
#define _RENDERCOMMANDQUEUE_H_

#if NEED_BOOST
#include "boost/noncopyable.hpp"
#endif 
namespace KY
{
	class RenderOperation;

    class RenderCommandQueue 
#if NEED_BOOST
		: public boost::noncopyable
#endif
		
    {
    public:
    	~RenderCommandQueue();

		bool IsEmpty() const {
			return mROList.empty();
		}
		
		void Push(const RenderOperation *ro);

		void Push(RenderCommandQueue &&q);

		const RenderOperation* Pop();

    private:
		typedef std::list<const RenderOperation*>	ROList;

		ROList	mROList;

    };
}
#endif // _RENDERCOMMANDQUEUE_H_
