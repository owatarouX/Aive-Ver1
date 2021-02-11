#include"CBoss.h"
#include"Utility.h"

CBoss::CBoss()
	:attackType(Stop)
	, m_direction()
	, m_pTexture(nullptr)
	, m_pos(0.0f, 0.0f)
	, m_moveVal(0.0f, 0.0f)
	, m_mat()
	, m_bAlive(false)
	, m_hp(HP::BOSS)
	, m_dmg(0)
	, m_deg(0.0f)
	, m_bSlashHit(false)
	, m_bBlastHit(false)
	, m_bSlash(false)
	, m_slashCnt(0)
	, m_shotFlg(false)
	, m_shotCnt(0)
	, m_moveCnt(MOVE_CNT_MAX)
	, m_rushCnt(0)
	, m_bRush(false)
	, m_bAtk(false)
	, m_atkCnt(0)
	, m_atkRnd(0)
	, m_scrollPos(0.0f, 0.0f)
	, m_playerPos(0.0f, 0.0f)
	, playerHitFlg(false)
{
}

CBoss::~CBoss()
{
	
}

void CBoss::Init()
{
	attackType = Stop;
	m_direction = BUp;
	m_bAlive = false;
	m_dmg = 0;
	m_bSlashHit = false;
	m_bBlastHit = false;

	m_bSlash = false;
	m_slashCnt = 0;

	playerHitFlg = false;
	attackType = Stop;
}

void CBoss::Update()
{
	if (!m_bAlive) return;

	playerHitFlg = false;	// �~����̎��Ɏg�p

	// �v���C���[�Ƃ̊p�x����߂�(��������߂�悤)
	float m_DirectionDeg = Utility::GetAngleDeg(m_pos, m_playerPos);

	if (m_DirectionDeg > 45 && m_DirectionDeg < 135)
	{
		m_direction = BUp;
	}
	else if (m_DirectionDeg > 135 && m_DirectionDeg < 225)
	{
		m_direction = BLeft;
	}
	else if (m_DirectionDeg > 225 && m_DirectionDeg < 315)
	{
		m_direction = BDown;
	}
	else if (m_DirectionDeg < 45 && m_DirectionDeg > 0 || m_DirectionDeg < 360 && m_DirectionDeg > 315)
	{
		m_direction = BRight;
	}
	// �_���[�W����
	m_hp -= m_dmg;
	m_dmg = 0;

	// ���S����
	if (m_hp <= 0)
	{
		m_bAlive = false;
		return;
	}

	// �v���C���[�Ƃ̋�������߂�
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// �v���C���[�Ƃ̊p�x����߂�
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);
	m_moveVal = { 0.0f,0.0f };

	if (m_slashCnt >= COOL_TIME::BOSS_SLASH) { m_slashCnt = COOL_TIME::BOSS_SLASH; }

	m_slashCnt++;


	Attake();
	if (m_dist < 100)
	{
		playerHitFlg = true;
		//MessageBox(NULL, L"Hit", L"hit", MB_OK);
	}
	else if (m_dist > 100 && m_dist < 300)
	{
		//attackType = Slash;
		//BossMoveRush();
	}
	else if (m_dist > 300 && m_dist < 400 )
	{
		attackType = Homing;
	}
	else if (m_dist > 600 && m_dist < 800)
	{
		//attackType = Shot;
	}



	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;
	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
}

void CBoss::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);	// �s��Z�b�g
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 256, 256), 1.0f);	// �`��
}

void CBoss::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;	// �|�C���^�̃A�h���X�����킩���ׂ�(null�Ȃ�Z�b�g���Ȃ�)

	m_pTexture = apTexture;
}

// X���W�Z�b�g
void CBoss::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y���W�Z�b�g
void CBoss::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X���W�ړ���
void CBoss::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

// Y���W�ړ���
void CBoss::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

// �����t���O�ݒ�
void CBoss::SetAlive()
{
	m_bAlive = false;
}

// �_���[�W����
void CBoss::SetDamage(int dmg)
{
	m_dmg += dmg;
}

// �a���̃q�b�g�t���O�Z�b�g
void CBoss::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// �����q�b�g�t���O�Z�b�g
void CBoss::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}
// ���˃t���O�ݒ�
void CBoss::SetShotFlg(bool flg)
{
	m_shotFlg = flg;
}
void CBoss::SetBoss(Math::Vector2 pos)
{
	m_pos = pos;
	m_bAlive = true;
}
//�X�N���[���ʎ擾
void CBoss::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
// �v���C���[�̍��W�擾
void CBoss::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

void CBoss::SetSlash(bool slash)
{
	m_bSlash = slash;
}

//�{�X�̍U��
void CBoss::Attake()
{

	switch (attackType)
	{
	case Stop:
		break;
	case Homing:BossMoveHoming(SPEED::BOSS);
		break;
	case Slash:BossMoveSlash();
		break;
	case Shot:BossMoveShot();
		break;
	case Rush:BossMoveRush();
		break;
	default:
		break;
	}
}

// �{�X�̍s���P �z�[�~���O
void CBoss::BossMoveHoming(float sp)
{
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// cos
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;	// sin
}

// �{�X�̍s���Q�F�a��
void CBoss::BossMoveSlash()
{
	if (m_slashCnt >= COOL_TIME::BOSS_SLASH)
	{
		m_slashCnt = 0;
		m_bSlash = true;	// �a�����s
	}
}

// �{�X�̍s���R�F����
void CBoss::BossMoveShot()
{
	// ���˂��ꂽ��
	if (m_shotFlg)
	{
		m_shotCnt = 0;	// �J�E���g���Z�b�g
		m_shotFlg = false;	// ���˃t���O����
	}
	// ���˃J�E���g
	if (m_shotCnt <= COOL_TIME::BOSS_ARROW) m_shotCnt++;
}
// �{�X�̍s���S�F�ːi
void CBoss::BossMoveRush()
{
	if (m_rushCnt >= RUSH_CNT_MAX)
	{
		m_rushCnt = 0;
		//m_bAtk = false;
	}
	else if (m_rushCnt >= RUSH_CNT_MAX - RUSH_CNT_MAX / 6)
	{
		m_moveVal = { 0,0 };
		m_bRush = false;
	}
	else if (m_rushCnt >= RUSH_CNT_MAX / 7)
	{
		if (!m_bRush)
		{
			m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);
		}

		m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * 5;	// cos
		m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * 5;

		m_bRush = true;
	}
	else if (m_rushCnt >= 0)
	{
		const float sp = 2;// �X�s�[�h
		m_moveVal.x = -cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// -��t���Ĉ�����\��
		m_moveVal.y = -sin(DirectX::XMConvertToRadians(m_deg)) * sp;	//
	}
	m_rushCnt++;
}
