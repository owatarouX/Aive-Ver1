#include "CPlayer.h"
#include "Scene.h"
#include"Utility.h"

//�R���X�g���N�^
CPlayer::CPlayer()
	:m_pTexture(nullptr)
	, m_pos(0.0f, 0.0f)
	, m_moveVal(0.0f, 0.0f)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_size(1.0f, 1.0f)
	, m_bAlive(true)
	, m_hp(HP::PLAYER)
	, m_bHeal(false)
	, m_hpCount()
	, m_alpha(1.0f)
	, m_HitFlg(false)
	, m_slashCnt(COOL_TIME::PLAYER_SLASH)
	, m_shurikenCnt(COOL_TIME::PLAYER_SHURIKEN)
	, m_bRClick(false)
	, m_bLClick(false)
	, m_bRChange(false)
	, m_bLChange(false)
	, m_aTimer(15)
	, m_aflame(5)
	, m_BombPossession(0)
	, m_KeyPossession(0)
	, m_bMinoPossession(false)
{
}

CPlayer::~CPlayer()
{
}

//������
void CPlayer::Init()
{
	//���W
	//m_pos = { -250.0f,-1080.0f };	// �������W
	m_pos = { 900.0f,200.0f };	// �ߓ�
	//m_pos = { 1600,-1800 };
	//m_pos = { 700, -1600 };

	//�ړ���
	m_moveVal.x = 0.0f;
	m_moveVal.y = 0.0f;
	
	//�����t���O
	m_bAlive = true;
	
	//�̗�
	m_hp = HP::PLAYER;
	m_hpCount = 0;

	//�����x
	m_alpha = 1.0f;

	//�G�Ɠ�������������
	m_HitFlg = false;

	//��������
	m_direction = Down;

	//��������
	m_LClick = eShuriken;
	m_RClick = eSword;

	//���E�N���b�N�t���O
	m_bRClick = false;
	m_bLClick = false;

	//����`�F���W�t���O
	m_bLChange = false;
	m_bRChange = false;

	//�e�̏�����
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].Init();
	}

	//��������
	m_swordList.Init();

	//���e�̏�����
	m_bombList.Init();
	m_BombPossession = 0;

	//�B��g������
	m_hiddenList.Init();
	m_bMinoPossession = false;

	//��������
	m_KeyPossession = 0;

	//SE(�T�E���h�̓ǂݍ��݂Ǝ��̉�)
	katanaseInst = Sound_Loading(katanase, "Sound/katana.WAV");
	shurikenseInst = Sound_Loading(shurikense, "Sound/shuriken.WAV");
	hitseInst = Sound_Loading(hitse,"Sound/hit.WAV");

}

// �ď�����
void CPlayer::ReInit(int mapData)
{
	switch (mapData)
	{
		//��K�w
	case OneFloor:
		m_pos = { 1600,-1800 };
		m_KeyPossession = 0;
		break;
		//��K�w
	case TwoFloor:
		m_pos = { -460,-2000 };
		m_KeyPossession = 0;
		break;
		//�O�K�w
	case ThreeFloor:
		m_pos = { -460,100 };
		m_KeyPossession = 0;
		break;
		//�{�X
	case BossFloor:
		m_pos = { 624,-1340 };
		m_KeyPossession = 0;
		break;
	}
}

//�X�V
void CPlayer::Updata(POINT aMousePos)
{
	//�������̂ݏ���
	if (!m_bAlive) return;
	CMap* map = m_pOwner->GetMap();		//�}�b�v�N���X�擾
	Math::Vector2 ScrollPos = map->GetscrollPos();		//�X�N���[���ʎ擾
	
	m_ClickPoint = aMousePos;	// �}�E�X���W�擾

	// �v���C���[�X�V
	UpDatePlayer(ScrollPos);
	
	//�e�̍X�V
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].SetScrollPos(ScrollPos);
		m_bulletList[i].Updata();
	}

	//���U���X�V
	m_swordList.SetScrollPos(ScrollPos);
	m_swordList.Updata(m_pos);

	//���e�̍X�V
	m_bombList.SetScrollPos(ScrollPos);
	m_bombList.Updata();

	//�B��g�̍X�V
	m_hiddenList.Updata();
}

// �v���C���[�X�V����
void CPlayer::UpDatePlayer(Math::Vector2 ScrollPos)
{
	// �L�[����ꗗ
	KeyOperation();

	//�T�C�Y�ύX(�摜���]�p)
	switch (m_direction) {
	case 2:
		m_size = { -1.0f, 1.0f };
		break;
	case 3:
		m_size = { 1.0f, 1.0f };
		break;
	}

	//�N�[���^�C������
	// �a���J�E���g
	m_slashCnt++;
	if (m_slashCnt >= COOL_TIME::PLAYER_SLASH)m_slashCnt = COOL_TIME::PLAYER_SLASH;
	// �藠���J�E���g
	m_shurikenCnt++;
	if (m_shurikenCnt >= COOL_TIME::PLAYER_SHURIKEN)m_shurikenCnt = COOL_TIME::PLAYER_SHURIKEN;
	
	/* �����蔻�� */
	//�}�b�v
	HitCheckMap();
	//�G
	HitCheckEnemy();
	//���e
	HitCheckBomb();
	//�A�C�e��
	HitCheckItem();
	
	//���G����
	InviTime();

	//HP0�Ńt���O����
	if (m_hp <= 0) m_bAlive = !m_bAlive;
	//HP�����݂���
	if (m_hp >= HP::PLAYER)m_hp = HP::PLAYER;

	//�A�j���[�V����
	const int CNT_MAX = m_aTimer * m_aflame;
	if (m_aCnt >= CNT_MAX + m_aTimer - 1)
		m_aCnt = 0;
	m_aCnt++;

	//���W�m��
	m_pos.x += m_moveVal.x;
	m_pos.y += m_moveVal.y;

	m_moveVal = { 0,0 };
	
	//�s��쐬
	m_transMat = DirectX::XMMatrixTranslation(m_pos.x - ScrollPos.x, m_pos.y - ScrollPos.y, 0.0f);
	m_scaleMat = DirectX::XMMatrixScaling(m_size.x, m_size.y, 0.0f);
	m_mat = m_scaleMat * m_transMat;
}

