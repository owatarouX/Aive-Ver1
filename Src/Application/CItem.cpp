#include"Scene.h"
#include"CItem.h"


CItem::CItem()
	:m_pOwner(nullptr)
{
}

CItem::~CItem()
{
}

//������
void CItem::Init()
{
	// �A�C�e���F���e
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].Init();
	}
	SetBomb();	//���e�ݒu
	
	// �A�C�e���F��
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].Init();
	}
	SetKey();	//���ݒu

	// �A�C�e���F��
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].Init();
	}

	// �A�C�e���F�B�ꖪ
	m_minoList.Init();
	SetMino();	// �B�ꖪ�z�u
}

//�X�V
void CItem::Update()
{
	//�}�b�v�N���X�擾
	CMap* map = m_pOwner->GetMap();
	
	//�X�N���[���ʎ擾
	Math::Vector2 ScrollPos = map->GetscrollPos();
	
	//���e
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].SetScrollPos(ScrollPos);		//�X�N���[���ʎ擾
		m_bombList[i].Update();		//�X�V
	}
	//��
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].SetScrollPos(ScrollPos);		//�X�N���[���ʎ擾
		m_keyList[i].Update();		//�X�V
	}
	// ��
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].SetScrollPos(ScrollPos);
		m_healthList[i].Update();
	}
	// �B�ꖪ
	m_minoList.SetScrollPos(ScrollPos);
	m_minoList.Update();
}

//�`��
void CItem::Draw()
{
	//���e
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].Draw();
	}
	//��
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].Draw();
	}
	// ��
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].Draw();
	}
	// �B�ꖪ
	m_minoList.Draw();
}

//�I�[�i�[�ݒ�擾
void CItem::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

//���e�ݒu
void CItem::SetBomb()
{
	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();	//�}�b�v�f�[�^�擾

	//�f�[�^���Ƃ̔z�u�ݒ�
	switch (mapData)
	{
	//��O
	case OutSide:
		m_bombList[0].SetBomb({ 930.0f,270.0f });
		break;
	//��K�w
	case OneFloor:
		m_bombList[0].SetBomb({ 1750, -750 });
		m_bombList[1].SetBomb({ 464,-744 });
		break;
	//��K�w
	case TwoFloor:
		break;
	//�O�K�w
	case ThreeFloor:
		break;
	//�l�K�w
	case FourFloor:
		break;
	//�{�X�K�w
	case BossFloor:
		
		break;
	default:
		break;
	}
}

//���ݒu
void CItem::SetKey()
{
	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();	//�}�b�v�f�[�^�擾

	//�f�[�^���Ƃ̔z�u�ݒ�
	switch (mapData)
	{
	//��K�w
	case OneFloor:
		m_keyList[0].SetKey({ 1450, 100 });
		m_keyList[1].SetKey({ -500, -1950 });
	//��K�w
	case TwoFloor:
		break;
	//�O�K�w
	case ThreeFloor:
		break;
	//�l�K�w
	case FourFloor:
		break;
	}
}

//�B�ꖪ�ݒu
void CItem::SetMino()
{
	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();	//�}�b�v�f�[�^�擾

	//�f�[�^���Ƃ̔z�u�ݒ�
	switch (mapData)
	{
		//��K�w
	case OneFloor:
		m_minoList.SetMino({ 1400,-1600 });
		break;
		//��K�w
	case TwoFloor:
		break;
		//�O�K�w
	case ThreeFloor:
		break;
	//�l�K�w
	case FourFloor:
		break;
	}
}

//�e�N�X�`���ݒ�F���etrue
void CItem::SetTexBomb_t(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].SetTexture_t(apTexture);
	}
}

//�e�N�X�`���ݒ�F���efalse
void CItem::SetTexBomb_f(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		m_bombList[i].SetTexture_f(apTexture);
	}
}

//�e�N�X�`���ݒ�F��
void CItem::SetTexKey(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < KEY_SETMAX; i++)
	{
		m_keyList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���ݒ�F��
void CItem::SetTexHealth(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		m_healthList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���ݒ�F�B�ꖪ
void CItem::SetTexMino(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;
	m_minoList.SetTexture(apTexture);
}

// �񕜃h���b�v����(true�F�h���b�v)
bool CItem::DropHealth(bool bDrop, Math::Vector2 pos)
{
	if (!bDrop) return false;

	if (int r = rand() % 2 > 0) return true;
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		if (m_healthList[i].GetAlive())continue;	// �L�[�t���O�`�F�b�N
		m_healthList[i].SetHealth(pos);		// �񕜃h���b�v
		return true;
	}
	return false;
}

// ���h���b�v����(true�F�h���b�v)
bool CItem::DropKey(bool bDrop, Math::Vector2 pos)
{
	if (!bDrop) return false;
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		if (m_keyList[i].GetAlive())continue;	// �L�[�t���O�`�F�b�N
		m_keyList[i].SetKey(pos);		// ���h���b�v
		return true;
	}
	return false;
}

