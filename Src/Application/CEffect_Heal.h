#pragma once

class CEffect_Heal
{
public:
	CEffect_Heal();
	~CEffect_Heal();

	void Init();
	void UpDate(Math::Vector2 scrollPos);
	void Draw();

	bool GetbAlive() { return m_bAlive; }
	Math::Vector2 GetPos() { return m_pos; }

	void SetTexture(KdTexture* apTexture);
	void EmitHeal(Math::Vector2 pos, Math::Vector2 move);

private:
	KdTexture* m_pTexture;			// �摜(�e�N�X�`��)
	Math::Vector2	 m_pos;			// ���W
	Math::Vector2	 m_moveVal;		// �ړ���
	Math::Matrix	 m_mat;			// �s��
	bool			 m_bAlive;		// �����t���O
	float			 m_size;		// �T�C�Y
	Math::Color		 m_color;		// �F
	int				 m_lifeSpan;	// �L������(�������E)
};