//�`��
void CPlayer::Draw()
{
	if (!m_bAlive) return;

	//�e�̕`��
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].Draw();
	}

	//�a���̕`��
	m_swordList.Draw();

	//���e�̕`��
	m_bombList.Draw();

	//�v���C���[�`��
	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle scrRect = { -20,Animation(m_aCnt,348),160,64 }; // �e�N�X�`�����W
	Math::Color color = { 1,1,1, m_alpha }; // �F�iRGBA�̏��ԂŁ@0.0�`1.0�j
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 160, 64, &scrRect, &color, Math::Vector2(0.5f, 0.5f));

}

//�e�N�X�`���ݒ�:���@
void CPlayer::SetTexture(KdTexture* apTexture)
{
	//�|�C���^�̃A�h���X�����퉻����ׂ� (null�Ȃ�Z�b�g���Ȃ�)
	if (apTexture == nullptr)return;

	m_pTexture = apTexture;

}

//�e�N�X�`���ݒ�:�藠��
void CPlayer::SetBulletTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_bulletList[i].SetTexture(apTexture);
	}
}

//�e�N�X�`���ݒ�:�a��
void CPlayer::SetSlashTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_swordList.SetTexture(apTexture);
}

//�e�N�X�`���ݒ�:���e
void CPlayer::SetBombTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_bombList.SetTexture(apTexture);
}

//�e�N�X�`���ݒ�F����
void CPlayer::SetBlastTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr)return;

	m_bombList.SetBlastTexture(apTexture);
}

//�I�[�i�[�ݒ�
void CPlayer::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

// �̗͌���
void CPlayer::SetDamage(int dmg)
{
	// �̗͌���
	m_hp -= dmg;
	//�q�b�g������
	hitseInst->Play();
	
	// �q�b�g�G�t�F�N�g����
	CEffect* effect = m_pOwner->GetEffect();
	CDamage* dmgList = effect->GetDmgList();

	for (int i = 0; i < EFFECT_DMG_MAX; i++)
	{
		if (dmgList[i].GetbAlive())continue;
		dmgList[i].EmitDmg(m_pos, m_moveVal, 1.5);
		return;
	}
}

// �̗͉�
void CPlayer::SetHeal(int heal)
{
	m_hp += heal;
	CEffect* effect = m_pOwner->GetEffect();
	effect->PlayerHealEffect();
}

// �q�b�g�t���O�Z�b�g
void CPlayer::SetHitFlg()
{
	m_HitFlg = true;
}

// ���W�Z�b�gX(���ݍ��W�ɑ����Z)
void CPlayer::SetPosX(float x)
{
	m_pos.x = x;
}
// ���W�Z�b�gY(���ݍ��W�ɑ����Z)
void CPlayer::SetPosY(float y)
{
	m_pos.y = y;
}
// �ړ��ʃZ�b�gX(�ړ��ʂ����)
void CPlayer::SetMovevalX(float movex)
{
	m_moveVal.x = movex;
}
// �ړ��ʃZ�b�gY(�ړ��ʂ����)
void CPlayer::SetMovevalY(float movey)
{
	m_moveVal.y = movey;
}

const int CPlayer::GetR()
{
	int a = m_RClick;
	return a;
}

const int CPlayer::GetL()
{
	int a = m_LClick;
	return a;
}

// �L�[����ꗗ
void CPlayer::KeyOperation()
{
	/* �ړ� */
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVal.y += SPEED::PLAYER;
		m_direction = Up;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVal.y -= SPEED::PLAYER;
		m_direction = Down;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVal.x -= SPEED::PLAYER;
		m_direction = Left;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVal.x += SPEED::PLAYER;
		m_direction = Right;
	}

	/* �U�� */
	//���N���b�N�U��
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		Attack(m_bLClick, m_LClick);
		m_bLClick = true;
	}
	else m_bLClick = false;
	//�E�N���b�N�U��
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		Attack(m_bRClick, m_RClick);
		m_bRClick = true;
	}
	else m_bRClick = false;

	/* ����`�F���W */
	//���N���b�N����
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (!m_bLChange)
		{
			m_LClick = ChangeItem(m_LClick);
			if (m_LClick == m_RClick)m_LClick = ChangeItem(m_LClick);
			m_bLChange = true;
		}
	}
	else m_bLChange = false;
	//�E�N���b�N����
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (!m_bRChange)
		{
			m_RClick = ChangeItem(m_RClick);
			if (m_RClick == m_LClick)m_RClick = ChangeItem(m_RClick);
			m_bRChange = true;
		}
	}
	else m_bRChange = false;
}

