#include "stdafx.h"
#include "Cannon.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		namespace Cannons 
		{

			Cannon::Cannon()
			{

			}


			Cannon::~Cannon()
			{
			}

			void CannonCube::Setup(D3DXVECTOR3 verScale, D3DXVECTOR3 verRot, D3DXVECTOR3 verPos)
			{
				std::vector<PNC_VERTEX> v;

				v.push_back(PNC_VERTEX(-0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0xff00ffff));
				v.push_back(PNC_VERTEX(-0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0xffff00ff));
				v.push_back(PNC_VERTEX(0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0xffffff00));
				v.push_back(PNC_VERTEX(0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0xff0000ff));
				v.push_back(PNC_VERTEX(-0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0xff00ff00));
				v.push_back(PNC_VERTEX(-0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0xffff0000));
				v.push_back(PNC_VERTEX(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0xff000000));
				v.push_back(PNC_VERTEX(0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0xffffffff));

				//임시 버텍스 변동사항 적용
				D3DXMATRIXA16 ms, mr, mp, mt;
				D3DXMatrixScaling(&ms, verScale.x, verScale.y, verScale.z);
				D3DXMatrixRotationQuaternion(&mr, &D3DXQUATERNION(verRot.x, verRot.y, verRot.z, 0));
				D3DXMatrixTranslation(&mp, verPos.x, verPos.y, verPos.z);
				//D3DXMatrixIdentity(&mt);

				mt = ms * mr * mp;

				for (int i = 0; i < 8; ++i)
				{
					D3DXVec3TransformCoord(&v[i].p, &v[i].p, &mt);
					D3DXVec3Normalize(&v[i].n, &v[i].n);
				}

				//    5========6
				//   /|       /|
				//  / |      / |
				// 1========2  |
				// |  4=====|==7  
				// | /      | /
				// |/       |/
				// 0========3
				//

				//버텍스 버퍼 입력
				DWORD a = DEVICE->CreateVertexBuffer(sizeof(PNC_VERTEX) * v.size(), 0, PNC_VERTEX::FVF, D3DPOOL_DEFAULT, &_vb, NULL);
				PNC_VERTEX* pc = NULL;
				_vb->Lock(0, 0, (LPVOID*)&pc, 0);

				//memset(pc, NULL, sizeof(PC_VERTEX) * v.size());
				//memcpy(pc, &v[0], sizeof(PC_VERTEX) * v.size());
				for (int i = 0; i < v.size(); i++)
				{
					pc[i] = v[i];
				}

				_vb->Unlock();

				//인덱스 버퍼 입력
				struct tagIndex {
					DWORD _1;
					DWORD _2;
					DWORD _3;

					tagIndex() {}
					tagIndex(DWORD a, DWORD b, DWORD c) { _1 = a; _2 = b; _3 = c; }
				};

				tagIndex *i = NULL;

				DEVICE->CreateIndexBuffer(sizeof(tagIndex) * 12, 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &_ib, NULL);
				_ib->Lock(0, 0, (LPVOID*)&i, 0);

				//memcpy(i, i, sizeof(tagIndex) * 12);
				//앞
				// 1==2
				// | /|
				// |/ |
				// 0==3
				i[0] = tagIndex(0, 1, 2);
				i[1] = tagIndex(0, 2, 3);

				//뒤
				// 6==5
				// | /|
				// |/ |
				// 7==4
				i[2] = tagIndex(7, 6, 5);
				i[3] = tagIndex(7, 5, 4);

				//좌
				// 5==1
				// | /|
				// |/ |
				// 4==0
				i[4] = tagIndex(4, 5, 1);
				i[5] = tagIndex(4, 1, 0);

				//우
				// 2==6
				// | /|
				// |/ |
				// 3==7
				i[6] = tagIndex(3, 2, 6);
				i[7] = tagIndex(3, 6, 7);

				//위
				// 5==6
				// | /|
				// |/ |
				// 1==2
				i[8] = tagIndex(1, 5, 6);
				i[9] = tagIndex(1, 6, 2);

				//밑
				// 0==3
				// | /|
				// |/ |
				// 4==7
				i[10] = tagIndex(4, 0, 3);
				i[11] = tagIndex(4, 3, 7);


				_ib->Unlock();
			}
			void CannonCube::Release()
			{
				SAFE_RELEASE(_vb);
				SAFE_RELEASE(_ib);
			}
			void CannonCube::Update()
			{
				//_matPos, _matRot, _matScale, _matLocal;

				D3DXMATRIXA16 rx, ry, rz;

				D3DXMatrixScaling(&_matScale, _scale.x, _scale.y, _scale.z);
				//D3DXMatrixRotationQuaternion(&_matRot, &D3DXQUATERNION(_rot.x, _rot.y, _rot.z, 1));
				if (_look != D3DXVECTOR3(0, 0, 0))
				{
					D3DXVECTOR3 cross, look;
					float dot;

					D3DXVec3Normalize(&look, &(_look - GetPosition()));

					D3DXVec3Cross(&cross, &D3DXVECTOR3(0, 0, 1), &look);
					dot = D3DXVec3Dot(&D3DXVECTOR3(0, 0, 1), &look);

					D3DXMatrixRotationAxis(&_matRot, &cross, acosf(dot));
					
					//롤링
					D3DXVECTOR3 dir = D3DXVECTOR3(0, 0, 1);
					D3DXVec3TransformCoord(&dir, &dir, &(_matRot));
					
					D3DXMatrixRotationAxis(&_rolling, &dir, RAD(GetTickCount() % 360));

					_matRot *= _rolling;
				}
				else
				{
					D3DXMatrixRotationX(&rx, _rot.x);
					D3DXMatrixRotationY(&ry, _rot.y);
					D3DXMatrixRotationZ(&rz, _rot.z);
					_matRot = rx * ry * rz;

					
				}
				D3DXMatrixTranslation(&_matPos, _pos.x, _pos.y, _pos.z);
				D3DXMatrixIdentity(&_matLocal);

				_matLocal = _matScale * _matRot * _matPos;

				if (_parent) _matLocal *= _parent->GetLocalMatrix();

				_direction = D3DXVECTOR3(0, 0, 1);
				D3DXVec3TransformCoord(&_direction, &_direction, &_matRot);
			}
			void CannonCube::Render(LPD3DXEFFECT pEffect)
			{
				DEVICE->SetTransform(D3DTS_WORLD, &_matLocal);

				DEVICE->SetFVF(PNC_VERTEX::FVF);
				DEVICE->SetStreamSource(0, _vb, 0, sizeof(PNC_VERTEX));
				DEVICE->SetIndices(_ib);

				if (!pEffect)
				{
					DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 12, 0, 12);;
					return;
				}

				pEffect->SetMatrix("matWorld", &GetLocalMatrix());

				UINT iPassNum = 0;

				pEffect->Begin(&iPassNum, 0);

				for (UINT i = 0; i < iPassNum; i++)
				{
					pEffect->BeginPass(i);		//i 번째 Pass 시작
					DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 12, 0, 12);
					pEffect->EndPass();			//Pass 끝
				}

				pEffect->End();
			}

			void CannonCube::SetPosition(float x, float y, float z)
			{
				_pos.x = x;
				_pos.y = y;
				_pos.z = z;
			}
			D3DXVECTOR3 CannonCube::GetPosition()
			{
				if (_parent) return _pos + _parent->GetPosition();
				return _pos;
			}
			void CannonCube::SetRotation(float x, float y, float z)
			{
				_rot.x = x;
				_rot.y = y;
				_rot.z = z;
			}
			D3DXVECTOR3 CannonCube::GetRotation()
			{
				if (_parent) return _pos + _parent->GetRotation();
				return _rot;
			}
			void CannonCube::SetScale(float x, float y, float z)
			{
				_scale.x = x;
				_scale.y = y;
				_scale.z = z;
			}
			D3DXVECTOR3 CannonCube::GetScale()
			{
				if (_parent) return _pos + _parent->GetScale();
				return _scale;
			}

			D3DXMATRIXA16 CannonCube::GetLocalMatrix()
			{
				return _matLocal;
			}

			void Cannon::Setup()
			{
				_big = new CannonCube;
				_big->Setup({ 2, 2, 2 }, { 0, 0, 0 }, { 0, 1, 0 });
				_big->SetParent(this);

				_small = new CannonCube;
				_small->Setup({ 1, 1, 3 }, { 0, 0, 0 }, { 0, 0, 1.5 });
				_small->SetPosition(0, 1, 0);
				_small->SetParent(this);

				//pEffect = NULL;
			}
			void Cannon::Release()
			{
				SAFE_RELEASE(_big);
				SAFE_RELEASE(_small);
			}
			void Cannon::Update()
			{
				CannonCube::Update();
				_big->Update();
				_small->Update();
			}
			void Cannon::Render(LPD3DXEFFECT pEffect)
			{
				_big->Render(pEffect);
				_small->Render(pEffect);
			}

			void Cannon::Look(D3DXVECTOR3 &look)
			{
				D3DXVECTOR3 p = GetPosition();
				D3DXVECTOR3 p1(0, 0, 1), p2(look.x - p.x, 0, look.z - p.z);
				float dot;
				D3DXVec3Normalize(&p1, &p1);
				D3DXVec3Normalize(&p2, &p2);

				if (look.x > p.x)
					dot = acosf(D3DXVec3Dot(&p1, &p2));
				else
					dot = -acosf(D3DXVec3Dot(&p2, &p1));

				//LOG_MGR->AddLog("%f", dot);

				_big->SetRotation(0, dot, 0);

				_small->Look(look);
			}
		}
	}
}