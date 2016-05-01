#include "FbxKeyFrameLoader.h"

using namespace aetherClass;
FbxKeyFrameLoader::FbxKeyFrameLoader()
{
}


FbxKeyFrameLoader::~FbxKeyFrameLoader()
{
}

FbxKeyframeAnimationInfo FbxKeyFrameLoader::GetKeyframeAnimation(FbxScene* fbxScene, FbxNode* fbxNode){
	bool isAnimated = false;
	FbxKeyframeAnimationInfo outInfomation;

	// アニメーションの数を取得
	const int animationCount = fbxScene->GetSrcObjectCount(FbxAnimStack::ClassId);
	for (int animationIndex = 0; animationIndex < animationCount; ++animationIndex)
	{
		FbxAnimStack* animStack = (FbxAnimStack*)fbxScene->GetSrcObject(FbxAnimStack::ClassId, animationIndex);
		FbxAnimEvaluator* animEvaluator = fbxScene->GetAnimationEvaluator();

		// アニメーションの名前を取得
		outInfomation._animationName = animStack->GetName();

		// レイヤーの数を取得
		const int layerCount = animStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < layerCount; ++layerIndex)
		{
			FbxAnimLayer* animationLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

			// アニメーションレイヤーの名前を取得
			outInfomation._animationLayerName = animationLayer->GetName();

			FbxAnimCurve* translationCurve = fbxNode->LclTranslation.GetCurve(animationLayer);
			FbxAnimCurve* rotationCurve = fbxNode->LclRotation.GetCurve(animationLayer);
			FbxAnimCurve* scalingCurve = fbxNode->LclScaling.GetCurve(animationLayer);

			// トランスレーションの取得
			if (translationCurve != 0)
			{
				int keyCount = translationCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
				{
					FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
					FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
					AnimationVector vector;
					vector._data._x = static_cast<float>(trancelate[0]);
					vector._data._y = static_cast<float>(trancelate[1]);
					vector._data._z = static_cast<float>(trancelate[2]);

					// フレーム数を秒単位で取得
					vector._frameSecounds = frameTime.GetSecondDouble();
					outInfomation._trancelation.push_back(vector);
				}
			}
			else
			{
				FbxDouble3 translation = fbxNode->LclTranslation.Get();
				AnimationVector vector;

				vector._data._x = static_cast<float>(translation[0]);
				vector._data._y = static_cast<float>(translation[1]);
				vector._data._z = static_cast<float>(translation[2]);
				vector._frameSecounds = 0;

				outInfomation._trancelation.push_back(vector);
			}

			// ローテーションの取得
			if (rotationCurve != 0)
			{
				int keyCount = rotationCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
				{
					FbxTime frameTime = rotationCurve->KeyGetTime(keyIndex);
					FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
					AnimationVector vector;
					vector._data._x = static_cast<float>(trancelate[0]);
					vector._data._y = static_cast<float>(trancelate[1]);
					vector._data._z = static_cast<float>(trancelate[2]);

					// フレーム数を秒単位で取得
					vector._frameSecounds = frameTime.GetSecondDouble();
					outInfomation._rotation.push_back(vector);
				}
			}
			else
			{
				FbxDouble3 translation = fbxNode->LclRotation.Get();
				AnimationVector vector;

				vector._data._x = static_cast<float>(translation[0]);
				vector._data._y = static_cast<float>(translation[1]);
				vector._data._z = static_cast<float>(translation[2]);
				vector._frameSecounds = 0;

				outInfomation._rotation.push_back(vector);
			}

			// スケーリングの取得
			if (scalingCurve != 0)
			{
				int keyCount = scalingCurve->KeyGetCount();
				for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
				{
					FbxTime frameTime = scalingCurve->KeyGetTime(keyIndex);
					FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
					AnimationVector vector;
					vector._data._x = static_cast<float>(trancelate[0]);
					vector._data._y = static_cast<float>(trancelate[1]);
					vector._data._z = static_cast<float>(trancelate[2]);

					// フレーム数を秒単位で取得
					vector._frameSecounds = frameTime.GetSecondDouble();
					outInfomation._scaling.push_back(vector);
				}
			}
			else
			{
				FbxDouble3 scaling = fbxNode->LclScaling.Get();
				AnimationVector vector;

				vector._data._x = static_cast<float>(scaling[0]);
				vector._data._y = static_cast<float>(scaling[1]);
				vector._data._z = static_cast<float>(scaling[2]);
				vector._frameSecounds = 0;

				outInfomation._scaling.push_back(vector);
			}

		}
	}

	return outInfomation;
}
