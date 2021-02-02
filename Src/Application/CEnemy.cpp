#include"CEnemy.h"
#include "Scene.h"
#include"Utility.h"

// コンストラクタ
CEnemy::CEnemy()
	:gimmickcount(0)
	, m_bEvent(false)
{
}

// デストラクタ
CEnemy::~CEnemy()
{
}

// 初期化
void CEnemy::Init()
{
	CMap* pMap = m_pOwner->GetMap();
	int mapData = pMap->GetMapData();	//マップデータ取得
	// 初期化：侍
	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].Init();
	}
	SetSamurai(mapData);	// 侍の配置

	// 初期化：弓兵
	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].Init();
	}
	SetArcher(mapData);	// 弓兵の配置

	// 初期化：大男
	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].Init();
	}
	SetGiant(mapData);		// 大男の配置

	// 初期化：ボス
	m_bossList.Init();
	SetBoss(mapData);		// ボスの配置

	gimmickcount = 0;
	m_bEvent = false;
}

// 更新
void CEnemy::Update()
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// プレイヤークラスの取得
	Math::Vector2 playerPos = pPlayer->GetPos();	// プレイヤー座標取得
	bool bHidden = pPlayer->bGetHidden();			// 隠れ身状態取得

	CMap* pMap = m_pOwner->GetMap();
	Math::Vector2 scrPos = pMap->GetscrollPos();	//スクロール量取得

	// 更新：侍
	Update_Samurai(playerPos,scrPos, bHidden);
	
	// 更新：弓兵
	Update_Archer(playerPos, scrPos, bHidden);

	// 更新：大男
	Update_Giant(playerPos, scrPos, bHidden);

	// 更新：ボス
	Update_Boss(playerPos, scrPos, bHidden);

	// 更新：矢
	Update_Arrow(scrPos);

	// 敵の斬撃処理
	Update_Sword(scrPos);

	// マップとの当たり判定
	HitCheckMap();
	// プレイヤーとの当たり判定
	HitCheckPlayer();

	//ギミック
	const int GMAX = 100;
	gimmickcount++;
	if (gimmickcount > GMAX)
	{
		gimmickcount = GMAX;
	}

	//イベント処理
	if(pMap->GetMapData()==OneFloor) Event();
}

// 更新：侍
void CEnemy::Update_Samurai(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// プレイヤークラスの取得

	CItem* item = m_pOwner->GetItem();

	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].SetPlayerPos(playerPos);
		m_samuraiList[i].SetScrollPos(scrPos);
		m_samuraiList[i].bSetHidden(hide);
		m_samuraiList[i].Update();
		
		// 回復アイテムドロップ処理
		if (item->DropHealth(m_samuraiList[i].bGetDrop(), m_samuraiList[i].GetPos())) m_samuraiList[i].bSetDrop();
		
		// 斬撃攻撃処理
		if (m_samuraiList[i].bGetSlash())
		{
			// 敵斬撃クラスメモリ新規
			CEnemySword* sword = new CEnemySword;

			sword->Init();	// 初期化
			sword->SetTexture(m_pSlashTex);	// テクスチャ設定

			// 斬撃発生
			sword->Slash(m_samuraiList[i].GetPos(), m_samuraiList[i].GetDeg(), SAMURAI_SLASH_SIZE, 50);// 敵の座標、角度、サイズの設定、距離
			m_enemySwordList.push_back(sword);

			m_samuraiList[i].bSetSlash(false);		// 斬撃フラグを下げて一度だけ実行するように 
		}
	}
}

// 更新：弓兵
void CEnemy::Update_Archer(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// プレイヤークラスの取得

	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].SetPlayerPos(playerPos);
		m_archerList[i].SetScrollPos(scrPos);
		m_archerList[i].bSetHidden(hide);
		m_archerList[i].Update();

		// 視野フラグtrue時＆発射カウント0以下の時
		if ((m_archerList[i].GetbVisibility()) && (m_archerList[i].GetShotCnt() >= COOL_TIME::ARCHER_ARROW))
		{
			// 矢クラスメモリ新規作成
			CArrow* arrow = new CArrow;

			arrow->Init();		// 初期化
			arrow->SetTexture(m_pArrawTex);	// テクスチャ設定

			// 発射処理
			arrow->Shot(m_archerList[i].GetPos(), playerPos);
			m_arrowList.push_back(arrow);

			// 発射フラグtrue
			m_archerList[i].SetShotFlg(true);
		}
	}
}

