#ifndef _MATRIX4X4_H
#define _MATRIX4X4_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Matrix4x4.h
@brief     4x4�̍s��N���X

*******************************************************************************
@date       2016/1/6
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include<DirectXMath.h>
#include"Vector3.h"
#include"Vector4.h"

namespace aetherClass{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const float* arr,unsigned int arraysize);
		Matrix4x4(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44	);
		~Matrix4x4();
		
		/*
		@brief          ���̍s���P�ʍs��ɂ���
		@param          none

		@return         none
		@exception      none
		*/
		void Identity();


		/*
		@brief          ���̍s���P�ʍs��ŁA3�s3��߂����}�C�i�X�l�ɂ���B
		                ���̍s����|�����킹�邱�ƂŉE��n������n�ɕϊ��ł���
		@param          none

		@return         none
		@exception      none
		*/
		void RightToLeftIdentity();


		/*
		@brief          ���̍s����t�s��ɂ���
		@param          none

		@return         none
		@exception      none
		*/
		void Inverse();

		/*
		@brief          ���̍s���]�u�s��ɂ���
		@param          none

		@return         none
		@exception      none
		*/
		void Transpose();

		/*
		@brief          ���̍s����ړ��s��ɂ���
		@param			xyz�̈ړ��v�f

		@return         none
		@exception      none
		*/
		void TranslateMatrix(Vector3 translate);

		/*
		@brief          ���̍s����g��k���s��ɂ���
		@param			xyz�̗v�f

		@return         none
		@exception      none
		*/
		void ScaliMatrix(Vector3 scaling);

		/*
		@brief          ���̍s����w�����̉�]�s��ɂ���
		@param			�p�x�iradian�j

		@return         none
		@exception      none
		*/
		void RotationAxisX(float rotation);

		/*
		@brief          ���̍s����x�����̉�]�s��ɂ���
		@param			�p�x�iradian�j

		@return         none
		@exception      none
		*/
		void RotationAxisY(float rotation);

		/*
		@brief          ���̍s����y�����̉�]�s��ɂ���
		@param			�p�x�iradian�j

		@return         none
		@exception      none
		*/
		void RotationAxisZ(float rotation);

		/*
		@brief          ���̍s���Euler�p�n�̉�]�s��ɂ���
		@param			�p�x�iradian�jx,y,z

		@return         none
		@exception      none
		*/
		void RotationMatrix(Vector3 rotation);

		/*
		@brief          ���̍s���YawPitchRoll�̉�]�s��ɂ���
		@param			�p�x�iradian�jx,y,z

		@return         none
		@exception      none
		*/
		void PitchYawRoll(Vector3 rotation);

		/*
		@brief          ���̍s���ʂ̍s��Ɗ|�����킹��
		@param			�|�����킹��s��

		@return         �|�����킳�ꂽ�s��
		@exception      none
		*/
		Matrix4x4 Multiply(Matrix4x4 matrix);


		/*
		@brief          ����n�̃X�N���[���ϊ��s��@����p�𗘗p
		@param			����p
		@param			�A�X�y�N�g��
		@param			�߃N���b�v�ʂ̋���
		@param			���N���b�v�ʂ̋���

		@return         none
		@exception      none
		*/
		void PerspectiveFovLH(float fov, float aspect, float zNear, float zFar);
		/*
		@brief          �E��n�̃X�N���[���ϊ��s��@����p�𗘗p
		@param			����p
		@param			�A�X�y�N�g��
		@param			�߃N���b�v�ʂ̋���
		@param			���N���b�v�ʂ̋���

		@return         none
		@exception      none
		*/
		void PerspectiveFovRH(float fov, float aspect, float zNear, float zFar);
		
		/*
		@brief          ����n�̃X�N���[���ϊ��s��@�߃N���b�v�ʂ̕��𗘗p
		@param			��
		@param			����
		@param			�߃N���b�v�ʂ̋���
		@param			���N���b�v�ʂ̋���

		@return         none
		@exception      none
		*/
		void PerspectiveLH(float width,float height,float zNear, float zFar);
		/*
		@brief          �E��n�̃X�N���[���ϊ��s��@�߃N���b�v�ʂ̕��𗘗p
		@param			��
		@param			����
		@param			�߃N���b�v�ʂ̋���
		@param			���N���b�v�ʂ̋���

		@return         none
		@exception      none
		*/
		void PerspectiveRH(float width, float height, float zNear, float zFar);

		/*
		@brief          ����n�̃X�N���[���ϊ��s��@z�𗘗p�����傫�������̂܂ܕ\���ł���
		@param			��
		@param			����
		@param			�߃N���b�v�ʂ̋���
		@param			���N���b�v�ʂ̋���

		@return         none
		@exception      none
		*/
		void OrthoLH(float width, float height, float zNear, float zFar);
		/*
		@brief          �E��n�̃X�N���[���ϊ��s��@z�𗘗p�����傫�������̂܂ܕ\���ł���
		@param			��
		@param			����
		@param			�߃N���b�v�ʂ̋���
		@param			���N���b�v�ʂ̋���

		@return         none
		@exception      none
		*/
		void OrthoRH(float width, float height, float zNear, float zFar);
	
		/*
		@brief          ����n�̃r���[�ϊ��s��
		@param			�ʒu
		@param			�����_
		@param			�J�����̏����

		@return         none
		@exception      none
		*/
		void LookAtLH(Vector3 pos, Vector3 lookat, Vector3 up);

		public:
		union{
			struct{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float _matrix[4][4];
		};
	public:
		Matrix4x4 operator +();
		Matrix4x4 operator -();

		Matrix4x4 operator +(Matrix4x4);
		Matrix4x4 operator -(Matrix4x4);
		Matrix4x4 operator *(Matrix4x4);
		Vector4 operator *(Vector4);
		Vector3 operator *(Vector3);

		Matrix4x4 operator +(float);
		Matrix4x4 operator -(float);
		Matrix4x4 operator *(float);
		Matrix4x4 operator /(float);

		void operator +=(Matrix4x4);
		void operator -=(Matrix4x4);
		void operator *=(Matrix4x4);

		void operator +=(float);
		void operator -=(float);
		void operator *=(float);
		void operator /=(float);

	};
};
#endif