#pragma once

class CBlack
{
public:
	CBlack();
	~CBlack();

	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��
	void SetTexture(KdTexture* apTexture);	//�e�N�X�`���ݒ�

	//�p�[�e�B�N�������֐�
	void EmitBlack();

private:
	Math::Vector2	m_pos;		//���W
	Math::Vector2	m_move;		//�ړ���
	float			m_size;		//�T�C�Y
	Math::Color		m_color;	//�F
	int				m_lifeSpan;	//�L������(�������E)
	Math::Matrix	m_mat;		//�s��
	float			m_transcnt; //���߃J�E���g
	KdTexture* m_pTexture;	//�e�N�X�`��(�A�h���X)
};

