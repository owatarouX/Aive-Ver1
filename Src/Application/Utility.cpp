#include "Utility.h"

//�l�ӂ̓����蔻��`�F�b�N
//����������true��false��Ԃ�
bool Utility::bHitCheck(Math::Vector2 aScrPos, Math::Vector2 aScrMove, Math::Vector2 aDestPos, 
	float aScrRad_Left, float aScrRad_Right, float aScrRad_Top, float aScrRad_Bottom,
	float aDesRad_Left, float aDesRad_Right, float aDesRad_Top, float aDesRad_Bottom)
{
	//�L����1�̌��ݍ��W�̎l��
	const float aScrLeft = aScrPos.x - aScrRad_Left;		//����
	const float aScrRight = aScrPos.x + aScrRad_Right;		//�E��
	const float aScrTop = aScrPos.y + aScrRad_Top;			//���
	const float aScrBottom = aScrPos.y - aScrRad_Bottom;	//����

	//�L����1�̖������W�̎l��
	const float nextLeft = aScrLeft + aScrMove.x;				//����
	const float nextRight = aScrRight + aScrMove.x;			//�E��
	const float nextTop = aScrTop + aScrMove.y;				//���
	const float nextBottom = aScrBottom + aScrMove.y;			//����

	//�L����2�̌��ݍ��W�̎l��
	const float aDestLeft = aDestPos.x - aDesRad_Left;	//����
	const float aDestRight = aDestPos.x + aDesRad_Right;	//�E��
	const float aDestTop = aDestPos.y + aDesRad_Top;	//���
	const float aDestBottom = aDestPos.y - aDesRad_Bottom;	//����

	/* ���ݍ��W :���E�����蔻��*/
	if (aScrRight > aDestLeft && aScrLeft < aDestRight)
	{
		//�������W :�ォ�炠������������
		if (nextBottom < aDestTop && nextTop > aDestTop)
		{
			return false;
		}
		//�������W :�����炠������������
		else if (nextTop > aDestBottom && nextBottom < aDestBottom)
		{
			return false;
		}
	}

	/* ���ݍ��W :�㉺�����蔻��*/
	if (aScrTop > aDestBottom && aScrBottom < aDestTop)
	{
		//�������W :�����炠������������
		if (nextRight > aDestLeft && nextLeft < aDestLeft)
		{
			return false;
		}
		//�������W :�E���炠������������
		else if (nextLeft < aDestRight && nextRight > aDestRight)
		{
			return false;
		}
	}
	return true;
}

//�l�ӂ̓����蔻����X�ɔ���
//1:�㔻�� 2:������ 3:�E 4:��
int Utility::iHitCheck(Math::Vector2 aScrPos, Math::Vector2 aScrMove, float aDestPosX, float aDestPosY, float aScrRad_Left, float aScrRad_Right, float aScrRad_Top, float aScrRad_Bottom, float aDesRad_Left, float aDesRad_Right, float aDesRad_Top, float aDesRad_Bottom)
{
	//�L����1�̌��ݍ��W�̎l��
	const float aScrLeft = aScrPos.x - aScrRad_Left;		//����
	const float aScrRight = aScrPos.x + aScrRad_Right;		//�E��
	const float aScrTop = aScrPos.y + aScrRad_Top;			//���
	const float aScrBottom = aScrPos.y - aScrRad_Bottom;	//����

	//�L����1�̖������W�̎l��
	const float nextLeft = aScrLeft + aScrMove.x;			//����
	const float nextRight = aScrRight + aScrMove.x;			//�E��
	const float nextTop = aScrTop + aScrMove.y;				//���
	const float nextBottom = aScrBottom + aScrMove.y;		//����

	//�L����2�̌��ݍ��W�̎l��
	const float aDestLeft = aDestPosX - aDesRad_Left;		//����
	const float aDestRight = aDestPosX + aDesRad_Right;		//�E��
	const float aDestTop = aDestPosY + aDesRad_Top;			//���
	const float aDestBottom = aDestPosY - aDesRad_Bottom;	//����

	/* ���ݍ��W :���E�����蔻��*/
	if (aScrRight > aDestLeft && aScrLeft < aDestRight)
	{
		//�������W :�ォ�炠������������
		if (nextBottom < aDestTop && nextTop > aDestTop)
		{
			return 1;	//��ɉ����߂�
		}
		//�������W :�����炠������������
		else if (aScrTop > aDestBottom && aScrBottom < aDestBottom)
		{
			return 2;	//���ɉ����߂�
		}
	}

	/* ���ݍ��W :�㉺�����蔻��*/
	if (aScrTop > aDestBottom && aScrBottom < aDestTop)
	{
		//�������W :�����炠������������
		if (nextRight > aDestLeft && nextLeft < aDestLeft)
		{
			return 3;	//���ɉ����߂�
		}
		//�������W :�E���炠������������
		else if (nextLeft < aDestRight && nextRight > aDestRight)
		{
			return 4;	//�E�ɉ����߂�
		}
	}

	return 0;
}

//2�_�Ԃ̊p�x�����߂�
float Utility::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
	float a;	// ���
	float b;	// ����
	float rad;	// ���W�A��
	float deg;	// �f�O���[

	//��ӂƍ��������߂�
	a = dest.x - src.x;
	b = dest.y - src.y;

	// tan�̋t�֐��Ŋp�x�����߂�  atan2(Y,X)�����̏��Ԃɒ���
	rad = atan2f(b, a);

	//�f�O���[�֕ϊ�(�v�Z���܂��͊֐����p)
	deg = DirectX::XMConvertToDegrees(rad);

	// ���̒l�̏ꍇ�͐��̒l�ɕ␳
	if (deg < 0)
	{
		deg += 360;
	}

	//�p�x��Ԃ�
	return deg;
}

//2�_�Ԃ̋��������߂�
float Utility::GetDistance(Math::Vector2 src, Math::Vector2 dest)
{
	float a, b, c;

	a = dest.x - src.x;			// ��ӂ����߂�
	b = dest.y - src.y;			// ���������߂�
	c = sqrt(a * a + b * b);	// �Εӂ����߂�<-���ꂪ��������
	return c;
}


