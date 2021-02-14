#pragma once
#include"CEnemySword.h"

enum eattackType
{
	Homing,
	Slash,
	Shot,
	Rush
};

enum BossDirection	//�����Ă������
{
	BUp,
	BDown,
	BLeft,
	BRight
};


class CBoss
{
public:
	CBoss();			// �R���X�g���N�^
	~CBoss();			// �f�X�g���N�^

	// boss
	void Init();		// ������
	void Update();		// �X�V
	void Draw();		// �`��

	// �Z�b�g
	void SetBoss(Math::Vector2 pos);
	void SetTexture(KdTexture* apTexture);	// �e�N�X�`���󂯎��
	void SetPosX(float posX);	// X���W�Z�b�g
	void SetPosY(float posY);	// Y���W�Z�b�g
	void SetMoveX(float moveX);	// X�ړ��ʃZ�b�g
	void SetMoveY(float moveY);	// Y�ړ��ʃZ�b�g
	void SetAlive();			// �����t���O�ݒ�
	void SetDamage(int dmg);	// �_���[�W����
	void bSetSlashHit(bool aHit);	// �a���q�b�g�t���O�Z�b�g
	void bSetBlastHit(bool aHit);	// �����q�b�g�t���O�Z�b�g
	void SetShotFlg(bool flg);	// ���˃t���O�ݒ�
	void SetAtkFlg();	// 
	void bSetButtleStart();		// �퓬�J�n�t���O�Z�b�g

	void SetSlash(bool slash);
	void SetScrollPos(Math::Vector2 scrPos);	//�X�N���[���ʎ擾
	void SetPlayerPos(Math::Vector2 pos);		// �v���C���[�̍��W�擾

	// �Q�b�^�[
	Math::Vector2 GetPos() { return { m_pos.x - 40 , m_pos.y }; }
	Math::Vector2 GetMove() { return m_moveVal; }
	float GetPosX() { return m_pos.x; }
	float GetPosY() { return m_pos.y; }
	float	GetDeg() { return m_deg; }
	bool	GetSlash() { return m_bSlash; }
	bool	bGetShot() { return m_shotFlg; }
	const bool IsAlive() { return m_bAlive; }
	int		GetHp() { return m_hp; }
	const bool bGetSlashHit() { return m_bSlashHit; }	// �a���q�b�g�t���O�擾
	const bool bGetBlastHit() { return m_bBlastHit; }	// �����q�b�g�t���O�擾
	const int iGetAttakeType() { return attackType; }	// �U�����@�擾
	const int GetShotCnt() { return m_shotCnt; }	// ���˃J�E���g�擾
	bool Getm_bRush() { return m_bRush; }			// �ːi�t���O
	bool GetPlayerHit() { return playerHitFlg; }	// �v���C���[�ɓ���������
	const int GetDirection() { return m_direction; }// ����
	int	GetAtkCnt() { return m_atkCnt; }
	int	GetAttakeType() { return attackType; }



private:

	eattackType attackType;		// �U���s��
	BossDirection	m_direction;	// �{�X�̌���
	KdTexture* m_pTexture;		// �摜(�e�N�X�`��)
	Math::Vector2	m_pos;		// ���W
	Math::Vector2	m_moveVal;	// �ړ���
	Math::Matrix	m_mat;		// �����s��
	bool			m_bAlive;	// �����t���O
	int				m_hp;		// �̗͗�
	int				m_dmg;		// �̗͌�����
	float			m_deg;		// �p�x
	bool			m_bSlashHit;		// �a���q�b�g�t���O
	bool			m_bBlastHit;		// �����q�b�g�t���O
	bool			m_bSlash;		// �a���t���O
	int				m_slashCnt;		//�J�E���g
	bool			m_shotFlg;	// ���˃t���O
	int				m_shotCnt;	// ���˃J�E���g



		//======�ːi(Rush)�p�ϐ�======
	int				m_moveCnt;			// �����_���s���J�E���g
	const int		MOVE_CNT_MAX = 40;	// �����_���s������
	int				m_rushCnt;			// �ːi�U���J�E���g
	const int		RUSH_CNT_MAX = 100;	// �ːi�J�E���g
	bool			m_bRush;			// �ːi�t���O
	bool			m_bAtk;				// �U���t���O
	int				m_atkCnt;			// �U���J�E���g
	int				m_atkRnd;			// �����_���ōU���ύX

	bool			playerHitFlg;		// �v���C���[�ƐG�ꂽ��

	bool			m_battleStartFlg;			// �퓬�J�n�t���O

	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p
	Math::Vector2	 m_playerPos;	//�v���C���[�̍��W�擾�p

	void Attake();	
	void BossMoveHoming(float sp);	// �{�X�̍s���P�F�ǐ�
	void BossMoveSlash();	// �{�X�̍s���Q�F�a��
	void BossMoveShot();	// �{�X�̍s���R�F����
	void BossMoveRush();	// �{�X�̍s���S�F�ːi

	void atkTypeRnd();
	void atkSleep(int cnt);

	CEnemySword	m_enemySwordList;

};
