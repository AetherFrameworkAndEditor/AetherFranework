#include "FbxKeyFrameLoader.h"

using namespace aetherClass;
FbxKeyFrameLoader::FbxKeyFrameLoader()
{
}


FbxKeyFrameLoader::~FbxKeyFrameLoader()
{
}

void FbxKeyFrameLoader::GetKeyframeAnimation(FbxKeyframeAnimationInfo* anim, FbxScene* fbxScene, FbxNode* fbxNode){
	bool isAnimated = false;

	// �A�j���[�V�����̐����擾
	const int animationCount = fbxScene->GetSrcObjectCount(FbxAnimStack::ClassId);
	for (int animationIndex = 0; animationIndex < animationCount; ++animationIndex)
	{
		FbxAnimStack* animStack = (FbxAnimStack*)fbxScene->GetSrcObject(FbxAnimStack::ClassId, animationIndex);
		FbxAnimEvaluator* animEvaluator = fbxScene->GetAnimationEvaluator();

		// �A�j���[�V�����̖��O���擾
		std::string animationName = animStack->GetName();
		anim->_keyframeNameList.push_back(animationName);
		anim->_keyframeHash[animationName].Reset();
		// ���C���[�̐����擾
		const int layerCount = animStack->GetMemberCount();
		for (int layerIndex = 0; layerIndex < layerCount; ++layerIndex)
		{
			FbxAnimLayer* animationLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

			// �A�j���[�V�������C���[�̖��O���擾
			anim->_animationLayerName = animationLayer->GetName();
			FbxAnimCurve* translationCurve = fbxNode->LclTranslation.GetCurve(animationLayer);
			FbxAnimCurve* rotationCurve = fbxNode->LclRotation.GetCurve(animationLayer);
			FbxAnimCurve* scalingCurve = fbxNode->LclScaling.GetCurve(animationLayer);

			// �g�����X���[�V�����̎擾
			if (translationCurve != 0)
			{
				int keyCount = translationCurve->KeyGetCount();
				anim->_keyframeHash[animationName]._size = keyCount;
				for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
				{
					FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
					FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
					AnimationVector vector;
					vector._data._x = static_cast<float>(trancelate[0]);
					vector._data._y = static_cast<float>(trancelate[1]);
					vector._data._z = static_cast<float>(trancelate[2]);

					// �t���[������b�P�ʂŎ擾
					vector._frameSecounds = frameTime.GetSecondDouble();
					anim->_keyframeHash[animationName]._trancelation.push_back(vector);
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

				anim->_keyframeHash[animationName]._trancelation.push_back(vector);
			}

			// ���[�e�[�V�����̎擾
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

					// �t���[������b�P�ʂŎ擾
					vector._frameSecounds = frameTime.GetSecondDouble();
					anim->_keyframeHash[animationName]._rotation.push_back(vector);
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

				anim->_keyframeHash[animationName]._rotation.push_back(vector);
			}

			// �X�P�[�����O�̎擾
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

					// �t���[������b�P�ʂŎ擾
					vector._frameSecounds = frameTime.GetSecondDouble();

					anim->_keyframeHash[animationName]._scaling.push_back(vector);
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

				anim->_keyframeHash[animationName]._scaling.push_back(vector);
			}

		}
	}

	return;
}
