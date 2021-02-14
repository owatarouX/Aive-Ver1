#include"CDescription.h"

CDescription::CDescription()
	:m_pTex_Descript(nullptr)
	, m_pTex_Line(nullptr)
	, m_matDescript()
	, m_matLine()
	, m_LinePos(0, 0)
	, m_bDrawLine(false)
	, m_drawLineCnt(0)
{
}

CDescription::~CDescription()
{
}

// ������
void CDescription::Init()
{
	m_LinePos = { 460,-225 };
	m_bDrawLine = false;
	m_drawLineCnt = 0;
}

// �X�V����
void CDescription::Update(POINT mouse)
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

	// �Q�[�������s��쐬
	m_matDescript = DirectX::XMMatrixTranslation(0, 0, 0);
	// �������s��쐬
	m_matLine = DirectX::XMMatrixTranslation(DRAW_MAX*2.5 - ((DRAW_MAX / 2 - m_drawLineCnt) / 2), m_LinePos.y - 50, 0);
}

// �`��
void CDescription::Draw()
{
	// �Q�[���������
	SHADER.m_spriteShader.SetMatrix(m_matDescript);
	SHADER.m_spriteShader.DrawTex(m_pTex_Descript, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	if (!m_bDrawLine) return;
	SHADER.m_spriteShader.SetMatrix(m_matLine);
	SHADER.m_spriteShader.DrawTex(m_pTex_Line, Math::Rectangle(0, 0, m_drawLineCnt, 15), 1.0f);

}

// �V�[���J�ڊ֐�
bool CDescription::SceneTransition()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bDrawLine)return true;
		else return false;
	}
}

// �e�N�X�`���ݒ�F�Q�[������
void CDescription::SetTexDescript(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Descript = apTexture;
}

// �e�N�X�`���ݒ�F������
void CDescription::SetTexLine(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Line = apTexture;
}

bool CDescription::bSceneButton(Math::Vector2 pos, Math::Vector2 mouse)
{
	const float Left = pos.x - 80;
	const float Right = pos.x + 80;
	const float Top = pos.y + 55;
	const float Bottom = pos.y - 55;
	
	if (mouse.x > Left && mouse.x < Right &&
		mouse.y > Bottom && mouse.y < Top)
	{
		return true;	//�g��\��
	}
	else return false;
}
