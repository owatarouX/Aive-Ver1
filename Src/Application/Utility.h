#pragma once

//��ʏ��
namespace Screen
{
	const int Width = 1280;				//��ʕ�
	const int Height = 720;				//��ʍ�
	const int HalfWidth = Width / 2;	//��ʕ�����
	const int HalfHeight = Height / 2;	//��ʍ�����

}

//�L�������
namespace Infor
{
	//���a���
	const float RADIUS_32 = 32.0f;
	const float RADIUS_16 = 16.0f;
	const float RADIUS_8 = 8.0f;
}

// �p�����[�^�F�̗�
namespace HP
{
	const int PLAYER = 100;		// �v���C���[
	const int SAMURAI = 15;		// ��
	const int ARCHER = 9;		// �|��
	const int GIANT = 30;		// ��j
	const int BOSS = 150;		// �{�X
}

// �p�����[�^�F�U����
namespace POWER
{
	// �v���C���[
	const int PLAYER_SHURIKEN = 2;	// �藠��
	const int PLAYER_SLASH = 9;		// �a��
	const int PLAYER_BLAST = 15;	// ����

	// �G
	const int ENEMY_PHYSICAL = 5;
	// ��
	const int SAMURAI_SLASH = 5;
	// �|��
	const int ARCHER_ARROW = 5;
	// ��j
	const int GIANT_RUSH = 10;
	// �{�X
	const int BOSS_SLASH = 10;
}

// �p�����[�^�F�X�s�[�h
namespace SPEED
{
	// �v���C���[
	const int PLAYER = 5;
	const int PLAYER_SHURIKEN = 12;

	// ��
	const int SAMURAI = 1.8;
	// �|��
	const int ARCHER = 1.5;
	// ��
	const int ARROW = 12;
	// ��j
	const int GIANT_NORMAL = 1.1;
	const int GIANT_RUSH = 6;
	// �{�Xww
	const int BOSS = 1.8;
}

// �p�����[�^�F�N�[���^�C��
namespace COOL_TIME
{
	// �v���C���[
	const int PLAYER_SLASH = 50;		// �a��
	const int PLAYER_SHURIKEN = 20;		// �藠��

	// ��
	const int SAMURAI_SLASH = 40;
	// �|��
	const int ARCHER_ARROW = 80;
	// ��j
	const int GIANT_ATK = 80;
	// �{�X
	const int BOSS_SLASH = 80;
	const int BOSS_ARROW = 120;
}

// �v���C���[�T�C�Y
namespace PLAYER_SIZE
{
	const float LEFT = 32;
	const float RIGHT = 32;
	const float TOP = 32;
	const float DOWN = 32;
}

// ���T�C�Y
namespace SAMURAI_SIZE
{
	const float LEFT = 20;
	const float RIGHT = 9;
	const float TOP = 32;
	const float DOWN = 32;
}
// �|���T�C�Y
namespace ARCHER_SIZE
{
	const float LEFT = 20;
	const float RIGHT = 9;
	const float TOP = 32;
	const float DOWN = 32;
}
// ��j�T�C�Y
namespace GIANT_SIZE
{
	const float LEFT = 30;
	const float RIGHT = 30;
	const float TOP = 35;
	const float DOWN = 35;
}
// �{�X�T�C�Y
namespace BOSS_SIZE
{
	const float LEFT = 40;
	const float RIGHT = 73;
	const float TOP = 70;
	const float DOWN = 80;
}

// �藠���T�C�Y
namespace SHURIKEN_SIZE
{
	const float LEFT = 8;
	const float RIGHT = 8;
	const float TOP = 8;
	const float DOWN = 8;
}
// �a���T�C�Y
namespace SLASH_SIZE
{
	const float LEFT = 32;
	const float RIGHT = 32;
	const float TOP = 32;
	const float DOWN = 32;
}
// �����T�C�Y
namespace BLAST_SIZE
{
	const float LEFT = 48*1.5;
	const float RIGHT = 48 * 1.5;
	const float TOP = 48 * 1.5;
	const float DOWN = 48 * 1.5;
}
// ��T�C�Y
namespace ARROW_SIZE
{
	const float LEFT = 16;
	const float RIGHT = 16;
	const float TOP = 16;
	const float DOWN = 16;
}


//�ėp������
namespace Utility
{
	/*�����蔻�菈��*/
	//0��1��Ԋ�
	bool bHitCheck(Math::Vector2 aScrPos,Math::Vector2 aScrMove, Math::Vector2 aDestPos,				// �L�����P���W�A�L�����P�ړ��ʁA�L�����Q���W�A
					float aScrRad_Left,float aScrRad_Right , float aScrRad_Top, float aScrRad_Bottom ,  // �L�����P���a ���E�㉺
					float aDesRad_Left,float aDesRad_Right,float aDesRad_Top,float aDesRad_Bottom);		// �L�����Q���a �㉺���E

	//0�܂���1�`4��Ԋ�
	int  iHitCheck(Math::Vector2 aScrPos,Math::Vector2 aScrMove, float aDestPosX, float aDestPosY,			// �L�����P���W�A�L�����P�ړ��ʁA�L�����Q���W�A
					float aScrRad_Left, float aScrRad_Right, float aScrRad_Top, float aScrRad_Bottom,		// �L�����P���a ���E�㉺
					float aDesRad_Left, float aDesRad_Right, float aDesRad_Top, float aDesRad_Bottom);		// �L�����Q���a �㉺���E

	//2�_�Ԃ̊p�x�����߂�
	float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest);	//���錳�̍��W,�����̍��W 
	
	//2�_�Ԃ̋��������߂�
	float GetDistance(Math::Vector2 src, Math::Vector2 dest);	//���錳�̍��W,�����̍��W 
}