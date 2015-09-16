#pragma once
#include "Action.h"
#include "Cube.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Charactor : public ActionObject, public ActionDeligate
		{
		private:
			Cube* _root;
		public:
			Charactor();
			virtual ~Charactor();

			void Update();
			void Release();
			void Render();
			void OnActionFinish();
		};
	}
}

