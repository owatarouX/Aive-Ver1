#include"CEffect_Heal.h"

CEffect_Heal::CEffect_Heal()
	: m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_bAlive(false)
	, m_size(0)
	, m_color(1,1,1,1)
	, m_lifeSpan(0)
{
}

CEffect_Heal::~CEffect_Heal()
{
}

// ������
void CEffect_Heal::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_size = 1;
	m_color = { 1,1,1,1 };
	m_lifeSpan = 0;
}

// �X�V
void CEffect_Heal::UpDate(Math::Vector2 scrollPos)
{
	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_lifeSpan = 0;
	}

	//���W�X�V
	m_pos += m_moveVal;

	//�T�C�Y�ύX
	m_size *= 0.95;


	//�s��쐬
	Math::Matrix scaleMat, transMat;
	//�g�k�s��
	scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 1);
	//�ړ��s��
	transMat = DirectX::XMMatrixTranslation(m_pos.x - scrollPos.x, m_pos.y - scrollPos.y, 0);

	//�s�񍇐�
	m_mat = scaleMat * transMat;
}

// �`��
void CEffect_Heal::Draw()
{
	if (m_lifeSpan <= 0) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { 0,0,15,15 }; // �e�N�X�`�����W
	m_color = { 1.0f,1.0f,1.0f,(rand()/(float)RAND_MAX)+0.5f };
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 15, 15,
		&scrRect, &m_color, Math::Vector2(0.5f, 0.5f));
}

// �e�N�X�`���ݒ�
void CEffect_Heal::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)	return;

	m_pTexture = apTexture;
}

// �񕜃G�t�F�N�g����
void CEffect_Heal::EmitHeal(Math::Vector2 pos, Math::Vector2 move)
{
	m_pos.x = pos.x + rand() % 20 - 10;
	m_pos.y = pos.y;
	m_moveVal = { 0,float(rand() % 2 + 1) };
	m_size = rand() % 2 + 0.5;
	m_lifeSpan = rand() % 30 + 20;
}

