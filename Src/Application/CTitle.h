#pragma once

class Scene;

class Ctitle
{
public:
	Ctitle();
	~Ctitle();

	void Init();
	void Update(POINT mouse);
	void Draw();

	int SceneTransition();		// �V�[���J�ڊ֐�

	bool bGetToGame() { return m_bToGame; }
	bool bGetToDescript() { return m_bToDescript; }

	void SetTexTitle(KdTexture* apTexture);	// �e�N�X�`���ݒ�F�^�C�g�����
	void SetTexLine(KdTexture* apTexture);	// �e�N�X�`���ݒ�F������

private:

	KdTexture*		m_pTex_Title;		// �摜(�e�N�X�`��)
	KdTexture*		m_pTex_Line;		// �摜(�e�N�X�`��)
	Math::Matrix	m_matTitle;			// �s��(�^�C�g��)
	Math::Matrix	m_matLine;			// �s��(������)
	Math::Vector2	m_toGamePos;		// �Q�[���V�[���J�ڃ{�^�����W
	Math::Vector2	m_toDescriptPos;	// �����V�[���J�ڃ{�^�����W
	Math::Vector2	m_LinePos;			// ���������W
	const float		LINE_POS_X = 10;	// ��������X���W�Œ�
	bool			m_bToGame;			// �Q�[���V�[���J�ڃt���O
	bool			m_bToDescript;		// �����V�[���J�ڃt���O
	const int		DRAW_MAX = 380;
	int				m_drawLineCnt;		// �������`��J�E���g

	bool bSceneButton(Math::Vector2 pos, Math::Vector2 mouse);
};
