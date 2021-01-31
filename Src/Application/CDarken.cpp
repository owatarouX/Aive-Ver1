#include"CDarken.h"

CDarken::CDarken()
	:m_pos(0, 0)
	, m_move(0, 0)
	, m_size(1)
	, m_color(1, 1, 1, 1)
	, m_lifeSpan(0)
	, m_loopFlg(false)
	, m_mat()
	, m_pTexture(nullptr)
{
}

CDarken::~CDarken()
{
}

// ������
void CDarken::Init()
{
	m_lifeSpan = 0;
}

// �X�V
void CDarken::Update()
{
	//�L������
	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_lifeSpan = 0;
	}

	//���W�X�V
	m_pos += m_move;

	//�T�C�Y�ύX
	m_size *= 0.95;	

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
void CDarken::Draw()
{
	if (m_lifeSpan <= 0) return;

	//�s��Z�b�g
	SHADER.m_spriteShader.SetMatrix(m_mat); //������s����Z�b�g���� 

	// �F�����ׂ����w��	
	Math::Rectangle scrRect = { 0,0,32 * 2,32 * 2 }; // �e�N�X�`�����W
	//                            �e�N�X�`���AX�AY�A���A�����A�e�N�X�`�����W�A�F�A��_���W
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 32, 32,
		&scrRect, &m_color, Math::Vector2(0.5f, 0.5f));
}

// �e�N�X�`���ݒ�
void CDarken::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)	return;
	m_pTexture = apTexture;
}

// �����_��
float CDarken::Rnd()
{
	return rand() / (float)RAND_MAX;
}

void CDarken::EmitDark()
{
	m_pos = {0, 0};
	m_move = { 0,0 };
	m_size = Rnd() * 100;
	m_color = { 1.0,1.0,1.0,1.0 };
	m_lifeSpan = 100;
}
