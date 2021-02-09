#include"CEffect.h"
#include"Scene.h"

CEffect::CEffect()
	:m_pOwner(nullptr)
{
}

CEffect::~CEffect()
{
}

// ������
void CEffect::Init()
{
	// �_���[�W�G�t�F�N�g������
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].Init();
	}
	// �Ó]�G�t�F�N�g������
	for (int i = 0; i < DARKEN_MAX; i++)
	{
		m_darkenList[i].Init();
	}
	// �񕜃G�t�F�N�g
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].Init();
	}
}

// �X�V
void CEffect::UpDate()
{
	CMap* map = m_pOwner->GetMap();
	Math::Vector2 scrollPos = map->GetscrollPos();

	// �_���[�W�G�t�F�N�g
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].UpDate(scrollPos);
	}
	// �Ó]�G�t�F�N�g
	for (int i = 0; i < DARKEN_MAX; i++)
	{
		m_darkenList[i].Update();
	}
	// �񕜃G�t�F�N�g
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].UpDate(scrollPos);
	}
}

// �`��
void CEffect::Draw()
{
	// �_���[�W�G�t�F�N�g
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].Draw();
	}
	// �Ó]�G�t�F�N�g
	for (int i = 0; i < DARKEN_MAX; i++)
	{
		m_darkenList[i].Draw();
	}
	// �񕜃G�t�F�N�g
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].Draw();
	}
}

// �e�N�X�`���ݒ�F�_���[�W
void CEffect::SetDmgTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_dmgList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���ݒ�F�Ó]
void CEffect::SetDarkTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		m_darkenList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���F�񕜃G�t�F�N�g
void CEffect::SetHealTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	for (int i = 0; i < HEAL_MAX; i++)
	{
		m_healList[i].SetTexture(apTexture);
	}
}

// �v���C���[�̃q�b�g�G�t�F�N�g����
void CEffect::PlayerHitEffect()
{
	CPlayer* player = m_pOwner->GetPlayer();
	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		if (!m_dmgList[i].GetbAlive())continue;
		m_dmgList[i].EmitDmg(player->GetPos(), player->GetMove(), 1.5);
		return;
	}
}

// �v���C���[�̉񕜃G�t�F�N�g����
void CEffect::PlayerHealEffect()
{
	CPlayer* player = m_pOwner->GetPlayer();
	for (int i = 0; i < HEAL_MAX; i++)
	{
		if (m_healList[i].GetbAlive())continue;
		m_healList[i].EmitHeal(player->GetPos(), player->GetMove());
	}
}

// �I�[�i�[�ݒ�擾
void CEffect::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr)return;
	m_pOwner = apOwner;
}
