#ifndef _RESOURCEINTERFACE_H_
#define _RESOURCEINTERFACE_H_

namespace KY
{
	template<class HardwareResType>
    class IResourceInterface
    {
	public:
		IResourceInterface() : mDx11Internal(nullptr){}
		virtual ~IResourceInterface() {
			SafeDelete(mDx11Internal);
		};

		const HardwareResType* GetInternal() const { return mDx11Internal; }

		bool IsValid() const {
			return nullptr != mDx11Internal && mDx11Internal->IsValid();
		}
	protected:
		HardwareResType* mDx11Internal;
    };
}
#endif // _RESOURCEINTERFACE_H_