#pragma once

class CEnemySword
{
public:
	CEnemySword();
	~CEnemySword();

	void Init();
	void Updata(Math::Vector2 playerPos);
	void Draw();
	void SetTexture(KdTexture* apTexture);
	const Math::Vector2 CEnemySword::GetPos();		//���W�擾
	const Math::Vector2 CEnemySword::GetMove();		//�ړ��ʎ擾
	const bool bGetSlash();		//�t���O��Ԏ擾
	
	const Math::Vector2 GetSize() { return m_size; }		// �T�C�Y�擾

	//�U������
	void Slash(Math::Vector2 Pos, float Deg,Math::Vector2 size, float s);	// �G�a���Ăяo��&�G���W�A�G�ƃv���C���[�̊p�x�A�T�C�Y�A����
	void SetScrollPos(Math::Vector2 scrPos);	//�X�N���[���ʎ擾

private:

	KdTexture* m_pTexture;	//�摜(�e�N�X�`��)
	Math::Vector2	 m_pos;			//���W
	Math::Vector2	 m_move;		//�ړ���
	Math::Matrix	 m_mat;			//�s��
	Math::Matrix	 m_transMat;	//�ړ��s��
	Math::Matrix	 m_scaleMat;	//�g��s��
	Math::Vector2	 m_size;		//�g��T�C�Y
	bool			 m_bSlash;		//�U���t���O
	int				 m_slashCnt;	//�U����������
	int				 m_slashAnime;	//�A�j���[�V����
	float			 m_deg;			//�p�x
	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p

};

