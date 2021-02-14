#include"CBoss.h"
#include"Utility.h"

CBoss::CBoss()
	:attackType(Homing)
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
	, m_battleStartFlg(false)
{
}

CBoss::~CBoss()
{
}

void CBoss::Init()
{
	attackType = Rush;
	m_direction = BUp;
	m_bAlive = false;
	m_hp = HP::BOSS;
	m_dmg = 0;
	m_bSlashHit = false;
	m_bBlastHit = false;

	m_bSlash = false;
	m_slashCnt = 0;

	playerHitFlg = false;
	m_bAtk = false;

	m_atkCnt = 0;

	m_battleStartFlg = false;
}

void CBoss::Update()
{
	if (!m_bAlive) return;

	// ダメージ処理
	m_hp -= m_dmg;
	m_dmg = 0;

	// 死亡処理
	if (m_hp <= 0)
	{
		m_bAlive = false;
		return;
	}

	playerHitFlg = false;	// 円判定の時に使用

	// プレイヤーとの角度を求める(向きを決めるよう)
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

	// プレイヤーとの距離を求める
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// プレイヤーとの角度を求める
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);
	m_moveVal = { 0.0f,0.0f };

	if (m_slashCnt >= COOL_TIME::BOSS_SLASH) { m_slashCnt = COOL_TIME::BOSS_SLASH; }
	m_slashCnt++;

	if (m_battleStartFlg)
	{
		Attake();
	}

	if (m_dist < 100)
	{
		playerHitFlg = true;
	}

	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;
	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
}

void CBoss::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 256, 256), 1.0f);	// �`��
}

void CBoss::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pTexture = apTexture;
}

void CBoss::SetPosX(float posX)
{
	m_pos.x = posX;
}

void CBoss::SetPosY(float posY)
{
	m_pos.y = posY;
}

void CBoss::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

void CBoss::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

void CBoss::SetAlive()
{
	m_bAlive = false;
}

void CBoss::SetDamage(int dmg)
{
	m_dmg += dmg;
}

void CBoss::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

void CBoss::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}
void CBoss::SetShotFlg(bool flg)
{
	m_shotFlg = flg;
}
void CBoss::SetAtkFlg()
{
	m_bAtk = true;
}
void CBoss::bSetButtleStart()
{
	m_battleStartFlg = true;
}
void CBoss::SetBoss(Math::Vector2 pos)
{
	m_pos = pos;
	m_bAlive = true;
}
void CBoss::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
void CBoss::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

void CBoss::SetSlash(bool slash)
{
	m_bSlash = slash;
}

//攻撃関数
void CBoss::Attake()
{
	if (!m_bAtk)
	{
		if (m_atkCnt <= 0)	// 攻撃していないとき
		{
			atkTypeRnd();
			m_bAtk = true;
		}
	}
	m_atkCnt++;
	switch (attackType)
	{
	case Homing:BossMoveHoming(SPEED::BOSS);
		break;
	case Slash:BossMoveSlash();
		break;
	case Shot:BossMoveShot();
		break;
	case Rush:BossMoveRush();
		break;
	}
}

// ボスの行動１：追跡
void CBoss::BossMoveHoming(float sp)
{
	atkSleep(40);
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// cos
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;	// sin
}

// ボスの行動２：斬撃
void CBoss::BossMoveSlash()
{
	atkSleep(180);
	if (!m_bAtk)return;
	if (m_slashCnt >= COOL_TIME::BOSS_SLASH)
	{
		m_slashCnt = 0;
		m_bSlash = true;	// �a�����s
		m_bAtk = false;
	}
}

// ボスの行動３：発射
void CBoss::BossMoveShot()
{
	atkSleep(120);
	
	if (m_atkCnt <= 80)
	{
		const float sp = 2;
		m_moveVal.x = -cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// -��t���Ĉ�����\��
		m_moveVal.y = -sin(DirectX::XMConvertToRadians(m_deg)) * sp;
	}
	else
	{
		if (!m_bAtk)return;
		if (m_shotFlg)
		{
			m_shotCnt = 0;	// �J�E���g���Z�b�g
			m_shotFlg = false;	// ���˃t���O����
			m_bAtk = false;
		}
	}
	// ���˂��ꂽ��
	
	// ���˃J�E���g
	if (m_shotCnt <= COOL_TIME::BOSS_ARROW) m_shotCnt++;
}

// ボスの行動４：突進
void CBoss::BossMoveRush()
{
	atkSleep(180);
	if (!m_bAtk)return;
	if (m_rushCnt >= RUSH_CNT_MAX)
	{
		m_rushCnt = 0;
		m_bAtk = false;
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

// 攻撃ランダム変化
void CBoss::atkTypeRnd()
{
	int r = rand() % 20+1;
	if (r <= 2)			attackType = Slash;
	else if (r <= 4)	attackType = Shot;
	else if (r <= 6)	attackType = Rush;
	else				attackType = Homing;
}

// モーション時間
void CBoss::atkSleep(int cnt)
{
	if (m_atkCnt >= cnt)
	{
		m_bAtk = false;
		m_atkCnt = 0;
	}
}

