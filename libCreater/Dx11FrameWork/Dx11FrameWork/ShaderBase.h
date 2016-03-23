#ifndef _SHADERBASE_H
#define _SHADERBASE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ShaderBase.h
@brief     Shaderの基底クラス

*******************************************************************************
@date       2016/1/10
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#include<string>
#include"DirectXEntity.h"
#include"Matrix4x4.h"

#include<D3DX11async.h>
namespace aetherClass{
	/*
	@brief          シェーダーの情報の設定 
					srcFile,entryName のみ最低限必要な設定
					使うシェーダーに対応する部分を設定していく
	*/
	struct ShaderDesc
	{
		ShaderDesc(){
			_vertex._shaderModel = "vs_5_0";
			_pixel._shaderModel = "ps_5_0";
			_geometry._shaderModel = "gs_5_0";
			_hull._shaderModel = "hs_5_0";
			_domain._shaderModel = "ds_5_0";
			_compute._shaderModel = "cs_5_0";
		}
		struct Shader{
			Shader(){
				SecureZeroMemory(this, sizeof(Shader));
				_shaderCompileFlags = D3D10_SHADER_ENABLE_STRICTNESS;
			}
			std::wstring _srcFile;
			CONST D3D10_SHADER_MACRO *_pDefines;
			LPD3D10INCLUDE _pInclude;
			std::string _entryName;
			std::string _shaderModel;
			UINT _shaderCompileFlags;
			UINT _effectCompileFlags;
			ID3DX11ThreadPump *_pPump;
		};
		Shader _vertex;
		Shader _pixel;
		Shader _geometry;
		Shader _hull;
		Shader _domain;
		Shader _compute;
	};

	enum ShaderType{
		eVertex = 0x0001,
		ePixel = 0x0002,
		eGeometry = 0x0004,
		eHull = 0x0008,
		eDomain = 0x0010,
		eCompute = 0x0020,
	};
	typedef int shaderType;		//一時的応急処理のため


	class ShaderBase : public DirectXEntity
	{
	public:
		ShaderBase();
		virtual ~ShaderBase() = default;

		/*
		@brief          シェーダーの初期化。
		@param[in]      シェーダーを作成するのに必要な情報　詳細はShaderDescを参照されたし
		@param[in]      使用するシェーダーの種類 enumフラグを指定する
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool Initialize(const ShaderDesc& shaderDesc, shaderType shaderTypeFlags)final;

		/*
		@brief          シェーダーの終了処理。
		@param[in]		none
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual void Finalize()final;

		/*
		@brief          登録した情報の描画処理。ModelBaseから呼ばれることになる
		@param[in]		IndexBufferから取得したindexCount
		@param[in]		WorldMatrix
		@param[in]		ViewMatrix
		@param[in]		ProjectionMatrix
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool Render(int index, Matrix4x4, Matrix4x4, Matrix4x4)final;
		
	private:
		/*
		@brief          追加するバッファー等、設定があれば継承した後に記述する初期化処理
		@param[in]		none
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool InitializeShader() = 0;

		/*
		@brief          追加するバッファー等、設定があれば継承した後に記述するそれらの終了処理
		@param[in]		none
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual void FinalizeShader() = 0;

		/*
		@brief          追加するバッファー等、設定があれば継承した後に記述する登録処理
						Renderから呼ばれているので独自処理を実装する場合はここ
		@param[in]		none
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool SetConstantBuffer(){ return true; };

		/*
		@brief          VertexShaderに渡すパラメーターの登録処理をする。
						bufferNumber = 0
		@param[in]		WorldMatrix
		@param[in]		ViewMatrix
		@param[in]		ProjectionMatrix
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool SetShaderParameters(Matrix4x4, Matrix4x4, Matrix4x4)final;

		/*
		@brief          シェーダーコンパイル時のエラーをファイルに出力する。
		@param[in]		エラーメッセージ
		@param[in]		ファイル名
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual void OutputShaderErrorMessage(ID3D10Blob*, std::wstring)final;

		/*
		@brief          描画処理、作られたシェーダーは必ず使うように出来ている。
		@param[in]		デバイスコンテキスト
		@param[in]		IndexCount
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual void RenderShader(ID3D11DeviceContext*, int index) final;

		/*
		@brief          シェーダーの初期化処理、Initializeから呼ばれる。
		@param[in]      シェーダーを作成するのに必要な情報　詳細はShaderDescを参照されたし
		@param[in]      使用するシェーダーの種類 enumフラグを指定する
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool InitializeShaderBuffer(const ShaderDesc& shaderDesc, shaderType shaderTypeFlags)final;

		/*
		@brief          基本コンスタントバッファーの初期化処理、Initializeから呼ばれる。
		@param[in]      none
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool InitializeConstantBuffer() final;
	private:
		struct MatrixBuffer
		{
			Matrix4x4 _world;
			Matrix4x4 _view;
			Matrix4x4 _projection;
		};

	private:
		ID3D11VertexShader*		m_vertexShader;
		ID3D11PixelShader*		m_pixelShader;
		ID3D11GeometryShader*	m_geometryShader;
		ID3D11ComputeShader*	m_computeShader;
		ID3D11HullShader*		m_hullShader;
		ID3D11DomainShader*		m_domainShader;
		ID3D11InputLayout* m_layout;

		ID3D11Buffer*	m_matrixBuffer;
	};
}

#endif

