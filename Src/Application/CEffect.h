#pragma once
#include"CDamage.h"
#include"CDarken.h"
#include"CEffect_Heal.h"
#include"CBlack.h"
class Scene;

constexpr int EFFECT_DMG_MAX = 4;
constexpr int HEAL_MAX = 20;

class CEffect
{
public:
	CEffect();
	~CEffect();

	void Init();
	void UpDate();
	void Draw();

	CDamage* GetDmgList() { return m_dmgList; }
	CDarken* GetDarkenList() { return &m_darkenList; }
	CEffect_Heal* GetHealList() { return m_healList; }
	CBlack* GetBlackList() { return &m_blackList; }

	void SetOwner(Scene* apOwner);	// �I�[�i�[�ݒ�
	void SetDmgTexture(KdTexture* apTexture);
	void SetDarkTexture(KdTexture* apTexture);
	void SetHealTexture(KdTexture* apTexture);
	void SetBlackTexture(KdTexture* apTexture);

	void HitEffect(Math::Vector2 pos, Math::Vector2 move, float size);	// �q�b�g�G�t�F�N�g����
	void PlayerHealEffect();	// �v���C���[�̉񕜃G�t�F�N�g����

private:

	CDamage		m_dmgList[EFFECT_DMG_MAX];
	CDarken		m_darkenList;
	CBlack		m_blackList;
	CEffect_Heal m_healList[HEAL_MAX];


	Scene* m_pOwner;			//�I�[�i�[�擾�p
};

