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
		@brief          �L�[�t���[���A�j���[�V�����擾�p
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetKeyframeAnimation(FbxKeyframeAnimationInfo*, FbxImporter*, FbxScene*, FbxNode*);


	};
}
#endif