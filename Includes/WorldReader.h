/******************************************************************************/
/*! @addtogroup aetherClass
@file      WorldReader.h
@brief     独自形式ファイル読み込み用クラス。エディターとの連携用

*******************************************************************************
@date       2016/3/7
@author     橋木航
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _WORLDREADER_H
#define _WORLDREADER_H
#include <string>
#include "World.h"
class WorldReader
{
public:
	WorldReader();
	~WorldReader();

	/*
	@brief          Editorで作成された独自ファイルの読み込み(読み込めるファイル：*.aether)
	@param[in]      ファイル名。
	@return         生成完了　true/失敗 false
	*/
	bool Load(std::string);

	/*
	@brief          Loadで読み取った情報を扱うための関数
	@param[out]     World構造体変数    
	@return			none
	*/
	World GetInputWorldInfo();

	/*
	@brief          読み込んだ情報すべての破棄用
	@param          none
	@return			none
	*/
	void UnLoad();

	/*
	@brief          読み込んだテクスチャ情報の破棄用
	@param          none
	@return			none
	*/
	void UnLoadTexture();

	/*
	@brief          読み込んだオブジェクト情報の破棄用
	@param          none
	@return			none
	*/
	void UnLoadObject();

	/*
	@brief          読み込んだマテリアル情報の破棄用
	@param          none
	@return			none
	*/
	void UnLoadMaterial();
private:
	World m_world;
	std::vector<std::string> m_input;
	std::string m_tag;
private:
	std::string GetExtension(const std::string path);
	void GetObjectInfo(std::string);
	void GetMaterialInfo(std::string);
	void GetCameraInfo(std::string);
	void GetTextureInfo(std::string);
	void GetLightInfo(std::string);
};

#endif