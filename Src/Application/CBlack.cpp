#include "CBlack.h"

CBlack::CBlack()
	:m_pos(0, 0)
	, m_move(0, 0)
	, m_size(1)
	, m_color(1, 1, 1, 1)
	, m_lifeSpan(0)
	, m_mat()
	, m_transcnt(0.0f)
	, m_pTexture(nullptr)
{
}

CBlack::~CBlack()
{
}

// ������
void CBlack::Init()
{
	m_pos = { 0,0 };
	m_move = { 0,0 };
	m_size = 1;
	m_color = { 1,1,1,1 };
	m_lifeSpan = 0;
	m_transcnt = 0.0f;
}

// �X�V
void CBlack::Update()
{
	//�L������
	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_lifeSpan = 0;
	}

	//���W�X�V
	m_pos += m_move;

	//�s��쐬
	Math::Matrix scaleMat, transMat;
	//�g�k�s��
	scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 1);
	//�ړ��s��
	transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);
	//�s�񍇐�
	m_mat = scaleMat * transMat;
}

// �`��
void CBlack::Draw()
{
	if (m_lifeSpan <= 0) return;

	//�s��Z�b�g
	SHADER.m_spriteShader.SetMatrix(m_mat); //������s����Z�b�g���� 

	// �F�����ׂ����w��	
	Math::Rectangle scrRect = { 0,0,1280,720 }; // �e�N�X�`�����W
	Math::Color m_color = { 0,0,0,m_transcnt };
	//                            �e�N�X�`���AX�AY�A���A�����A�e�N�X�`�����W�A�F�A��_���W
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 1280, 720,
		&scrRect, &m_color, Math::Vector2(0.5f, 0.5f));
}

// �e�N�X�`���ݒ�
void CBlack::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)	return;
	m_pTexture = apTexture;
}

void CBlack::EmitBlack()
{
	m_transcnt +=0.02;
	m_pos = {0, 0};
	m_move = { 0,0 };
	m_size = 200;
	m_color = { 1.0,1.0,1.0,m_transcnt};
	m_lifeSpan = 100;
}
