#ifndef _MATERIALSHADER_H
#define _MATERIALSHADER_H

#include"Light.h"
#include"ViewCamera.h"
#include "ShaderBase.h"
namespace aetherClass{
	class MaterialShader :
		public ShaderBase
	{
	public:
		MaterialShader();
		~MaterialShader();
		void SetLight(Light*);
		void SetCamera(ViewCamera* camera);

	private:
		bool InitializeShader()override;
		void FinalizeShader()override;
		bool SetConstantBuffer()override;
		

		ID3D11Buffer *m_lightBuffer ,*m_cameraBuffer;
		Light *m_light;
		ViewCamera *m_camera;
	private:
		struct CameraBuffer
		{
			Vector3 _Position;
			float Padding;
		};
	};

}

#endif