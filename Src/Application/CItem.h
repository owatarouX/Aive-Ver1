#pragma once

#include"CItem_Bomb.h"
#include"CItem_Key.h"
#include"CItem_Health.h"
class Scene;

// ���e�z�u��
constexpr int BOMB_SETMAX = 3;
// ���ݒu��
constexpr int KEY_SETMAX = 3;
// �񕜐ݒu���
constexpr int HEALTH_SETMAX = 3;

class CItem
{
public:
	CItem();
	~CItem();

	void Init();
	void Update();
	void Draw();

	void SetOwner(Scene* apOwner);

	//�A�C�e���F���e
	void SetBomb();
	//�A�C�e���F��
	void SetKey();

	CItem_Bomb* GetBombItem() { return m_bombList; }	//���e���X�g�擾
	CItem_Key* GetKeyItem() { return m_keyList; }		//�����X�g�擾
	CItem_Health* GetHealehItem() { return m_healthList; }	// �񕜃��X�g�擾

	/* �e�N�X�`���ݒ� */
	// ���e
	void SetTexBomb_t(KdTexture* apTexture);
	void SetTexBomb_f(KdTexture* apTexture);
	// ��
	void SetTexKey(KdTexture* apTexture);
	// ��
	void SetHealthTex(KdTexture* apTexture);

	bool DropHealth(bool bDrop, Math::Vector2 pos);	// �A�C�e���h���b�v����
	bool DropKey(bool bDrop, Math::Vector2 pos);	// �A�C�e���h���b�v����

private:


	Scene* m_pOwner;			//�I�[�i�[�擾�p

	CItem_Bomb		m_bombList[BOMB_SETMAX];		// ���e�N���X�擾
	CItem_Key		m_keyList[KEY_SETMAX];			// ���N���X�擾
	CItem_Health	m_healthList[HEALTH_SETMAX];	// �񕜃N���X�擾

};

