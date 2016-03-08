#ifndef _LIGHTSHADER_H
#define _LIGHTSHADER_H
#include "ShaderBase.h"
#include"ModelUtility.h"
#include"Light.h"
namespace aetherClass{
	class LightShader :
		public ShaderBase
	{
	public:
		LightShader();
		~LightShader();
		void SetLight(Light*);
	private:
		bool InitializeShader()override;
		void FinalizeShader()override;
		bool SetConstantBuffer()override;

		ID3D11Buffer* m_lightBuffer;
		Light *m_light;
	};
}

#endif