#include "CSword.h"

CSword::CSword()
	:m_pTexture(nullptr)
	,m_pos(0,0)
	,m_move(0,0)
	,m_mat()
	,m_size(1.0f,1.0f)
	,m_direction(0)
	,m_bSlash(false)
	,m_slashCnt(0)
	,m_slashAnime(0)
{
}

CSword::~CSword()
{
}

//������
void CSword::Init()
{
	m_pos = { 0,0 };		//���W
	m_move = { 64,64 };		//�ړ���
	m_bSlash = false;		//�U���t���O
	m_direction = 0;		//��������
	m_scrollPos = { 0,0 };	//�X�N���[���ʎ擾�p
	m_slashAnime = 6;
}

//�X�V����
void CSword::Updata(Math::Vector2 playerPos)
{
	if (!m_bSlash)return;

	m_pos = playerPos;

	//�U�������ɂ��
	//���W�ύX�A�T�C�Y�ύX
	switch (m_direction) {
	case 0:
		m_pos.y += m_move.y;
		m_size = { 1.0f, 1.0f };
		break;
	case 1:
		m_pos.y -= m_move.y;
		m_size = { 1.0f, -1.0f };
		break;
	case 2:
		m_pos.x -= m_move.x;
		m_size = { -1.0f, 1.0f };
		break;
	case 3:
		m_pos.x += m_move.x;
		m_size = { 1.0f, 1.0f };
		break;
	}

	//��������
	const int CNT_MAX = m_slashAnime * 2;
	if (m_slashCnt >= CNT_MAX)
	{
		m_bSlash = false;
		m_slashCnt = 0;
		m_move = { 64,64 };
	}
	m_slashCnt++;


	//�s��쐬
	m_scaleMat = DirectX::XMMatrixScaling(m_size.x, m_size.y, 0.0f);
	m_transMat= DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_mat = m_scaleMat * m_transMat;
}

//�`�揈��
void CSword::Draw()
{
	if (!m_bSlash) return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle((m_slashCnt/m_slashAnime)* 64 , 0, 64, 64), 1.0f);

}

//�e�N�X�`���ݒ�
void CSword::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//���W�擾
const Math::Vector2 CSword::GetPos()
{
	return m_pos;
}

//�ړ��ʎ擾
const Math::Vector2 CSword::GetMove()
{
	return m_move;
}

//�U������
void CSword::Slash(Math::Vector2 Pos, const int Direct)
{
	m_bSlash = true;
	m_pos = Pos;
	m_direction = Direct;
}

//�t���O��Ԏ擾
const bool CSword::bGetSlash()
{
	return m_bSlash;
}


void CSword::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
