#include "CPlayer.h"
#include "Scene.h"
#include"Utility.h"

//�R���X�g���N�^
CPlayer::CPlayer()
	: m_direction(Right)
	, m_LClick(eShuriken)
	, m_RClick(eSword)
	, m_status(eIdle)
	, m_pTexture(nullptr)
	, m_pos(0.0f, 0.0f)
	, m_moveVal(0.0f, 0.0f)
	, m_mat()
	, m_transMat()
	, m_scaleMat()
	, m_size(1.0f, 1.0f)
	, m_bAlive(true)
	, m_hp(HP::PLAYER)
	, m_bHeal(false)
	, m_invincibleCnt()
	, m_alpha(1.0f)
	, m_HitFlg(false)
	, m_slashCnt(COOL_TIME::PLAYER_SLASH)
	, m_shurikenCnt(COOL_TIME::PLAYER_SHURIKEN/2)
	, m_bRClick(false)
	, m_bLClick(false)
	, m_bRChange(false)
	, m_bLChange(false)
	, m_aCnt(0)
	, m_aAttackCnt(0)
	, m_aTimer(15)
	, m_aflame(5)
	, scrRect(0,0,0,0)
	, m_BombPossession(0)
	, m_KeyPossession(0)
	, m_bMinoPossession(false)
	,m_pOwner(nullptr)
	,m_ClickPoint()
{
}

CPlayer::~CPlayer()
{
}

//������
void CPlayer::Init()
{
	//���W
	m_pos = { -250.0f,-1080.0f };	// �������W
	m_pos = { 900.0f,200.0f };	// �ߓ�

	//�ړ���
	m_moveVal = { 0.0f,0.0f };
	
	//�����t���O
	m_bAlive = true;
	
	//�̗�
	m_hp = HP::PLAYER;
	m_invincibleCnt = 0;

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
	m_shurikenCnt = COOL_TIME::PLAYER_SHURIKEN/2;

	//��������
	m_swordList.Init();
	m_slashCnt = COOL_TIME::PLAYER_SLASH;

	//���e�̏�����
	m_bombList.Init();
	m_BombPossession = 0;

	//�B��g������
	m_hiddenList.Init();
	m_bMinoPossession = false;

	//��������
	m_KeyPossession = 0;

	//SE(�T�E���h�̓ǂݍ��݂Ǝ��̉�)
	katanaseInst = Utility::Sound_Loading(katanase, "Resource/Sound/katana.WAV");
	shurikenseInst = Utility::Sound_Loading(shurikense, "Resource/Sound/shuriken.WAV");
	hitseInst = Utility::Sound_Loading(hitse,"Resource/Sound/hit.WAV");
	healseInst = Utility::Sound_Loading(healse, "Resource/Sound/heal.WAV");
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
		m_pos = { -460,100 };
		m_KeyPossession = 0;
		break;
	//�O�K�w
	case ThreeFloor:
		m_pos = { -460,-2000 };
		m_KeyPossession = 0;
		break;
	//�l�K�w
	case FourFloor:
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
	//�v���C���[��"����"��Ԃ̎��v���C���[�̏�Ԃ�"����"�̏�Ԃɂ���
	if(m_status==eWalking)
	m_status = eIdle;

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
	invincibleTime();

	//HP0�Ńt���O����
	if (m_hp <= 0) m_bAlive = !m_bAlive;
	//HP�����݂���
	if (m_hp >= HP::PLAYER)m_hp = HP::PLAYER;

	Animation();

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
	switch (m_status)
	{
	case eIdle:
		scrRect = { -20,AnimationCalc(m_aCnt,348),160,64 }; // �e�N�X�`�����W
		break;
	case eWalking:
		scrRect = { -20,AnimationCalc(m_aCnt,1044),160,64 }; // �e�N�X�`�����W
		break;
	case eAttack:
		scrRect = { -20,AnimationCalc(m_aCnt,0),160,64 }; // �e�N�X�`�����W
		break;
	default:
		break;
	}
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
	m_HitFlg = true;
	CEffect* effect = m_pOwner->GetEffect();
	effect->HitEffect(m_pos,m_moveVal,1.5);	// �q�b�g�G�t�F�N�g����
}

