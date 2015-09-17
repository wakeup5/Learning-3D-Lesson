#pragma once
#include "Cube.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Body : public Cube
		{
		public:
			Body() {}
			~Body() {}

			void Setup();
			void Update();
			void Render();
		};

		class Head : public Cube
		{
		public:
			Head() {}
			~Head() {}

			void Setup();
			void Update();
			void Render();
		};

		class ArmL : public Cube
		{
		public:
			ArmL() {}
			~ArmL() {}

			void Setup();
			void Update();
			void Render();
		};

		class ArmR : public Cube
		{
		public:
			ArmR() {}
			~ArmR() {}

			void Setup();
			void Update();
			void Render();
		};

		class LegL : public Cube
		{
		public:
			LegL() {}
			~LegL() {}

			void Setup();
			void Update();
			void Render();
		};

		class LegR : public Cube
		{
		public:
			LegR() {}
			~LegR() {}

			void Setup();
			void Update();
			void Render();
		};
	}
}

