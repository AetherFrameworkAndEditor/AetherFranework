/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxBoneInfo.h
@brief     Fbx����̃{�[�������擾����\���̌Q

*******************************************************************************
@date       2015/01/30
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _FBXBONEINFO_H
#define _FBXBONEINFO_H

#ifndef _FBX_
#define _FBX_
#pragma comment (lib,"libfbxsdk-md.lib")
#endif
#include <fbxsdk.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Matrix4x4.h"

#include "SkeletonInfo.h"
namespace{
	const int kMaxBoneImpactCount = 8;
}
namespace aetherClass{
	// �{�[�����
	struct BoneInfo{
		std::string _name;   // �{�[����
		unsigned int _frameCount;   // �t���[����
		Matrix4x4 _initialMatrix;   // �����p���s��
		std::vector<Matrix4x4> _frameMatrix;   // �t���[�����p���s��
	};

	// �{�[���̉e�����
	struct BoneImpactInfo{
		unsigned int _index;         // ���_�̃C���f�b�N�X
		unsigned int _impactCount;    // �e����
		unsigned int _boneIndex[kMaxBoneImpactCount];
		float _weight[kMaxBoneImpactCount];    // �E�F�C�g

		// �ǉ��֐�
		bool addBoneImpact(unsigned int boneIndex, float weight){
			if (_impactCount >= kMaxBoneImpactCount)
			{
				return false;
			}

			_boneIndex[_impactCount] = boneIndex;
			_weight[_impactCount] = weight;

			_impactCount += 1;

			return true;
		}

		friend bool operator ==(const BoneImpactInfo& src0, const BoneImpactInfo& src1) {
			if (src0._boneIndex == src1._boneIndex) {
				return true;
			}
			return false;
		}

		friend bool operator !=(const BoneImpactInfo& src0, const BoneImpactInfo& src1) {
			if (src0._boneIndex != src1._boneIndex) {
				return true;
			}
			return false;
		}

		friend bool operator <(const BoneImpactInfo& src0, const BoneImpactInfo& src1) {
			if (src0._boneIndex < src1._boneIndex) {
				return true;
			}
			return false;
		}


	};

	// �{�[�����Ǘ��N���X
	struct SkinInfo{
		int		_clusterCount;		// �N���X�^��
		std::set<BoneImpactInfo> _boneImpactInfoSet;	// �{�[���e�����Z�b�g
		std::vector<BoneInfo>		_boneInfoAry;	// �{�[�����z��
		
	};
}
#endif