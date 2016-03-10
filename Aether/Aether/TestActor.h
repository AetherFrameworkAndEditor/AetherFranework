#pragma once
#include "GameActor.h"
namespace aetherClass{
	class TestActor :
		public GameActor
	{
	public:
		TestActor();
		~TestActor();
		bool Initialize()override;
		void Update()override;
		void DoCollide()override;
	};

}