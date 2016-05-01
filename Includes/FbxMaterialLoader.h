#ifndef _FBXMATERIALLOADER_H
#define _FBXMATERIALLOADER_H
#include <fbxsdk.h>
#include "FbxMeshNode.h"
namespace aetherClass{
	class FbxMaterialLoader
	{
	public:
		FbxMaterialLoader();
		~FbxMaterialLoader();

		/*
		@brief          �}�e���A������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetMaterial(FbxMeshNode* meshNode, FbxMesh*);

	private:
		/*
		@brief          �}�e���A�������擾
		@param[in]		FbxSurfaceMaterial�^�I�u�W�F�N�g
		@param[out]     Material�^�̃I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void CopyMaterialData(FbxSurfaceMaterial*, Material*);

		/*
		@brief          �}�e���A���̏ڍ׏����擾
		@param[in]		FbxSurfaceMaterial�^�I�u�W�F�N�g
		@param[in]      �}�e���A����ނ̖��O
		@param[in]      �}�e���A����ނ̖��O
		@param[out]     �擾�������I�u�W�F�N�g
		@return         �J���[����Ԃ�
		@exception      none
		*/
		FbxDouble3 GetMaterialPropertey(
			const FbxSurfaceMaterial* material,
			std::string propertyName,
			std::string factorPropertyName,
			MaterialElement* element);

		/*
		@brief          �m�[�h���Ƃ̍s��擾�p
		@param[out]		FbxMeshNode�^�I�u�W�F�N�g
		@param[in]      FbxNode�^�I�u�W�F�N�g
		@param[in]      FbxScene�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void ComputeNodeMatrix(FbxMeshNode* meshNode, FbxNode* node, FbxScene* scene);
	};
}
#endif