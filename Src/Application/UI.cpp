#include "UI.h"
#include "Scene.h"

CUI::CUI()
	:m_pbackTexture(nullptr)
	,m_prframeTexture(nullptr)
	,m_plframeTexture(nullptr)
	,m_pHPTexture(nullptr)
	,m_prweaponTexture(nullptr)
	,m_plweaponTexture(nullptr)
	,m_pIconKatanaTexture(nullptr)
	,m_pIconShurikenTexture(nullptr)
	,m_pIconBombTexture(nullptr)
	,m_pStackBombTexture(nullptr)
	,m_backmat()
	, m_rframemat()
	, m_lframemat()
	, m_hpmat()
	,m_stackbombIconmat()
	,m_bombstacks(0)
	,m_keystacks(0)
{
}

CUI::~CUI()
{
}

void CUI::Init()
{
}

void CUI::Updata()
{
	//プレイヤークラス取得
	CPlayer* player=m_pOwner->GetPlayer(); //プレイヤークラスの取得
	int rightWeaponType = player->GetR();
	int leftWeaponType = player->GetL();
	m_hp = player->GetHp();
	m_bombstacks = player->GetBombPossession();
	m_keystacks = player->GetKeyPossession();

	switch (rightWeaponType)
	{
	case eShuriken:
		m_prweaponTexture = m_pIconShurikenTexture;
		break;
	case eSword:
		m_prweaponTexture = m_pIconKatanaTexture;
		break;
	case eBomb:
		m_prweaponTexture = m_pIconBombTexture;
		break;
	default:
		break;
	}

	switch (leftWeaponType)
	{
	case eShuriken:
		m_plweaponTexture = m_pIconShurikenTexture;
		break;
	case eSword:
		m_plweaponTexture = m_pIconKatanaTexture;
		break;
	case eBomb:
		m_plweaponTexture = m_pIconBombTexture;
		break;
	default:
		break;
	}

	m_backmat = DirectX::XMMatrixTranslation(0, -280, 0);
	m_rframemat = DirectX::XMMatrixTranslation(100, -283, 0);
	m_lframemat = DirectX::XMMatrixTranslation(-40, -283, 0);
}

void CUI::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_backmat);
	SHADER.m_spriteShader.DrawTex(m_pbackTexture, Math::Rectangle(0, 0, 600, 140), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_rframemat);
	SHADER.m_spriteShader.DrawTex(m_prweaponTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_lframemat);
	SHADER.m_spriteShader.DrawTex(m_plweaponTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_rframemat);
	SHADER.m_spriteShader.DrawTex(m_prframeTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_lframemat);
	SHADER.m_spriteShader.DrawTex(m_plframeTexture, Math::Rectangle(0, 0, 100, 100), 1.0f);
	
	for (int i = 0; i < m_bombstacks; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_stackbombIconmat);
		Math::Rectangle scrRect = { 0,0,64,64 }; // テクスチャ座標
		Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
		SHADER.m_spriteShader.DrawTex(m_pStackBombTexture, 250-i*15, -255, 64, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}

	for (int i = 0; i < m_keystacks; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_stackkeyIconmat);
		Math::Rectangle scrRect = { 0,0,32,32 }; // テクスチャ座標
		Math::Color color = { 1,1,1,1 }; // 色（RGBAの順番で　0.0～1.0）
		SHADER.m_spriteShader.DrawTex(m_pStackKeyTexture, 250 - i * 30, -310, 32, 32, &scrRect, &color, Math::Vector2(0.5f, 0.5f));
	}

	m_hpbarmat = DirectX::XMMatrixTranslation(-200, -250, 0);//ここは座標
	SHADER.m_spriteShader.SetMatrix(m_hpbarmat);
	SHADER.m_spriteShader.DrawTex(m_pHPbarTexture, Math::Rectangle(0, 0, 110, 28), 1.0f);

	m_hpmat = DirectX::XMMatrixTranslation(-200-((100-m_hp)/2), -250, 0);//ここは座標
	SHADER.m_spriteShader.SetMatrix(m_hpmat);
	SHADER.m_spriteShader.DrawTex(m_pHPTexture, Math::Rectangle(0, 0, m_hp, 18), 1.0f);

	


}

void CUI::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

void CUI::SetbackTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pbackTexture = apTexture;
}

void CUI::SetrframeTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_prframeTexture = apTexture;
}

void CUI::SetlframeTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_plframeTexture = apTexture;
}

void CUI::SetHPTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pHPTexture = apTexture;
}

void CUI::SetHPBarTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pHPbarTexture = apTexture;
}

void CUI::SetIconKatanaTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconKatanaTexture = apTexture;
}

void CUI::SetIconShurikenTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconShurikenTexture = apTexture;
}

void CUI::SetIconBombTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pIconBombTexture = apTexture;
}

void CUI::SetStackBombTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pStackBombTexture = apTexture;
}

void CUI::SetStackKeyTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pStackKeyTexture = apTexture;
}
