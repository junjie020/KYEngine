
#ifndef _HARDWAREINTERFACE_H_
#define _HARDWAREINTERFACE_H_

namespace KY
{
	template<class ImplType>
    class Dx11HardwareInterface
    {
    public:
		Dx11HardwareInterface() : mInternal(nullptr){}
		~Dx11HardwareInterface(){
			SafeRelease(mInternal);
		}
	
		ImplType* GetInternal() const {
			return mInternal;
		}

		bool IsValid() const {
			return nullptr != mInternal;
		}
	protected:
		ImplType *mInternal;
    };
}
#endif // _HARDWAREINTERFACE_H_
