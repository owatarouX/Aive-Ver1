#include"CEnemy.h"
#include "Scene.h"
#include"Utility.h"

// �R���X�g���N�^
CEnemy::CEnemy()
	:gimmickcount(0)
	, m_bEvent(false)
	,m_pOwner(nullptr)
{
}

// �f�X�g���N�^
CEnemy::~CEnemy()
{
}

// ������
void CEnemy::Init()
{
	CMap* pMap = m_pOwner->GetMap();
	int mapData = pMap->GetMapData();	//�}�b�v�f�[�^�擾
	// �������F��
	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].Init();
	}
	SetSamurai(mapData);	// ���̔z�u

	// �������F�|��
	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].Init();
	}
	SetArcher(mapData);	// �|���̔z�u

	// �������F��j
	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].Init();
	}
	SetGiant(mapData);		// ��j�̔z�u

	// �������F�{�X
	m_bossList.Init();
	SetBoss(mapData);		// �{�X�̔z�u

	gimmickcount = 0;
	m_bEvent = false;
}

// �X�V
void CEnemy::Update()
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// �v���C���[�N���X�̎擾
	Math::Vector2 playerPos = pPlayer->GetPos();	// �v���C���[���W�擾
	bool bHidden = pPlayer->bGetHidden();			// �B��g��Ԏ擾

	CMap* pMap = m_pOwner->GetMap();
	Math::Vector2 scrPos = pMap->GetscrollPos();	//�X�N���[���ʎ擾

	// �X�V�F��
	Update_Samurai(playerPos,scrPos, bHidden);
	
	// �X�V�F�|��
	Update_Archer(playerPos, scrPos, bHidden);

	// �X�V�F��j
	Update_Giant(playerPos, scrPos, bHidden);

	// �X�V�F�{�X
	Update_Boss(playerPos, scrPos, bHidden);

	// �X�V�F��
	Update_Arrow(scrPos);

	// �G�̎a������
	Update_Sword(scrPos);

	// �}�b�v�Ƃ̓����蔻��
	HitCheckMap();
	// �v���C���[�Ƃ̓����蔻��
	HitCheckPlayer();

	//�M�~�b�N
	const int GMAX = 100;
	gimmickcount++;
	if (gimmickcount > GMAX)
	{
		gimmickcount = GMAX;
	}

	//�C�x���g����
	if(pMap->GetMapData()==OneFloor) Event();
}

// �X�V�F��
void CEnemy::Update_Samurai(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// �v���C���[�N���X�̎擾

	CItem* item = m_pOwner->GetItem();

	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].SetPlayerPos(playerPos);
		m_samuraiList[i].SetScrollPos(scrPos);
		m_samuraiList[i].bSetHidden(hide);
		m_samuraiList[i].Update();
		
		// �񕜃A�C�e���h���b�v����
		if (item->DropHealth(m_samuraiList[i].bGetDrop(), m_samuraiList[i].GetPos())) m_samuraiList[i].bSetDrop();
		
		// �a���U������
		if (m_samuraiList[i].bGetSlash())
		{
			// �G�a���N���X�������V�K
			CEnemySword* sword = new CEnemySword;

			sword->Init();	// ������
			sword->SetTexture(m_pSlashTex);	// �e�N�X�`���ݒ�

			// �a������
			sword->Slash(m_samuraiList[i].GetPos(), m_samuraiList[i].GetDeg(), SAMURAI_SLASH_SIZE, 50);// �G�̍��W�A�p�x�A�T�C�Y�̐ݒ�A����
			m_enemySwordList.push_back(sword);

			m_samuraiList[i].bSetSlash(false);		// �a���t���O������Ĉ�x�������s����悤�� 
		}
	}
}

