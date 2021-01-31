#pragma once
//�G�N���X�F�|��

class CArcher
{
public:
	CArcher();
	~CArcher();

	void Init();			// ������
	void Update();			// �X�V
	void Draw();			// �`��
	
	const bool IsAlive() { return m_bAlive; }	// �����m�F
	Math::Vector2 GetPos() { return m_pos; }	// ���W�擾
	Math::Vector2 GetMove() { return m_moveVal; }	// �ړ��ʎ擾
	const bool GetbVisibility() { return m_VisibilityFlg; }		// ����t���O�擾
	const int GetShotCnt() { return m_shotCnt; }	// ���˃J�E���g�擾
	const bool bGetSlashHit() { return m_bSlashHit; }	// �a���q�b�g�t���O�擾
	const bool bGetBlastHit() { return m_bBlastHit; }	// �����q�b�g�t���O�擾

	void SetArchaer(Math::Vector2 pos);		// �|���ݒu
	void SetTexture(KdTexture* apTexture);	// �e�N�X�`���󂯎��
	void SetPosX(float posX);	// X���W�Z�b�g
	void SetPosY(float posY);	// Y���W�Z�b�g
	void SetMoveX(float moveX);	// X�ړ��ʃZ�b�g
	void SetMoveY(float moveY);	// Y�ړ��ʃZ�b�g
	void SetAlive();	// �����t���O�ݒ�
	void SetDamage(int dmg);	// �_���[�W���Z
	void SetShotFlg(bool flg);	// ���˃t���O�ݒ�
	void bSetSlashHit(bool aHit);	// �a���q�b�g�t���O�Z�b�g
	void bSetBlastHit(bool aHit);	// �����q�b�g�t���O�Z�b�g

	void SetScrollPos(Math::Vector2 scrPos);	//�X�N���[���ʎ擾
	void SetPlayerPos(Math::Vector2 pos);		// �v���C���[�̍��W�擾

private:

	KdTexture* m_pTexture;		// �摜(�e�N�X�`��)
	Math::Vector2	m_pos;		// ���W
	Math::Vector2	m_moveVal;	// �ړ���
	Math::Matrix	m_mat;		// �����s��
	Math::Matrix	m_transMat;	// �ړ��s��
	Math::Matrix	m_scaleMat;	// �g��s��
	bool			m_bAlive;	// �����t���O
	int				m_hp;		// �̗͗�
	int				m_dmg;		// �̗͌�����
	float			m_deg;		// �p�x
	bool			m_VisibilityFlg;	// ����t���O
	bool			m_shotFlg;	// ���˃t���O
	int				m_shotCnt;	// ���˃J�E���g

	bool			m_bSlashHit;		// �a���q�b�g�t���O
	bool			m_bBlastHit;		// �����q�b�g�t���O

	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p
	Math::Vector2	 m_playerPos;	//�v���C���[�̍��W�擾�p

};

