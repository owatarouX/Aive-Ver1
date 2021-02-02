#pragma once
// �A�C�e���F�B�ꖪ

class CItem_Mino
{
public:
	CItem_Mino();
	~CItem_Mino();

	bool GetAlive() { return m_bAlive; }
	Math::Vector2 GetPos() { return m_pos; }

	void Init();
	void Update();
	void Draw();
	void SetTexture(KdTexture* apTexture);
	void SetMino(Math::Vector2 Pos);	// �A�C�e���Z�b�g
	void SetAlive();				//�����t���O�ύX
	void SetScrollPos(Math::Vector2 scrPos);

private:
	KdTexture* m_pTexture;			//�摜(�e�N�X�`��)
	Math::Matrix m_mat;			//�s��
	Math::Vector2 m_pos;		//���W
	bool m_bAlive;				//�����t���O
	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p

};
