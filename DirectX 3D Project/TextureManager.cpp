#include "stdafx.h"
#include "TextureManager.h"

namespace NS_ROOT
{
	namespace NS_DIRECTX
	{

		TextureManager::TextureManager()
		{
		}


		TextureManager::~TextureManager()
		{
		}

		LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char* path, D3DXIMAGE_INFO *i)
		{
			if (_mapTexture.find(path) == _mapTexture.end())
			{
				D3DXIMAGE_INFO info;
				//D3DXCreateTextureFromFile(DEVICE, path, &_mapTexture[path]);
				//D3DXGetImageInfoFromFile(path, &info);

				D3DXCreateTextureFromFileEx(
					DEVICE,
					path,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_DEFAULT,
					0,
					&_mapTextureInfo[path],
					NULL,
					&_mapTexture[path]);
			}

			if (i) *i = _mapTextureInfo[path];

			return _mapTexture[path];
		}
		LPDIRECT3DTEXTURE9 TextureManager::GetTexture(std::string& path, D3DXIMAGE_INFO *i)
		{
			return GetTexture((char*)path.c_str(), i);
		}

		void TextureManager::Release()
		{

		}
	}
}