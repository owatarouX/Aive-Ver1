#include "CArcher.h"
#include"CArrow.h"
#include"Utility.h"

CArcher::CArcher()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_bAlive(false)
	, m_hp(HP::ARCHER)
	, m_deg()
	, m_VisibilityFlg(false)
	, m_shotFlg(false)
	, m_shotCnt(0)
{
}

CArcher::~CArcher()
{
}

//������
void CArcher::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_hp = HP::ARCHER;
	m_VisibilityFlg = false;
	m_shotFlg = false;
	m_shotCnt = 0;
}

//�X�V
void CArcher::Update()
{
	if (!m_bAlive) return;
	
	// �_���[�W����
	m_hp -= m_dmg;
	m_dmg = 0;

	// ���S����
	if (m_hp <= 0)
	{
		m_bAlive = false;
		m_shotCnt = 0;
		return;
	}

	m_moveVal = { 0,0 };

	// �v���C���[�Ƃ̋��������߂�
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// �v���C���[�Ƃ̊p�x�����߂� 
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);


	// ���̋����ɋ߂Â�����
	if (m_dist < 350)
		m_VisibilityFlg = true;		// ����t���O�グ
	// ��苗�����ꂽ��
	if (m_dist > 500)
		m_VisibilityFlg = false;	// ����t���O����

	// �v���C���[���B�ꖪ�g�p���A����t���O������
	if (m_bHidden)m_VisibilityFlg = false;

	if (m_VisibilityFlg)
	{
		// �v���C���[���߂Â��ė�����
		if (m_dist < 200)
		{
			// �v���C���[���瓦����
			float spd = SPEED::ARCHER;
			m_moveVal.x = -(cos(DirectX::XMConvertToRadians(m_deg)) * spd);
			m_moveVal.y = -(sin(DirectX::XMConvertToRadians(m_deg)) * spd);
		}
	}


	// ���˂��ꂽ��
	if (m_shotFlg)
	{
		m_shotCnt = 0;	// �J�E���g���Z�b�g
		m_shotFlg = false;			// ���˃t���O����
	}
	// ���˃J�E���g
	if (m_shotCnt <= COOL_TIME::ARCHER_ARROW) m_shotCnt++;


	// ���W�m��
	m_pos += m_moveVal;

	//�s��
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(1.0f, 1.0f, 0.0f);
	m_mat = m_scaleMat * m_transMat;	// �s��쐬
}

//�`��
void CArcher::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);	
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 64, 64), 1.0f);	
}

//�e�N�X�`���ݒ�
void CArcher::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//�|���ݒu
void CArcher::SetArchaer(Math::Vector2 pos)
{
	m_pos = pos;

	m_bAlive = true;
}

// X���W�Z�b�g
void CArcher::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y���W�Z�b�g
void CArcher::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X�ړ��ʃZ�b�g
void CArcher::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

// Y�ړ��ʃZ�b�g
void CArcher::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

// �����t���O�ݒ�
void CArcher::SetAlive()
{
	m_bAlive = false;
}

// �_���[�W����
void CArcher::SetDamage(int dmg)
{
	m_hp -= dmg;
}

// ���˃t���O�ݒ�
void CArcher::SetShotFlg(bool flg)
{
	m_shotFlg = flg;
}

// �a���q�b�g�t���O�Z�b�g
void CArcher::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// �����q�b�g�t���O�Z�b�g
void CArcher::bSetBlastHit(bool aHit)
{
	m_bBlastHit=aHit;
}

//�X�N���[���ʎ擾
void CArcher::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// �v���C���[�̍��W�擾
void CArcher::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

void CArcher::bSetHidden(bool flg)
{
	m_bHidden = flg;
}