//�}�b�v�Ƃ̓����蔻��
void CPlayer::HitCheckMap()
{
	CEnemy* enemy = m_pOwner->GetEnemy();
	CMap* map = m_pOwner->GetMap();
	CEffect* effect = m_pOwner->GetEffect();
	CDarken* darkenList = effect->GetDarkenList();

	float(*chipX)[MAP_CHIP_W] = map->GetPosX();
	float(*chipY)[MAP_CHIP_W] = map->GetPosY();
	int(*chipData)[MAP_CHIP_W] = map->GetChipData();
	int mapData = map->GetMapData();	//�}�b�v�f�[�^�擾

	//�}�b�v�f�[�^��g����
	int hit = 0;
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			//�}�b�v�̌��ݍ��W�̎l��
			const float MAP_LEFT = chipX[h][w] - Infor::RADIUS_32;		//����
			const float MAP_RIGHT = chipX[h][w] + Infor::RADIUS_32;		//�E��
			const float MAP_TOP = chipY[h][w] + Infor::RADIUS_32;		//���
			const float MAP_BOTTOM = chipY[h][w] - Infor::RADIUS_32;	//����

			if (chipData[h][w] >= 78 && chipData[h][w] <= 79)	//�f�[�^�F�M�~�b�N
			{
				if (mapData == OneFloor)
				{
					if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
						PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
					{
						if (enemy->bGetEvent())map->SetLock();	// �J�M��
						enemy->Event();		// �C�x���g����
					}
				}
				else if (mapData == BossFloor)
				{
					// �C�x���g��������
					if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
						PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
					{
						if (enemy->bGetEvent())map->SetLock();	// �J�M��
					}
				}
			}
			else if (chipData[h][w] >= 91)	//�f�[�^�F��
			{
				// �ʏ�̕ǔ���
				hit = Utility::iHitCheck(m_pos, m_moveVal, chipX[h][w], chipY[h][w],
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);

				switch (hit)
				{
				case 1:m_pos.y = MAP_TOP + Infor::RADIUS_32;
					m_moveVal.y = 0;
					break;
				case 2:
					m_pos.y = MAP_BOTTOM - Infor::RADIUS_32;
					m_moveVal.y = 0;
					break;
				case 3:m_pos.x = MAP_LEFT - Infor::RADIUS_32;
					m_moveVal.x = 0;
					break;
				case 4:
					m_pos.x = MAP_RIGHT + Infor::RADIUS_32;
					m_moveVal.x = 0;
				break; default:
					break;
				}
			}
			else if (chipData[h][w] >= 90)	//�f�[�^�F�񕜃|�C���g
			{
				if (m_bHeal) return;
				if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
				{
					SetHeal(HP::PLAYER);
					m_bHeal = true;
				}
			}
			else if (chipData[h][w] == 80)	//�f�[�^�F�M�~�b�N
			{
				// ��̔���
				if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
				{
					int y = rand() % 4 + 18;
					int x = 37;
					enemy->shot({ chipX[y][x], chipY[y][x] }, m_pos);
				}
			}
			else if (chipData[h][w] == 70)	//�f�[�^�F�ŔW��
			{
				if (mapData != OutSide)continue;
				CMessage* msgList = m_pOwner->GetMsg();
				//�ŔO����
				if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
				{
					int msgNum = 0;
					if (w == 5)msgNum = 0;
					else if (w == 8)msgNum = 1;
					else if (w == 11)msgNum = 2;
					
					// ���b�Z�[�W�\��
					msgList->SetMessage({ chipX[h][w],chipY[h][w] + 100 }, msgNum);
					return;
				}
				else msgList->SetAlive();
			}
			else if (chipData[h][w] >= 60 && chipData[h][w] <= 69)	//�f�[�^�F�}�b�v�`�F���W
			{
				if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
				{
					map->SetMapSwitchFlg(true);		//�}�b�v�؂�ւ��t���O
				}
			}
			else if (chipData[h][w] >= 49 && chipData[h][w] <= 59)	//�f�[�^�F��
			{
				////////////////////////////////////////////////////////////////
				//		�v���C���[�̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				// �ʏ�̕ǔ���
				hit = Utility::iHitCheck(m_pos, m_moveVal, chipX[h][w], chipY[h][w],
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);

				switch (hit)
				{
				case 1:m_pos.y = MAP_TOP + Infor::RADIUS_32;
					m_moveVal.y = 0;
					break;
				case 2:
					m_pos.y = MAP_BOTTOM - Infor::RADIUS_32;
					m_moveVal.y = 0;
					break;
				case 3:m_pos.x = MAP_LEFT - Infor::RADIUS_32;
					m_moveVal.x = 0;
					break;
				case 4:
					m_pos.x = MAP_RIGHT + Infor::RADIUS_32;
					m_moveVal.x = 0;
				break; default:
					break;
				}

				// ���t���ǂƂ̓����蔻��
				bool hit = Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);

				// ���𐧌��������Ă��ԂŐG����
				if ((m_KeyPossession >= 2) && (!hit))
				{
					map->SetUnlock();	// ���J������
					m_KeyPossession = 0;
				}
				////////////////////////////////////////////////////////////////
				//		�e�̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				for (int i = 0; i < BULLET_MAX; i++)
				{
					//�q�b�g��
					if (!Utility::bHitCheck(m_bulletList[i].GetPos(), m_bulletList[i].GetMove(), { chipX[h][w],chipY[h][w] },
						SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
					{
						m_bulletList[i].SetAlive(false);	//�e�̃t���O����
					}
				}
			}
			else if (chipData[h][w] == 21)
			{
				if (mapData != OneFloor)continue;
				CMessage* msgList = m_pOwner->GetMsg();
				//�ŔO����
				if (!Utility::bHitCheck(m_pos, m_moveVal, { chipX[h][w],chipY[h][w] },
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
				{
					int msgNum = 0;
					if (w == 23)msgNum = 3;

					// ���b�Z�[�W�\��
					msgList->SetMessage({ chipX[h][w],chipY[h][w] + 100 }, msgNum);
					return;
				}
				else msgList->SetAlive();
			}
			else if (chipData[h][w] >= 10)	//�f�[�^�F��
			{
				continue;
			}
			else	//�f�[�^�F��
			{
				////////////////////////////////////////////////////////////////
				//		�v���C���[�̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				hit = Utility::iHitCheck(m_pos, m_moveVal, chipX[h][w], chipY[h][w],
					PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
					Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);

				switch (hit)
				{
				case 1:m_pos.y = MAP_TOP + Infor::RADIUS_32;
					m_moveVal.y = 0;
					break;
				case 2:
					m_pos.y = MAP_BOTTOM - Infor::RADIUS_32;
					m_moveVal.y = 0;
					break;
				case 3:m_pos.x = MAP_LEFT - Infor::RADIUS_32;
					m_moveVal.x = 0;
					break;
				case 4:
					m_pos.x = MAP_RIGHT + Infor::RADIUS_32;
					m_moveVal.x = 0;
				break; default:
					break;
				}
				////////////////////////////////////////////////////////////////
				//		�e�̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				for (int i = 0; i < BULLET_MAX; i++)
				{
					bool hit = Utility::bHitCheck(m_bulletList[i].GetPos(), m_bulletList[i].GetMove(), { chipX[h][w],chipY[h][w] },
						SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
						Infor::RADIUS_32,Infor::RADIUS_32,Infor::RADIUS_32,Infor::RADIUS_32);
					//�q�b�g��
					if (!hit)
					{
						m_bulletList[i].SetAlive(false);	//�e�̃t���O����
					}
				}
			}
		}
	}
}

