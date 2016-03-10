/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxUtility.h
@brief     Fbx‚ÌƒTƒ|[ƒgŠÖ”

*******************************************************************************
@date       2016/01/16
@author     ‹´–{q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/01/16 14:53 ‹´–{q
-# Initial Version
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
	@brief          FbxDoubleŒ^‚ğVector3Œ^‚É•ÏŠ·—p
	@param[in]      •ÏŠ·‚µ‚½‚¢FbxDoubleŒ^
	@return         •ÏŠ·Œã‚ÌVector3Œ^
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
	@brief          FbxVector4Œ^‚ğVector3Œ^‚É•ÏŠ·—p
	@param[in]      •ÏŠ·‚µ‚½‚¢FbxVector4Œ^
	@return         •ÏŠ·Œã‚ÌVector3Œ^
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
	@brief          FbxDouble3Œ^‚ğColorŒ^‚É•ÏŠ·—p
	@param[in]      •ÏŠ·‚µ‚½‚¢FbxVector3Œ^
	@return         •ÏŠ·Œã‚ÌColorŒ^
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
	@brief          FbxMatrixŒ^‚ğMatrix4x4Œ^‚É•ÏŠ·—p
	@param[out]     •ÏŠ·Œã‚Ìæ“¾‚·‚éMatrix4x4Œ^
	@param[in]      •ÏŠ·‚µ‚½‚¢FbxMatrixŒ^
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
	@brief          FbxAMatrixŒ^‚ğMatrix4x4Œ^‚É•ÏŠ·—p
	@param[out]     •ÏŠ·Œã‚Ìæ“¾‚·‚éMatrix4x4Œ^
	@param[in]      •ÏŠ·‚µ‚½‚¢FbxMatrixŒ^
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
	@brief          ‘S‚Ä‚Ìƒ|ƒŠƒSƒ“‚ğOŠpŒ`‰»‚·‚é
	@param[in]      ƒV[ƒ“î•ñ‚ğ‚Á‚½FbxSceneŒ^
	@param[in]      OŠpŒ`‰»‚µ‚½‚¢ƒm[ƒh
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

				// ‚Ç‚ñ‚ÈŒ`ó‚àOŠpŒ`‰»
				converter.Triangulate(scene, true);

			}
			default:
				break;
			}
		}
		const int childCount = node->GetChildCount();

		for (int index = 0; index < childCount; ++index)
		{
			// qƒm[ƒh‚ğ’Tõ
			TriangulatedPolygons(scene, node->GetChild(index));
		}
		return;
	}

	/*
	@brief          •¶š‚ğw’è‚Ì‰ÓŠê‚Å‹æØ‚é
	@param[in]      ‹æØ‚è‚½‚¢•¶š—ñ
	@param[in]      ‚È‚­‚µ‚½‚¢•¶š
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
	@brief          ƒeƒNƒXƒ`ƒƒ‚Ì“Ç‚İ‚İ
	@param[in]      ‘Î‰ƒeƒNƒXƒ`ƒƒ‚ª‚ ‚éeƒfƒBƒŒƒNƒgƒŠ–¼
	@param[in]      “Ç‚İ‚Şƒ}ƒeƒŠƒAƒ‹‘®«
	@return         none
	@exception      none
	@other          ‚Ü‚¾ˆê–‡‚Ì‰æ‘œ‚µ‚©“Ç‚İæ‚ç‚È‚¢
	*/
	static std::string GetMaterialTextureName(std::string directryName, aetherClass::MaterialElement& element){
		
		// –³‚¯‚ê‚Î‰½‚à‚µ‚È‚¢
		if (element._texturePath.size() <= 0)
		{
			return "null";
		}
	
		const std::string referenceSprite = "\\";
		const std::string textureName = element._texturePath[0];
		std::string textureFilePath = directryName + referenceSprite + textureName;
		
		return textureFilePath;
	}


}

#endif