// �X�V�F�|��
void CEnemy::Update_Archer(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// �v���C���[�N���X�̎擾

	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].SetPlayerPos(playerPos);
		m_archerList[i].SetScrollPos(scrPos);
		m_archerList[i].bSetHidden(hide);
		m_archerList[i].Update();

		// ����t���Otrue�������˃J�E���g0�ȉ��̎�
		if ((m_archerList[i].GetbVisibility()) && (m_archerList[i].GetShotCnt() >= COOL_TIME::ARCHER_ARROW))
		{
			// ��N���X�������V�K�쐬
			CArrow* arrow = new CArrow;

			arrow->Init();		// ������
			arrow->SetTexture(m_pArrawTex);	// �e�N�X�`���ݒ�

			// ���ˏ���
			arrow->Shot(m_archerList[i].GetPos(), playerPos);
			m_arrowList.push_back(arrow);

			// ���˃t���Otrue
			m_archerList[i].SetShotFlg(true);
		}
	}
}

// �X�V�F��j
void CEnemy::Update_Giant(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// �v���C���[�N���X�̎擾

	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();
	CItem* item = m_pOwner->GetItem();

	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].SetScrollPos(scrPos);
		m_giantList[i].SetPlayerPos(playerPos);
		m_giantList[i].bSetHidden(hide);
		m_giantList[i].Update(mapData);

		// ���h���b�v����
		if (item->DropKey(m_giantList[i].bGetDrop(), m_giantList[i].GetPos())) m_giantList[i].bSetDrop();
	}
}

// �X�V�F�{�X
void CEnemy::Update_Boss(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	m_bossList.SetScrollPos(scrPos);
	m_bossList.SetPlayerPos(playerPos);
	m_bossList.Update();

	if (m_bossList.GetSlash())	// �a���t���O��true�ɂȂ����Ƃ�
	{
		// �G�a���N���X�������V�K
		CEnemySword* sword = new CEnemySword;

		sword->Init();	// ������
		sword->SetTexture(m_pSlashTex);	// �e�N�X�`���ݒ�

		// �a������
		sword->Slash(m_bossList.GetPos(), m_bossList.GetDeg(), BOSS_SLASH_SIZE, 120);// �G�̍��W�A�p�x�A�T�C�Y�̐ݒ�A����
		m_enemySwordList.push_back(sword);

		m_bossList.SetSlash(false);		// �a���t���O������Ĉ�x�������s����悤�� 
	}

	// ����t���Otrue�������˃J�E���g0�ȉ��̎�
	if ((m_bossList.iGetAttakeType() == Shot) && (m_bossList.GetShotCnt() >= COOL_TIME::BOSS_ARROW))
	{
		// ��N���X�������V�K�쐬
		CArrow* arrow = new CArrow;

		arrow->Init();		// ������
		arrow->SetTexture(m_pArrawTex);	// �e�N�X�`���ݒ�

		// ���ˏ���
		arrow->Shot(m_bossList.GetPos(), playerPos);
		m_arrowList.push_back(arrow);

		// ���˃t���Otrue
		m_bossList.SetShotFlg(true);
	}
}

// �X�V�F��
void CEnemy::Update_Arrow(Math::Vector2 scrPos)
{
	for (int i = 0; i < m_arrowList.size(); i++)
	{
		m_arrowList[i]->SetScrollPos(scrPos);
		m_arrowList[i]->Update();
	}

	std::vector<CArrow*>::iterator it;
	it = m_arrowList.begin();

	// �s�v�Ȗ�̗v�f���폜
	while (it != m_arrowList.end())
	{
		// �t���Oture�Ȃ�X���[
		if (!(*it)->IsAlive())
		{
			delete(*it);
			it = m_arrowList.erase(it);
		}
		else
			it++;
	}
}

// �X�V�F�a��
void CEnemy::Update_Sword(Math::Vector2 scrPos)
{
	for (int i = 0; i < m_enemySwordList.size(); i++)
	{
		m_enemySwordList[i]->SetScrollPos(scrPos);
		m_enemySwordList[i]->Updata();
	}

	std::vector<CEnemySword*>::iterator it;
	it = m_enemySwordList.begin();

	// �s�v�Ȗ�̗v�f���폜
	while (it != m_enemySwordList.end())
	{
		// �t���Oture�Ȃ�X���[
		if (!(*it)->bGetSlash())
		{
			delete(*it);
			it = m_enemySwordList.erase(it);
		}
		else
			it++;
	}
}

