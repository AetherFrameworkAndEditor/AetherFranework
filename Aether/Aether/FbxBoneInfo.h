/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxBoneInfo.h
@brief     Fbxからのボーン情報を取得する構造体群

*******************************************************************************
@date       2015/01/30
@author     橋本航
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
	// ボーン情報
	struct BoneInfo{
		std::string _name;   // ボーン名
		unsigned int _frameCount;   // フレーム数
		Matrix4x4 _initialMatrix;   // 初期姿勢行列
		std::vector<Matrix4x4> _frameMatrix;   // フレーム時姿勢行列
	};

	// ボーンの影響情報
	struct BoneImpactInfo{
		unsigned int _index;         // 頂点のインデックス
		unsigned int _impactCount;    // 影響数
		unsigned int _boneIndex[kMaxBoneImpactCount];
		float _weight[kMaxBoneImpactCount];    // ウェイト

		// 追加関数
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

	// ボーン情報管理クラス
	struct SkinInfo{
		int		_clusterCount;		// クラスタ数
		std::set<BoneImpactInfo> _boneImpactInfoSet;	// ボーン影響情報セット
		std::vector<BoneInfo>		_boneInfoAry;	// ボーン情報配列
		
	};
}
#endif