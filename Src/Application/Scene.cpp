#include "main.h"
#include "Scene.h"
#include"Utility.h"

void Scene::Draw2D()
{
	switch (sceneType)
	{
	case eSceneTitle:
		//タイトル
		TitleDraw();
		break;
	case eSceneGame:
		//ゲーム本編
		GameDraw();
		break;
	case eSceneExplanation:
		//説明
		ExplanationDraw();
		break;
	case eSceneResult:
		//リザルト
		ResultDraw();
		break;
	}

}

void Scene::Update()
{
	switch (sceneType)
	{
	case eSceneTitle:
		//タイトル
		TitleUpdate();
		break;
	case eSceneGame:
		//ゲーム本編
		GameUpdate();
		break;
	case eSceneExplanation:
		//説明
		ExplanationUpdate();
		break;
	case eSceneResult:
		//説明
		ResultUpdate();
		break;
	}
}

void Scene::Init()
{
	//コンソール作成
	//m_map.CreateConsole();

	srand(timeGetTime());

	Reset();

	bgm = std::make_shared<KdSoundEffect>();
	bgm->Load("Sound/BGM.WAV");
	bgmInst = bgm->CreateInstance(false);
	bgmInst->SetVolume(0.3);
	//bgmInst->Play(true);
}

void Scene::Release()
{
	//m_map.DestroyConsole();

	// プレイヤー
	m_playerTex.Release();
	m_bulletTex.Release();
	m_bombTex.Release();

	// 敵
	m_samuraiTex.Release();
	m_archerTex.Release();
	m_arrowTex.Release();
	m_GiantTex.Release();
	m_bossTex.Release();

	// マップ
	m_mapTex.Release();

	// アイテム
	m_ItemBombTex_t.Release();
	m_ItemBombTex_f.Release();
	m_ItemKeyTex.Release();
	m_ItemHealthTex.Release();
	m_ItemMinoTex.Release();

	// UI
	m_backTex.Release();
	m_rframeTex.Release();
	m_lframeTex.Release();
	m_HPTex.Release();
	m_HPbarTex.Release();
	m_HideTex.Release();
	m_HidebarTex.Release();
	m_katanaTex.Release();
	m_shurikenTex.Release();
	m_iconBombTex.Release();
	m_iconMinoTex.Release();
	m_stackBombTex.Release();
	m_stackKeyTex.Release();

	// エフェクト
	m_pSlashTex.Release();
	m_eSlashTex.Release();
	m_dmgTex.Release();
	m_HealTex.Release();

	// メッセージ
	m_msgTex.Release();

	// その他
	titleTex.Release();
	ExpTex.Release();
	resultTex.Release();
	delete spriteFont;
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

	CBoss* BossList = m_enemy.GetBossList();
	bool a = m_player.bGetHidden();

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::Text("playerX : %.2f", m_player.GetPos().x);
		ImGui::Text("playerY : %.2f", m_player.GetPos().y);
		ImGui::Text("HP : %d", m_player.GetHp());
		ImGui::Text("R_Click : %d", m_player.GetR());
		ImGui::Text("L_Click : %d", m_player.GetL());
		ImGui::Text("Item_BombNum : %d", m_player.GetBombPossession());
		ImGui::Text("Item_KeyNum : %d", m_player.GetKeyPossession());
		ImGui::Text("BossHp : %d", BossList->GetHp());
		ImGui::Text("Activate : %f", m_player.GetHideCnt());
		ImGui::Text("BossDirection : %d", BossList->GetDirection());

		ImGui::Checkbox("HideFlg", &a);

	}
	ImGui::End();
}