// 更新：大男
void CEnemy::Update_Giant(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	CPlayer* pPlayer = m_pOwner->GetPlayer();		// プレイヤークラスの取得

	CMap* map = m_pOwner->GetMap();
	int mapData = map->GetMapData();
	CItem* item = m_pOwner->GetItem();

	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].SetScrollPos(scrPos);
		m_giantList[i].SetPlayerPos(playerPos);
		m_giantList[i].bSetHidden(hide);
		m_giantList[i].Update(mapData);

		// 鍵ドロップ処理
		if (item->DropKey(m_giantList[i].bGetDrop(), m_giantList[i].GetPos())) m_giantList[i].bSetDrop();
	}
}

// 更新：ボス
void CEnemy::Update_Boss(Math::Vector2 playerPos, Math::Vector2 scrPos, bool hide)
{
	m_bossList.SetScrollPos(scrPos);
	m_bossList.SetPlayerPos(playerPos);
	m_bossList.Update();

	if (m_bossList.GetSlash())	// 斬撃フラグがtrueになったとき
	{
		// 敵斬撃クラスメモリ新規
		CEnemySword* sword = new CEnemySword;

		sword->Init();	// 初期化
		sword->SetTexture(m_pSlashTex);	// テクスチャ設定

		// 斬撃発生
		sword->Slash(m_bossList.GetPos(), m_bossList.GetDeg(), BOSS_SLASH_SIZE, 120);// 敵の座標、角度、サイズの設定、距離
		m_enemySwordList.push_back(sword);

		m_bossList.SetSlash(false);		// 斬撃フラグを下げて一度だけ実行するように 
	}

	// 視野フラグtrue時＆発射カウント0以下の時
	if ((m_bossList.iGetAttakeType() == Shot) && (m_bossList.GetShotCnt() >= COOL_TIME::BOSS_ARROW))
	{
		// 矢クラスメモリ新規作成
		CArrow* arrow = new CArrow;

		arrow->Init();		// 初期化
		arrow->SetTexture(m_pArrawTex);	// テクスチャ設定

		// 発射処理
		arrow->Shot(m_bossList.GetPos(), playerPos);
		m_arrowList.push_back(arrow);

		// 発射フラグtrue
		m_bossList.SetShotFlg(true);
	}
}

// 更新：矢
void CEnemy::Update_Arrow(Math::Vector2 scrPos)
{
	for (int i = 0; i < m_arrowList.size(); i++)
	{
		m_arrowList[i]->SetScrollPos(scrPos);
		m_arrowList[i]->Update();
	}

	std::vector<CArrow*>::iterator it;
	it = m_arrowList.begin();

	// 不要な矢の要素数削除
	while (it != m_arrowList.end())
	{
		// フラグtureならスルー
		if (!(*it)->IsAlive())
		{
			delete(*it);
			it = m_arrowList.erase(it);
		}
		else
			it++;
	}
}

// 更新：斬撃
void CEnemy::Update_Sword(Math::Vector2 scrPos)
{
	for (int i = 0; i < m_enemySwordList.size(); i++)
	{
		m_enemySwordList[i]->SetScrollPos(scrPos);
		m_enemySwordList[i]->Updata();
	}

	std::vector<CEnemySword*>::iterator it;
	it = m_enemySwordList.begin();

	// 不要な矢の要素数削除
	while (it != m_enemySwordList.end())
	{
		// フラグtureならスルー
		if (!(*it)->bGetSlash())
		{
			delete(*it);
			it = m_enemySwordList.erase(it);
		}
		else
			it++;
	}
}

// 描画
void CEnemy::Draw()
{
	// 描画：侍
	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].Draw();
	}

	// 描画：弓兵
	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].Draw();
	}

	// 描画：大男
	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].Draw();
	}

	// 描画：ボス
	m_bossList.Draw();
	
	// 描画：矢
	for (int i = 0; i < m_arrowList.size(); i++)
	{
		m_arrowList[i]->Draw();
	}

	// 描画：敵斬撃
	for (int i = 0; i < m_enemySwordList.size(); i++)
	{
		m_enemySwordList[i]->Draw();
	}
}

// テクスチャ設定：侍
void CEnemy::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < SAMURAI_MAX; i++)
	{
		m_samuraiList[i].SetTexture(apTexture);
	}
}

// テクスチャ設定：弓兵
void CEnemy::SetArcherTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < ARCHER_MAX; i++)
	{
		m_archerList[i].SetTexture(apTexture);
	}
}

// テクスチャ設定：矢
void CEnemy::SetArrowTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pArrawTex = apTexture;
}

// テクスチャ設定：斬撃
void CEnemy::SetSwordTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pSlashTex = apTexture;
}

// テクスチャ設定：大男
void CEnemy::SetGiantTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	for (int i = 0; i < GIANT_MAX; i++)
	{
		m_giantList[i].SetTexture(apTexture);
	}
}

// テクスチャ設定：ボス
void CEnemy::SetBossTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_bossList.SetTexture(apTexture);
}