//�G�Ƃ̓����蔻��
void CPlayer::HitCheckEnemy()
{
	CEnemy* enemy = m_pOwner->GetEnemy();	// �G�N���X�擾
	CEffect* effect = m_pOwner->GetEffect();
	CDamage* dmgList = effect->GetDmgList();

	const float EffectSize = 1.6;	// �q�b�g�G�t�F�N�g�T�C�Y

	////////////////////////////////////////////////////////////////
	//		���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CSamurai* samuraiList = enemy->GetSamuraiList();	//�G�N���X�F�����X�g�擾
	for (int e = 0; e < SAMURAI_MAX; e++)
	{
		Math::Vector2 enePos = samuraiList[e].GetPos();		//�G�̍��W�擾
		Math::Vector2 eneMove = samuraiList[e].GetMove();		//�G�̈ړ��ʎ擾

		//�����Ă�G�̂�
		if (!samuraiList[e].IsAlive()) continue;

		////////////////////////////////////////////////////////////////
		//		�v���C���[�̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		if (!m_HitFlg)	//���G��ԂłȂ��Ƃ�
		{
			int player_hit = Utility::iHitCheck(m_pos, m_moveVal, enePos.x, enePos.y,
				PLAYER_SIZE::LEFT,PLAYER_SIZE::RIGHT,PLAYER_SIZE::TOP,PLAYER_SIZE::DOWN,
				SAMURAI_SIZE::LEFT,SAMURAI_SIZE::RIGHT,SAMURAI_SIZE::TOP,SAMURAI_SIZE::DOWN);

			//�G�̌��ݍ��W�̎l��
			const float ENEMY_LEFT = enePos.x - Infor::RADIUS_32;	//����
			const float ENEMY_RIGHT = enePos.x + Infor::RADIUS_32;	//�E��
			const float ENEMY_TOP = enePos.y + Infor::RADIUS_32;		//���
			const float ENEMY_BOTTOM = enePos.y - Infor::RADIUS_32;	//����

			//�����蔻�蕪�򏈗�
			//1:��	2:�� 3:�� 4:�E
			int dmg = 5;
			switch (player_hit)
			{
			case 1:
				m_pos.y = ENEMY_TOP + Infor::RADIUS_32;
				m_moveVal.y = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);			//�̗͌���
				m_HitFlg = true;
				
				break;
			case 2:
				m_pos.y = ENEMY_BOTTOM - Infor::RADIUS_32;
				m_moveVal.y = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);
				m_HitFlg = true;
				break;
			case 3:
				m_pos.x = ENEMY_LEFT - Infor::RADIUS_32;
				m_moveVal.x = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);
				m_HitFlg = true;
				break;
			case 4:
				m_pos.x = ENEMY_RIGHT + Infor::RADIUS_32;
				m_moveVal.x = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);
				m_HitFlg = true;
				break;
			default:
				break;
			}
		}
		////////////////////////////////////////////////////////////////
		//		�e�̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		for (int i = 0; i < BULLET_MAX; i++)
		{
			//�����Ă�e�̂�
			if (m_bulletList[i].IsAlive())
			{
				bool bullet_hit = true;
				bullet_hit = Utility::bHitCheck(m_bulletList[i].GetPos(), m_bulletList[i].GetMove(), enePos,
					SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
					SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN);

				//�q�b�g��
				if (!bullet_hit)
				{
					samuraiList[e].SetDamage(POWER::PLAYER_SHURIKEN);			//�G�Ƀ_���[�W
					m_bulletList[i].SetAlive(false);	//�e�̃t���O����
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
					break;
				}
			}
		}
		////////////////////////////////////////////////////////////////
		//		�a���̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		//�a����o���Ă����
		if (m_swordList.bGetSlash())
		{
			if (!samuraiList[e].bGetSlashHit())	// ���i�q�b�g�h�~�t���O
			{
				// �G�Ǝa���̋���
				const float checkDist = Utility::GetDistance(enePos, m_swordList.GetPos());

				// �q�b�g����̋���
				const float hitDist = SLASH_SIZE::LEFT+SAMURAI_SIZE::LEFT;

				// �q�b�g�������������߂��Ƃ�
				if (checkDist <= hitDist)
				{
					samuraiList[e].SetDamage(POWER::PLAYER_SLASH);	//�G�Ƀ_���[�W
					samuraiList[e].bSetSlashHit(true);	// ���i�q�b�g�h�~
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
				}
			}
		}
		else samuraiList[e].bSetSlashHit(false);
		////////////////////////////////////////////////////////////////
		//		�����̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		//�������Ă��鎞
		if (m_bombList.GetBlastAlive())
		{
			if (!samuraiList[e].bGetBlastHit())
			{
				bool blast_hit = true;
				blast_hit = Utility::bHitCheck(m_bombList.GetBlastPos(), { 0,0 }, enePos,
					BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN,
					SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN);
				//�q�b�g��
				if (!blast_hit)
				{
					samuraiList[e].SetDamage(POWER::PLAYER_BLAST);			//�G�Ƀ_���[�W
					samuraiList[e].bSetBlastHit(true);
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
				}
			}
		}
		else samuraiList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		�|���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CArcher* archerList = enemy->GetArcherList();	//�G�N���X�F�|�����X�g�擾
	for (int i = 0; i < ARCHER_MAX; i++)
	{
		Math::Vector2 enePos = archerList[i].GetPos();		//�G�̍��W�擾
		Math::Vector2 eneMove = archerList[i].GetMove();	//�G�̈ړ��ʎ擾

		//�����Ă�G�̂�
		if (!archerList[i].IsAlive()) continue;

		////////////////////////////////////////////////////////////////
		//		�v���C���[�̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		if (!m_HitFlg)	//���G��ԂłȂ��Ƃ�
		{
			int player_hit = Utility::iHitCheck(m_pos, m_moveVal, enePos.x, enePos.y,
				PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
				ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN);

			//�G�̌��ݍ��W�̎l��
			const float ENEMY_LEFT = enePos.x - Infor::RADIUS_32;	//����
			const float ENEMY_RIGHT = enePos.x + Infor::RADIUS_32;	//�E��
			const float ENEMY_TOP = enePos.y + Infor::RADIUS_32;		//���
			const float ENEMY_BOTTOM = enePos.y - Infor::RADIUS_32;	//����

			//�����蔻�蕪�򏈗�
			//1:��	2:�� 3:�� 4:�E
			switch (player_hit)
			{
			case 1:
				m_pos.y = ENEMY_TOP + Infor::RADIUS_32;
				m_moveVal.y = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);			//�̗͌���
				m_HitFlg = true;
				break;
			case 2:
				m_pos.y = ENEMY_BOTTOM - Infor::RADIUS_32;
				m_moveVal.y = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);			//�̗͌���
				m_HitFlg = true; break;
			case 3:
				m_pos.x = ENEMY_LEFT - Infor::RADIUS_32;
				m_moveVal.x = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);			//�̗͌���
				m_HitFlg = true; break;
			case 4:
				m_pos.x = ENEMY_RIGHT + Infor::RADIUS_32;
				m_moveVal.x = 0;
				SetDamage(POWER::ENEMY_PHYSICAL);			//�̗͌���
				m_HitFlg = true; break;
			default:
				break;
			}
		}
		////////////////////////////////////////////////////////////////
		//		�e�̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		for (int b = 0; b < BULLET_MAX; b++)
		{
			//�����Ă�e�̂�
			if (m_bulletList[b].IsAlive())
			{
				bool bullet_hit = true;
				bullet_hit = Utility::bHitCheck(m_bulletList[b].GetPos(), m_bulletList[b].GetMove(),enePos,
					SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
					ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN);

				//�q�b�g��
				if (!bullet_hit)
				{
					archerList[i].SetDamage(POWER::PLAYER_SHURIKEN);	//�G�Ƀ_���[�W
					m_bulletList[b].SetAlive(false);	//�e�̃t���O����
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
					break;
				}
			}
		}
		////////////////////////////////////////////////////////////////
		//		�a���̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		//�a����o���Ă����
		if (m_swordList.bGetSlash())
		{
			if (!archerList[i].bGetSlashHit())	// ���i�q�b�g�h�~
			{
				// �G�Ǝa���̋���
				const float checkDist = Utility::GetDistance(enePos, m_swordList.GetPos());

				// �q�b�g����̋���
				const float hitDist = SLASH_SIZE::LEFT + ARCHER_SIZE::LEFT;

				// �q�b�g�������������߂��Ƃ�
				if (checkDist <= hitDist)
				{
					archerList[i].SetDamage(POWER::PLAYER_SLASH);	//�G�Ƀ_���[�W
					archerList[i].bSetSlashHit(true);	// ���i�q�b�g�h�~
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
				}
			}
		}
		else archerList[i].bSetSlashHit(false);
		////////////////////////////////////////////////////////////////
		//		�����̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		//�������Ă��鎞
		if (m_bombList.GetBlastAlive())
		{
			if (!archerList[i].bGetBlastHit())
			{
				bool blast_hit = true;
				blast_hit = Utility::bHitCheck(m_bombList.GetBlastPos(), { 0,0 }, enePos,
					BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN,
					ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN);
				//�q�b�g��
				if (!blast_hit)
				{
					archerList[i].SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
					archerList[i].bSetSlashHit(true);
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
				}
			}
		}
		else archerList[i].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		��j�Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CGiant* giantList = enemy->GetGiantList();	//�G�N���X�F��j���X�g�擾
	for (int i = 0; i < GIANT_MAX; i++)
	{
		Math::Vector2 enePos = giantList[i].GetPos();		//�G�̍��W�擾
		Math::Vector2 eneMove = giantList[i].GetMove();		//�G�̈ړ��ʎ擾

		//�����Ă�G�̂�
		if (!giantList[i].IsAlive()) continue;

		////////////////////////////////////////////////////////////////
		//		�v���C���[�̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		if (!m_HitFlg)	//���G��ԂłȂ��Ƃ�
		{
			int player_hit = Utility::iHitCheck(m_pos, m_moveVal, enePos.x, enePos.y,
				PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
				GIANT_SIZE::LEFT,GIANT_SIZE::RIGHT,GIANT_SIZE::TOP,GIANT_SIZE::DOWN);

			//�G�̌��ݍ��W�̎l��
			const float ENEMY_LEFT = enePos.x - Infor::RADIUS_32;	//����
			const float ENEMY_RIGHT = enePos.x + Infor::RADIUS_32;	//�E��
			const float ENEMY_TOP = enePos.y + Infor::RADIUS_32;		//���
			const float ENEMY_BOTTOM = enePos.y - Infor::RADIUS_32;	//����

			// �ːi��������Ƒ�_���[�W
			int dmg = 0;
			float knockBack = 0;
			if (giantList[i].bGetRush())
			{
				dmg = 10;
				knockBack = 80;
			}
			else
			{
				dmg = POWER::ENEMY_PHYSICAL;
				knockBack = 0;
			}

			//�����蔻�蕪�򏈗�
			//1:��	2:�� 3:�� 4:�E
			switch (player_hit)
			{
			case 1:
				m_pos.y = ENEMY_TOP + Infor::RADIUS_32;
				m_moveVal.y = knockBack;
				SetDamage(dmg);			//�̗͌���
				m_HitFlg = true; 
				break;
			case 2:
				m_pos.y = ENEMY_BOTTOM - Infor::RADIUS_32;
				m_moveVal.y = -knockBack;
				SetDamage(dmg);			//�̗͌���
				m_HitFlg = true; 
				break;
			case 3:
				m_pos.x = ENEMY_LEFT - Infor::RADIUS_32;
				m_moveVal.x = -knockBack;
				SetDamage(dmg);			//�̗͌���
				m_HitFlg = true; 
				break;
			case 4:
				m_pos.x = ENEMY_RIGHT + Infor::RADIUS_32;
				m_moveVal.x = knockBack;
				SetDamage(dmg);			//�̗͌���
				m_HitFlg = true; 
				break;
			default:
				break;
			}
		}
		////////////////////////////////////////////////////////////////
		//		�e�̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		for (int b = 0; b < BULLET_MAX; b++)
		{
			//�����Ă�e�̂�
			if (!m_bulletList[b].IsAlive()) continue;
			
			bool bullet_hit = true;
			bullet_hit = Utility::bHitCheck(m_bulletList[b].GetPos(), m_bulletList[b].GetMove(), enePos,
				SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
				GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN);

			//�q�b�g��
			if (!bullet_hit)
			{
				giantList[i].SetDamage(POWER::PLAYER_SHURIKEN);	//�G�Ƀ_���[�W
				m_bulletList[b].SetAlive(false);	//�e�̃t���O����
				for (int i = 0; i < EFFECT_DMG_MAX; i++)
				{
					if (dmgList[i].GetbAlive())continue;
					dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
					break;
				}
				break;
			}
		}
		////////////////////////////////////////////////////////////////
		//		�a���̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		//�a����o���Ă����
		if (m_swordList.bGetSlash())
		{
			if (!giantList[i].bGetSlashHit())	// ���i�q�b�g�h�~
			{
				// �G�Ǝa���̋���
				const float checkDist = Utility::GetDistance(enePos, m_swordList.GetPos());

				// �q�b�g����̋���
				const float hitDist = SLASH_SIZE::LEFT + GIANT_SIZE::LEFT;

				// �q�b�g�������������߂��Ƃ�
				if (checkDist <= hitDist)
				{
					giantList[i].SetDamage(POWER::PLAYER_SLASH);	//�G�Ƀ_���[�W
					giantList[i].bSetSlashHit(true);	// ���i�q�b�g�h�~
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
				}
			}
		}
		else giantList[i].bSetSlashHit(false);
		////////////////////////////////////////////////////////////////
		//		�����̃q�b�g�`�F�b�N								
		////////////////////////////////////////////////////////////////
		//�������Ă��鎞
		if (m_bombList.GetBlastAlive())
		{
			if (!giantList[i].bGetBlastHit())
			{
				bool blast_hit = true;
				blast_hit = Utility::bHitCheck(m_bombList.GetBlastPos(), { 0,0 }, enePos,
					BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN,
					GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN);
				//�q�b�g��
				if (!blast_hit)
				{
					giantList[i].SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
					giantList[i].bSetBlastHit(true);
					for (int i = 0; i < EFFECT_DMG_MAX; i++)
					{
						if (dmgList[i].GetbAlive())continue;
						dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
						break;
					}
				}
			}
		}
		else giantList[i].bSetBlastHit(false);
	}


	//------------------------------------------
