#include"CGiant.h"
#include"Utility.h"

CGiant::CGiant()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_bAlive(false)
	, m_hp(HP::GIANT)
	, m_dmg(0)
	, m_deg(0)
	, m_VisibilityFlg(false)
	, m_bSlashHit(false)
	, m_bBlastHit(false)
	, m_bDrop(false)
	, m_moveCnt(MOVE_CNT_MAX)
	, m_rushCnt(0)
	, m_bRush(false)
	, m_bAtk(false)
	, m_atkCnt(0)
	, m_atkRnd(0)
{
}

CGiant::~CGiant()
{
}

// ������
void CGiant::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_hp = HP::GIANT;
	m_dmg = 0;
	m_VisibilityFlg = false;
	m_bSlashHit = false;
	m_bBlastHit = false;
	m_bDrop = false;
	m_rushCnt = 0;
	m_bRush = false;
	m_bAtk = false;
	m_atkCnt = 0;
	m_atkRnd = 0;
}

// �X�V
void CGiant::Update(int mapData)
{
	if (!m_bAlive) return;

	// �_���[�W����
	m_hp -= m_dmg;
	m_dmg = 0;
	// ���S����
	if (m_hp <= 0)
	{
		m_bAlive = false;
		if (mapData == 2) m_bDrop = true;
		return;
	}

	// �v���C���[�Ƃ̋��������߂�
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// �v���C���[�Ƃ̊p�x�����߂� 
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	// ���̋����ɋ߂Â�����
	if (m_dist < 400 ) m_VisibilityFlg = true;		// ����t���O�グ
	// ���̋����ɗ��ꂽ��
	if (m_dist > 500)	m_VisibilityFlg = false;	// ����t���O����

	// �v���C���[���B�ꖪ�g�p��
	if (m_bHidden) m_VisibilityFlg = false;	// ����t���O������

	// ���E���̎�
	if (m_VisibilityFlg) Attack();	//�U���Ԑ�
	// ����O
	else Walk();	//�U��

	// ���W�m��
	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;

	//�s��
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(1.0f, 1.0f, 0.0f);
	m_mat = m_scaleMat * m_transMat;	// �s��쐬
}

// �`��
void CGiant::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 70, 80), 1.0f);
}

// �z�u�֐�
void CGiant::SetGiant(Math::Vector2 pos)
{
	m_pos = pos;
	m_bAlive = true;
}

// �e�N�X�`���ݒ�
void CGiant::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pTexture = apTexture;
}

// X���W�Z�b�g
void CGiant::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y���W�Z�b�g
void CGiant::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X�ړ��ʃZ�b�g
void CGiant::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

//  Y�ړ��ʃZ�b�g
void CGiant::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

//  �����t���O�ݒ�
void CGiant::SetAlive()
{
	m_bAlive = false;
}

// �_���[�W����
void CGiant::SetDamage(int dmg)
{
	m_dmg += dmg;
}

// �a���q�b�g�t���O�Z�b�g
void CGiant::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// �����q�b�g�t���O�Z�b�g
void CGiant::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}

// �h���b�v�t���O�Z�b�g
void CGiant::bSetDrop()
{
	m_bDrop = false;
}

// �X�N���[���ʎ擾�p
void CGiant::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// �v���C���[�̍��W�擾
void CGiant::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

// �B��g��Ԏ擾
void CGiant::bSetHidden(bool flg)
{
	m_bHidden = flg;
}

// �U���֐�
void CGiant::Attack()
{
	// �����_���s��
	switch (m_atkRnd)
	{
	case 1:
		m_bAtk = true;
		Rush();	// �ːi
		break;
	default:
		Homing(SPEED::GIANT_NORMAL);	// �������߂Â�
		break;
	}

	// �s���ω��J�E���g
	if (m_atkRnd == 1)return;
	if (m_atkCnt >= COOL_TIME::GIANT_ATK)
	{
		m_atkCnt = COOL_TIME::GIANT_ATK;
		// �U�����ĂȂ��Ƃ�
		if (!m_bAtk)
		{
			m_atkRnd = 1;
			m_atkCnt = 0;
		}
	}
	m_atkCnt++;
}

// �z�[�~���O����
void CGiant::Homing(float sp)
{
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;
}

// �ːi
void CGiant::Rush()
{
	if (m_rushCnt >= RUSH_CNT_MAX)
	{
		m_rushCnt = 0;
		m_atkRnd = 0;
		m_bAtk = false;
	}
	else if (m_rushCnt >= RUSH_CNT_MAX / 1.2)
	{
		m_moveVal = { 0,0 };
		m_bRush = false;
	}
	else if (m_rushCnt >= RUSH_CNT_MAX / 2.5)
	{
		if (!m_bRush) Homing(SPEED::GIANT_RUSH);
		m_bRush = true;
	}
	else if (m_rushCnt >= 0)
	{
		const float sp = SPEED::GIANT_NORMAL;
		m_moveVal.x = -cos(DirectX::XMConvertToRadians(m_deg)) * sp;
		m_moveVal.y = -sin(DirectX::XMConvertToRadians(m_deg)) * sp;
	}
	m_rushCnt++;
}

// �p�j����
void CGiant::Walk()
{
	if (m_moveCnt >= MOVE_CNT_MAX)
	{
		const int rnd = 2;	// �����_����
		float moveX = (rand() % rnd - rnd/2);
		float moveY = (rand() % rnd - rnd/2);

		// �����_���ړ��ʃZ�b�g
		switch (int r = rand() % 16)
		{
		case 1:
			m_moveVal = { moveX, moveY };
			break;
		case 2:
			m_moveVal = { -moveX, -moveY };
			break;
		case 3:
			m_moveVal = { -moveX, moveY };
			break;
		case 4:
			m_moveVal = { moveX, -moveY };
			break;
		default:
			m_moveVal = { 0, 0 };
			break;
		}
		m_moveCnt = 0;
	}
	m_moveCnt++;
}