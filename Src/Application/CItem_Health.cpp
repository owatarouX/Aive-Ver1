#include"CItem_Health.h"

CItem_Health::CItem_Health()
	:m_pTexture(nullptr)
	, m_mat()
	, m_pos(0, 0)
	, m_bAlive(false)
{
}

CItem_Health::~CItem_Health()
{
}

// ������
void CItem_Health::Init()
{
	m_pos = { 0,0 };
	m_bAlive = false;
}

// �X�V
void CItem_Health::Update()
{
	if (!m_bAlive)return;

	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0);

}

// �`��
void CItem_Health::Draw()
{
	if (!m_bAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { 0,0,32,32 };	// �e�N�X�`�����W
	Math::Color color = { 1,1,1,0.8 };			// �F�iRGBA�̏��ԂŁ@0.0�`1.0�j
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 32, 32, &scrRect, &color, Math::Vector2(0.5f, 0.5f));

}

// �e�N�X�`���ݒ�
void CItem_Health::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}

// �A�C�e���Z�b�g
void CItem_Health::SetHealth(Math::Vector2 Pos)
{
	m_pos = Pos;
	m_bAlive = true;
}

// �t���O�Z�b�g
void CItem_Health::SetAlive()
{
	m_bAlive = false;
}

// �X�N���[���ʎ擾
void CItem_Health::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
