#include"CTitle.h"
#include"Utility.h"

Ctitle::Ctitle()
	:m_pTex_Title(nullptr)
	,m_pTex_Line(nullptr)
	,m_matTitle()
	,m_matLine()
	,m_toGamePos(0,0)
	,m_toDescriptPos(0,0)
	,m_LinePos(0,0)
	,m_bToGame(false)
	,m_bToDescript(false)
	,m_drawLineCnt(0)
{
}

Ctitle::~Ctitle()
{
}

// ������
void Ctitle::Init()
{
	m_toGamePos = { LINE_POS_X, -10 };
	m_toDescriptPos = { LINE_POS_X, -137 };
	m_LinePos = { LINE_POS_X,0 };
	m_bToGame = false;
	m_bToDescript = false;
	m_drawLineCnt = 0;
}

// �X�V
void Ctitle::Update(POINT mouse)
{
	// �}�E�X���W�擾
	Math::Vector2 mousePos = { (float)mouse.x,(float)mouse.y };

	// �J�[�\�����V�[���J�ڃ{�^�����Ńt���O�ύX
	m_bToGame = bSceneButton(m_toGamePos, mousePos);
	m_bToDescript = bSceneButton(m_toDescriptPos, mousePos);

	// �������A�j���[�V����
	if (m_bToGame || m_bToDescript)
	{
		m_drawLineCnt+=20;
		if (m_drawLineCnt >= DRAW_MAX)m_drawLineCnt = DRAW_MAX;
	}
	else m_drawLineCnt = 0;

	// �^�C�g����ʍs��쐬
	m_matTitle = DirectX::XMMatrixTranslation(0, 0, 0);
	
	// ���������W�w��
	if (m_bToGame)m_LinePos.y = m_toGamePos.y;
	else if (m_bToDescript)m_LinePos.y = m_toDescriptPos.y;
	// �������s��쐬
	m_matLine = DirectX::XMMatrixTranslation(-DRAW_MAX/4 - ((DRAW_MAX /2 - m_drawLineCnt)/2), m_LinePos.y - 35, 0);
}

// �`��
void Ctitle::Draw()
{
	// �^�C�g�����
	SHADER.m_spriteShader.SetMatrix(m_matTitle);
	SHADER.m_spriteShader.DrawTex(m_pTex_Title,Math::Rectangle(0,0,1280,720),1.0f);
	
	// ������
	if (m_bToGame || m_bToDescript)
	{
		SHADER.m_spriteShader.SetMatrix(m_matLine);
		SHADER.m_spriteShader.DrawTex(m_pTex_Line, Math::Rectangle(0, 0, m_drawLineCnt, 15), 1.0f);
	}
}

// �V�[���J�ڊ֐�
int Ctitle::SceneTransition()
{
	if (!m_bToGame && !m_bToDescript) return 0;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bToGame)return 1;
		else if (m_bToDescript)return 2;
	}
}

// �e�N�X�`���ݒ�F�^�C�g�����C�����
void Ctitle::SetTexTitle(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Title = apTexture;
}

// �e�N�X�`���ݒ�F������
void Ctitle::SetTexLine(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_pTex_Line = apTexture;
}

bool Ctitle::bSceneButton(Math::Vector2 pos, Math::Vector2 mouse)
{
	const float Left = pos.x - 190;
	const float Right = pos.x + 190;
	const float Top = pos.y + 50;
	const float Bottom = pos.y - 50;
	if (mouse.x > Left && mouse.x < Right &&
		mouse.y > Bottom && mouse.y < Top)
	{
		return true;	//�g��\��
	}
	else return false;
}
