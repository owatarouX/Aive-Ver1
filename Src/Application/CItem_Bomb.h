#pragma once

class CItem_Bomb
{
public:
	CItem_Bomb();
	~CItem_Bomb();

	void Init();
	void Update();
	void Draw();
	void SetTexture_t(KdTexture* apTexture);
	void SetTexture_f(KdTexture* apTexture);
	void SetBomb(Math::Vector2 Pos);		//���W�Z�b�g�A�t���O����
	void SetAlive();				//�����t���O�ύX
	void bSetbombHit();				//���e�A�C�e���q�b�g�t���O�Z�b�g
	void SetScrollPos(Math::Vector2 scrPos);

	bool GetAlive() { return m_bAlive; }
	Math::Vector2 GetPos() { return m_pos; }

private:
	KdTexture* m_pTexture_t;			//�摜(true)
	KdTexture* m_pTexture_f;			//�摜(false)
	Math::Matrix m_mat;			//�s��
	Math::Vector2 m_pos;		//���W
	bool m_bAlive;				//�����t���O
	bool m_bBombHit;			//���e�A�C�e���q�b�g�t���O

	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p

};