//======�{�X�̓����蔻��======
//===========)()(("&)'!)#)'%$)&!)(#!)(#
//(�v���C���[�ւ̃_���[�W��enemy�N���X�ɓ��͂���Ă���̂ŁA�{�X���󂯂�_���[�W�̏����̂�)

	CBoss* bossList = enemy->GetBossList();
	Math::Vector2 enePos = bossList->GetPos();		//�G�̍��W�擾
	Math::Vector2 eneMove = bossList->GetMove();		//�G�̈ړ��ʎ擾

	// �{�X�������Ă鎞�̂�
	if (!bossList->IsAlive()) return;

	// �e(�藠��)�̃q�b�g�`�F�b�N
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// �����Ă�e�̂�
		if (m_bulletList[i].IsAlive())
		{
			bool bullet_hit = true;
			bullet_hit = Utility::bHitCheck(m_bulletList[i].GetPos(), m_bulletList[i].GetMove(), bossList->GetPos(),
				SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
				BOSS_SIZE::LEFT,BOSS_SIZE::RIGHT,BOSS_SIZE::TOP,BOSS_SIZE::DOWN);

			// �q�b�g��
			if (!bullet_hit)
			{
				bossList->SetDamage(POWER::PLAYER_SHURIKEN);	//�G�Ƀ_���[�W
				m_bulletList[i].SetAlive(false);	//�e�̃t���O����
				for (int i = 0; i < EFFECT_DMG_MAX; i++)
				{
					if (dmgList[i].GetbAlive())continue;
					dmgList[i].EmitDmg(m_bulletList[i].GetPos(), eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
					break;
				}
				break;
			}
		}
	}

	//======�a���̃q�b�g�`�F�b�N======
	//�a����o���Ă����
	if (m_swordList.bGetSlash())
	{
		if (!bossList->bGetSlashHit())	// ���i�q�b�g�h�~�t���O
		{
			// �G�Ǝa���̋���
			const float checkDist = Utility::GetDistance(enePos, m_swordList.GetPos());

			// �q�b�g����̋���
			const float hitDist = SLASH_SIZE::LEFT + BOSS_SIZE::LEFT;

			// �q�b�g�������������߂��Ƃ�
			if (checkDist <= hitDist)
			{
				bossList->SetDamage(POWER::PLAYER_SLASH);	//�G�Ƀ_���[�W
				bossList->bSetSlashHit(true);	// ���i�q�b�g�h�~
				for (int i = 0; i < EFFECT_DMG_MAX; i++)
				{
					if (dmgList[i].GetbAlive())continue;
					dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
					break;
				}
			}
		}
	}
	else
	{
		bossList->bSetSlashHit(false);
	}

	////////////////////////////////////////////////////////////////
	//		�����̃q�b�g�`�F�b�N								
	////////////////////////////////////////////////////////////////
	//�������Ă��鎞
	if (m_bombList.GetBlastAlive())
	{
		if (!bossList->bGetBlastHit())
		{
			bool blast_hit = true;
			blast_hit = Utility::bHitCheck(m_bombList.GetBlastPos(), { 0,0 }, bossList->GetPos(),
				BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN,
				BOSS_SIZE::LEFT, BOSS_SIZE::RIGHT, BOSS_SIZE::TOP, BOSS_SIZE::DOWN);
			//�q�b�g��
			if (!blast_hit)
			{
				bossList->SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
				bossList->bSetBlastHit(true);
				for (int i = 0; i < EFFECT_DMG_MAX; i++)
				{
					if (dmgList[i].GetbAlive())continue;
					dmgList[i].EmitDmg(enePos, eneMove, EffectSize);	// �_���[�W�G�t�F�N�g����
					break;
				}
			}
		}
	}
	else bossList->bSetBlastHit(false);
}

