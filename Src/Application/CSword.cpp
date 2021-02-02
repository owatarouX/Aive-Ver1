#include "CSword.h"

CSword::CSword()
	:m_pTexture(nullptr)
	,m_pos(0,0)
	,m_move(0,0)
	,m_mat()
	,m_size(1.0f,1.0f)
	,m_bSlash(false)
	,m_slashCnt(0)
	,m_slashAnime(0)
	,m_deg(0)
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
	m_scrollPos = { 0,0 };	//�X�N���[���ʎ擾�p
	m_slashAnime = 6;
	m_deg = 0;
}

//�X�V����
void CSword::Updata(Math::Vector2 playerPos)
{
	if (!m_bSlash)return;

	m_pos = playerPos;

	//��������
	const int CNT_MAX = m_slashAnime * 2;
	if (m_slashCnt >= CNT_MAX)
	{
		m_bSlash = false;
		m_slashCnt = 0;
	}
	m_slashCnt++;

	//���W�m��
	m_pos += m_move;
	
	// �摜���]����
	if (playerPos.x > m_pos.x) m_size.y = -1;
	else m_size.y = 1;

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
void CSword::Slash(Math::Vector2 Pos, const float deg)
{
	m_bSlash = true;
	m_pos = Pos;
	m_deg = deg;
	const float dist = 64;	// �v���C���[�Ƃ̋���
	m_move.x = cos(DirectX::XMConvertToRadians(m_deg)) * dist;
	m_move.y = sin(DirectX::XMConvertToRadians(m_deg)) * dist;
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