// �`��
void CEnemy::Draw()
{
	// �`��F��
	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].Draw();
	}

	// �`��F�|��
	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].Draw();
	}

	// �`��F��j
	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].Draw();
	}

	// �`��F�{�X
	m_bossList.Draw();
	
	// �`��F��
	for (int i = 0; i < m_arrowList.size(); i++)
	{
		m_arrowList[i]->Draw();
	}

	// �`��F�G�a��
	for (int i = 0; i < m_enemySwordList.size(); i++)
	{
		m_enemySwordList[i]->Draw();
	}
}

// �e�N�X�`���ݒ�F��
void CEnemy::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���ݒ�F�|��
void CEnemy::SetArcherTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���ݒ�F��
void CEnemy::SetArrowTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pArrawTex = apTexture;
}

// �e�N�X�`���ݒ�F�a��
void CEnemy::SetSwordTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pSlashTex = apTexture;
}

// �e�N�X�`���ݒ�F��j
void CEnemy::SetGiantTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].SetTexture(apTexture);
	}
}

// �e�N�X�`���ݒ�F�{�X
void CEnemy::SetBossTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_bossList.SetTexture(apTexture);
}

// ���̐ݒu�֐�
void CEnemy::SetSamurai(int data)
{
	//�f�[�^���Ƃ̔z�u�ݒ�
	switch (data)
	{
	//��O
	case OutSide:
		m_samuraiList[1].SetSamurai({ 300.0f, -1080.0f });
		m_samuraiList[2].SetSamurai({ 640.0f,230.0f });
		m_samuraiList[3].SetSamurai({ 640.0f,110.0f });
		break;
	//��K�w
	case OneFloor:
		m_samuraiList[1].SetSamurai({ 731,-1531 });

		m_samuraiList[2].SetSamurai({ 1250,-900 });
		m_samuraiList[3].SetSamurai({ 1600,-1250 });
		m_samuraiList[4].SetSamurai({ 1500,-1000 });

		m_samuraiList[5].SetSamurai({ 1350, 100 });
		m_samuraiList[6].SetSamurai({ 1550, 100 });
		m_samuraiList[7].SetSamurai({ -400, -1950 });
		m_samuraiList[8].SetSamurai({ -500, -1850 });

		m_samuraiList[9].SetSamurai({ -84,-1250 });
		m_samuraiList[10].SetSamurai({ -324,-1486 });
		m_samuraiList[11].SetSamurai({ 221,-1486 });
		
		m_samuraiList[12].SetSamurai({ 610,0 });
		m_samuraiList[13].SetSamurai({ -400,-550 });
		break;
	//��K�w
	case TwoFloor:
		m_samuraiList[1].SetSamurai({ 165,-875 });
		m_samuraiList[2].SetSamurai({ 600,-875 });
		m_samuraiList[3].SetSamurai({ 1000,-875 });
		m_samuraiList[4].SetSamurai({ 1635,-884 });
		break;
	//�O�K�w
	case ThreeFloor:
		break;
	//�l�K�w
	case FourFloor:
		break;
	}

}