//初期化リセット
void Scene::Reset()
{
	/*bool load = false;
	load =
	_ASSERT_EXPR(load == true, L"読み込み失敗");*/

	//MessageBox(NULL, L"HIT", L"hit", MB_OK);

	/*テクスチャ*/
	// プレイヤー
	m_playerTex.Load("Texture/Player/player.png");
	m_bulletTex.Load("Texture/Player/shuriken.png");
	m_bombTex.Load("Texture/Player/bomb.png");
	m_blastTex.Load("Texture/Player/blast.png");

	// 敵
	m_samuraiTex.Load("Texture/Enemy/enemy.png");
	m_archerTex.Load("Texture/Enemy/Archer.png");
	m_arrowTex.Load("Texture/Enemy/arrow.png");
	m_GiantTex.Load("Texture/Enemy/giant.png");
	m_bossTex.Load("Texture/Enemy/boss1.png");	// ボス

	// マップ
	m_mapTex.Load("Texture/Map/Map1.png");
	
	// アイテム
	m_ItemBombTex_t.Load("Texture/Item/BombStorage_true.png");		// 爆弾_有
	m_ItemBombTex_f.Load("Texture/Item/BombStorage_false.png");		// 爆弾_無
	m_ItemKeyTex.Load("Texture/Item/Key.png");						// 鍵
	m_ItemHealthTex.Load("Texture/Item/onigirio.png");				// 回復
	m_ItemMinoTex.Load("Texture/Item/hidemino.png");					// 隠れ蓑

	// UI
	m_backTex.Load("Texture/UI/back.png");
	m_rframeTex.Load("Texture/UI/frameR.png");
	m_lframeTex.Load("Texture/UI/frameL.png");
	m_HPTex.Load("Texture/UI/HP.png");
	m_HPbarTex.Load("Texture/UI/HPbar.png");
	m_HideTex.Load("Texture/UI/Hide.png");
	m_HidebarTex.Load("Texture/UI/Hidebar.png");
	m_katanaTex.Load("Texture/UI/Katana.png");
	m_shurikenTex.Load("Texture/UI/Shuriken.png");
	m_iconBombTex.Load("Texture/UI/Bomb.png");
	m_iconMinoTex.Load("Texture/UI/Hidemino.png");
	m_stackBombTex.Load("Texture/UI/bomb_icon.png");
	m_stackKeyTex.Load("Texture/UI/key.png");


	// エフェクト
	m_pSlashTex.Load("Texture/Effect/p_slash.png");
	m_eSlashTex.Load("Texture/Effect/e_slash.png");
	m_dmgTex.Load("Texture/Effect/dmg.png");
	m_darkenTex.Load("Texture/Effect/Dark.gif");
	m_HealTex.Load("Texture/Effect/heal.png");

	// メッセージ
	m_msgTex.Load("Texture/Message/AOMessage.png");

	// その他
	titleTex.Load("Texture/Title/Op.png");
	ExpTex.Load("Texture/Title/ex.png");
	resultTex.Load("Texture/Result/end_01.png");


	/*クラスごとの初期化*/
	//マップ
	m_map.Init();
	m_map.SetTexture(&m_mapTex);
	m_map.SetOwner(this);

	//プレイヤー
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_player.SetOwner(this);
	m_player.SetBulletTexture(&m_bulletTex);
	m_player.SetSlashTexture(&m_pSlashTex);
	m_player.SetBombTexture(&m_bombTex);
	m_player.SetBlastTexture(&m_blastTex);

	//敵
	m_enemy.SetOwner(this);
	m_enemy.Init();					// 敵：初期化
	m_enemy.SetTexture(&m_samuraiTex);		// 侍
	m_enemy.SetArcherTexture(&m_archerTex);	// 弓兵
	m_enemy.SetArrowTexture(&m_arrowTex);	// 矢(縦)
	m_enemy.SetGiantTexture(&m_GiantTex);	// 大男
	m_enemy.SetBossTexture(&m_bossTex);		// ボス
	m_enemy.SetSwordTexture(&m_eSlashTex);// 敵斬撃

	//アイテム
	m_item.SetTexBomb_t(&m_ItemBombTex_t);
	m_item.SetTexBomb_f(&m_ItemBombTex_f);
	m_item.SetTexKey(&m_ItemKeyTex);
	m_item.SetTexHealth(&m_ItemHealthTex);
	m_item.SetTexMino(&m_ItemMinoTex);
	m_item.SetOwner(this);
	m_item.Init();

	//UI
	m_ui.Init();
	m_ui.SetbackTexture(&m_backTex);
	m_ui.SetrframeTexture(&m_rframeTex);
	m_ui.SetlframeTexture(&m_lframeTex);
	m_ui.SetHPTexture(&m_HPTex);
	m_ui.SetHPBarTexture(&m_HPbarTex);
	m_ui.SetHideTexture(&m_HideTex);
	m_ui.SetHideBarTexture(&m_HidebarTex);
	m_ui.SetIconKatanaTexture(&m_katanaTex);
	m_ui.SetIconShurikenTexture(&m_shurikenTex);
	m_ui.SetIconBombTexture(&m_iconBombTex);
	m_ui.SetIconMinoTexture(&m_iconMinoTex);
	m_ui.SetStackBombTexture(&m_stackBombTex);
	m_ui.SetStackKeyTexture(&m_stackKeyTex);
	m_ui.SetOwner(this);

	// エフェクト
	m_effect.Init();
	m_effect.SetDmgTexture(&m_dmgTex);
	m_effect.SetDarkTexture(&m_darkenTex);
	m_effect.SetHealTexture(&m_HealTex);
	m_effect.SetOwner(this);

	// メッセージ
	m_message.Init();
	m_message.SetTexture(&m_msgTex);

	/*Scene内の初期化*/

	//初期シーン　タイトル
	sceneType = eSceneTitle;	//0:タイトル　1:ゲーム本編

	//キー制御
	keyFlg = 0;		//0:押してない1:押している
	clickFlg = false;

	//ゲームスタートボタン
	gameStartPos = { 9, -10 };
	gameStartFlg = false;

	//説明スタートボタン
	ExplanationStartPos = { 9, -137 };
	ExplanationStartFlg = false;

	//タイトルスタートボタン
	TitleStartPos = { 488, -243 };
	TitleStartFlg = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												タイトル画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//タイトル:更新
void Scene::TitleUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	////////////////////////////////////////////////////////////
	//	タイトルからゲーム本編								///
	////////////////////////////////////////////////////////////

	float Left = gameStartPos.x - 190;
	float Right = gameStartPos.x + 190;
	float Top = gameStartPos.y + 50;
	float Bottom = gameStartPos.y - 50;

	gameStartFlg = false;

	//強調枠内の判定
	if (m_mouse.cur.x > Left && m_mouse.cur.x < Right)
	{
		if (m_mouse.cur.y > Bottom && m_mouse.cur.y < Top)
		{
			gameStartFlg = true;	//枠を表示

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				sceneType = eSceneGame;	//ゲーム画面移行
				clickFlg = true;
			}
			else
			{
				clickFlg = false;
			}
		}
	}

	///////////////////////////////////////////////////////
	//	タイトルから説明								///
	///////////////////////////////////////////////////////

	float exLeft = ExplanationStartPos.x - 150;
	float exRight = ExplanationStartPos.x + 150;
	float exTop = ExplanationStartPos.y + 43;
	float exBottom = ExplanationStartPos.y - 43;

	ExplanationStartFlg = false;

	//強調枠内の判定
	if (m_mouse.cur.x > exLeft && m_mouse.cur.x < exRight)
	{
		if (m_mouse.cur.y > exBottom && m_mouse.cur.y < exTop)
		{
			ExplanationStartFlg = true;	//強調枠表示

			if (clickFlg == false)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					sceneType = eSceneExplanation;	//説明画面に移行
					clickFlg = true;
				}
				else
				{
					clickFlg = false;
				}
			}
		}
	}

}
//タイトル:描画
void Scene::TitleDraw()
{
	Titlemat = DirectX::XMMatrixTranslation(0, 0, 0);//ここは座標
	SHADER.m_spriteShader.SetMatrix(Titlemat);
	SHADER.m_spriteShader.DrawTex(&titleTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	//強調枠描画
	if (gameStartFlg)	//ゲーム
	{
		color = { 1,1,0,1 };
		SHADER.m_spriteShader.DrawBox(gameStartPos.x, gameStartPos.y, 190, 50, &color, false);
	}
	if (ExplanationStartFlg)	//説明
	{
		color = { 1,0,0,1 };
		SHADER.m_spriteShader.DrawBox(ExplanationStartPos.x, ExplanationStartPos.y, 150, 43, &color, false);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												ゲーム画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ゲーム:更新
void Scene::GameUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	//マップ切り替え時の処理
	if (m_map.GetMapSwitchFlg())
	{
		CDarken* darkenList = m_effect.GetDarkenList();
		for (int i = 0; i < DARKEN_MAX; i++)
		{
			darkenList[i].EmitDark();
		}

		//マップ情報の切り替え
		m_map.SetMapData();
		m_map.LoadMapFile();

		//チップ画像切り替え
		switch (m_map.GetMapData())
		{
		//城外
		case OutSide:
			m_mapTex.Load("Texture/Map/Map1.png");
			break;
		//一階層
		case OneFloor:
			m_mapTex.Load("Texture/Map/Map2.png");
			break;
		//二階層
		case TwoFloor:
			m_mapTex.Load("Texture/Map/Map3.png");
			break;
		//三階層
		case ThreeFloor:
			m_mapTex.Load("Texture/Map/Map4.png");
			break;
		//ボス階層
		case BossFloor:
			m_mapTex.Load("Texture/Map/Boss.png");
			break;
		}

		// プレイヤー再初期化
		m_player.ReInit(m_map.GetMapData());

		//アイテム再初期化
		m_item.Init();

		//敵クラス再初期化
		m_enemy.Init();

		m_map.SetMapSwitchFlg(false);	//切り替えフラグ下げ
	}

	//マップ
	m_map.Update();

	//プレイヤー
	m_player.Updata(m_mouse.cur);

	//敵
	m_enemy.Update();

	//アイテム
	m_item.Update();

	//UI
	m_ui.Updata();

	// エフェクト
	m_effect.UpDate();

	// メッセージ
	switch (m_message.GetMsgNum())
	{
	case 0: m_msgTex.Load("Texture/Message/Attack description.png");
		break;
	case 1: m_msgTex.Load("Texture/Message/Weapon change description.png");
		break; 
	case 2: m_msgTex.Load("Texture/Message/Weapon description.png");
		break; 
	case 3: m_msgTex.Load("Texture/Message/Door description.png");
		break; 
	case 4: m_msgTex.Load("Texture/Message/.png");
		break;
	}
	m_message.SetScrollPos(m_map.GetscrollPos());
	m_message.Update();

	//タイトル移行
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		if (keyFlg == 0)
		{
			Reset();
			keyFlg = 1;
			sceneType = eSceneTitle;//タイトルへ
		}
	}
	else
	{
		keyFlg = 0;
	}

	if (m_enemy.GetBossHp() <= 0)
	{
		sceneType = eSceneResult;
	}
	
}

//ゲーム:描画
void Scene::GameDraw()
{
	//マップ
	m_map.Draw();

	//アイテム
	m_item.Draw();

	//敵
	m_enemy.Draw();
	
	//プレイヤー
	m_player.Draw();

	// エフェクト
	m_effect.Draw();

	// メッセージ
	m_message.Draw();
	
	//UI
	m_ui.Draw();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												操作説明画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//説明:更新
void Scene::ExplanationUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	////////////////////////////////////////////////////////
	//	説明からタイトル								///
	//////////////////////////////////////////////////////

	float eLeft = TitleStartPos.x - 80;
	float eRight = TitleStartPos.x + 80;
	float eTop = TitleStartPos.y + 80;
	float eBottom = TitleStartPos.y - 80;

	TitleStartFlg = false;

	//強調枠内の判定
	if (m_mouse.cur.x > eLeft && m_mouse.cur.x < eRight)
	{
		if (m_mouse.cur.y > eBottom && m_mouse.cur.y < eTop)
		{
			TitleStartFlg = true;	//強調枠表示

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (clickFlg == false)
				{
					sceneType = eSceneTitle;	//タイトル移行
					clickFlg = true;
				}
			}
			else
			{
				clickFlg = false;
			}
		}
	}

}