// 侍の設置関数
void CEnemy::SetSamurai(int data)
{
	//データごとの配置設定
	switch (data)
	{
	//城外
	case OutSide:
		m_samuraiList[1].SetSamurai({ 300.0f, -1080.0f });
		m_samuraiList[2].SetSamurai({ 640.0f,230.0f });
		m_samuraiList[3].SetSamurai({ 640.0f,110.0f });
		break;
	//一階層
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
	//二階層
	case TwoFloor:
		m_samuraiList[1].SetSamurai({ 165,-875 });
		m_samuraiList[2].SetSamurai({ 600,-875 });
		m_samuraiList[3].SetSamurai({ 1000,-875 });
		m_samuraiList[4].SetSamurai({ 1635,-884 });
		break;
	//三階層
	case ThreeFloor:
		break;
	}

}

// 弓兵配置
void CEnemy::SetArcher(int data)
{
	//データごとの配置設定
	switch (data)
	{
	//城外
	case OutSide:
		m_archerList[1].SetArchaer({ 925.0f, -250.0f });
		break;
	//一階層
	case OneFloor:
		m_archerList[1].SetArchaer({ 720.0f, -1250.0f });
		m_archerList[2].SetArchaer({ 1600.0f, -650.0f });

		m_archerList[3].SetArchaer({ -384,-1246 });
		m_archerList[4].SetArchaer({ 136,-1751 });
		
		m_archerList[5].SetArchaer({ 1186,-190 });
		m_archerList[6].SetArchaer({ 1700,-190 });
		
		m_archerList[7].SetArchaer({ 160,-22 });
		break;
	//二階層
	case TwoFloor:
		break;
	//三階層
	case ThreeFloor:
		break;
	
	}
}

// 大男配置
void CEnemy::SetGiant(int data)
{
	//データごとの配置設定
	switch (data)
	{
	//二階層
	case TwoFloor:
		m_giantList[1].SetGiant({ 1675,210 });
		m_giantList[2].SetGiant({ 1675,-1600 });
		break;
	//三階層
	case ThreeFloor:
		break;
	}
}

// ボス配置
void CEnemy::SetBoss(int data)
{
	//データごとの配置設定
	if (data == BossFloor)m_bossList.SetBoss({ 609.0f,0.0f });
}

// ギミック発射
void CEnemy::shot(Math::Vector2 apos, Math::Vector2 bpos)
{
	const int GMAX = 100;
	if (gimmickcount >= GMAX)
	{

		CArrow* arrow = new CArrow;

		arrow->Init();		// 初期化
		arrow->SetTexture(m_pArrawTex);	// テクスチャ設定

		// 発射処理
		arrow->Shot(apos, bpos);
		m_arrowList.push_back(arrow);

		gimmickcount = 0;

	}
}

// イベント処理
void CEnemy::Event()
{
	CMap* map = m_pOwner->GetMap();
	// イベント発生内容
	if (!m_bEvent)
	{
		m_giantList[1].SetGiant({ 409, -250 });
		m_giantList[2].SetGiant({ -90, -250 });
		m_bEvent = true;
		return;
	}
	// イベント終了処理
	if (!m_giantList[1].IsAlive() && !m_giantList[2].IsAlive())
	{
		map->SetUnlock();
	}
}

//オーナー設定取得
void CEnemy::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

