#pragma once
#include "Transform.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class ActionObject;
		interface ActionDeligate;

		class Action
		{
		public:
			virtual void Start() = 0;
			virtual void Update() = 0;

			void SetDeligate(ActionDeligate* d) { _deligate = d; }
			void SetObject(ActionObject* o) { _object = o; }
		protected:
			ActionDeligate*		_deligate = NULL;
			ActionObject*		_object = NULL;
		};

		class ActionObject : public Transform
		{
		public:
			ActionObject();
			virtual ~ActionObject();

			virtual void Update();

			void SetAction(Action* a) { _action = a; _action->SetObject(this); }
		protected:
			Action* _action = NULL;
		};

		interface ActionDeligate
		{
		public:
			virtual void OnActionFinish() = 0;
		};

	}
}
