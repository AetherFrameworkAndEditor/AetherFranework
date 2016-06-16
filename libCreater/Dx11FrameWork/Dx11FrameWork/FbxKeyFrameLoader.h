#ifndef _FBXKEYFRAMELOADER_H
#define _FBXKEYFRAMELOADER_H
#include "FbxKeyFrameAnimationInfo.h"
#include <fbxsdk.h>
namespace aetherClass{
	class FbxKeyFrameLoader
	{
	public:
		FbxKeyFrameLoader();
		~FbxKeyFrameLoader();

		/*
		@brief          キーフレームアニメーション取得用
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetKeyframeAnimation(FbxKeyframeAnimationInfo*, FbxImporter*, FbxScene*, FbxNode*);


	};
}
#endif