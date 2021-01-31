#pragma once

class Scene;

class CUI
{
public:
	CUI();
	~CUI();

	void Init();
	void Updata();
	void Draw();

	void SetOwner(Scene* apOwner);

	/*テクスチャ*/
	void SetbackTexture(KdTexture* apTexture);
	void SetrframeTexture(KdTexture* apTexture);
	void SetlframeTexture(KdTexture* apTexture);
	void SetHPTexture(KdTexture* apTexture);
	void SetHPBarTexture(KdTexture* apTexture);
	void SetIconKatanaTexture(KdTexture* apTexture);
	void SetIconShurikenTexture(KdTexture* apTexture);
	void SetIconBombTexture(KdTexture* apTexture);
	void SetStackBombTexture(KdTexture* apTexture);

private:
	KdTexture* m_pbackTexture;
	KdTexture* m_prframeTexture;
	KdTexture* m_plframeTexture;
	KdTexture* m_pHPTexture;
	KdTexture* m_pHPbarTexture;

	KdTexture* m_prweaponTexture;
	KdTexture* m_plweaponTexture;

	KdTexture* m_pIconKatanaTexture;
	KdTexture* m_pIconShurikenTexture;
	KdTexture* m_pIconBombTexture;

	KdTexture* m_pStackBombTexture;

	Math::Matrix m_backmat;
	Math::Matrix m_rframemat;
	Math::Matrix m_lframemat;
	Math::Matrix m_hpmat;
	Math::Matrix m_hpbarmat;
	Math::Matrix m_stackIconmat;

	int m_hp;//HP取得用
	int m_bombstacks; //爆弾の所持数取得用
	//int m_weaponType; //プレイヤーの武器種取得用

	Scene* m_pOwner;			//オーナー取得用
};