//説明:描画
void Scene::ExplanationDraw()
{
	Titlemat = DirectX::XMMatrixTranslation(0, 0, 0);//ここは座標
	SHADER.m_spriteShader.SetMatrix(Titlemat);
	SHADER.m_spriteShader.DrawTex(&ExpTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	if (TitleStartFlg)
	{
		//強調枠
		color = { 0,0,1,1 };
		SHADER.m_spriteShader.DrawBox(TitleStartPos.x, TitleStartPos.y, 80, 80, &color, false);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												リザルト画面
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// リザルト：更新
void Scene::ResultUpdate()
{
	Resultmat = DirectX::XMMatrixTranslation(0, 0, 0);
	bgmInst->Pause();
}

// リザルト：描画
void Scene::ResultDraw()
{
	SHADER.m_spriteShader.SetMatrix(Resultmat);
	SHADER.m_spriteShader.DrawTex(&resultTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
}

//マウス座標取得関数
void Scene::GetMousePos(Math::Vector2 scrPos)
{
	GetCursorPos(&m_mouse.cur);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse.cur);

	m_mouse.cur.x -= Screen::HalfWidth - scrPos.x;
	m_mouse.cur.y -= Screen::HalfHeight + scrPos.y;
	m_mouse.cur.y *= -1;
}