// �|���z�u
void CEnemy::SetArcher(int data)
{
	//�f�[�^���Ƃ̔z�u�ݒ�
	switch (data)
	{
	//��O
	case OutSide:
		m_archerList[1].SetArchaer({ 925.0f, -250.0f });
		break;
	//��K�w
	case OneFloor:
		m_archerList[1].SetArchaer({ 720.0f, -1250.0f });
		m_archerList[2].SetArchaer({ 1600.0f, -650.0f });

		m_archerList[3].SetArchaer({ -384,-1246 });
		m_archerList[4].SetArchaer({ 136,-1751 });
		
		m_archerList[5].SetArchaer({ 1186,-190 });
		m_archerList[6].SetArchaer({ 1700,-190 });
		
		m_archerList[7].SetArchaer({ 160,-22 });
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

// ��j�z�u
void CEnemy::SetGiant(int data)
{
	//�f�[�^���Ƃ̔z�u�ݒ�
	switch (data)
	{
	//��K�w
	case TwoFloor:
		m_giantList[1].SetGiant({ 1675,210 });
		m_giantList[2].SetGiant({ 1675,-1600 });
		break;
	//�O�K�w
	case ThreeFloor:
		break;
	//�l�K�w
	case FourFloor:
		break;
	}
}

// �{�X�z�u
void CEnemy::SetBoss(int data)
{
	//�f�[�^���Ƃ̔z�u�ݒ�
	if (data == BossFloor)m_bossList.SetBoss({ 609.0f,0.0f });
}

// �M�~�b�N����
void CEnemy::shot(Math::Vector2 apos, Math::Vector2 bpos)
{
	const int GMAX = 100;
	if (gimmickcount >= GMAX)
	{

		CArrow* arrow = new CArrow;

		arrow->Init();		// ������
		arrow->SetTexture(m_pArrawTex);	// �e�N�X�`���ݒ�

		// ���ˏ���
		arrow->Shot(apos, bpos);
		m_arrowList.push_back(arrow);

		gimmickcount = 0;

	}
}

// �C�x���g����
void CEnemy::Event()
{
	CMap* map = m_pOwner->GetMap();
	// �C�x���g������e
	if (!m_bEvent)
	{
		m_giantList[1].SetGiant({ 409, -250 });
		m_giantList[2].SetGiant({ -90, -250 });
		m_bEvent = true;
		return;
	}
	// �C�x���g�I������
	if (!m_giantList[1].IsAlive() && !m_giantList[2].IsAlive())
	{
		map->SetUnlock();
	}
}

//�I�[�i�[�ݒ�擾
void CEnemy::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

// �v���C���[�Ƃ̓����蔻��
void CEnemy::HitCheckPlayer()
{
	CPlayer* player = m_pOwner->GetPlayer();

	// �v���C���[�������Ă��邩�A���G��ԂłȂ����ɏ���
	if (!player->IsAlive() || player->bGetHit()) return;

	Math::Vector2 playerPos = player->GetPos();		// �v���C���[�̍��W�擾
	Math::Vector2 playerMove = player->GetMove();	// �v���C���[�̈ړ��ʎ擾
	CEffect* effect = m_pOwner->GetEffect();		// �G�t�F�N�g�N���X
	CDamage* dmgList = effect->GetDmgList();		// �_���[�W���X�g

	////////////////////////////////////////////////////////////////
	//					��Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_arrowList.size(); i++)
	{
		if (!m_arrowList[i]->IsAlive()) continue;

		// �v���C���[�Ɩ�̋���
		const float checkDist = Utility::GetDistance(playerPos, m_arrowList[i]->GetPos());
		// �q�b�g����̋���
		const float hitDist = 16;

		// �q�b�g�������������߂��Ƃ�
		if (checkDist <= hitDist)
		{
			player->SetDamage(POWER::ARCHER_ARROW);	// �v���C���[�^�_���[�W
			player->SetHitFlg();			// �q�b�g�t���O�Z�b�g
			m_arrowList[i]->SetAlive();		// ��̃t���O����
		}
	}
	////////////////////////////////////////////////////////////////
	//					�a���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_enemySwordList.size(); i++)
	{
		if (!m_enemySwordList[i]->bGetSlash()) continue;

		// �v���C���[�Ǝa���̋���
		const float checkDist = Utility::GetDistance(playerPos, m_enemySwordList[i]->GetPos());
		
		// ���̎a���p����
		if (m_enemySwordList[i]->GetSize() == SAMURAI_SLASH_SIZE)
		{
			// �q�b�g����̋���
			const float hitDist = PLAYER_SIZE::LEFT+SLASH_SIZE::LEFT;

			// �q�b�g�������������߂��Ƃ�
			if (checkDist <= hitDist)
			{
				player->SetDamage(POWER::SAMURAI_SLASH);	// �v���C���[�^�_���[�W
				player->SetHitFlg();		// �q�b�g�t���O�Z�b�g
			}
		}
		// �{�X�̎a���p����
		else if (m_enemySwordList[i]->GetSize() == BOSS_SLASH_SIZE)
		{
			// �q�b�g����̋���
			const float hitDist = PLAYER_SIZE::LEFT+BOSS_SIZE::LEFT;

			// �q�b�g�������������߂��Ƃ�
			if (checkDist <= hitDist)
			{
				player->SetDamage(POWER::BOSS_SLASH);		// �v���C���[�^�_���[�W
				player->SetHitFlg();	// �q�b�g�t���O�Z�b�g
			}
		}
	}

	int knockBack = 20;
	////////////////////////////////////////////////////////////////
	//					���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		if (!m_samuraiList[i].IsAlive()) continue;
		// �v���C���[�Ƃ̓����蔻��֐�
		HitCheckEnemy_And_Player(m_samuraiList[i].GetPos(),POWER::ENEMY_PHYSICAL, knockBack, SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN);
	}
	////////////////////////////////////////////////////////////////
	//					�|���Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < ARCHER_MAX; i++)
	{
		if (!m_archerList[i].IsAlive())continue;
		// �v���C���[�Ƃ̓����蔻��֐�
		HitCheckEnemy_And_Player(m_archerList[i].GetPos(), POWER::ENEMY_PHYSICAL, knockBack, ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN);
	}
	////////////////////////////////////////////////////////////////
	//					��j�Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < GIANT_MAX; i++)
	{
		if (!m_giantList[i].IsAlive())continue;
		// �ːi��������Ƒ�_���[�W
		int dmg = 0;
		if (m_giantList[i].bGetRush())
		{
			dmg = 10;
			knockBack = 80;
		}
		else dmg = POWER::ENEMY_PHYSICAL;
		
		// �v���C���[�Ƃ̓����蔻��֐�
		HitCheckEnemy_And_Player(m_giantList[i].GetPos(), dmg, knockBack, GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN);
	}
	////////////////////////////////////////////////////////////////
	//					�{�X�Ƃ̓����蔻��								
	////////////////////////////////////////////////////////////////
	int bossknockback = 80;	//ノックバックの値

	if (m_bossList.IsAlive())
	{
		if (m_bossList.GetPlayerHit())
		{
			switch (m_bossList.GetDirection())
			{
			case 0:	// ボスが上向き
				player->SetPosY(m_bossList.GetPosY() + BOSS_SIZE::TOP + bossknockback);	// ボスの上部に出現
				player->SetMovevalY(0);					// 移動量を0に
				player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
				player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
				break;
			case 1: // ボスが下向き
				player->SetPosY(m_bossList.GetPosY() - BOSS_SIZE::DOWN - bossknockback);	// ボスの上部に出現
				player->SetMovevalY(0);						// 移動量を0に
				player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
				player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
				break;
			case 2:	// ボスが左向き
				player->SetPosX(m_bossList.GetPosX() - BOSS_SIZE::LEFT - bossknockback);	// ボスの上部に出現
				player->SetMovevalX(0);					// 移動量を0に
				player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
				player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
				break;
			case 3:	// ボスが右向き
				player->SetPosX(m_bossList.GetPosX() + BOSS_SIZE::RIGHT + bossknockback);	// ボスの上部に出現
				player->SetMovevalX(0);					// 移動量を0に
				player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
				player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
				break;
			default:
				break;
			}
		}
	}
}

// �v���C���[�ƓG�̓����蔻��֐�
void CEnemy::HitCheckEnemy_And_Player(Math::Vector2 enePos, int dmg, float knockBack, float Left, float Right, float Top, float Down)
{
	CPlayer* player = m_pOwner->GetPlayer();
	for (int e = 0; e < SAMURAI_MAX; e++)
	{
		//�����Ă�G�̂�
		if (!m_samuraiList[e].IsAlive()) continue;
		int player_hit = Utility::iHitCheck(player->GetPos(), player->GetMove(), enePos.x, enePos.y,
			PLAYER_SIZE::LEFT, PLAYER_SIZE::RIGHT, PLAYER_SIZE::TOP, PLAYER_SIZE::DOWN,
			Left,Right,Top,Down);

		//�G�̌��ݍ��W�̎l��
		const float ENEMY_LEFT = enePos.x - Left;	//����
		const float ENEMY_RIGHT = enePos.x + Right;	//�E��
		const float ENEMY_TOP = enePos.y + Top;		//���
		const float ENEMY_BOTTOM = enePos.y - Down;	//����

		//�����蔻�蕪�򏈗�
		//1:��	2:�� 3:�� 4:�E
		switch (player_hit)
		{
		case 1:
			player->SetPosY(ENEMY_TOP + PLAYER_SIZE::TOP);
			player->SetMovevalY(knockBack);
			player->SetDamage(dmg);			//�̗͌���
			player->SetHitFlg();
			break;
		case 2:
			player->SetPosY(ENEMY_BOTTOM - PLAYER_SIZE::DOWN);
			player->SetMovevalY(-knockBack);
			player->SetDamage(dmg);			//�̗͌���
			player->SetHitFlg();
			break;
		case 3:
			player->SetPosX(ENEMY_LEFT - PLAYER_SIZE::LEFT);
			player->SetMovevalX(-knockBack);
			player->SetDamage(dmg);			//�̗͌���
			player->SetHitFlg();
			break;
		case 4:
			player->SetPosX(ENEMY_RIGHT + PLAYER_SIZE::RIGHT);
			player->SetMovevalX(knockBack);
			player->SetDamage(dmg);			//�̗͌���
			player->SetHitFlg();
			break;
		}
	}
}

//�}�b�v�Ƃ̓����蔻��
void CEnemy::HitCheckMap()
{
	CMap* map = m_pOwner->GetMap();

	float(*chipX)[MAP_CHIP_W] = map->GetPosX();
	float(*chipY)[MAP_CHIP_W] = map->GetPosY();
	int(*chipData)[MAP_CHIP_W] = map->GetChipData();

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

			if (chipData[h][w] >= 10 && chipData[h][w] < 49 || chipData[h][w]>=78)
			{
				continue;
			}
			else
			{
				////////////////////////////////////////////////////////////////
				//		���Ƃ̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				for (int i = 0; i < SAMURAI_MAX; i++)
				{
					if (!m_samuraiList[i].IsAlive()) continue;

					hit = Utility::iHitCheck(m_samuraiList[i].GetPos(), m_samuraiList[i].GetMove(), chipX[h][w], chipY[h][w],
						SAMURAI_SIZE::LEFT, SAMURAI_SIZE::RIGHT, SAMURAI_SIZE::TOP, SAMURAI_SIZE::DOWN,
						Infor::RADIUS_32,Infor::RADIUS_32,Infor::RADIUS_32,Infor::RADIUS_32);

					switch (hit)
					{
					case 1: m_samuraiList[i].SetPosY(MAP_TOP + Infor::RADIUS_32);
						m_samuraiList[i].SetMoveY(0);
						break;
					case 2:m_samuraiList[i].SetPosY(MAP_BOTTOM - Infor::RADIUS_32);
						m_samuraiList[i].SetMoveY(0);
						break;
					case 3:m_samuraiList[i].SetPosX(MAP_LEFT - Infor::RADIUS_32);
						m_samuraiList[i].SetMoveX(0);
						break;
					case 4:m_samuraiList[i].SetPosX(MAP_RIGHT + Infor::RADIUS_32);
						m_samuraiList[i].SetMoveX(0);
					break; default:
						break;
					}
				}

				////////////////////////////////////////////////////////////////
				//		�|���Ƃ̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				for (int i = 0; i < ARCHER_MAX; i++)
				{
					if (!m_archerList[i].IsAlive()) continue;

					hit = Utility::iHitCheck(m_archerList[i].GetPos(), m_archerList[i].GetMove(), chipX[h][w], chipY[h][w],
						ARCHER_SIZE::LEFT, ARCHER_SIZE::RIGHT, ARCHER_SIZE::TOP, ARCHER_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);

					switch (hit)
					{
					case 1: m_archerList[i].SetPosY(MAP_TOP + Infor::RADIUS_32);
						m_archerList[i].SetMoveY(0);
						break;
					case 2:m_archerList[i].SetPosY(MAP_BOTTOM - Infor::RADIUS_32);
						m_archerList[i].SetMoveY(0);
						break;
					case 3:m_archerList[i].SetPosX(MAP_LEFT - Infor::RADIUS_32);
						m_archerList[i].SetMoveX(0);
						break;
					case 4:m_archerList[i].SetPosX(MAP_RIGHT + Infor::RADIUS_32);
						m_archerList[i].SetMoveX(0);
					break; default:
						break;
					}
				}
				////////////////////////////////////////////////////////////////
				//		��j�Ƃ̃q�b�g�`�F�b�N								
				////////////////////////////////////////////////////////////////
				for (int i = 0; i < GIANT_MAX; i++)
				{
					if (!m_giantList[i].IsAlive()) continue;

					hit = Utility::iHitCheck(m_giantList[i].GetPos(), m_giantList[i].GetMove(), chipX[h][w], chipY[h][w],
						GIANT_SIZE::LEFT, GIANT_SIZE::RIGHT, GIANT_SIZE::TOP, GIANT_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32);

					switch (hit)
					{
					case 1: m_giantList[i].SetPosY(MAP_TOP + Infor::RADIUS_32);
						m_giantList[i].SetMoveY(0);
						break;
					case 2:m_giantList[i].SetPosY(MAP_BOTTOM - Infor::RADIUS_32);
						m_giantList[i].SetMoveY(0);
						break;
					case 3:m_giantList[i].SetPosX(MAP_LEFT - Infor::RADIUS_32);
						m_giantList[i].SetMoveX(0);
						break;
					case 4:m_giantList[i].SetPosX(MAP_RIGHT + Infor::RADIUS_32);
						m_giantList[i].SetMoveX(0);
						break;
					default:
						break;
					}
				}
				for (int i = 0; i < m_arrowList.size(); i++)
				{
					if (!m_arrowList[i]->IsAlive()) continue;
					if (!Utility::bHitCheck(m_arrowList[i]->GetPos(), m_arrowList[i]->GetMove(), { chipX[h][w], chipY[h][w] },
						ARROW_SIZE::LEFT, ARROW_SIZE::RIGHT, ARROW_SIZE::TOP, ARROW_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
					{
						m_arrowList[i]->SetAlive();		// ��̃t���O����
					}
				}
			}
			////////////////////////////////////////////////////////////////
			//		��Ƃ̃q�b�g�`�F�b�N								
			////////////////////////////////////////////////////////////////
			if (chipData[h][w] >= 10 && chipData[h][w] < 49 || chipData[h][w]>80)
			{
				for (int i = 0; i < m_arrowList.size(); i++)
				{
					if (!m_arrowList[i]->IsAlive()) continue;
					if (!Utility::bHitCheck(m_arrowList[i]->GetPos(), m_arrowList[i]->GetMove(), { chipX[h][w], chipY[h][w] },
						ARROW_SIZE::LEFT, ARROW_SIZE::RIGHT, ARROW_SIZE::TOP, ARROW_SIZE::DOWN,
						Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32, Infor::RADIUS_32))
					{
						m_arrowList[i]->SetAlive();		// ��̃t���O����
					}
					//// �}�b�v�Ɩ�̋���
					//const float checkDist = Utility::GetDistance(
					//	m_arrowList[i]->GetPos(), { chipX[h][w],chipY[h][w] });
					//// �q�b�g����̋���
					//const float hitDist = 32 + 16;

					//// �q�b�g�������������߂��Ƃ�
					//if (checkDist <= hitDist)
					//{
					//	m_arrowList[i]->SetAlive();		// ��̃t���O����
					//}
				}
			}
		}
	}
}