// プレイヤーとの当たり判定
void CEnemy::HitCheckPlayer()
{
	CPlayer* player = m_pOwner->GetPlayer();

	// プレイヤーが生きているか、無敵状態でない時に処理
	if (!player->IsAlive() || player->bGetHit()) return;

	Math::Vector2 playerPos = player->GetPos();		// プレイヤーの座標取得
	Math::Vector2 playerMove = player->GetMove();	// プレイヤーの移動量取得
	CEffect* effect = m_pOwner->GetEffect();		// エフェクトクラス
	CDamage* dmgList = effect->GetDmgList();		// ダメージリスト

	////////////////////////////////////////////////////////////////
	//					矢との当たり判定								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_arrowList.size(); i++)
	{
		if (!m_arrowList[i]->IsAlive()) continue;

		// プレイヤーと矢の距離
		const float checkDist = Utility::GetDistance(playerPos, m_arrowList[i]->GetPos());
		// ヒット判定の距離
		const float hitDist = 16;

		// ヒット判定よりも距離が近いとき
		if (checkDist <= hitDist)
		{
			player->SetDamage(POWER::ARCHER_ARROW);	// プレイヤー与ダメージ
			player->SetHitFlg();			// ヒットフラグセット
			m_arrowList[i]->SetAlive();		// 矢のフラグ下げ
		}
	}
	////////////////////////////////////////////////////////////////
	//					斬撃との当たり判定								
	////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_enemySwordList.size(); i++)
	{
		if (!m_enemySwordList[i]->bGetSlash()) continue;

		// プレイヤーと斬撃の距離
		const float checkDist = Utility::GetDistance(playerPos, m_enemySwordList[i]->GetPos());
		
		// 侍の斬撃用判定
		if (m_enemySwordList[i]->GetSize() == SAMURAI_SLASH_SIZE)
		{
			// ヒット判定の距離
			const float hitDist = PLAYER_SIZE::LEFT+SLASH_SIZE::LEFT;

			// ヒット判定よりも距離が近いとき
			if (checkDist <= hitDist)
			{
				player->SetDamage(POWER::SAMURAI_SLASH);	// プレイヤー与ダメージ
				player->SetHitFlg();		// ヒットフラグセット
			}
		}
		// ボスの斬撃用判定
		else if (m_enemySwordList[i]->GetSize() == BOSS_SLASH_SIZE)
		{
			// ヒット判定の距離
			const float hitDist = PLAYER_SIZE::LEFT+BOSS_SIZE::LEFT;

			// ヒット判定よりも距離が近いとき
			if (checkDist <= hitDist)
			{
				player->SetDamage(POWER::BOSS_SLASH);		// プレイヤー与ダメージ
				player->SetHitFlg();	// ヒットフラグセット
			}
		}
	}

	if (m_bossList.IsAlive())
	{
		// ボス本体とのヒット関数　　　　　　　　
		int playerhit = Utility::iHitCheck(playerPos, playerMove, m_bossList.GetPosX(), m_bossList.GetPosY(),
			PLAYER_SIZE::LEFT,PLAYER_SIZE::RIGHT,PLAYER_SIZE::TOP,PLAYER_SIZE::DOWN,
			BOSS_SIZE::LEFT,BOSS_SIZE::RIGHT,BOSS_SIZE::TOP,BOSS_SIZE::DOWN);
		switch (playerhit)
		{
		case 1:	// ボスの上部に触れたら
			player->SetPosY(m_bossList.GetPosY() + 160);	// ボスの上部に出現
			player->SetMovevalY(0);					// 移動量を0に
			player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
			player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
			break;
		case 2:	// ボスの下部に触れたら
			player->SetPosY(m_bossList.GetPosY() - 150);	// ボスの上部に出現
			player->SetMovevalY(0);					// 移動量を0に
			player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
			player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
			break;
		case 3:	// ボスの左に触れたら
			player->SetPosX(m_bossList.GetPosX() - 100);	// ボスの上部に出現
			player->SetMovevalX(0);					// 移動量を0に
			player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
			player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
			break;
		case 4:	// ボスの右に触れたら
			player->SetPosX(m_bossList.GetPosX() + 180);	// ボスの上部に出現
			player->SetMovevalX(0);					// 移動量を0に
			player->SetDamage(POWER::ENEMY_PHYSICAL);	// プレイヤーのHP減少
			player->SetHitFlg();	// 当たっている状態にする(無敵処理を呼び出すため)
			break;
		default:
			break;
		}
	}
}

//マップとの当たり判定
void CEnemy::HitCheckMap()
{
	CMap* map = m_pOwner->GetMap();

	float(*chipX)[MAP_CHIP_W] = map->GetPosX();
	float(*chipY)[MAP_CHIP_W] = map->GetPosY();
	int(*chipData)[MAP_CHIP_W] = map->GetChipData();

	//マップデータを使って
	int hit = 0;
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			//マップの現在座標の四辺
			const float MAP_LEFT = chipX[h][w] - Infor::RADIUS_32;		//左辺
			const float MAP_RIGHT = chipX[h][w] + Infor::RADIUS_32;		//右辺
			const float MAP_TOP = chipY[h][w] + Infor::RADIUS_32;		//上辺
			const float MAP_BOTTOM = chipY[h][w] - Infor::RADIUS_32;	//下辺

			if (chipData[h][w] >= 10 && chipData[h][w] < 49 || chipData[h][w]>=80)
			{
				continue;
			}
			else
			{
				////////////////////////////////////////////////////////////////
				//		侍とのヒットチェック								
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
				//		弓兵とのヒットチェック								
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
				//		大男とのヒットチェック								
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
						m_arrowList[i]->SetAlive();		// 矢のフラグ下げ
					}
				}
			}
			////////////////////////////////////////////////////////////////
			//		矢とのヒットチェック								
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
						m_arrowList[i]->SetAlive();		// 矢のフラグ下げ
					}
					//// マップと矢の距離
					//const float checkDist = Utility::GetDistance(
					//	m_arrowList[i]->GetPos(), { chipX[h][w],chipY[h][w] });
					//// ヒット判定の距離
					//const float hitDist = 32 + 16;

					//// ヒット判定よりも距離が近いとき
					//if (checkDist <= hitDist)
					//{
					//	m_arrowList[i]->SetAlive();		// 矢のフラグ下げ
					//}
				}
			}
		}
	}
}