// �����Ƃ̓����蔻��
void CPlayer::HitCheckBomb()
{
	if (m_HitFlg) return;

	CEffect* effect = m_pOwner->GetEffect();
	CDamage* dmgList = effect->GetDmgList();
	//�������Ă��鎞
	if (m_bombList.GetBlastAlive())
	{
		bool blast_hit = true;
		blast_hit = Utility::bHitCheck(m_pos, m_moveVal, m_bombList.GetBlastPos(), 
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN);
		//�q�b�g��
		if (!blast_hit)
		{
			SetDamage(POWER::PLAYER_BLAST);
			m_HitFlg = true;
		}
	}
}

//�A�C�e���Ƃ̓����蔻��
void CPlayer::HitCheckItem()
{
	CItem* item = m_pOwner->GetItem();
	
	////////////////////////////////////////////////////////////////
	//		�A�C�e���F���e								
	////////////////////////////////////////////////////////////////
	CItem_Bomb* ItemBomb = item->GetBombItem();	//���e���X�g�擾
	for (int i = 0; i < BOMB_SETMAX; i++)
	{
		// ���e�������ő�Ȃ���肵�Ȃ�
		if (m_BombPossession >= BOMB_MAX) break;

		if (!ItemBomb[i].GetAlive())continue;
		
		//�q�b�g��
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemBomb[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			56, 40, 24, 24))
		{
			ItemBomb[i].bSetbombHit();	//�E�����������
			ItemBomb[i].SetAlive();		//���e�̃t���O����
			m_BombPossession = BOMB_MAX;	//�A�C�e������
		}
	}
	////////////////////////////////////////////////////////////////
	//		�A�C�e���F��								
	////////////////////////////////////////////////////////////////
	//�����X�g�擾
	CItem_Key* ItemKey = item->GetKeyItem();
	for (int i = 0; i < KEY_SETMAX; i++)
	{
		if (!ItemKey[i].GetAlive()) continue;

		//�q�b�g��
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemKey[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			16, 16, 16, 16))
		{
			ItemKey[i].SetAlive();		//���̃t���O����
			m_KeyPossession++;		//������
		}
	}
	////////////////////////////////////////////////////////////////
	//		�A�C�e���F��								
	////////////////////////////////////////////////////////////////
	//�񕜃��X�g�擾
	CItem_Health* ItemHealth = item->GetHealehItem();
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		if (!ItemHealth[i].GetAlive())continue;
		
		//�q�b�g��
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemHealth[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			16, 16, 16, 16))
		{
			ItemHealth[i].SetAlive();		// �񕜂̃t���O����
			SetHeal(10);		// ��
		}
	}
	////////////////////////////////////////////////////////////////
	//		�A�C�e���F�B�ꖪ								
	////////////////////////////////////////////////////////////////
	//�B�ꖪ���X�g�擾
	CItem_Mino* ItemMino = item->GetMinoItem();
	if (!ItemMino->GetAlive())return;
	//�q�b�g��
	if (!Utility::bHitCheck(m_pos, m_moveVal, ItemMino->GetPos(),
		PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
		32,32,32,32))
	{
		ItemMino->SetAlive();	// �t���O����
		m_bMinoPossession = true;		// �B�ꖪ����
	}
}