// �̗͉�
void CPlayer::SetHeal(int heal)
{
	m_hp += heal;
	CEffect* effect = m_pOwner->GetEffect();
	effect->PlayerHealEffect();		// �񕜃G�t�F�N�g����
	healseInst->Play();
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

// �L�[����ꗗ
void CPlayer::KeyOperation()
{
	/* �ړ� */
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVal.y += SPEED::PLAYER;
		m_direction = Up;
		if(m_status==eIdle) //�v���C���[��"����"��Ԃ̎���"����"��Ԃɕς���
		m_status = eWalking;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVal.y -= SPEED::PLAYER;
		m_direction = Down;
		if (m_status == eIdle) //�v���C���[��"����"��Ԃ̎���"����"��Ԃɕς���
			m_status = eWalking;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVal.x -= SPEED::PLAYER;
		m_direction = Left;
		if (m_status == eIdle) //�v���C���[��"����"��Ԃ̎���"����"��Ԃɕς���
			m_status = eWalking;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVal.x += SPEED::PLAYER;
		m_direction = Right;
		if (m_status == eIdle) //�v���C���[��"����"��Ԃ̎���"����"��Ԃɕς���
			m_status = eWalking;
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

	float(*chipX)[MAP_CHIP_W] = map->GetPosX();
	float(*chipY)[MAP_CHIP_W] = map->GetPosY();
	int(*chipData)[MAP_CHIP_W] = map->GetChipData();
	int mapData = map->GetMapData();	//�}�b�v�f�[�^�擾

	//�}�b�v�f�[�^���g����
	int hit = 0;
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			if (chipData[h][w] >= 78 && chipData[h][w] <= 79)	//�f�[�^�F�M�~�b�N
			{
				if (mapData == OneFloor)
				{
					hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
					if (hit == 1)
					{
						if (enemy->bGetEvent())map->SetLock();	// �J�M��
						enemy->Event();		// �C�x���g����
					}
				}
				else if (mapData == BossFloor)
				{
					// �C�x���g��������
					if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
					{
						if (enemy->bGetEvent())map->SetLock();	// �J�M��
					}
				}
			}
			else if (chipData[h][w] >= 91 && chipData[h][w] <= 94)	//�f�[�^�F��
			{
				// �ʏ�̕ǔ���
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
			}
			else if (chipData[h][w] >= 90 && chipData[h][w] <= 94)	//�f�[�^�F�񕜃|�C���g
			{
				if (m_bHeal) return;
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
				{
					SetHeal(HP::PLAYER);
					m_bHeal = true;
				}
			}
			else if (chipData[h][w] == 95)	// �M�~�b�N�F�g�Q
			{
				if (m_HitFlg) continue;
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] })) SetDamage(10);
			}
			else if (chipData[h][w] == 96 || chipData[h][w] == 97)
			{
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				if (hit == 2 || hit == 4)map->SetUnlock();
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
			}
			else if (chipData[h][w] == 80)	//�f�[�^�F�M�~�b�N
			{
				// ��̔���
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
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
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
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
				if (bMapHitFunction({ chipX[h][w],chipY[h][w] }))
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
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);

				// ���𐧌��������Ă��ԂŌ��t���ǂɐG����
				if ((m_KeyPossession >= 2) && (bMapHitFunction({ chipX[h][w],chipY[h][w] })))
				{
					map->SetUnlock();	// ���J������
					m_KeyPossession = 0;
				}
				////////////////////////////////////////////////////////////////
				//		�e�̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				for (int i = 0; i < BULLET_MAX; i++)
				{
					if (bMapHitFunction({ chipX[h][w],chipY[h][w] })) 
					{
						m_bulletList[i].SetAlive();	//�e�̃t���O����
					}
				}
			}
			else if (chipData[h][w] == 21)		// �f�[�^�F���b�Z�[�W
			{
				if (mapData != OneFloor && mapData != TwoFloor)continue;
				CMessage* msgList = m_pOwner->GetMsg();
				//�ŔO����
				if (bMapHitFunction({chipX[h][w],chipY[h][w]}))
				{
					int msgNum = 0;
					if (w == 23)msgNum = 3;
					if (w == 34)msgNum = 4;
					
					// ���b�Z�[�W�\��
					msgList->SetMessage({ chipX[h][w],chipY[h][w] + 100 }, msgNum);
					return;
				}
				else msgList->SetAlive();
			}
			else if (chipData[h][w] >= 10)	continue; //�f�[�^�F��
			else	//�f�[�^�F��
			{
				////////////////////////////////////////////////////////////////
				//		�v���C���[�̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				hit = iMapHitFunction({ chipX[h][w],chipY[h][w] });
				HitMapCase({ chipX[h][w],chipY[h][w] }, hit);
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
						m_bulletList[i].SetAlive();	//�e�̃t���O����
					}
				}
			}
		}
	}
}

