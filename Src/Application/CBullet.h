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
	
	const Math::Vector2 CBullet::GetPos();		//���W�擾
	const Math::Vector2 CBullet::GetMove();		//�ړ��ʎ擾
	const bool IsAlive();

	void SetTexture(KdTexture* apTexture);
	void SetAlive();			//�t���O��Ԑݒ�
	
	void Shot(const Math::Vector2 aShotPos,float deg);
	
	void SetScrollPos(Math::Vector2 scrPos);

private:
	KdTexture*		m_pTexture;		//�摜
	Math::Vector2	m_pos;
	Math::Vector2	m_moveVal;
	Math::Matrix	m_mat;
	bool			m_bAlive;
	float			m_deg;
	Math::Vector2	m_scrollPos;

};