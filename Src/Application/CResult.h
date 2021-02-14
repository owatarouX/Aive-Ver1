#pragma once

class CResult
{
public:
	CResult();
	~CResult();

	void Init();
	void Update(POINT mouse);
	void Draw();

	bool SceneTransition();		// �V�[���J�ڊ֐�

	void SetTexResult(KdTexture* apTexture);	// �e�N�X�`���ݒ�
	void SetTexLine(KdTexture* apTexture);		// �e�N�X�`���ݒ�F������

private:
	KdTexture*		m_pTex_Result;		// �e�N�X�`��(���U���g)
	KdTexture*		m_pTex_Line;		// �e�N�X�`���i�������j
	Math::Matrix	m_matResult;		// �s��(���U���g)
	Math::Matrix	m_matLine;			// �s��(������)
	Math::Vector2	m_LinePos;			// ���������W
	bool			m_bDrawLine;		// �������\���t���O
	int				m_drawLineCnt;		// �������`��J�E���g
	const int		DRAW_MAX = 380;

	bool bSceneButton(Math::Vector2 pos, Math::Vector2 mouse);
};
