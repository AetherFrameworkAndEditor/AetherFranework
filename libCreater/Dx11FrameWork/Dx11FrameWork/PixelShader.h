#ifndef _PIXELSHADER_H
#define _PIXELSHADER_H

#include "ShaderBase.h"
namespace aetherClass{
	class  PixelShader :
		public ShaderBase
	{

	
	public:
		PixelShader();
		~PixelShader() = default;

	private:

		bool InitializeShader()override;
		void FinalizeShader()override;
		bool SetConstantBuffer()override;
	};


}

#endif