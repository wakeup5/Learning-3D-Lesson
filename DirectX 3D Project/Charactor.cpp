#include "stdafx.h"
#include "Charactor.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Charactor::Charactor()
		{
			Body* body = new Body;
			body->Setup();
			body->AttachTo(this);

			_parts.push_back(body);

			_root = body;

			Head* head = new Head;
			head->Setup();
			head->AttachTo(_root);

			_parts.push_back(head);

			ArmL* al = new ArmL;
			al->Setup();
			al->AttachTo(_root);

			_parts.push_back(al);

			ArmR* ar = new ArmR;
			ar->Setup();
			ar->AttachTo(_root);

			_parts.push_back(ar);

			LegL* ll = new LegL;
			ll->Setup();
			ll->AttachTo(_root);

			_parts.push_back(ll);

			LegR* lr = new LegR;
			lr->Setup();
			lr->AttachTo(_root);

			_parts.push_back(lr);
		}


		Charactor::~Charactor()
		{
		}
		void Charactor::Release()
		{
			//_root->Release();
		}
		void Charactor::Update()
		{
			if (_action) _action->Update();
			for (int i = 0; i < _parts.size(); i++)
			{
				_parts[i]->Update();
			}
		}
		void Charactor::Render()
		{
			for (int i = 0; i < _parts.size(); i++)
			{
				_parts[i]->Render();
			}
		}
		void Charactor::OnActionFinish()
		{
			if (_action) _action->Start();
		}
	}
}