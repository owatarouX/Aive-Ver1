#include "Pch.h"
#include "CItem_Bomb.h"

CItem_Bomb::CItem_Bomb()
	:m_pTexture_t(nullptr)
	,m_pTexture_f(nullptr)
	,m_mat()
	,m_pos(0,0)
	,m_bAlive(false)
	,m_bBombHit(false)
{
}

CItem_Bomb::~CItem_Bomb()
{
}

//������
void CItem_Bomb::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
	m_bBombHit = false;
}

//�X�V
void CItem_Bomb::Update()
{
	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);
}

//�`��
void CItem_Bomb::Draw()
{
	if (m_bAlive)
	{
		// ���e�u����F�L
		SHADER.m_spriteShader.SetMatrix(m_mat);
		Math::Rectangle scrRect = { 0,0,96,96 }; // �e�N�X�`�����W
		Math::Color color = { 1,1,1,1 }; // �F�iRGBA�̏��ԂŁ@0.0�`1.0�j
		SHADER.m_spriteShader.DrawTex(m_pTexture_t, 0, 0, 96, 96, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}
	else
	{
		if (!m_bBombHit) return;

		// ���e�u����F��
		SHADER.m_spriteShader.SetMatrix(m_mat);
		Math::Rectangle scrRect = { 0,0,96,96 }; // �e�N�X�`�����W
		Math::Color color = { 1,1,1,1 }; // �F�iRGBA�̏��ԂŁ@0.0�`1.0�j
		SHADER.m_spriteShader.DrawTex(m_pTexture_f, 0, 0, 96, 96, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}
}

//�e�N�X�`���ݒ�Ftrue��
void CItem_Bomb::SetTexture_t(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture_t = apTexture;
}

// �e�N�X�`���ݒ�Ffalse
void CItem_Bomb::SetTexture_f(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture_f = apTexture;
}

// ���W�Z�b�g�A�t���O���Ă�
void CItem_Bomb::SetBomb(Math::Vector2 Pos)
{
	m_bAlive = true;
	m_pos = Pos;
}

void CItem_Bomb::SetAlive()
{
	m_bAlive = false;
}

//���e�A�C�e���q�b�g�t���O�Z�b�g
void CItem_Bomb::bSetbombHit()
{
	m_bBombHit = true;
}

void CItem_Bomb::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
