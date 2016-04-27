#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace KY
{
	template<class T>
    class Singleton
    {
    public:
		Singleton()
		{
			BOOST_ASSERT(mInst == nullptr);
			mInst = (T*)(this);
		}
		~Singleton()
		{
			BOOST_ASSERT(nullptr != mInst);			
		}

		static T* Inst(){ return mInst;  }

		static T* Create()
		{
			return new T();
		}

		static void Destroy()
		{
			SafeDelete(mInst);
		}

		static bool HasInst()
		{
			return mInst != nullptr;
		}
    	
    protected:
    	

    private:
		static T* mInst;
    };

	template<class T>
	T* Singleton<T>::mInst = nullptr;
}
#endif // _SINGLETON_H_