//���G����
void CPlayer::InviTime()
{
	if (m_HitFlg)	//�v���C���[������������
	{
		m_hiddenList.bSetHidden();		// �B��g���

		const int CNT_MAX = 120;	//���G����
		if (m_hpCount >= CNT_MAX)
		{
			m_alpha = 1.0f;
			m_hpCount = 0;
			m_HitFlg = false;
			return;
		}
		m_hpCount++;

		//�_��
		if (m_hpCount % 10 == 0)
		{
			if (m_alpha < 1)m_alpha = 1;
			else m_alpha = 0.5;
		}
	}
	else
	{
		m_hpCount = 0;
		if (!m_hiddenList.bGetHidden()) m_alpha = 1.0f;
	}
}

//����؂�ւ��֐�
eClick CPlayer::ChangeItem(eClick click)
{
	switch (click)
	{
	case eShuriken:
		return eSword;
	case eSword:
		return eBomb;
	case eBomb:
		if (m_bMinoPossession) return eHidden;	// �B�ꖪ�������g�p�\
		else return eShuriken;
	case eHidden:
		return eShuriken;
	}
}

// �U���֐�
void CPlayer::Attack(bool flg, eClick click)
{
	if (flg) return;
	switch (click)
	{
	case eSword:	//��
		SetSword();
		break;
	case eShuriken:	//�藠��
		SetShuriken();
		break;
	case eBomb:		//���e
		SetBomb();
		break;
	case eHidden:	//�B��g
		SetHidden();
		break;
	}
}

