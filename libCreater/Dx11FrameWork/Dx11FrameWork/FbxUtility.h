/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxUtility.h
@brief     Fbx�̃T�|�[�g�֐�

*******************************************************************************
@date       2016/01/16
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _FBXUTILITY_H
#define _FBXUTILITY_H

#include <sstream>
#include <string>
#include <vector>
#ifndef _FBX_
#define _FBX_
#pragma comment (lib,"libfbxsdk-md.lib")
#endif
#include <fbxsdk.h>
#include "Vector3.h"
#include "Material.h"
#include "FbxMeshNode.h"

namespace aetherFunction{


	/*
	@brief          FbxDouble�^��Vector3�^�ɕϊ��p
	@param[in]      �ϊ�������FbxDouble�^
	@return         �ϊ����Vector3�^
	@exception      none
	*/
	static aetherClass::Vector3 FbxDoubleToVector3(FbxDouble3* copyData){
		aetherClass::Vector3 outData;
		outData._x = static_cast<float>(copyData->mData[0]);
		outData._y = static_cast<float>(copyData->mData[1]);
		outData._z = static_cast<float>(copyData->mData[2]);
		return outData;
	}

	/*
	@brief          FbxVector4�^��Vector3�^�ɕϊ��p
	@param[in]      �ϊ�������FbxVector4�^
	@return         �ϊ����Vector3�^
	@exception      none
	*/
	static aetherClass::Vector3 FbxVector4ToVector3(FbxVector4 input){
		aetherClass::Vector3 out;
		out._x = static_cast<float>(input[0]);
		out._y = static_cast<float>(input[1]);
		out._z = static_cast<float>(input[2]);
	
		return out;
	}

	/*
	@brief          FbxDouble3�^��Color�^�ɕϊ��p
	@param[in]      �ϊ�������FbxVector3�^
	@return         �ϊ����Color�^
	@exception      none
	*/
	static aetherClass::Color SetFbxColor(FbxDouble3 srcColor){
		aetherClass::Color color;
		color._red = static_cast<float>(srcColor[0]);
		color._green = static_cast<float>(srcColor[1]);
		color._blue = static_cast<float>(srcColor[2]);
		color._alpha = 1.0f;
		return color;
	}



	/*
	@brief          FbxMatrix�^��Matrix4x4�^�ɕϊ��p
	@param[out]     �ϊ���̎擾����Matrix4x4�^
	@param[in]      �ϊ�������FbxMatrix�^
	@return         none
	@exception      none
	*/
	static void FbxMatrixToMatrix4x4(aetherClass::Matrix4x4* output, FbxMatrix* src)
	{
		unsigned int nn = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				output->_matrix[i][j] = static_cast<float>(src->Get(i, j));
				nn++;
			}
		}
		return;
	}

	/*
	@brief          FbxAMatrix�^��Matrix4x4�^�ɕϊ��p
	@param[out]     �ϊ���̎擾����Matrix4x4�^
	@param[in]      �ϊ�������FbxMatrix�^
	@return         none
	@exception      none
	*/
	static aetherClass::Matrix4x4 FbxAMatrixToMatrix4x4(FbxAMatrix& src)
	{
		aetherClass::Matrix4x4 out = aetherClass::Matrix4x4(
			static_cast<float>(src.Get(0, 0)), static_cast<float>(src.Get(0, 1)), static_cast<float>(src.Get(0, 2)), static_cast<float>(src.Get(0, 3)),
			static_cast<float>(src.Get(1, 0)), static_cast<float>(src.Get(1, 1)), static_cast<float>(src.Get(1, 2)), static_cast<float>(src.Get(1, 3)),
			static_cast<float>(src.Get(2, 0)), static_cast<float>(src.Get(2, 1)), static_cast<float>(src.Get(2, 2)), static_cast<float>(src.Get(2, 3)),
			static_cast<float>(src.Get(3, 0)), static_cast<float>(src.Get(3, 1)), static_cast<float>(src.Get(3, 2)), static_cast<float>(src.Get(3, 3)));
		return out;
	}



	/*
	@brief          �S�Ẵ|���S�����O�p�`������
	@param[in]      �V�[������������FbxScene�^
	@param[in]      �O�p�`���������m�[�h
	@return         none
	@exception      none
	*/
	static void TriangulatedPolygons(FbxScene* scene, FbxNode* node){
		FbxNodeAttribute* lNodeAttribute = node->GetNodeAttribute();

		if (lNodeAttribute)
		{
			switch (lNodeAttribute->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
			case FbxNodeAttribute::eNurbs:
			case FbxNodeAttribute::eNurbsSurface:
			case FbxNodeAttribute::ePatch:
			{
				FbxGeometryConverter converter(node->GetFbxManager());

				// �ǂ�Ȍ`����O�p�`��
				converter.Triangulate(scene, true);

			}
			default:
				break;
			}
		}
		const int childCount = node->GetChildCount();

		for (int index = 0; index < childCount; ++index)
		{
			// �q�m�[�h��T��
			TriangulatedPolygons(scene, node->GetChild(index));
		}
		return;
	}

	/*
	@brief          �������w��̉ӏ���ŋ�؂�
	@param[in]      ��؂肽��������
	@param[in]      �Ȃ�����������
	@return         none
	@exception      none
	*/
	static std::string StringSplite(const std::string& fileFullPath, char spliteChar){
		std::vector<std::string> stringVector;
		std::stringstream string(fileFullPath);
		std::string buffer;
		while (std::getline(string, buffer, spliteChar))
		{

			stringVector.push_back(buffer);
		}
		const int charLastCount = stringVector.size() - 1;
		return stringVector[charLastCount];
	}

	/*
	@brief          �e�N�X�`���̓ǂݍ���
	@param[in]      �Ή��e�N�X�`��������e�f�B���N�g����
	@param[in]      �ǂݍ��ރ}�e���A������
	@return         none
	@exception      none
	@other          �܂��ꖇ�̉摜�����ǂݎ��Ȃ�
	*/
	static std::string GetMaterialTextureName(std::string directryName, aetherClass::MaterialElement& element){
		
		// ������Ή������Ȃ�
		if (element._texturePath.size() <= 0)
		{
			return "null";
		}
	
		const std::string referenceSprite = "\\";
		const std::string textureName = element._texturePath[0];
		std::string textureFilePath = directryName + referenceSprite + textureName;
		
		return textureFilePath;
	}

	/*
	@brief          string�^��wstring�ɕϊ�
	@param[in]      �ϊ�����string
	@return         �ϊ����wstring
	@exception      none
	*/
	static std::wstring StringToWString(std::string oString)
	{
		// SJIS �� wstring
		int bufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
			, -1, (wchar_t*)NULL, 0);

		// �o�b�t�@�̎擾
		wchar_t* cpUCS2 = new wchar_t[bufferSize];

		// SJIS �� wstring
		MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
			, bufferSize);

		// wstring�̐���
		std::wstring result(cpUCS2, cpUCS2 + bufferSize - 1);

		// �o�b�t�@�̔j��
		delete[] cpUCS2;

		// �ϊ����ʂ�Ԃ�
		return result;
	}
}

#endif

