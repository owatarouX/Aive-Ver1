#include"CDamage.h"

CDamage::CDamage()
	: m_pTexture(nullptr)
	 ,m_pos(0,0)
	 ,m_moveVal(0,0)
	 ,m_mat()
	 ,m_bAlive(false)
	 ,m_size(0)
	 ,m_lifeSpan(0)
	, m_dmgAnime(6)

{
}

CDamage::~CDamage()
{
}

// ������
void CDamage::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_size = 0;
	m_lifeSpan = 0;
	m_dmgAnime = 3;
}

// �X�V
void CDamage::UpDate(Math::Vector2 scrollPos)
{
	if (!m_bAlive) return;

	//�L������
	const float ANIMESPEED = 2;
	const int LIFESPAN_MAX = m_dmgAnime * ANIMESPEED;
	if (m_lifeSpan > LIFESPAN_MAX)
	{
		m_lifeSpan = 0;
		m_bAlive = false;
		return;
	}
	m_lifeSpan++;

	//�s��쐬
	Math::Matrix scaleMat, transMat;
	//�g�k�s��
	scaleMat = DirectX::XMMatrixScaling(m_size,m_size,1);
	//�ړ��s��
	transMat = DirectX::XMMatrixTranslation(m_pos.x - scrollPos.x, m_pos.y - scrollPos.y, 0);

	//�s�񍇐�
	m_mat = scaleMat * transMat;
}

// �`��
void CDamage::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle((m_lifeSpan/m_dmgAnime)*32, 0, 32, 32), 1.0f);
}

// �e�N�X�`���ݒ�
void CDamage::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTexture = apTexture;
}

// �G�t�F�N�g����
void CDamage::EmitDmg(Math::Vector2 pos, Math::Vector2 move, float size)
{
	m_bAlive = true;
	m_pos = pos;
	m_moveVal = move;
	m_size = size;
	m_lifeSpan = 0;
}
