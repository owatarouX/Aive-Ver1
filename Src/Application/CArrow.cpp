#include"CArrow.h"
#include"Utility.h"

CArrow::CArrow()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_bAlive(false)
	, m_deg()
	, m_direct(LEFT)
	, m_bDirect(false)
{
}

CArrow::~CArrow()
{
}

// 初期化
void CArrow::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_deg = 0;
	m_direct = LEFT;
	m_bDirect = false;
}

// 更新
void CArrow::Update()
{
	if (!m_bAlive) return;

	/*if (!m_bDirect)
	{
		switch (ArrowDirect())
		{
		case LEFT:
			m_direct = LEFT;
			break;
		case RIGHT:
			m_direct = RIGHT;
			break;
		case TOP:
			m_direct = TOP;
			break;
		case DOWN:
			m_direct = DOWN;
			break;
		default:
			MessageBox(NULL, L"no", L"hit", MB_OK);
			break;
		}
		m_bDirect = true;
	}*/

	//座標確定
	m_pos += m_moveVal;

	//行列作成
	Math::Matrix scaleMat, RotMat,transMat;
	//拡縮行列
	scaleMat = DirectX::XMMatrixScaling(1, 1, 1);
	//回転行列
	RotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_deg));
	//移動行列
	transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	//行列合成
	m_mat = scaleMat * RotMat * transMat;
}

// 描画
void CArrow::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(32, 0, 32, 32), 1.0f);
}

// テクスチャ設定：
void CArrow::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

// フラグ変更
void CArrow::SetAlive()
{
	m_bAlive = false;
}

void CArrow::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// 発射処理関数
void CArrow::Shot(const Math::Vector2 aScrPos, const Math::Vector2 aDestPos)
{
	if (m_bAlive) return;

	m_pos = aScrPos;	// 発射座標

	m_deg = Utility::GetAngleDeg(aScrPos, aDestPos);
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * SPEED::ARROW;
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * SPEED::ARROW;

	m_bAlive = true;
}

// 矢の向き判別関係
int CArrow::ArrowDirect()
{
	float s = 45.0f;
	if		((m_deg >= s * 3) && (m_deg < s * 5)) return LEFT;
	else if ((m_deg >= s * 7) || (m_deg < s)) return RIGHT;
	else if ((m_deg >= s)	  && (m_deg < s * 3)) return TOP;
	else if ((m_deg >= s * 5) && (m_deg < s * 7)) return DOWN;
}
