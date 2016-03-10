#pragma once
#include "GameActor.h"
namespace aetherClass{
	class TestActor2 :public GameActor
	{
	public:
		TestActor2();
		~TestActor2();
		bool Initialize()override;
		void Update()override;
		void DoCollide()override;
	};

}