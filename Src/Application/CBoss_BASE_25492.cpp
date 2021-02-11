#include"CBoss.h"
#include"Utility.h"

CBoss::CBoss()
	:attackType()
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
{
}

CBoss::~CBoss()
{
	
}

void CBoss::Init()
{
	m_bAlive = false;
	m_dmg = 0;
	m_bSlashHit = false;
	m_bBlastHit = false;

	m_bSlash = false;
	m_slashCnt = 0;

	attackType = Stop;
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

	// プレイヤーとの距離を求める
	float m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// プレイヤーとの角度を求める
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);
	m_moveVal = { 0.0f,0.0f };

	if (m_slashCnt >= COOL_TIME::BOSS_SLASH) { m_slashCnt = COOL_TIME::BOSS_SLASH; }

	m_slashCnt++;


	Attake();
	// MessageBox(NULL, L"HIT", L"hit", MB_OK);
	if (m_dist < 400 && m_dist > 300)
	{
		attackType = Homing;
	}
	else if (m_dist < 300)
	{
		attackType = Slash;
	}
	else if (m_dist > 400 && m_dist < 800)
	{
		attackType = Shot;
	}



	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;
	m_mat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
}

void CBoss::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);	// 行列セット
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 256, 256), 1.0f);	// 描画
}

void CBoss::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;	// ポインタのアドレスが正常か調べる(nullならセットしない)

	m_pTexture = apTexture;
}

// X座標セット
void CBoss::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y座標セット
void CBoss::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X座標移動量
void CBoss::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

// Y座標移動量
void CBoss::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

// 生存フラグ設定
void CBoss::SetAlive()
{
	m_bAlive = false;
}

// ダメージ処理
void CBoss::SetDamage(int dmg)
{
	m_dmg += dmg;
}

// 斬撃のヒットフラグセット
void CBoss::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// 爆風ヒットフラグセット
void CBoss::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}
// 発射フラグ設定
void CBoss::SetShotFlg(bool flg)
{
	m_shotFlg = flg;
}
void CBoss::SetBoss(Math::Vector2 pos)
{
	m_pos = pos;
	m_bAlive = true;
}
//スクロール量取得
void CBoss::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}
// プレイヤーの座標取得
void CBoss::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

void CBoss::SetSlash(bool slash)
{
	m_bSlash = slash;
}

//ボスの攻撃
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

// ボスの行動１ ホーミング
void CBoss::BossMoveHoming(float sp)
{
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// cos
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;	// sin
}

// ボスの行動２：斬撃
void CBoss::BossMoveSlash()
{
	if (m_slashCnt >= COOL_TIME::BOSS_SLASH)
	{
		m_slashCnt = 0;
		m_bSlash = true;	// 斬撃実行
	}
}

// ボスの行動３：発射
void CBoss::BossMoveShot()
{
	// 発射された時
	if (m_shotFlg)
	{
		m_shotCnt = 0;	// カウントリセット
		m_shotFlg = false;	// 発射フラグ下げ
	}
	// 発射カウント
	if (m_shotCnt <= COOL_TIME::BOSS_ARROW) m_shotCnt++;
}
// ボスの行動４：突進
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
		if (!m_bRush) BossMoveHoming(5.0);
		m_bRush = true;
	}
	else if (m_rushCnt >= 0)
	{
		const float sp = 3;// スピード
		m_moveVal.x = -cos(DirectX::XMConvertToRadians(m_deg)) * sp;
		m_moveVal.y = -sin(DirectX::XMConvertToRadians(m_deg)) * sp;
	}
	m_rushCnt++;
}
