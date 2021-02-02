#include"CSamurai.h"
#include"Utility.h"
#include"Scene.h"

CSamurai::CSamurai()
	:m_pTexture(nullptr)
	, m_pos(0, 0)
	, m_moveVal(0, 0)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_bAlive(false)
	, m_hp(HP::SAMURAI)
	, m_dmg(0)
	, m_deg(0)
	, m_dist(0)
	, m_VisibilityFlg(false)
	, m_bSlashHit(false)
	, m_bBlastHit(false)
	, m_bDrop(false)
	, m_moveCnt(MOVE_CNT_MAX)
	, m_bSlash(false)
	, m_bAtk(false)
	, m_atkCnt(0)
{
}

CSamurai::~CSamurai()
{
}

//������
void CSamurai::Init()
{
	m_pos = { 0,0 };
	m_moveVal = { 0,0 };
	m_bAlive = false;
	m_hp = HP::SAMURAI;
	m_dmg = 0;
	m_VisibilityFlg = false;
	m_bSlashHit = false;
	m_bBlastHit = false;
	m_bDrop = false;
	m_moveCnt = MOVE_CNT_MAX;
	m_bSlash = false;
	m_bAtk = false;
	m_atkCnt = 0;
}

//�X�V
void CSamurai::Update()
{
	if (!m_bAlive) return;

	// �_���[�W����
	m_hp -= m_dmg;
	m_dmg = 0;

	// ���S����
	if (m_hp <= 0)
	{
		m_bAlive = false;
		m_bDrop = true;
		return;
	}

	// �v���C���[�Ƃ̋��������߂�
	m_dist = Utility::GetDistance(m_pos, m_playerPos);
	// �v���C���[�Ƃ̊p�x�����߂� 
	m_deg = Utility::GetAngleDeg(m_pos, m_playerPos);

	// ���̋����ɋ߂Â�����
	if (m_dist < 300) m_VisibilityFlg = true;		// ����t���O�グ
	// ���̋����ɗ��ꂽ��
	else if (m_dist > 400)	m_VisibilityFlg = false;	// ����t���O����
	
	// �v���C���[���B�ꖪ�g�p���A����t���O������
	if (m_bHidden)m_VisibilityFlg = false;

	// ���E���̎�
	if (m_VisibilityFlg)
	{
		Attack();
	}
	// ����O
	else Walk(); // �p�j

	// ���W�m��
	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;

	//�s��
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - m_scrollPos.x, m_pos.y - m_scrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(1.0f, 1.0f, 0.0f);
	m_mat = m_scaleMat * m_transMat;	// �s��쐬
}

//�`��
void CSamurai::Draw()
{
	if (!m_bAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTexture, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

//�e�N�X�`���ݒ�
void CSamurai::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;
}

//���̐ݒu
void CSamurai::SetSamurai(Math::Vector2 pos)
{
	m_pos = pos;

	m_bAlive = true;
}

// X���W�Z�b�g
void CSamurai::SetPosX(float posX)
{
	m_pos.x = posX;
}

// Y���W�Z�b�g
void CSamurai::SetPosY(float posY)
{
	m_pos.y = posY;
}

// X�ړ��ʃZ�b�g
void CSamurai::SetMoveX(float moveX)
{
	m_moveVal.x = moveX;
}

// Y�ړ��ʃZ�b�g
void CSamurai::SetMoveY(float moveY)
{
	m_moveVal.y = moveY;
}

//�����t���O�ݒ�
void CSamurai::SetAlive()
{
	m_bAlive = false;
}

// �_���[�W����
void CSamurai::SetDamage(int dmg)
{
	m_dmg += dmg;
}

// �a���U���t���O�Z�b�g
void CSamurai::bSetSlash(bool flg)
{
	m_bSlash = flg;
}

// �U���t���O�Z�b�g
void CSamurai::bSetAtk()
{
	m_bAtk = false;
}

// �a���q�b�g�t���O�Z�b�g
void CSamurai::bSetSlashHit(bool aHit)
{
	m_bSlashHit = aHit;
}

// �����q�b�g�t���O�Z�b�g
void CSamurai::bSetBlastHit(bool aHit)
{
	m_bBlastHit = aHit;
}

// �h���b�v�t���O�Z�b�g
void CSamurai::bSetDrop()
{
	m_bDrop = false;
}

//�X�N���[���ʎ擾
void CSamurai::SetScrollPos(Math::Vector2 scrPos)
{
	m_scrollPos = scrPos;
}

// �v���C���[�̍��W�擾
void CSamurai::SetPlayerPos(Math::Vector2 pos)
{
	m_playerPos = pos;
}

// �v���C���[�̉B�ꖪ�g�p�t���O�擾
void CSamurai::bSetHidden(bool flg)
{
	m_bHidden = flg;
}

// �U���֐�
void CSamurai::Attack()
{
	// ��苗���܂ŋ߂Â��Ă���
	if (m_dist >= 90)	Homing(SPEED::SAMURAI);
	else
	{
		m_moveVal = { 0,0 };
		if (m_atkCnt >= COOL_TIME::SAMURAI_SLASH)
		{
			bSetSlash(true);
			m_atkCnt = 0;
		}
	}
	m_atkCnt++;
	if (m_atkCnt >= COOL_TIME::SAMURAI_SLASH)
		m_atkCnt = COOL_TIME::SAMURAI_SLASH;	// �J�E���g����
}

void CSamurai::Homing(float sp)
{
	m_moveVal.x = cos(DirectX::XMConvertToRadians(m_deg)) * sp;	// cos
	m_moveVal.y = sin(DirectX::XMConvertToRadians(m_deg)) * sp;	// sin
}

// �����֐�
void CSamurai::Walk()
{
	if (m_moveCnt >= MOVE_CNT_MAX)
	{
		float moveX = (rand() % 2 - 1);
		float moveY = (rand() % 2 - 1);

		// �����_���ړ��ʃZ�b�g
		switch (int r = rand() % 16)
		{
		case 1:
			m_moveVal = { moveX, moveY };
			break;
		case 2:
			m_moveVal = { -moveX, -moveY };
			break;
		case 3:
			m_moveVal = { -moveX, moveY };
			break;
		case 4:
			m_moveVal = { moveX, -moveY };
			break;
		default:
			m_moveVal = { 0, 0 };
			break;
		}
		m_moveCnt = 0;
	}
	m_moveCnt++;
}
