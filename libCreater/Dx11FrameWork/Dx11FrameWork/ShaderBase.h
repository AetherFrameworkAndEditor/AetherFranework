#ifndef _SHADERBASE_H
#define _SHADERBASE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ShaderBase.h
@brief     Shader�̊��N���X

*******************************************************************************
@date       2016/1/10
@author     ���q�a��
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
	@brief          �V�F�[�_�[�̏��̐ݒ� 
					srcFile,entryName �̂ݍŒ���K�v�Ȑݒ�
					�g���V�F�[�_�[�ɑΉ����镔����ݒ肵�Ă���
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
	typedef int shaderType;		//�ꎞ�I���}�����̂���


	class ShaderBase : public DirectXEntity
	{
	public:
		ShaderBase();
		virtual ~ShaderBase() = default;

		/*
		@brief          �V�F�[�_�[�̏������B
		@param[in]      �V�F�[�_�[���쐬����̂ɕK�v�ȏ��@�ڍׂ�ShaderDesc���Q�Ƃ��ꂽ��
		@param[in]      �g�p����V�F�[�_�[�̎�� enum�t���O���w�肷��
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool Initialize(const ShaderDesc& shaderDesc, shaderType shaderTypeFlags)final;

		/*
		@brief          �V�F�[�_�[�̏I�������B
		@param[in]		none
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual void Finalize()final;

		/*
		@brief          �o�^�������̕`�揈���BModelBase����Ă΂�邱�ƂɂȂ�
		@param[in]		IndexBuffer����擾����indexCount
		@param[in]		WorldMatrix
		@param[in]		ViewMatrix
		@param[in]		ProjectionMatrix
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool Render(int index, Matrix4x4, Matrix4x4, Matrix4x4)final;
		
	private:
		/*
		@brief          �ǉ�����o�b�t�@�[���A�ݒ肪����Όp��������ɋL�q���鏉��������
		@param[in]		none
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool InitializeShader() = 0;

		/*
		@brief          �ǉ�����o�b�t�@�[���A�ݒ肪����Όp��������ɋL�q���邻���̏I������
		@param[in]		none
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual void FinalizeShader() = 0;

		/*
		@brief          �ǉ�����o�b�t�@�[���A�ݒ肪����Όp��������ɋL�q����o�^����
						Render����Ă΂�Ă���̂œƎ���������������ꍇ�͂���
		@param[in]		none
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool SetConstantBuffer(){ return true; };

		/*
		@brief          VertexShader�ɓn���p�����[�^�[�̓o�^����������B
						bufferNumber = 0
		@param[in]		WorldMatrix
		@param[in]		ViewMatrix
		@param[in]		ProjectionMatrix
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool SetShaderParameters(Matrix4x4, Matrix4x4, Matrix4x4)final;

		/*
		@brief          �V�F�[�_�[�R���p�C�����̃G���[���t�@�C���ɏo�͂���B
		@param[in]		�G���[���b�Z�[�W
		@param[in]		�t�@�C����
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual void OutputShaderErrorMessage(ID3D10Blob*, std::wstring)final;

		/*
		@brief          �`�揈���A���ꂽ�V�F�[�_�[�͕K���g���悤�ɏo���Ă���B
		@param[in]		�f�o�C�X�R���e�L�X�g
		@param[in]		IndexCount
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual void RenderShader(ID3D11DeviceContext*, int index) final;

		/*
		@brief          �V�F�[�_�[�̏����������AInitialize����Ă΂��B
		@param[in]      �V�F�[�_�[���쐬����̂ɕK�v�ȏ��@�ڍׂ�ShaderDesc���Q�Ƃ��ꂽ��
		@param[in]      �g�p����V�F�[�_�[�̎�� enum�t���O���w�肷��
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool InitializeShaderBuffer(const ShaderDesc& shaderDesc, shaderType shaderTypeFlags)final;

		/*
		@brief          ��{�R���X�^���g�o�b�t�@�[�̏����������AInitialize����Ă΂��B
		@param[in]      none
		@return         ������ ture/���s�� false
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

