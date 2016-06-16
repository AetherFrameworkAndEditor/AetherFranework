#include "FbxKeyFrameLoader.h"
#include "FbxUtility.h"
#include <iostream>
using namespace aetherClass;
FbxKeyFrameLoader::FbxKeyFrameLoader()
{
}


FbxKeyFrameLoader::~FbxKeyFrameLoader()
{
}

void FbxKeyFrameLoader::GetKeyframeAnimation(FbxKeyframeAnimationInfo* anim, FbxImporter* importer, FbxScene* fbxScene, FbxNode* fbxNode){
	// アニメーションの数を取得
	const int animationNum = importer->GetAnimStackCount();
	for (int animationIndex = 0; animationIndex < animationNum; ++animationIndex)
	{
		FbxAnimEvaluator* animEvaluator = fbxScene->GetAnimationEvaluator();
		FbxTakeInfo* takeInfo = importer->GetTakeInfo(animationIndex);
		FbxAnimStack* animeStack = (FbxAnimStack*)fbxScene->GetSrcObject<FbxAnimStack>(animationIndex);

		fbxScene->SetCurrentAnimationStack(animeStack);
		// アニメーションの名前を取得
		std::string animationName = takeInfo->mName;
		
		FbxTime::EMode TimeMode = fbxScene->GetGlobalSettings().GetTimeMode();
		FbxTime TimeObject;
		TimeObject.SetTime(0, 0, 0, 1, 0, 0, TimeMode);

		auto offset = takeInfo->mImportOffset;
		auto startTime = takeInfo->mLocalTimeSpan.GetStart();
		auto stopTime = takeInfo->mLocalTimeSpan.GetStop();
		bool result = animeStack->BakeLayers(animEvaluator, startTime, stopTime, TimeObject);
		float start = (offset.Get() + startTime.Get());
		float stop = (offset.Get() + stopTime.Get()) / TimeObject.Get();
		auto flameAll = stop - start;

		// レイヤーの数を取得
		const int layerCount = animeStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < layerCount; ++layerIndex)
		{

			FbxAnimLayer* animationLayer = (FbxAnimLayer*)animeStack->GetMember(layerIndex);

			// アニメーションレイヤーの名前を取得
			anim->_animationLayerName = animationLayer->GetName();
			anim->_initMatrix = aetherFunction::FbxAMatrixToMatrix4x4(fbxNode->EvaluateGlobalTransform());
	
			FbxNode* parent = fbxNode->GetParent();
			if (parent){
				anim->_parentMatrix = aetherFunction::FbxAMatrixToMatrix4x4(parent->EvaluateLocalTransform());
			}
			
			for (int keyIndex = 0; keyIndex < (int)flameAll; ++keyIndex)
			{
				FbxTime frameTime = keyIndex*TimeObject.Get();
				auto matrix = fbxNode->EvaluateGlobalTransform(frameTime);
				anim->_keyframeHash[animationName].push_back(aetherFunction::FbxAMatrixToMatrix4x4(matrix));
			}
		}
		anim->_keyframeHash[animationName].shrink_to_fit();
	}
	return;
}
