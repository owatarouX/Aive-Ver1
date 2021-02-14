#pragma once

#include<vector>
#include"CSamurai.h"
#include"CArcher.h"
#include"CArrow.h"
#include"CGiant.h"
#include"CBoss.h"
#include"CEnemySword.h"

//�N���X�̑O���錾
class Scene;

//�G�̗v�f��
constexpr int SAMURAI_MAX = 20;
constexpr int ARCHER_MAX = 15;
constexpr int GIANT_MAX = 5;

class CEnemy
{
public:		// �O������A�N�Z�X��
	CEnemy();		// �R���X�g���N�^
	~CEnemy();		// �f�X�g���N�^

	void SetOwner(Scene* apOwner);		// �I�[�i�[�ݒ�擾

	void Init();			// ������
	void Update();			// �X�V
	void Draw();			// �`��
	
	CSamurai* GetSamuraiList() { return m_samuraiList; }	// �����X�g�擾
	CArcher* GetArcherList() { return m_archerList; }		// �|�����X�g�擾
	CGiant* GetGiantList() { return m_giantList; }			// ��j���X�g�擾
	CBoss* GetBossList() { return &m_bossList; }			// �{�X���X�g�擾
	int GetArrowSize() { return m_arrowList.size(); }		// ��̔z��Ԋ�
	int GetSwordSize() { return m_enemySwordList.size(); }	// �a���̔z��Ԋ�
	int GetBossHp() { return m_bossList.GetHp(); }			// �{�X��HP�擾
	bool bGetEvent() { return m_bEvent; }					// �C�x���g�����t���O�擾
	
	void SetTexture(KdTexture* apTexture);			// �e�N�X�`���ݒ�F��
	void SetArcherTexture(KdTexture* apTexture);	// �e�N�X�`���ݒ�F�|��
	void SetGiantTexture(KdTexture* apTexture);		// �e�N�X�`���ݒ�F��j
	void SetBossTexture(KdTexture* apTexture);		// �e�N�X�`���ݒ�F�{�X
	void SetArrowTexture(KdTexture* apTexture);		// �e�N�X�`���ݒ�F��
	void SetSwordTexture(KdTexture* apTexture);		// �e�N�X�`���ݒ�F�a��

	void SetSamurai(int data);		// ���z�u
	void SetArcher(int data);		// �|���z�u
	void SetGiant(int data);		// ��j�z�u
	void SetBoss(int data);			// �{�X�z�u

	void shot(Math::Vector2 apos, Math::Vector2 bpos);  //���ˏ���
	void Event();	// �C�x���g����

private:	// �O������A�N�Z�X�s��

	void Update_Samurai(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Archer(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Giant(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Boss(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide);
	void Update_Arrow(Math::Vector2 scrPos);
	void Update_Sword(Math::Vector2 scrPos);

	void HitCheckPlayer();	// �v���C���[�Ƃ̓����蔻��
	void HitCheckEnemy_And_Player(Math::Vector2 enePos, int dmg, float knockBack, float Left,float Right,float Top,float Down);	// �v���C���[�ƓG�̓����蔻��
	void HitCheckMap();		//�}�b�v�Ƃ̓����蔻��

	CSamurai	m_samuraiList[SAMURAI_MAX];		// ���N���X�̃��X�g
	const Math::Vector2 SAMURAI_SLASH_SIZE = { 1,1 };	// ���a���T�C�Y
	CArcher		m_archerList[ARCHER_MAX];		// �|���N���X�̃��X�g
	CGiant		m_giantList[GIANT_MAX];			// ��j�N���X�̃��X�g
	CBoss		m_bossList;						// �{�X�N���X�̃��X�g
	const Math::Vector2 BOSS_SLASH_SIZE = { 2,2 };		// �{�X�a���T�C�Y

	std::vector<CEnemySword*>	m_enemySwordList;	// �G�a�����X�g
	KdTexture* m_pSlashTex;	// �e�N�X�`���F�a��
	std::vector<CArrow*>	m_arrowList;	// ��X�g
	KdTexture* m_pArrawTex;	// �e�N�X�`���F��		

	int         gimmickcount;                   //�M�~�b�N�J�E���g
	bool m_bEvent;	// �C�x���g��������

	Scene* m_pOwner;	// �I�[�i�[�擾�p
};

