#include"CResult.h"

CResult::CResult()
	:m_pTex_Result(nullptr)
	,m_pTex_Line(nullptr)
	,m_matResult()
	,m_matLine()
	,m_LinePos(0,0)
	,m_bDrawLine(false)
	,m_drawLineCnt(0)
{
}

CResult::~CResult()
{
}

// ������
void CResult::Init()
{
	m_LinePos = { -425,-205 };
	m_bDrawLine = false;
	m_drawLineCnt = 0;
}

// �X�V
void CResult::Update(POINT mouse)
{
	// �}�E�X���W�擾
	Math::Vector2 mousePos = { (float)mouse.x,(float)mouse.y };

	// �J�[�\�����V�[���J�ڃ{�^�����Ńt���O�ύX
	m_bDrawLine = bSceneButton(m_LinePos, mousePos);

	// �������A�j���[�V����
	if (m_bDrawLine)
	{
		m_drawLineCnt += 30;
		if (m_drawLineCnt >= DRAW_MAX)m_drawLineCnt = DRAW_MAX;
	}
	else m_drawLineCnt = 0;

	// ���U���g�s��쐬
	m_matResult = DirectX::XMMatrixTranslation(0, 0, 0);
	// �������s��쐬
	m_matLine = DirectX::XMMatrixTranslation(-DRAW_MAX*1.25 - ((DRAW_MAX / 2 - m_drawLineCnt) / 2), m_LinePos.y - 30, 0);
}

// �`��
void CResult::Draw()
{
	// �^�C�g�����
	SHADER.m_spriteShader.SetMatrix(m_matResult);
	SHADER.m_spriteShader.DrawTex(m_pTex_Result, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	
	if (!m_bDrawLine) return;
	SHADER.m_spriteShader.SetMatrix(m_matLine);
	SHADER.m_spriteShader.DrawTex(m_pTex_Line, Math::Rectangle(0, 0, m_drawLineCnt, 15), 1.0f);

}

// �V�[���J�ڊ֐�
bool CResult::SceneTransition()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bDrawLine)return true;
		else return false;
	}
}

// �e�N�X�`���ݒ�F���U���g
void CResult::SetTexResult(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Result = apTexture;
}

// �e�N�X�`���ݒ�F������
void CResult::SetTexLine(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Line = apTexture;
}

// �V�[���J�ڃ{�^������֐�
bool CResult::bSceneButton(Math::Vector2 pos, Math::Vector2 mouse)
{
	const float Left = pos.x - 125;
	const float Right = pos.x + 125;
	const float Top = pos.y + 25;
	const float Bottom = pos.y - 25;
	if (mouse.x > Left && mouse.x < Right &&
		mouse.y > Bottom && mouse.y < Top)
	{
		return true;	//�g��\��
	}
	else return false;
}

