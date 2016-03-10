#ifndef _QUATERNION_H
#define _QUATERNION_H
#include "Vector3.h"
#include "Matrix4x4.h"
namespace aetherClass{
	class Quaternion
	{

	public:
		float _x, _y, _z, _w;

		static const Quaternion _identity; // �P�ʃN�H�[�^�j�I��
	public:
		Quaternion();

		/*
		@brief          �w��v�f�ŏ�����
		@param[in]      x����
		@param[in]      y����
		@param[in]      z����
		@param[in]      w����
		@return         none
		@exception      none
		*/
		Quaternion(const float x,const float y,const float z,const float w);

		/*
		@brief          ��]���Ɖ�]�p�x���w�肵�ď�����
		@param[in]      ��]��
		@param[in]      �p�x
		@return         none
		@exception      none
		*/
		Quaternion(const Vector3,const float radian);

		~Quaternion();

	public:

		/*
		@brief          �e�v�f�ɒl��ݒ�
		@param[in]      x����
		@param[in]      y����
		@param[in]      z����
		@param[in]      w����
		@return         none
		@exception      none
		*/
		void SetElement(const float x, const float y, const float z, const float w);

		/*
		@brief          ���̃N�H�[�^�j�I���̒�����Ԃ�
		@param[in]      none
		@return         ����
		@exception      none
		*/
		float GetLength()const;

		/*
		@brief          ���̃N�H�[�^�j�I���̒����̓���Ԃ�
		@param[in]      none
		@return         �����̓��
		@exception      none
		*/
		float GetLengthSquared()const;

		/*
		@brief          ���̃N�H�[�^�j�I���𐳋K������
		@param[in]      none
		@return         none
		@exception      none
		*/
		Quaternion Normalize();

		/*
		@brief          ���̃N�H�[�^�j�I�����P�ʃN�H�[�^�j�I���ł��邩�̔���
		@param[in]      none
		@return         �P�ʃN�H�[�^�j�I���ł���F true/ �P�ʃN�H�[�^�j�I���ł͂Ȃ��F false 
		@exception      none
		*/
		bool isIdentity();

		/*
		@brief          �����̃N�H�[�^�j�I���Ƃ̏�Z���s��
		@param[in]      ��Z����N�H�[�^�j�I�� 
		@return         none
		@exception      none
		*/
		Quaternion Multiply(const Quaternion&);

		/*
		@brief          ���̃N�H�[�^�j�I����X���ŉ�]����
		@param[in]      ��]����p�x
		@return         none
		@exception      none
		*/
		void RotationByX(const float);

		/*
		@brief          ���̃N�H�[�^�j�I����Y���ŉ�]����
		@param[in]      ��]����p�x
		@return         none
		@exception      none
		*/
		void RotationByY(const float);

		/*
		@brief          ���̃N�H�[�^�j�I����Z���ŉ�]����
		@param[in]      ��]����p�x
		@return         none
		@exception      none
		*/
		void RotationByZ(const float);

		
		/*
		@brief          ���̃N�H�[�^�j�I�������Ƃɉ�]�s����쐬
		@param[in]      none
		@return         none
		@exception      none
		*/
		Matrix4x4 Matrix4x4FromQuaternion();
	};
}
#endif