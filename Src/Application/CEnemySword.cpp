#include "CEnemySword.h"
#include"Utility.h"

CEnemySword::CEnemySword()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_move(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_rotMat()
	, m_size(1.0f, 1.0f)
	, m_bSlash(false)
	, m_slashCnt(0)
	, m_slashAnime(0)
	, m_deg(0.0f)
	, m_scrollPos(0.0f,0.0f)
{
}

CEnemySword::~CEnemySword()
{
}

//������
void CEnemySword::Init()
{
	m_pos = { 0,0 };		//���W
	m_move = { 0,0 };		//�ړ���
	m_bSlash = false;		//�U���t���O
	m_deg = 0;				//��������
	m_scrollPos = { 0,0 };	//�X�N���[���ʎ擾�p
	m_slashAnime = 6;		//�a���A�j���[�V����
}

//�X�V����
void CEnemySword::Updata()
{
	if (!m_bSlash)return;	// �t���O�������Ă��Ȃ����return

	//��������
	const int CNT_MAX = m_slashAnime * 2;
	if (m_slashCnt >= CNT_MAX)
	{
		m_bSlash = false;
		m_slashCnt = 0;
		m_move = { 64,64 };
	}
	m_slashCnt++;

	//�g�k�s��
	m_scaleMat = DirectX::XMMatrixScaling(m_size.x, m_size.y, 1);
	//��]�s��
	m_rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_deg));
	//�ړ��s��
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	//�s�񍇐�
	m_mat = m_scaleMat * m_rotMat * m_transMat;
}

//�`�揈��
void CEnemySword::Draw()
{
	if (!m_bSlash) return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { (m_slashCnt / m_slashAnime) * 64, 0, 64, 64 }; // �e�N�X�`�����W
	Math::Color color = { 1,1,1,1 }; // �F�iRGBA�̏��ԂŁ@0.0�`1.0�j
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 64, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
}
//�e�N�X�`���ݒ�
void CEnemySword::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}
//���W�擾
const Math::Vector2 CEnemySword::GetPos()
{
	return m_pos;
}
//�ړ��ʎ擾
const Math::Vector2 CEnemySword::GetMove()
{
	return m_move;
}

//�U������(�����L�������W�A�p�x�A�T�C�Y�A���������j
void CEnemySword::Slash(Math::Vector2 Pos, float deg, Math::Vector2 size, float dist)
{
	m_bSlash = true;
	m_pos = Pos;
	m_deg = deg;
	m_size = size;
	m_move.x = cos(DirectX::XMConvertToRadians(m_deg)) * dist;	// cos
	m_move.y = sin(DirectX::XMConvertToRadians(m_deg)) * dist;	// sin
	m_pos += m_move;	// �ړ��ʂ��Z�b�g

	// �摜���]����
	if (Pos.x > m_pos.x) m_size.y *=-1;
}

//�t���O��Ԏ擾
const bool CEnemySword::bGetSlash()
{
	return m_bSlash;
}
//�X�N���[���ʎ擾
void CEnemySword::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
