#pragma once

class Scene;

class CBullet
{
public:
	CBullet();
	~CBullet();

	void Init();
	void Updata();
	void Draw();
	
	const Math::Vector2 CBullet::GetPos();		//座標取得
	const Math::Vector2 CBullet::GetMove();		//移動量取得
	const float CBullet::GetRadius();			//半径取得
	const bool IsAlive();

	void SetTexture(KdTexture* apTexture);
	void SetAlive(const float bAlive);			//フラグ状態設定
	
	void Shot(const Math::Vector2 aShotPos,float deg);
	
	void SetScrollPos(Math::Vector2 scrPos);

private:
	KdTexture*		m_pTexture;		//画像
	Math::Vector2	m_pos;
	Math::Vector2	m_moveVal;
	Math::Matrix	m_mat;
	bool			m_bAlive;
	const float		m_radius;
	float			m_deg;
	Math::Vector2	m_scrollPos;

};