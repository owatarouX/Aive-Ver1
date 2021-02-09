#include"CArrow.h"
#include"Utility.h"

CArrow::CArrow()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_bAlive(false)
	, m_deg()
	, m_scrollPos(0,0)
{
}

CArrow::~CArrow()
{
}

// ������
void CArrow::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_deg = 0;
}

// �X�V
void CArrow::Update()
{
	if (!m_bAlive) return;

	//���W�m��
	m_pos += m_moveVal;

	//�s��쐬
	Math::Matrix scaleMat, RotMat,transMat;
	//�g�k�s��
	scaleMat = DirectX::XMMatrixScaling(1, 1, 1);
	//��]�s��
	RotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_deg));
	//�ړ��s��
	transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	//�s�񍇐�
	m_mat = scaleMat * RotMat * transMat;
}

// �`��
void CArrow::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(32, 0, 32, 32), 1.0f);
}

// �e�N�X�`���ݒ�F
void CArrow::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

// �t���O�ύX
void CArrow::SetAlive()
{
	m_bAlive = false;
}

void CArrow::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// ���ˏ����֐�
void CArrow::Shot(const Math::Vector2 aScrPos, const Math::Vector2 aDestPos)
{
	if (m_bAlive) return;

	m_pos = aScrPos;	// ���ˍ��W

	m_deg = Utility::GetAngleDeg(aScrPos, aDestPos);
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * SPEED::ARROW;
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * SPEED::ARROW;

	m_bAlive = true;
}
