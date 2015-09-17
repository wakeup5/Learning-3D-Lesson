#include "stdafx.h"
#include "Cubes.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		void Body::Setup()
		{
			Cube::Setup();

			//uvÁÂÇ¥ ¼³Á¤
			_vertex[0].t.x = (float)32 / 64;	_vertex[0].t.y = (float)32 / 32;
			_vertex[1].t.x = (float)32 / 64;	_vertex[1].t.y = (float)20 / 32;
			_vertex[2].t.x = (float)40 / 64;	_vertex[2].t.y = (float)20 / 32;	 //¾Õ¸é À­»ï°¢ 
																							 //0,1,2

			_vertex[3].t.x = (float)32 / 64;	_vertex[3].t.y = (float)32 / 32;
			_vertex[4].t.x = (float)40 / 64;	_vertex[4].t.y = (float)20 / 32;
			_vertex[5].t.x = (float)40 / 64;	_vertex[5].t.y = (float)32 / 32;	 //¾Õ¸é ¾Æ·§»ï°¢
																							 //0,2,3

			_vertex[6].t.x = (float)28 / 64;	_vertex[6].t.y = (float)32 / 32;
			_vertex[7].t.x = (float)20 / 64;	_vertex[7].t.y = (float)20 / 32;
			_vertex[8].t.x = (float)28 / 64;	_vertex[8].t.y = (float)20 / 32;	 //µÞ¸é À­»ï°¢
																							 //4,6,5

			_vertex[9].t.x = (float)28 / 64;	_vertex[9].t.y = (float)32 / 32;
			_vertex[10].t.x = (float)20 / 64;	_vertex[10].t.y = (float)32 / 32;
			_vertex[11].t.x = (float)20 / 64;	_vertex[11].t.y = (float)20 / 32;	 //µÞ¸é ¾Æ·§»ï°¢
																							 //4,7,6

			_vertex[12].t.x = (float)28 / 64;	_vertex[12].t.y = (float)32 / 32;
			_vertex[13].t.x = (float)28 / 64;	_vertex[13].t.y = (float)20 / 32;
			_vertex[14].t.x = (float)32 / 64;	_vertex[14].t.y = (float)20 / 32;	 //¿ÞÂÊ¸é À­»ï°¢
																							 //4,5,1

			_vertex[15].t.x = (float)28 / 64;	_vertex[15].t.y = (float)32 / 32;
			_vertex[16].t.x = (float)32 / 64;	_vertex[16].t.y = (float)20 / 32;
			_vertex[17].t.x = (float)32 / 64;	_vertex[17].t.y = (float)32 / 32;	 //¿ÞÂÊ¸é ¾Æ·§»ï°¢
																							 //4,1,0

			_vertex[18].t.x = (float)16 / 64;	_vertex[18].t.y = (float)32 / 32;
			_vertex[19].t.x = (float)16 / 64;	_vertex[19].t.y = (float)20 / 32;
			_vertex[20].t.x = (float)20 / 64;	_vertex[20].t.y = (float)20 / 32;	 //¿À¸¥¸é À­»ï°¢
																							 //3,2,6

			_vertex[21].t.x = (float)16 / 64;	_vertex[21].t.y = (float)32 / 32;
			_vertex[22].t.x = (float)20 / 64;	_vertex[22].t.y = (float)20 / 32;
			_vertex[23].t.x = (float)20 / 64;	_vertex[23].t.y = (float)32 / 32;	 //¿À¸¥¸é ¾Æ·§»ï°¢
																							 //3,6,7

			_vertex[24].t.x = (float)28 / 64;	_vertex[24].t.y = (float)16 / 32;
			_vertex[25].t.x = (float)28 / 64;	_vertex[25].t.y = (float)20 / 32;
			_vertex[26].t.x = (float)20 / 64;	_vertex[26].t.y = (float)20 / 32;	 //À­¸é À­»ï°¢
																							 //1,5,6

			_vertex[27].t.x = (float)28 / 64;	_vertex[27].t.y = (float)16 / 32;
			_vertex[28].t.x = (float)20 / 64;	_vertex[28].t.y = (float)20 / 32;
			_vertex[29].t.x = (float)20 / 64;	_vertex[29].t.y = (float)16 / 32;	 //À­¸é ¾Æ·§»ï°¢
																							 //1,6,2

			_vertex[30].t.x = (float)28 / 64;	_vertex[30].t.y = (float)16 / 32;
			_vertex[31].t.x = (float)28 / 64;	_vertex[31].t.y = (float)20 / 32;
			_vertex[32].t.x = (float)36 / 64;	_vertex[32].t.y = (float)20 / 32;	 //¾Æ·§¸é À­»ï°¢
																							 //4,0,3

			_vertex[33].t.x = (float)28 / 64;	_vertex[33].t.y = (float)16 / 32;
			_vertex[34].t.x = (float)36 / 64;	_vertex[34].t.y = (float)20 / 32;
			_vertex[35].t.x = (float)36 / 64;	_vertex[35].t.y = (float)20 / 32;	 //¾Æ·§¸é ¾Æ·§»ï°¢

			SetScale(0.4f, 0.6f, 0.2f);
			SetLocalPosition(0, 0, 0);
		}
		void Body::Update()
		{
			Cube::Update();
		}
		void Body::Render()
		{
			Cube::Render();
		}

		void Head::Setup()
		{
			Cube::Setup();

			_vertex[0].t.x = (float)24 / 64;	_vertex[0].t.y = (float)16 / 32;
			_vertex[1].t.x = (float)24 / 64;	_vertex[1].t.y = (float)8 / 32;
			_vertex[2].t.x = (float)32 / 64;	_vertex[2].t.y = (float)8 / 32;	 //¾Õ¸é À­»ï°¢ 
																						 //0,1,2

			_vertex[3].t.x = (float)24 / 64;	_vertex[3].t.y = (float)16 / 32;
			_vertex[4].t.x = (float)32 / 64;	_vertex[4].t.y = (float)8 / 32;
			_vertex[5].t.x = (float)32 / 64;	_vertex[5].t.y = (float)16 / 32;	 //¾Õ¸é ¾Æ·§»ï°¢
																							 //0,2,3

			_vertex[6].t.x = (float)16 / 64;	_vertex[6].t.y = (float)16 / 32;
			_vertex[7].t.x = (float)8 / 64;	_vertex[7].t.y = (float)8 / 32;
			_vertex[8].t.x = (float)16 / 64;	_vertex[8].t.y = (float)8 / 32;	 //µÞ¸é À­»ï°¢
																						 //4,6,5

			_vertex[9].t.x = (float)16 / 64;	_vertex[9].t.y = (float)16 / 32;
			_vertex[10].t.x = (float)8 / 64;	_vertex[10].t.y = (float)16 / 32;
			_vertex[11].t.x = (float)8 / 64;	_vertex[11].t.y = (float)8 / 32;	 //µÞ¸é ¾Æ·§»ï°¢
																							 //4,7,6

			_vertex[12].t.x = (float)16 / 64;	_vertex[12].t.y = (float)16 / 32;
			_vertex[13].t.x = (float)16 / 64;	_vertex[13].t.y = (float)8 / 32;
			_vertex[14].t.x = (float)24 / 64;	_vertex[14].t.y = (float)8 / 32;	 //¿ÞÂÊ¸é À­»ï°¢
																							 //4,5,1

			_vertex[15].t.x = (float)16 / 64;	_vertex[15].t.y = (float)16 / 32;
			_vertex[16].t.x = (float)24 / 64;	_vertex[16].t.y = (float)8 / 32;
			_vertex[17].t.x = (float)25 / 64;	_vertex[17].t.y = (float)16 / 32;	 //¿ÞÂÊ¸é ¾Æ·§»ï°¢
																							 //4,1,0

			_vertex[18].t.x = (float)0 / 64;	_vertex[18].t.y = (float)16 / 32;
			_vertex[19].t.x = (float)0 / 64;	_vertex[19].t.y = (float)8 / 32;
			_vertex[20].t.x = (float)8 / 64;	_vertex[20].t.y = (float)8 / 32;	 //¿À¸¥¸é À­»ï°¢
																							 //3,2,6

			_vertex[21].t.x = (float)0 / 64;	_vertex[21].t.y = (float)16 / 32;
			_vertex[22].t.x = (float)8 / 64;	_vertex[22].t.y = (float)8 / 32;
			_vertex[23].t.x = (float)8 / 64;	_vertex[23].t.y = (float)16 / 32;	 //¿À¸¥¸é ¾Æ·§»ï°¢
																							 //3,6,7

			_vertex[24].t.x = (float)16 / 64;	_vertex[24].t.y = (float)0 / 32;
			_vertex[25].t.x = (float)16 / 64;	_vertex[25].t.y = (float)8 / 32;
			_vertex[26].t.x = (float)8 / 64;	_vertex[26].t.y = (float)8 / 32;	 //À­¸é À­»ï°¢
																							 //1,5,6

			_vertex[27].t.x = (float)16 / 64;	_vertex[27].t.y = (float)0 / 32;
			_vertex[28].t.x = (float)8 / 64;	_vertex[28].t.y = (float)8 / 32;
			_vertex[29].t.x = (float)8 / 64;	_vertex[29].t.y = (float)0 / 32;	 //À­¸é ¾Æ·§»ï°¢
																							 //1,6,2

			_vertex[30].t.x = (float)24 / 64;	_vertex[30].t.y = (float)0 / 32;
			_vertex[31].t.x = (float)24 / 64;	_vertex[31].t.y = (float)8 / 32;
			_vertex[32].t.x = (float)16 / 64;	_vertex[32].t.y = (float)8 / 32;	 //¾Æ·§¸é À­»ï°¢
																							 //4,0,3

			_vertex[33].t.x = (float)24 / 64;	_vertex[33].t.y = (float)0 / 32;
			_vertex[34].t.x = (float)16 / 64;	_vertex[34].t.y = (float)8 / 32;
			_vertex[35].t.x = (float)16 / 64;	_vertex[35].t.y = (float)0 / 32;	 //¾Æ·§¸é ¾Æ·§»ï°¢

			SetScale(0.4f, 0.4f, 0.4f);
			SetLocalPosition(0, 0.8f, 0);
		}
		void Head::Update()
		{
			Cube::Update();
		}
		void Head::Render()
		{
			Cube::Render();
		}

		void ArmL::Setup()
		{
			Cube::Setup();

			_vertex[0].t.x = (float)44 / 64;	_vertex[0].t.y = (float)32 / 32;
			_vertex[1].t.x = (float)44 / 64;	_vertex[1].t.y = (float)20 / 32;
			_vertex[2].t.x = (float)48 / 64;	_vertex[2].t.y = (float)20 / 32;	 //¾Õ¸é À­»ï°¢ 
																							 //0,1,2

			_vertex[3].t.x = (float)44 / 64;	_vertex[3].t.y = (float)32 / 32;
			_vertex[4].t.x = (float)48 / 64;	_vertex[4].t.y = (float)20 / 32;
			_vertex[5].t.x = (float)48 / 64;	_vertex[5].t.y = (float)32 / 32;	 //¾Õ¸é ¾Æ·§»ï°¢
																							 //0,2,3

			_vertex[6].t.x = (float)56 / 64;	_vertex[6].t.y = (float)32 / 32;
			_vertex[7].t.x = (float)52 / 64;	_vertex[7].t.y = (float)20 / 32;
			_vertex[8].t.x = (float)56 / 64;	_vertex[8].t.y = (float)20 / 32;	 //µÞ¸é À­»ï°¢
																							 //4,6,5

			_vertex[9].t.x = (float)56 / 64;	_vertex[9].t.y = (float)32 / 32;
			_vertex[10].t.x = (float)52 / 64;	_vertex[10].t.y = (float)32 / 32;
			_vertex[11].t.x = (float)52 / 64;	_vertex[11].t.y = (float)20 / 32;	 //µÞ¸é ¾Æ·§»ï°¢
																							 //4,7,6

			_vertex[12].t.x = (float)40 / 64;	_vertex[12].t.y = (float)32 / 32;
			_vertex[13].t.x = (float)40 / 64;	_vertex[13].t.y = (float)20 / 32;
			_vertex[14].t.x = (float)44 / 64;	_vertex[14].t.y = (float)20 / 32;	 //¿ÞÂÊ¸é À­»ï°¢
																							 //4,5,1

			_vertex[15].t.x = (float)40 / 64;	_vertex[15].t.y = (float)32 / 32;
			_vertex[16].t.x = (float)44 / 64;	_vertex[16].t.y = (float)20 / 32;
			_vertex[17].t.x = (float)44 / 64;	_vertex[17].t.y = (float)32 / 32;	 //¿ÞÂÊ¸é ¾Æ·§»ï°¢
																							 //4,1,0

			_vertex[18].t.x = (float)48 / 64;	_vertex[18].t.y = (float)32 / 32;
			_vertex[19].t.x = (float)48 / 64;	_vertex[19].t.y = (float)20 / 32;
			_vertex[20].t.x = (float)52 / 64;	_vertex[20].t.y = (float)20 / 32;	 //¿À¸¥¸é À­»ï°¢
																							 //3,2,6

			_vertex[21].t.x = (float)48 / 64;	_vertex[21].t.y = (float)32 / 32;
			_vertex[22].t.x = (float)52 / 64;	_vertex[22].t.y = (float)20 / 32;
			_vertex[23].t.x = (float)52 / 64;	_vertex[23].t.y = (float)32 / 32;	 //¿À¸¥¸é ¾Æ·§»ï°¢
																							 //3,6,7

			_vertex[24].t.x = (float)44 / 64;	_vertex[24].t.y = (float)20 / 32;
			_vertex[25].t.x = (float)44 / 64;	_vertex[25].t.y = (float)16 / 32;
			_vertex[26].t.x = (float)48 / 64;	_vertex[26].t.y = (float)16 / 32;	 //À­¸é À­»ï°¢
																							 //1,5,6

			_vertex[27].t.x = (float)44 / 64;	_vertex[27].t.y = (float)20 / 32;
			_vertex[28].t.x = (float)48 / 64;	_vertex[28].t.y = (float)16 / 32;
			_vertex[29].t.x = (float)48 / 64;	_vertex[29].t.y = (float)20 / 32;	 //À­¸é ¾Æ·§»ï°¢
																							 //1,6,2

			_vertex[30].t.x = (float)48 / 64;	_vertex[30].t.y = (float)16 / 32;
			_vertex[31].t.x = (float)48 / 64;	_vertex[31].t.y = (float)20 / 32;
			_vertex[32].t.x = (float)52 / 64;	_vertex[32].t.y = (float)20 / 32;	 //¾Æ·§¸é À­»ï°¢
																							 //4,0,3

			_vertex[33].t.x = (float)48 / 64;	_vertex[33].t.y = (float)16 / 32;
			_vertex[34].t.x = (float)52 / 64;	_vertex[34].t.y = (float)20 / 32;
			_vertex[35].t.x = (float)52 / 64;	_vertex[35].t.y = (float)16 / 32;	 //¾Æ·§¸é ¾Æ·§»ï°¢
																							 //4,3,7

			SetScale(0.2f, 0.6f, 0.2f);
			SetLocalPosition(-0.6f, 0, 0);
		}
		void ArmL::Update()
		{
			Cube::Update();
			SetRotateLocal(-sin(TIME_MGR->GetLastTime() * 10), 0, 0);
		}
		void ArmL::Render()
		{
			Cube::Render();
		}

		void ArmR::Setup()
		{
			Cube::Setup();

			_vertex[0].t.x = (float)48 / 64;	_vertex[0].t.y = (float)32 / 32;
			_vertex[1].t.x = (float)48 / 64;	_vertex[1].t.y = (float)20 / 32;
			_vertex[2].t.x = (float)44 / 64;	_vertex[2].t.y = (float)20 / 32;	 //¾Õ¸é À­»ï°¢ 
																							 //0,1,2

			_vertex[3].t.x = (float)48 / 64;	_vertex[3].t.y = (float)32 / 32;
			_vertex[4].t.x = (float)44 / 64;	_vertex[4].t.y = (float)20 / 32;
			_vertex[5].t.x = (float)44 / 64;	_vertex[5].t.y = (float)32 / 32;	 //¾Õ¸é ¾Æ·§»ï°¢
																							 //0,2,3

			_vertex[6].t.x = (float)52 / 64;	_vertex[6].t.y = (float)32 / 32;
			_vertex[7].t.x = (float)56 / 64;	_vertex[7].t.y = (float)20 / 32;
			_vertex[8].t.x = (float)52 / 64;	_vertex[8].t.y = (float)20 / 32;	 //µÞ¸é À­»ï°¢
																							 //4,6,5

			_vertex[9].t.x = (float)52 / 64;	_vertex[9].t.y = (float)32 / 32;
			_vertex[10].t.x = (float)56 / 64;	_vertex[10].t.y = (float)32 / 32;
			_vertex[11].t.x = (float)56 / 64;	_vertex[11].t.y = (float)20 / 32;	 //µÞ¸é ¾Æ·§»ï°¢
																							 //4,7,6

			_vertex[18].t.x = (float)44 / 64;	_vertex[12].t.y = (float)32 / 32;
			_vertex[19].t.x = (float)44 / 64;	_vertex[13].t.y = (float)20 / 32;
			_vertex[20].t.x = (float)40 / 64;	_vertex[14].t.y = (float)20 / 32;	 //¿ÞÂÊ¸é À­»ï°¢
																							 //4,5,1

			_vertex[21].t.x = (float)44 / 64;	_vertex[15].t.y = (float)32 / 32;
			_vertex[22].t.x = (float)40 / 64;	_vertex[16].t.y = (float)20 / 32;
			_vertex[23].t.x = (float)40 / 64;	_vertex[17].t.y = (float)32 / 32;	 //¿ÞÂÊ¸é ¾Æ·§»ï°¢
																							 //4,1,0

			_vertex[12].t.x = (float)52 / 64;	_vertex[18].t.y = (float)32 / 32;
			_vertex[13].t.x = (float)52 / 64;	_vertex[19].t.y = (float)20 / 32;
			_vertex[14].t.x = (float)48 / 64;	_vertex[20].t.y = (float)20 / 32;	 //¿À¸¥¸é À­»ï°¢
																							 //3,2,6

			_vertex[15].t.x = (float)52 / 64;	_vertex[21].t.y = (float)32 / 32;
			_vertex[16].t.x = (float)48 / 64;	_vertex[22].t.y = (float)20 / 32;
			_vertex[17].t.x = (float)48 / 64;	_vertex[23].t.y = (float)32 / 32;	 //¿À¸¥¸é ¾Æ·§»ï°¢
																							 //3,6,7

			_vertex[24].t.x = (float)48 / 64;	_vertex[24].t.y = (float)20 / 32;
			_vertex[25].t.x = (float)48 / 64;	_vertex[25].t.y = (float)16 / 32;
			_vertex[26].t.x = (float)44 / 64;	_vertex[26].t.y = (float)16 / 32;	 //À­¸é À­»ï°¢
																							 //1,5,6

			_vertex[27].t.x = (float)48 / 64;	_vertex[27].t.y = (float)20 / 32;
			_vertex[28].t.x = (float)44 / 64;	_vertex[28].t.y = (float)16 / 32;
			_vertex[29].t.x = (float)44 / 64;	_vertex[29].t.y = (float)20 / 32;	 //À­¸é ¾Æ·§»ï°¢
																							 //1,6,2

			_vertex[30].t.x = (float)52 / 64;	_vertex[30].t.y = (float)16 / 32;
			_vertex[31].t.x = (float)52 / 64;	_vertex[31].t.y = (float)20 / 32;
			_vertex[32].t.x = (float)48 / 64;	_vertex[32].t.y = (float)20 / 32;	 //¾Æ·§¸é À­»ï°¢
																							 //4,0,3

			_vertex[33].t.x = (float)52 / 64;	_vertex[33].t.y = (float)16 / 32;
			_vertex[34].t.x = (float)48 / 64;	_vertex[34].t.y = (float)20 / 32;
			_vertex[35].t.x = (float)48 / 64;	_vertex[35].t.y = (float)16 / 32;	 //¾Æ·§¸é ¾Æ·§»ï°¢

			SetScale(0.2f, 0.6f, 0.2f);
			SetLocalPosition(0.6f, 0, 0);
		}
		void ArmR::Update()
		{
			Cube::Update();
			SetRotateLocal(sin(TIME_MGR->GetLastTime() * 10), 0, 0);
		}
		void ArmR::Render()
		{
			Cube::Render();
		}

		void LegL::Setup()
		{
			Cube::Setup();

			_vertex[0].t.x = (float)4 / 64;	_vertex[0].t.y = (float)32 / 32;
			_vertex[1].t.x = (float)4 / 64;	_vertex[1].t.y = (float)20 / 32;
			_vertex[2].t.x = (float)8 / 64;	_vertex[2].t.y = (float)20 / 32;	 //¾Õ¸é À­»ï°¢ 
																						 //0,1,2

			_vertex[3].t.x = (float)4 / 64;	_vertex[3].t.y = (float)32 / 32;
			_vertex[4].t.x = (float)8 / 64;	_vertex[4].t.y = (float)20 / 32;
			_vertex[5].t.x = (float)8 / 64;	_vertex[5].t.y = (float)32 / 32;	 //¾Õ¸é ¾Æ·§»ï°¢
																						 //0,2,3

			_vertex[6].t.x = (float)16 / 64;	_vertex[6].t.y = (float)32 / 32;
			_vertex[7].t.x = (float)12 / 64;	_vertex[7].t.y = (float)20 / 32;
			_vertex[8].t.x = (float)16 / 64;	_vertex[8].t.y = (float)20 / 32;	 //µÞ¸é À­»ï°¢
																							 //4,6,5

			_vertex[9].t.x = (float)16 / 64;	_vertex[9].t.y = (float)32 / 32;
			_vertex[10].t.x = (float)12 / 64;	_vertex[10].t.y = (float)32 / 32;
			_vertex[11].t.x = (float)12 / 64;	_vertex[11].t.y = (float)20 / 32;	 //µÞ¸é ¾Æ·§»ï°¢
																							 //4,7,6

			_vertex[12].t.x = (float)0 / 64;	_vertex[12].t.y = (float)32 / 32;
			_vertex[13].t.x = (float)0 / 64;	_vertex[13].t.y = (float)20 / 32;
			_vertex[14].t.x = (float)4 / 64;	_vertex[14].t.y = (float)20 / 32;	 //¿ÞÂÊ¸é À­»ï°¢
																							 //4,5,1

			_vertex[15].t.x = (float)0 / 64;	_vertex[15].t.y = (float)32 / 32;
			_vertex[16].t.x = (float)4 / 64;	_vertex[16].t.y = (float)20 / 32;
			_vertex[17].t.x = (float)4 / 64;	_vertex[17].t.y = (float)32 / 32;	 //¿ÞÂÊ¸é ¾Æ·§»ï°¢
																							 //4,1,0

			_vertex[18].t.x = (float)8 / 64;	_vertex[18].t.y = (float)32 / 32;
			_vertex[19].t.x = (float)8 / 64;	_vertex[19].t.y = (float)20 / 32;
			_vertex[20].t.x = (float)12 / 64;	_vertex[20].t.y = (float)20 / 32;	 //¿À¸¥¸é À­»ï°¢
																							 //3,2,6

			_vertex[21].t.x = (float)8 / 64;	_vertex[21].t.y = (float)32 / 32;
			_vertex[22].t.x = (float)12 / 64;	_vertex[22].t.y = (float)20 / 32;
			_vertex[23].t.x = (float)12 / 64;	_vertex[23].t.y = (float)32 / 32;	 //¿À¸¥¸é ¾Æ·§»ï°¢
																							 //3,6,7

			_vertex[24].t.x = (float)4 / 64;	_vertex[24].t.y = (float)20 / 32;
			_vertex[25].t.x = (float)4 / 64;	_vertex[25].t.y = (float)16 / 32;
			_vertex[26].t.x = (float)8 / 64;	_vertex[26].t.y = (float)16 / 32;	 //À­¸é À­»ï°¢
																							 //1,5,6

			_vertex[27].t.x = (float)4 / 64;	_vertex[27].t.y = (float)20 / 32;
			_vertex[28].t.x = (float)8 / 64;	_vertex[28].t.y = (float)16 / 32;
			_vertex[29].t.x = (float)8 / 64;	_vertex[29].t.y = (float)20 / 32;	 //À­¸é ¾Æ·§»ï°¢
																							 //1,6,2

			_vertex[30].t.x = (float)8 / 64;	_vertex[30].t.y = (float)16 / 32;
			_vertex[31].t.x = (float)8 / 64;	_vertex[31].t.y = (float)20 / 32;
			_vertex[32].t.x = (float)12 / 64;	_vertex[32].t.y = (float)20 / 32;	 //¾Æ·§¸é À­»ï°¢
																							 //4,0,3

			_vertex[33].t.x = (float)8 / 64;	_vertex[33].t.y = (float)16 / 32;
			_vertex[34].t.x = (float)12 / 64;	_vertex[34].t.y = (float)20 / 32;
			_vertex[35].t.x = (float)12 / 64;	_vertex[35].t.y = (float)16 / 32;	 //¾Æ·§¸é ¾Æ·§»ï°¢

			SetScale(0.2f, 0.6f, 0.2f);
			MovePositionLocal(-0.2, -1.2, 0);
		}
		void LegL::Update()
		{
			Cube::Update();
			SetRotateLocal(sin(TIME_MGR->GetLastTime() * 10), 0, 0);
		}
		void LegL::Render()
		{
			Cube::Render();
		}

		void LegR::Setup()
		{
			Cube::Setup();

			_vertex[0].t.x = (float)8 / 64;	_vertex[0].t.y = (float)32 / 32;
			_vertex[1].t.x = (float)8 / 64;	_vertex[1].t.y = (float)20 / 32;
			_vertex[2].t.x = (float)4 / 64;	_vertex[2].t.y = (float)20 / 32;	 //¾Õ¸é À­»ï°¢ 
																						 //0,1,2

			_vertex[3].t.x = (float)8 / 64;	_vertex[3].t.y = (float)32 / 32;
			_vertex[4].t.x = (float)4 / 64;	_vertex[4].t.y = (float)20 / 32;
			_vertex[5].t.x = (float)4 / 64;	_vertex[5].t.y = (float)32 / 32;	 //¾Õ¸é ¾Æ·§»ï°¢
																						 //0,2,3

			_vertex[6].t.x = (float)12 / 64;	_vertex[6].t.y = (float)32 / 32;
			_vertex[7].t.x = (float)16 / 64;	_vertex[7].t.y = (float)20 / 32;
			_vertex[8].t.x = (float)12 / 64;	_vertex[8].t.y = (float)20 / 32;	 //µÞ¸é À­»ï°¢
																							 //4,6,5

			_vertex[9].t.x = (float)12 / 64;	_vertex[9].t.y = (float)32 / 32;
			_vertex[10].t.x = (float)16 / 64;	_vertex[10].t.y = (float)32 / 32;
			_vertex[11].t.x = (float)16 / 64;	_vertex[11].t.y = (float)20 / 32;	 //µÞ¸é ¾Æ·§»ï°¢
																							 //4,7,6

			_vertex[18].t.x = (float)4 / 64;	_vertex[12].t.y = (float)32 / 32;
			_vertex[19].t.x = (float)4 / 64;	_vertex[13].t.y = (float)20 / 32;
			_vertex[20].t.x = (float)0 / 64;	_vertex[14].t.y = (float)20 / 32;	 //¿ÞÂÊ¸é À­»ï°¢
																							 //4,5,1

			_vertex[21].t.x = (float)4 / 64;	_vertex[15].t.y = (float)32 / 32;
			_vertex[22].t.x = (float)0 / 64;	_vertex[16].t.y = (float)20 / 32;
			_vertex[23].t.x = (float)0 / 64;	_vertex[17].t.y = (float)32 / 32;	 //¿ÞÂÊ¸é ¾Æ·§»ï°¢
																							 //4,1,0

			_vertex[12].t.x = (float)12 / 64;	_vertex[18].t.y = (float)32 / 32;
			_vertex[13].t.x = (float)12 / 64;	_vertex[19].t.y = (float)20 / 32;
			_vertex[14].t.x = (float)8 / 64;	_vertex[20].t.y = (float)20 / 32;	 //¿À¸¥¸é À­»ï°¢
																							 //3,2,6

			_vertex[15].t.x = (float)12 / 64;	_vertex[21].t.y = (float)32 / 32;
			_vertex[16].t.x = (float)8 / 64;	_vertex[22].t.y = (float)20 / 32;
			_vertex[17].t.x = (float)8 / 64;	_vertex[23].t.y = (float)32 / 32;	 //¿À¸¥¸é ¾Æ·§»ï°¢
																							 //3,6,7

			_vertex[24].t.x = (float)8 / 64;	_vertex[24].t.y = (float)20 / 32;
			_vertex[25].t.x = (float)8 / 64;	_vertex[25].t.y = (float)16 / 32;
			_vertex[26].t.x = (float)4 / 64;	_vertex[26].t.y = (float)16 / 32;	 //À­¸é À­»ï°¢
																							 //1,5,6

			_vertex[27].t.x = (float)8 / 64;	_vertex[27].t.y = (float)20 / 32;
			_vertex[28].t.x = (float)4 / 64;	_vertex[28].t.y = (float)16 / 32;
			_vertex[29].t.x = (float)4 / 64;	_vertex[29].t.y = (float)20 / 32;	 //À­¸é ¾Æ·§»ï°¢
																							 //1,6,2

			_vertex[30].t.x = (float)12 / 64;	_vertex[30].t.y = (float)16 / 32;
			_vertex[31].t.x = (float)12 / 64;	_vertex[31].t.y = (float)20 / 32;
			_vertex[32].t.x = (float)8 / 64;	_vertex[32].t.y = (float)20 / 32;	 //¾Æ·§¸é À­»ï°¢
																							 //4,0,3

			_vertex[33].t.x = (float)12 / 64;	_vertex[33].t.y = (float)16 / 32;
			_vertex[34].t.x = (float)8 / 64;	_vertex[34].t.y = (float)20 / 32;
			_vertex[35].t.x = (float)8 / 64;	_vertex[35].t.y = (float)16 / 32;	 //¾Æ·§¸é ¾Æ·§»ï°¢

			SetScale(0.2f, 0.6f, 0.2f);
			MovePositionLocal(0.2, -1.2, 0);
		}
		void LegR::Update()
		{
			Cube::Update();
			SetRotateLocal(-sin(TIME_MGR->GetLastTime() * 10), 0, 0);
		}
		void LegR::Render()
		{
			Cube::Render();
		}
	}
}