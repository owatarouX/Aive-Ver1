#pragma once

class CArrow
{
public:
	CArrow();
	~CArrow();

	void Init();			// ������
	void Update();			// �X�V
	void Draw();			// �`��

	const bool IsAlive() { return m_bAlive; }	// �����m�F
	Math::Vector2 GetPos() { return m_pos; }	// ���W�擾
	Math::Vector2 GetMove() { return m_moveVal; }	// �ړ��ʎ擾

	void SetTexture(KdTexture* apTexture);
	void SetAlive();			//�t���O��Ԑݒ�
	void SetScrollPos(Math::Vector2 scrPos);	//�X�N���[���ʎ擾

	void Shot(const Math::Vector2 aScrPos,const Math::Vector2 aDestPos);

private:
	KdTexture*		m_pTexture;		//�摜
	Math::Vector2	m_pos;			//���W
	Math::Vector2	m_moveVal;		//�ړ���
	Math::Matrix	m_mat;			//�����s��
	bool			m_bAlive;		//�����t���O
	float			m_deg;			//�p�x

	Math::Vector2	m_scrollPos;
};

