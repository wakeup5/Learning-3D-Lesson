#pragma once

namespace NS_ROOT
{
	namespace NS_BASE
	{
		class GameMain
		{
		public:
			GameMain();
			virtual ~GameMain();

			HRESULT Setup();
			void Release();
			void Update();
			void Render();
		};
	}//end NS_BASE
}//end NS_ROOT