//�U���F�藠��
void CPlayer::SetShuriken()
{
	if (m_shurikenCnt < COOL_TIME::PLAYER_SHURIKEN) return;
	
	m_hiddenList.bSetHidden();	// 攻撃時隠れ身解除
	CMap* map = m_pOwner->GetMap();		//マップクラス取得
	Math::Vector2 ScrollPos = map->GetscrollPos();		//スクロール量取得
	// 弾発射
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!m_bulletList[i].IsAlive())
		{
			// ���ˊp�x����߂�
			float deg = Utility::GetAngleDeg(m_pos, { (float)m_ClickPoint.x, (float)m_ClickPoint.y });
			// ����
			m_bulletList[i].Shot(m_pos, deg);
			m_shurikenCnt = 0;
			shurikenseInst->Play();
			break;
		}
	}
}

//�U���F��
void CPlayer::SetSword()
{
	if (m_slashCnt < COOL_TIME::PLAYER_SLASH) return;	// �a���J�E���g����
	
	m_hiddenList.bSetHidden();	// �U�����B��g���

	CMap* map = m_pOwner->GetMap();
	Math::Vector2 ScrollPos = map->GetscrollPos();

	m_hiddenList.bSetHidden();	// �U�����B��g���
	
	// �a������
	if (!m_swordList.bGetSlash())
	{
		// ���ˊp�x����߂�
		float deg = Utility::GetAngleDeg(m_pos, { (float)m_ClickPoint.x, (float)m_ClickPoint.y });
		// �a������
		m_swordList.Slash(m_pos, deg);
		m_slashCnt = 0;
		katanaseInst->Play();
	}
}

//�U���F���e
void CPlayer::SetBomb()
{
	if (m_BombPossession <= 0) return;

	m_hiddenList.bSetHidden();	// 攻撃時隠れ身解除

	// 爆弾発動
	if (!m_bombList.IsAlive())
	{
		m_bombList.InstBomb(m_pos);
		/* �A�C�e������� */
		m_BombPossession--;
	}
}

//�B��g
void CPlayer::SetHidden()
{
	m_hiddenList.Hidden();	// �B��g
	if (m_hiddenList.bGetHidden())
	{
		m_alpha = 0.2f;
		m_HitFlg = false;
	}
}

// �A�j���[�V����
int CPlayer::Animation(int cnt, const int xtex)
{
	return cnt / m_aTimer * 116 + 38 + xtex;
}

//std::shared_ptr<KdSoundInstance> CPlayer::Sound_Loading(std::shared_ptr<KdSoundEffect> se, std::shared_ptr<KdSoundInstance> seInst, const std::string& seName)
std::shared_ptr<KdSoundInstance> CPlayer::Sound_Loading(std::shared_ptr<KdSoundEffect> se, const std::string &seName)
{
	//�@�̈�m��
	se = std::make_shared<KdSoundEffect>();
	//�A���ǂݍ���
	se->Load(seName);
	//�B���̉�
	//seInst = se->CreateInstance(false);

	//return seInst;

	return se->CreateInstance(false);

	//�@�̈�m��
//	se = std::make_shared<KdSoundEffect>();
	//�A���ǂݍ���
//	se->Load("Sound/hit.WAV");
	//�B���̉�
//	seInst = se->CreateInstance(false);
}

