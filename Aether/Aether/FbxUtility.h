/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxUtility.h
@brief     Fbxのサポート関数

*******************************************************************************
@date       2016/01/16
@author     橋本航
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
	@brief          FbxDouble型をVector3型に変換用
	@param[in]      変換したいFbxDouble型
	@return         変換後のVector3型
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
	@brief          FbxVector4型をVector3型に変換用
	@param[in]      変換したいFbxVector4型
	@return         変換後のVector3型
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
	@brief          FbxDouble3型をColor型に変換用
	@param[in]      変換したいFbxVector3型
	@return         変換後のColor型
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
	@brief          FbxMatrix型をMatrix4x4型に変換用
	@param[out]     変換後の取得するMatrix4x4型
	@param[in]      変換したいFbxMatrix型
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
	@brief          FbxAMatrix型をMatrix4x4型に変換用
	@param[out]     変換後の取得するMatrix4x4型
	@param[in]      変換したいFbxMatrix型
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
	@brief          全てのポリゴンを三角形化する
	@param[in]      シーン情報を持ったFbxScene型
	@param[in]      三角形化したいノード
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

				// どんな形状も三角形化
				converter.Triangulate(scene, true);

			}
			default:
				break;
			}
		}
		const int childCount = node->GetChildCount();

		for (int index = 0; index < childCount; ++index)
		{
			// 子ノードを探索
			TriangulatedPolygons(scene, node->GetChild(index));
		}
		return;
	}

	/*
	@brief          文字を指定の箇所場で区切る
	@param[in]      区切りたい文字列
	@param[in]      なくしたい文字
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
	@brief          テクスチャの読み込み
	@param[in]      対応テクスチャがある親ディレクトリ名
	@param[in]      読み込むマテリアル属性
	@return         none
	@exception      none
	@other          まだ一枚の画像しか読み取らない
	*/
	static std::string GetMaterialTextureName(std::string directryName, aetherClass::MaterialElement& element){
		
		// 無ければ何もしない
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
	@brief          string型をwstringに変換
	@param[in]      変換するstring
	@return         変換後のwstring
	@exception      none
	*/
	static std::wstring StringToWString(std::string oString)
	{
		// SJIS → wstring
		int bufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
			, -1, (wchar_t*)NULL, 0);

		// バッファの取得
		wchar_t* cpUCS2 = new wchar_t[bufferSize];

		// SJIS → wstring
		MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
			, bufferSize);

		// wstringの生成
		std::wstring result(cpUCS2, cpUCS2 + bufferSize - 1);

		// バッファの破棄
		delete[] cpUCS2;

		// 変換結果を返す
		return result;
	}
}

#endif

