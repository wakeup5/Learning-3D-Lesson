#pragma once
namespace NS_ROOT
{
	namespace NS_DIRECTX
	{
		class Device : public Util::Singleton < Device >
		{
		private:
			LPDIRECT3DDEVICE9 _device;

		public:
			Device();
			virtual ~Device();

		public:
			LPDIRECT3DDEVICE9 GetDevice();

			HRESULT Setup();
			void Release() override;
		};
	}
}

#define DEVICEMANAGER	NS_ROOT::NS_DIRECTX::Device::GetInstance()
#define DEVICE			DEVICEMANAGER->GetDevice()
