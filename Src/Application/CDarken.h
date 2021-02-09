#pragma once
// �}�b�v�F�Ó]

class CDarken
{
public:
	CDarken();
	~CDarken();

	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��
	void SetTexture(KdTexture* apTexture);	//�e�N�X�`���ݒ�
	float Rnd();	//0�`1�̗��������߂�֐�

	//�p�[�e�B�N�������֐�
	void EmitDark();

private:
	Math::Vector2	m_pos;		//���W
	Math::Vector2	m_move;		//�ړ���
	float			m_size;		//�T�C�Y
	Math::Color		m_color;	//�F
	int				m_lifeSpan;	//�L������(�������E)
	Math::Matrix	m_mat;		//�s��
	KdTexture* m_pTexture;	//�e�N�X�`��(�A�h���X)
};

