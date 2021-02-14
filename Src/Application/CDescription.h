#pragma once

class CDescription
{
public:
	CDescription();
	~CDescription();

	void Init();
	void Update(POINT mouse);
	void Draw();

	bool SceneTransition();		// �V�[���J�ڊ֐�

	void SetTexDescript(KdTexture* apTexture);	// �e�N�X�`���ݒ�F�������
	void SetTexLine(KdTexture* apTexture);		// �e�N�X�`���ݒ�F������

private:
	KdTexture*		m_pTex_Descript;		// �e�N�X�`��(����)
	KdTexture*		m_pTex_Line;			// �e�N�X�`��(������)
	Math::Matrix	m_matDescript;			// �s��(����)
	Math::Matrix	m_matLine;				// �s��(������)
	Math::Vector2	m_LinePos;				// ���������W
	bool			m_bDrawLine;			// �������\���t���O
	int				m_drawLineCnt;			// �������`��J�E���g
	const int		DRAW_MAX = 170;

	bool bSceneButton(Math::Vector2 pos, Math::Vector2 mouse);
};

