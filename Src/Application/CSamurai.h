#pragma once
// �G�N���X�F����

class Scene;

class CSamurai
{
public:
	CSamurai();
	~CSamurai();

	void Init();			// ������
	void Update();			// �X�V
	void Draw();			// �`��

	const bool IsAlive() { return m_bAlive; }	// �����m�F
	Math::Vector2 GetPos() { return m_pos; }	// ���W�擾
	Math::Vector2 GetMove() { return m_moveVal; }	// �ړ��ʎ擾
	float GetDeg() { return m_deg; }	// �p�x�擾
	const bool bGetSlashHit() { return m_bSlashHit; }	// �a���q�b�g�t���O�擾
	const bool bGetBlastHit() { return m_bBlastHit; }	// �����q�b�g�t���O�擾
	bool	bGetSlash() { return m_bSlash; }			// �a���t���O�擾
	const bool bGetDrop() { return m_bDrop; }			// �h���b�v�t���O�擾

	void SetSamurai(Math::Vector2 pos);		// ���ݒu
	void SetTexture(KdTexture* apTexture);	// �e�N�X�`���󂯎��
	void SetPosX(float posX);	// X���W�Z�b�g
	void SetPosY(float posY);	// Y���W�Z�b�g
	void SetMoveX(float moveX);	// X�ړ��ʃZ�b�g
	void SetMoveY(float moveY);	// Y�ړ��ʃZ�b�g
	void SetAlive();	// �����t���O�ݒ�
	void SetDamage(int dmg);	// �_���[�W���Z
	void bSetSlash(bool flg);	// �a���U���t���O�Z�b�g
	void bSetAtk();		// �U���t���O�Z�b�g
	void bSetSlashHit(bool aHit);	// �a���q�b�g�t���O�Z�b�g
	void bSetBlastHit(bool aHit);	// �����q�b�g�t���O�Z�b�g
	void bSetDrop();			// �h���b�v�t���O�Z�b�g

	void SetScrollPos(Math::Vector2 scrPos);	//�X�N���[���ʎ擾
	void SetPlayerPos(Math::Vector2 pos);		// �v���C���[�̍��W�擾
	void bSetHidden(bool flg);					// �B��g��Ԏ擾

private:
	KdTexture* m_pTexture;		// �摜(�e�N�X�`��)
	Math::Vector2	m_pos;		// ���W
	Math::Vector2	m_moveVal;	// �ړ���
	Math::Matrix	m_mat;		// �����s��
	Math::Matrix	m_transMat;	// �ړ��s��
	Math::Matrix	m_scaleMat;	// �g��s��
	Math::Vector2	m_size;	// �摜���]�p
	bool			m_bAlive;	// �����t���O
	int				m_hp;		// �̗͗�
	int				m_dmg;		// �̗͌�����
	float			m_deg;		// �p�x
	float			m_dist;		// ����
	bool			m_VisibilityFlg;	// ����t���O
	bool			m_bSlashHit;		// �a���q�b�g�t���O
	bool			m_bBlastHit;		// �����q�b�g�t���O
	bool			m_bDrop;			// �h���b�v�t���O

	int				m_moveCnt;			// �����_���s���J�E���g
	const int		MOVE_CNT_MAX = 40;	// �����_���s������
	bool			m_bSlash;			// �a���U���t���O
	int				m_atkRnd;			// �U�������_��
	bool			m_bAtk;				// �U���t���O
	int				m_atkCnt;			// �U���J�E���g

	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p
	Math::Vector2	 m_playerPos;	//�v���C���[�̍��W�擾�p
	bool			 m_bHidden;		//�B��g�t���O�擾�p

	void Attack();		// �U���֐�
	void Homing(float sp);		// ���b�N�I��
	void Walk();		// �����֐�
};

