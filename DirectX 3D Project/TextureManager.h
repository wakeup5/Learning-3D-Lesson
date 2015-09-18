#pragma once
#include "Singleton.h"

namespace NS_ROOT
{
	namespace NS_DIRECTX
	{
		class TextureManager : public NS_UTIL::Singleton < TextureManager >
		{
		private:
			std::map<std::string, LPDIRECT3DTEXTURE9> _mapTexture;
			std::map<std::string, D3DXIMAGE_INFO> _mapTextureInfo;
		public:
			TextureManager();
			~TextureManager();

			LPDIRECT3DTEXTURE9 GetTexture(char* path, D3DXIMAGE_INFO *i = NULL);
			LPDIRECT3DTEXTURE9 GetTexture(std::string& path, D3DXIMAGE_INFO *i = NULL);

			void Release();
		};
	}
}

#define TEXTURE_MGR NS_ROOT::NS_DIRECTX::TextureManager::GetInstance()