// �}�b�v�ƃv���C���[�̔���֐�(bool����)
bool CPlayer::bMapHitFunction(Math::Vector2 chipPos)
{
	if (!Utility::bHitCheck(m_pos, m_moveVal,chipPos,
		PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
		Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
	{
		return true;
	}
	return false;
}
// �}�b�v�ƃv���C���[�̔���֐�(int����)
int CPlayer::iMapHitFunction(Math::Vector2 chipPos)
{
	return Utility::iHitCheck(m_pos, m_moveVal, chipPos.x, chipPos.y,
		PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
		Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);
}
// �l�ӂ̓����蔻��֐�
void CPlayer::HitMapCase(Math::Vector2 chipPos, int HitCase)
{
	//�}�b�v�̌��ݍ��W�̎l��
	const float MAP_LEFT = chipPos.x - Infor::RADIUS_32;		//����
	const float MAP_RIGHT = chipPos.x + Infor::RADIUS_32;		//�E��
	const float MAP_TOP = chipPos.y + Infor::RADIUS_32;		//���
	const float MAP_BOTTOM = chipPos.y - Infor::RADIUS_32;	//����
	switch (HitCase)
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
	break; 
	default:
		break;
	}
}

//�G�Ƃ̓����蔻��
void CPlayer::HitCheckEnemy()
{
	CEnemy* enemy = m_pOwner->GetEnemy();		// �G�N���X�擾
	CEffect* effect = m_pOwner->GetEffect();	// �G�t�F�N�g�N���X�擾
	const float EffectSize = 1.6;	// �q�b�g�G�t�F�N�g�T�C�Y

	////////////////////////////////////////////////////////////////
	//		���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CSamurai* samuraiList = enemy->GetSamuraiList();	//�G�N���X�F�����X�g�擾
	for (int e = 0; e < SAMURAI_MAX; e++)
	{
		Math::Vector2 enePos = samuraiList[e].GetPos();		//���W�擾
		Math::Vector2 eneMove = samuraiList[e].GetMove();	//�ړ��ʎ擾

		if (!samuraiList[e].IsAlive()) continue;	// �������̓G�̂�

		/* �e�̃q�b�g�`�F�b�N */
		if (HitCheckEnemy_And_Bullet(enePos, SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN))
		{
			samuraiList[e].SetDamage(POWER::PLAYER_SHURIKEN);	// �G�Ƀ_���[�W
			effect->HitEffect(enePos, eneMove, EffectSize);		// �_���[�W�G�t�F�N�g����
		}
		/* �a���̃q�b�g�`�F�b�N */
		if (m_swordList.bGetSlash()) // �a�����o���Ă����
		{
			if(HitCheckEnemy_And_Slash(enePos, samuraiList[e].bGetSlashHit(), SAMURAI_SIZE::LEFT))
			{
				samuraiList[e].SetDamage(POWER::PLAYER_SLASH);	// �G�Ƀ_���[�W
				samuraiList[e].bSetSlashHit(true);				// ���i�q�b�g�h�~
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else samuraiList[e].bSetSlashHit(false);
		/* �����̃q�b�g�`�F�b�N */
		if (m_bombList.GetBlastAlive()) // �������Ă��鎞
		{
			if (HitCheckEnemy_And_Blast(enePos, samuraiList[e].bGetBlastHit(), SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN))
			{
				samuraiList[e].SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
				samuraiList[e].bSetBlastHit(true);				// ���i�q�b�g�h�~
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else samuraiList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		�|���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CArcher* archerList = enemy->GetArcherList();	//�G�N���X�F�|�����X�g�擾
	for (int e = 0; e < ARCHER_MAX; e++)
	{
		Math::Vector2 enePos = archerList[e].GetPos();		//���W�擾
		Math::Vector2 eneMove = archerList[e].GetMove();	//�ړ��ʎ擾

		if (!archerList[e].IsAlive()) continue;	// �������̓G�̂�

		/* �e�̃q�b�g�`�F�b�N */
		if (HitCheckEnemy_And_Bullet(enePos, ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN))
		{
			archerList[e].SetDamage(POWER::PLAYER_SHURIKEN);	// �G�Ƀ_���[�W
			effect->HitEffect(enePos, eneMove, EffectSize);		// �_���[�W�G�t�F�N�g����
		}
		/* �a���̃q�b�g�`�F�b�N */
		if (m_swordList.bGetSlash()) // �a�����o���Ă����
		{
			if (HitCheckEnemy_And_Slash(enePos, archerList[e].bGetSlashHit(), ARCHER_SIZE::LEFT))
			{
				archerList[e].SetDamage(POWER::PLAYER_SLASH);	// �G�Ƀ_���[�W
				archerList[e].bSetSlashHit(true);				// ���i�q�b�g�h�~
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else archerList[e].bSetSlashHit(false);
		/* �����̃q�b�g�`�F�b�N */
		if (m_bombList.GetBlastAlive()) // �������Ă��鎞
		{
			if (HitCheckEnemy_And_Blast(enePos, archerList[e].bGetBlastHit(), ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN))
			{
				archerList[e].SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
				archerList[e].bSetBlastHit(true);				// ���i�q�b�g�h�~
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else archerList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		��j�Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CGiant* giantList = enemy->GetGiantList();	//�G�N���X�F��j���X�g�擾
	for (int e = 0; e < GIANT_MAX; e++)
	{
		Math::Vector2 enePos = giantList[e].GetPos();		//���W�擾
		Math::Vector2 eneMove = giantList[e].GetMove();		//�ړ��ʎ擾

		if (!giantList[e].IsAlive()) continue;	// �������̓G�̂�

		/* �e�̃q�b�g�`�F�b�N */
		if (HitCheckEnemy_And_Bullet(enePos, GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN))
		{
			giantList[e].SetDamage(POWER::PLAYER_SHURIKEN);		//�G�Ƀ_���[�W
			effect->HitEffect(enePos, eneMove, EffectSize);		//�_���[�W�G�t�F�N�g����
		}
		/* �a���̃q�b�g�`�F�b�N */
		if (m_swordList.bGetSlash()) // �a�����o���Ă����
		{
			if (HitCheckEnemy_And_Slash(enePos, giantList[e].bGetSlashHit(), GIANT_SIZE::LEFT))
			{
				giantList[e].SetDamage(POWER::PLAYER_SLASH);	//�G�Ƀ_���[�W
				giantList[e].bSetSlashHit(true);				// ���i�q�b�g�h�~
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else giantList[e].bSetSlashHit(false);
		/* �����̃q�b�g�`�F�b�N */
		if (m_bombList.GetBlastAlive()) // �������Ă��鎞
		{
			if (HitCheckEnemy_And_Blast(enePos, giantList[e].bGetBlastHit(), GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN))
			{
				giantList[e].SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
				giantList[e].bSetBlastHit(true);				// ���i�q�b�g�h�~
				effect->HitEffect(enePos, eneMove, EffectSize);
			}
		}
		else giantList[e].bSetBlastHit(false);
	}
	////////////////////////////////////////////////////////////////
	//		�{�X�Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	CBoss* bossList = enemy->GetBossList();				//�G�N���X�F�{�X���X�g�擾
	Math::Vector2 enePos = bossList->GetPos();			//���W�擾
	Math::Vector2 eneMove = bossList->GetMove();		//�ړ��ʎ擾

	if (!bossList->IsAlive()) return;	// �������̓G�̂�

	/* �e�̃q�b�g�`�F�b�N */
	if (HitCheckEnemy_And_Bullet(enePos,BOSS_SIZE::LEFT, BOSS_SIZE::RIGHT, BOSS_SIZE::TOP, BOSS_SIZE::DOWN))
	{
		bossList->SetDamage(POWER::PLAYER_SHURIKEN);		//�G�Ƀ_���[�W
		effect->HitEffect(enePos, eneMove, EffectSize);		//�_���[�W�G�t�F�N�g����
	}
	/* �a���̃q�b�g�`�F�b�N */
	if (m_swordList.bGetSlash()) // �a�����o���Ă����
	{
		if (HitCheckEnemy_And_Slash(enePos, bossList->bGetSlashHit(), BOSS_SIZE::LEFT))
		{
			bossList->SetDamage(POWER::PLAYER_SLASH);	//�G�Ƀ_���[�W
			bossList->bSetSlashHit(true);				// ���i�q�b�g�h�~
			effect->HitEffect(enePos, eneMove, EffectSize);
		}
	}
	else bossList->bSetSlashHit(false);
	/* �����̃q�b�g�`�F�b�N */
	if (m_bombList.GetBlastAlive()) // �������Ă��鎞
	{
		if (HitCheckEnemy_And_Blast(enePos, bossList->bGetBlastHit(), BOSS_SIZE::LEFT, BOSS_SIZE::RIGHT, BOSS_SIZE::TOP, BOSS_SIZE::DOWN))
		{
			bossList->SetDamage(POWER::PLAYER_BLAST);	//�G�Ƀ_���[�W
			bossList->bSetBlastHit(true);				// ���i�q�b�g�h�~
			effect->HitEffect(enePos, eneMove, EffectSize);
		}
	}
	else bossList->bSetBlastHit(false);
}

// �G�Ǝ藠�������蔻��֐�
bool CPlayer::HitCheckEnemy_And_Bullet(Math::Vector2 enePos, float left, float right, float top, float down)
{
	for (int b = 0; b < BULLET_MAX; b++)
	{
		if (m_bulletList[b].IsAlive()) // ���˒��̂�
		{
			//�q�b�g��
			if (!Utility::bHitCheck(m_bulletList[b].GetPos(), m_bulletList[b].GetMove(), enePos,
				SHURIKEN_SIZE::LEFT, SHURIKEN_SIZE::RIGHT, SHURIKEN_SIZE::TOP, SHURIKEN_SIZE::DOWN,
				left,right,top,down))
			{
				m_bulletList[b].SetAlive();	//�e�̃t���O����
				return true;
			}
		}
	}
	return false;
}
// �G�Ǝa�������蔻��֐�
bool CPlayer::HitCheckEnemy_And_Slash(Math::Vector2 enePos, bool bSlashHit, float size)
{
	if (!bSlashHit)	// ���i�q�b�g�h�~�t���O
	{
		// �G�Ǝa���̋���
		const float checkDist = Utility::GetDistance(enePos, m_swordList.GetPos());
		// �q�b�g����̋���
		const float hitDist = SLASH_SIZE::LEFT + size;
		// �q�b�g��������������߂��Ƃ�
		if (checkDist <= hitDist) return true;
	}
	return false;
}
// �G�Ɣ��������蔻��֐�
bool CPlayer::HitCheckEnemy_And_Blast(Math::Vector2 enePos, bool bBlastHit, float left, float right, float top, float down)
{
	if (!bBlastHit)
	{
		if (!Utility::bHitCheck(m_bombList.GetBlastPos(), { 0,0 }, enePos,
			BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN,
			left,right,top,down)) return true;
	}
	return false;
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
		//�q�b�g��
		if (!Utility::bHitCheck(m_pos, m_moveVal, m_bombList.GetBlastPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			BLAST_SIZE::LEFT, BLAST_SIZE::RIGHT, BLAST_SIZE::TOP, BLAST_SIZE::DOWN))
		{
			SetDamage(POWER::PLAYER_BLAST);
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
			ITEM_BOMB_SIZE::LEFT,ITEM_BOMB_SIZE::RIGHT,ITEM_BOMB_SIZE::TOP,ITEM_BOMB_SIZE::DOWN))
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
			ITEM_KEY_SIZE::LEFT,ITEM_KEY_SIZE::RIGHT,ITEM_KEY_SIZE::TOP,ITEM_KEY_SIZE::DOWN))
		{
			ItemKey[i].SetAlive();		//���̃t���O����
			m_KeyPossession++;		//������
		}
	}
	////////////////////////////////////////////////////////////////
	//		�A�C�e���F��								
	////////////////////////////////////////////////////////////////
	//�񕜃��X�g�擾
	CItem_Health* ItemHealth = item->GetHealthItem();
	for (int i = 0; i < HEALTH_SETMAX; i++)
	{
		if (!ItemHealth[i].GetAlive())continue;
		
		//�q�b�g��
		if (!Utility::bHitCheck(m_pos, m_moveVal, ItemHealth[i].GetPos(),
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			ITEM_HELSE_SIZE::LEFT,ITEM_HELSE_SIZE::RIGHT,ITEM_HELSE_SIZE::TOP,ITEM_HELSE_SIZE::DOWN))
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
		ITEM_HIDE_SIZE::LEFT,ITEM_HIDE_SIZE::RIGHT,ITEM_HIDE_SIZE::TOP,ITEM_HIDE_SIZE::DOWN))
	{
		ItemMino->SetAlive();			// �t���O����
		m_bMinoPossession = true;		// �B�ꖪ����
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
		if (m_BombPossession > 0)return eBomb;
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
	
	m_hiddenList.bSetHidden();	// �U�����B��g����

	// �e����
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!m_bulletList[i].IsAlive())
		{
			Inversion();	// �v���C���[���E���]�֐�
			// ���ˊp�x�����߂�
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
	
	m_status = eAttack; //�v���C���[�̏�Ԃ�"�U��"�ɂ���
	m_hiddenList.bSetHidden();	// �U�����B��g����

	// �a������
	if (!m_swordList.bGetSlash())
	{
		Inversion();	// �v���C���[���E���]�֐�
		// ���ˊp�x�����߂�
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

	m_hiddenList.bSetHidden();	// �U�����B��g����

	// ���e����
	if (!m_bombList.IsAlive())
	{
		m_bombList.InstBomb(m_pos);
		m_BombPossession--;		// ������
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

//���G����
void CPlayer::invincibleTime()
{
	if (m_HitFlg)	//�v���C���[������������
	{
		m_hiddenList.bSetHidden();		// �B��g����

		const int CNT_MAX = 120;	//���G����
		if (m_invincibleCnt >= CNT_MAX)
		{
			m_alpha = 1.0f;
			m_invincibleCnt = 0;
			m_HitFlg = false;
			return;
		}
		m_invincibleCnt++;

		//�_��
		if (m_invincibleCnt % 10 == 0)
		{
			if (m_alpha < 1)m_alpha = 1;
			else m_alpha = 0.5;
		}
	}
	else
	{
		m_invincibleCnt = 0;
		if (!m_hiddenList.bGetHidden()) m_alpha = 1.0f;
	}
}

// �������]�֐�
void CPlayer::Inversion()
{
	// �v���C���[�̕����Ƌt�����ɃJ�[�\��������ꍇ���E���]
	if (m_pos.x < (float)m_ClickPoint.x && m_direction != Right) m_direction = Right;
	else if (m_pos.x > (float)m_ClickPoint.x && m_direction != Left) m_direction = Left;
}

void CPlayer::Animation()
{
	switch (m_status)
	{
	case eIdle:
		m_aTimer = 15;
		m_aflame = 6;
		break;
	case eWalking:
		m_aTimer = 10;
		m_aflame = 6;
		break;
	case eAttack:
		m_aTimer = 5;
		m_aflame = 3;
		break;
	default:
		break;
	}

	const int CNT_MAX = m_aTimer * m_aflame;
	if (m_aCnt >= CNT_MAX - 1)
	{
		m_aCnt = 0;
	}
	m_aCnt++;

	//�U���A�j���[�V�����̌v�Z
	if (m_status == eAttack)
	{
		const int CNT_MAX = m_aTimer * m_aflame;
		if (m_aCnt >= CNT_MAX - 1)
		{
			m_aAttackCnt = 0;
			m_status = eIdle;
		}
		m_aAttackCnt++;
	}

}

// �A�j���[�V����
int CPlayer::AnimationCalc(int cnt, const int xtex)
{
	return cnt / m_aTimer * 116 + 38 + xtex;
}
