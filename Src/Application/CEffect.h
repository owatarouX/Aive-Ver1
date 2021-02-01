#pragma once
#include"CDamage.h"
#include"CDarken.h"
#include"CEffect_Heal.h"
class Scene;

constexpr int EFFECT_DMG_MAX = 4;
constexpr int DARKEN_MAX = 50;
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
	CDarken* GetDarkenList() { return m_darkenList; }
	CEffect_Heal* GetHealList() { return m_healList; }

	void SetOwner(Scene* apOwner);	// �I�[�i�[�ݒ�
	void SetDmgTexture(KdTexture* apTexture);
	void SetDarkTexture(KdTexture* apTexture);
	void SetHealTexture(KdTexture* apTexture);

	void PlayerHitEffect();	// �v���C���[�̃q�b�g�G�t�F�N�g����
	void PlayerHealEffect();	// �v���C���[�̉񕜃G�t�F�N�g����

private:

	CDamage		m_dmgList[EFFECT_DMG_MAX];
	CDarken		m_darkenList[DARKEN_MAX];
	CEffect_Heal m_healList[HEAL_MAX];

	Scene* m_pOwner;			//�I�[�i�[�擾�p
};
