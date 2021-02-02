#pragma once

#include"CBullet.h"
#include"CSword.h"
#include"CBomb.h"
#include"CHidden.h"

//�N���X�̑O���錾
class Scene;

enum eDirection	//�����Ă������
{
	Up,
	Down,
	Left,
	Right
};

//����Z���N�g
enum eClick
{
	eShuriken,	//0.�藠��
	eSword,		//1.��
	eBomb,		//2.���e
	eHidden		//3.�B��g	
};

enum eStatus
{
	eIdle,
	eWalking,
	eAttack
};

//�藠���̗v�f��
constexpr int BULLET_MAX = 2;

//���e�̗v�f��
constexpr int BOMB_MAX = 5;

//�v���C���[�N���X
class CPlayer
{
public:

	CPlayer();	//�R���X�g���N�^
	~CPlayer();	//�f�X�g���N�^

	//�v���C���[
	void Init();
	void ReInit(int mapData);
	void Updata();
	void UpDatePlayer(Math::Vector2 ScrollPos);
	void Draw();

	//�Z�b�^�[
	void SetTexture(KdTexture* apTexture);
	void SetBulletTexture(KdTexture* apTexture);
	void SetSlashTexture(KdTexture* apTexture);
	void SetBombTexture(KdTexture* apTexture);
	void SetBlastTexture(KdTexture* apTexture);
	void SetOwner(Scene* apOwner);
	void SetDamage(int dmg);	// �̗͌���
	void SetHeal(int heal);		// �̗͉�
	void SetHitFlg();			// �q�b�g�t���O�Z�b�g
	void SetPosX(float x);	// ���W�Z�b�gX(���ݍ��W�ɑ����Z)
	void SetPosY(float y);	// ���W�Z�b�gY(���ݍ��W�ɑ����Z)
	void SetMovevalX(float movex);	// �ړ��ʃZ�b�gX(�ړ��ʂ����)
	void SetMovevalY(float movey);	// �ړ��ʃZ�b�gY(�ړ��ʂ����)

	//�Q�b�^�[
	const bool IsAlive() { return m_bAlive; }
	const Math::Vector2 GetPos() { return m_pos; }				//�v���C���[���W�擾
	const Math::Vector2 GetMove() { return m_moveVal; }			//�v���C���[�ړ��ʎ擾
	const int GetHp() { return m_hp; }							//�̗͗ʎ擾
	const int GetBombPossession() { return m_BombPossession; }	//���e�������擾
	const int GetKeyPossession() { return m_KeyPossession; }	//���������擾
	const bool bGetHit() { return m_HitFlg; }					// ���G��Ԏ擾
	const bool bGetHidden() { return m_hiddenList.bGetHidden(); }	// �B��g�t���O�擾
	const float GetHideCnt() { return m_hiddenList.GetHiddenCnt(); }

	//�L�[���e�擾
	const int GetR();
	const int GetL();

private:		//�O������A�N�Z�X�s��

	eDirection		m_direction;	//�v���C���[�̌���
	eClick			m_LClick;
	eClick			m_RClick;

	KdTexture*		 m_pTexture;	//�摜(�e�N�X�`��)
	Math::Vector2	 m_pos;			//���W
	Math::Vector2	 m_moveVal;		//�ړ���
	Math::Matrix	 m_mat;			//�s��
	Math::Matrix	 m_transMat;	//�ړ��s��
	Math::Matrix	 m_scaleMat;	//�g��s��
	Math::Vector2	 m_size;		//�g��T�C�Y
	
	bool			 m_bAlive;		//�����t���O
	int				 m_hp;			//HP
	bool			 m_bHeal;		//HP�񕜃|�C���g�t���O
	int				 m_hpCount;		//���G����
	float			 m_alpha;		//�摜�̓����x
	bool			 m_HitFlg;		//�����蔻��t���O
	float			 m_slashCnt;	//�a���U���̃N�[���^�C��
	float			 m_shurikenCnt;	//�藠���N�[���^�C��

	bool			 m_bRClick;	//�E�N���b�N�t���O
	bool			 m_bLClick;	//���N���b�N�t���O
	bool			 m_bRChange;//�E����ύX�t���O
	bool			 m_bLChange;//������ύX�t���O

	int	 m_aCnt;	//�A�j���[�V�����J�E���g
	int m_aTimer;	//�A�j���[�V��������f��1��������
	int m_aflame;	//�A�j���[�V��������

	int				 m_BombPossession;		//���e������
	int				 m_KeyPossession;		//��������
	bool			 m_bMinoPossession;		//�B�ꖪ�����t���O


	void KeyOperation();	// �L�[����ꗗ

	/* �����蔻�� */
	void HitCheckMap();			// �}�b�v
	void HitCheckEnemy();		// �G
	void HitCheckBomb();		// ���e
	void HitCheckItem();		// �A�C�e��

	void InviTime();			//���G����
	eClick ChangeItem(eClick click);		//����ύX�֐�
	void Attack(bool flg, eClick click);
	void SetShuriken();		//�藠���U��
	void SetSword();		//���U��
	void SetBomb();			//���e�U��
	void SetHidden();		//�B��g 

	Scene*			 m_pOwner;			//�I�[�i�[�擾�p
	CBullet m_bulletList[BULLET_MAX];	//�藠���N���X�擾
	CSword  m_swordList;				//�a���N���X�擾
	CBomb  m_bombList;					//���e�N���X�擾
	CHidden m_hiddenList;				//�B��g�N���X�擾

	//��
	std::shared_ptr<KdSoundEffect> katanase;
	std::shared_ptr<KdSoundInstance> katanaseInst;

	std::shared_ptr<KdSoundEffect> shurikense;
	std::shared_ptr<KdSoundInstance> shurikenseInst;

	std::shared_ptr<KdSoundEffect> hitse;
	std::shared_ptr<KdSoundInstance> hitseInst;

	int Animation(int cnt, const int xtex);
	std::shared_ptr<KdSoundInstance> Sound_Loading(std::shared_ptr<KdSoundEffect> se, const std::string &seName);
};