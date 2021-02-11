#include "main.h"
#include "Scene.h"
#include"Utility.h"

void Scene::Draw2D()
{
	switch (sceneType)
	{
	case eSceneTitle:
		//�^�C�g��
		TitleDraw();
		break;
	case eSceneGame:
		//�Q�[���{��
		GameDraw();
		break;
	case eSceneExplanation:
		//����
		ExplanationDraw();
		break;
	case eSceneResult:
		//���U���g
		ResultDraw();
		break;
	}

}

void Scene::Update()
{
	switch (sceneType)
	{
	case eSceneTitle:
		//�^�C�g��
		TitleUpdate();
		break;
	case eSceneGame:
		//�Q�[���{��
		GameUpdate();
		break;
	case eSceneExplanation:
		//����
		ExplanationUpdate();
		break;
	case eSceneResult:
		//����
		ResultUpdate();
		break;
	}
}

void Scene::Init()
{
	//�R���\�[���쐬
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

	// �v���C���[
	m_playerTex.Release();
	m_bulletTex.Release();
	m_bombTex.Release();

	// �G
	m_samuraiTex.Release();
	m_archerTex.Release();
	m_arrowTex.Release();
	m_GiantTex.Release();
	m_bossTex.Release();

	// �}�b�v
	m_mapTex.Release();

	// �A�C�e��
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

	// �G�t�F�N�g
	m_pSlashTex.Release();
	m_eSlashTex.Release();
	m_dmgTex.Release();
	m_HealTex.Release();

	// ���b�Z�[�W
	m_msgTex.Release();

	// ���̑�
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

	// �f�o�b�O�E�B���h�E
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

//���������Z�b�g
void Scene::Reset()
{
	/*bool load = false;
	load =
	_ASSERT_EXPR(load == true, L"�ǂݍ��ݎ��s");*/

	//MessageBox(NULL, L"HIT", L"hit", MB_OK);

	/*�e�N�X�`��*/
	// �v���C���[
	m_playerTex.Load("Texture/Player/player.png");
	m_bulletTex.Load("Texture/Player/shuriken.png");
	m_bombTex.Load("Texture/Player/bomb.png");
	m_blastTex.Load("Texture/Player/blast.png");

	// �G
	m_samuraiTex.Load("Texture/Enemy/enemy.png");
	m_archerTex.Load("Texture/Enemy/Archer.png");
	m_arrowTex.Load("Texture/Enemy/arrow.png");
	m_GiantTex.Load("Texture/Enemy/giant.png");
	m_bossTex.Load("Texture/Enemy/boss1.png");	// �{�X

	// �}�b�v
	m_mapTex.Load("Texture/Map/Map1.png");
	
	// �A�C�e��
	m_ItemBombTex_t.Load("Texture/Item/BombStorage_true.png");		// ���e_�L
	m_ItemBombTex_f.Load("Texture/Item/BombStorage_false.png");		// ���e_��
	m_ItemKeyTex.Load("Texture/Item/Key.png");						// ��
	m_ItemHealthTex.Load("Texture/Item/onigirio.png");				// ��
	m_ItemMinoTex.Load("Texture/Item/hidemino.png");					// �B�ꖪ

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


	// �G�t�F�N�g
	m_pSlashTex.Load("Texture/Effect/p_slash.png");
	m_eSlashTex.Load("Texture/Effect/e_slash.png");
	m_dmgTex.Load("Texture/Effect/dmg.png");
	m_darkenTex.Load("Texture/Effect/Dark.gif");
	m_HealTex.Load("Texture/Effect/heal.png");

	// ���b�Z�[�W
	m_msgTex.Load("Texture/Message/AOMessage.png");

	// ���̑�
	titleTex.Load("Texture/Title/Op.png");
	ExpTex.Load("Texture/Title/ex.png");
	resultTex.Load("Texture/Result/end_01.png");


	/*�N���X���Ƃ̏�����*/
	//�}�b�v
	m_map.Init();
	m_map.SetTexture(&m_mapTex);
	m_map.SetOwner(this);

	//�v���C���[
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_player.SetOwner(this);
	m_player.SetBulletTexture(&m_bulletTex);
	m_player.SetSlashTexture(&m_pSlashTex);
	m_player.SetBombTexture(&m_bombTex);
	m_player.SetBlastTexture(&m_blastTex);

	//�G
	m_enemy.SetOwner(this);
	m_enemy.Init();					// �G�F������
	m_enemy.SetTexture(&m_samuraiTex);		// ��
	m_enemy.SetArcherTexture(&m_archerTex);	// �|��
	m_enemy.SetArrowTexture(&m_arrowTex);	// ��(�c)
	m_enemy.SetGiantTexture(&m_GiantTex);	// ��j
	m_enemy.SetBossTexture(&m_bossTex);		// �{�X
	m_enemy.SetSwordTexture(&m_eSlashTex);// �G�a��

	//�A�C�e��
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

	// �G�t�F�N�g
	m_effect.Init();
	m_effect.SetDmgTexture(&m_dmgTex);
	m_effect.SetDarkTexture(&m_darkenTex);
	m_effect.SetHealTexture(&m_HealTex);
	m_effect.SetOwner(this);

	// ���b�Z�[�W
	m_message.Init();
	m_message.SetTexture(&m_msgTex);

	/*Scene���̏�����*/

	//�����V�[���@�^�C�g��
	sceneType = eSceneTitle;	//0:�^�C�g���@1:�Q�[���{��

	//�L�[����
	keyFlg = 0;		//0:�����ĂȂ�1:�����Ă���
	clickFlg = false;

	//�Q�[���X�^�[�g�{�^��
	gameStartPos = { 9, -10 };
	gameStartFlg = false;

	//�����X�^�[�g�{�^��
	ExplanationStartPos = { 9, -137 };
	ExplanationStartFlg = false;

	//�^�C�g���X�^�[�g�{�^��
	TitleStartPos = { 488, -243 };
	TitleStartFlg = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												�^�C�g�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�^�C�g��:�X�V
void Scene::TitleUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	////////////////////////////////////////////////////////////
	//	�^�C�g������Q�[���{��								///
	////////////////////////////////////////////////////////////

	float Left = gameStartPos.x - 190;
	float Right = gameStartPos.x + 190;
	float Top = gameStartPos.y + 50;
	float Bottom = gameStartPos.y - 50;

	gameStartFlg = false;

	//�����g���̔���
	if (m_mouse.cur.x > Left && m_mouse.cur.x < Right)
	{
		if (m_mouse.cur.y > Bottom && m_mouse.cur.y < Top)
		{
			gameStartFlg = true;	//�g��\��

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				sceneType = eSceneGame;	//�Q�[����ʈڍs
				clickFlg = true;
			}
			else
			{
				clickFlg = false;
			}
		}
	}

	///////////////////////////////////////////////////////
	//	�^�C�g���������								///
	///////////////////////////////////////////////////////

	float exLeft = ExplanationStartPos.x - 150;
	float exRight = ExplanationStartPos.x + 150;
	float exTop = ExplanationStartPos.y + 43;
	float exBottom = ExplanationStartPos.y - 43;

	ExplanationStartFlg = false;

	//�����g���̔���
	if (m_mouse.cur.x > exLeft && m_mouse.cur.x < exRight)
	{
		if (m_mouse.cur.y > exBottom && m_mouse.cur.y < exTop)
		{
			ExplanationStartFlg = true;	//�����g�\��

			if (clickFlg == false)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					sceneType = eSceneExplanation;	//������ʂɈڍs
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
//�^�C�g��:�`��
void Scene::TitleDraw()
{
	Titlemat = DirectX::XMMatrixTranslation(0, 0, 0);//�����͍��W
	SHADER.m_spriteShader.SetMatrix(Titlemat);
	SHADER.m_spriteShader.DrawTex(&titleTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	//�����g�`��
	if (gameStartFlg)	//�Q�[��
	{
		color = { 1,1,0,1 };
		SHADER.m_spriteShader.DrawBox(gameStartPos.x, gameStartPos.y, 190, 50, &color, false);
	}
	if (ExplanationStartFlg)	//����
	{
		color = { 1,0,0,1 };
		SHADER.m_spriteShader.DrawBox(ExplanationStartPos.x, ExplanationStartPos.y, 150, 43, &color, false);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												�Q�[�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�Q�[��:�X�V
void Scene::GameUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	//�}�b�v�؂�ւ����̏���
	if (m_map.GetMapSwitchFlg())
	{
		CDarken* darkenList = m_effect.GetDarkenList();
		for (int i = 0; i < DARKEN_MAX; i++)
		{
			darkenList[i].EmitDark();
		}

		//�}�b�v���̐؂�ւ�
		m_map.SetMapData();
		m_map.LoadMapFile();

		//�`�b�v�摜�؂�ւ�
		switch (m_map.GetMapData())
		{
		//��O
		case OutSide:
			m_mapTex.Load("Texture/Map/Map1.png");
			break;
		//��K�w
		case OneFloor:
			m_mapTex.Load("Texture/Map/Map2.png");
			break;
		//��K�w
		case TwoFloor:
			m_mapTex.Load("Texture/Map/Map3.png");
			break;
		//�O�K�w
		case ThreeFloor:
			m_mapTex.Load("Texture/Map/Map4.png");
			break;
		//�{�X�K�w
		case BossFloor:
			m_mapTex.Load("Texture/Map/Boss.png");
			break;
		}

		// �v���C���[�ď�����
		m_player.ReInit(m_map.GetMapData());

		//�A�C�e���ď�����
		m_item.Init();

		//�G�N���X�ď�����
		m_enemy.Init();

		m_map.SetMapSwitchFlg(false);	//�؂�ւ��t���O����
	}

	//�}�b�v
	m_map.Update();

	//�v���C���[
	m_player.Updata(m_mouse.cur);

	//�G
	m_enemy.Update();

	//�A�C�e��
	m_item.Update();

	//UI
	m_ui.Updata();

	// �G�t�F�N�g
	m_effect.UpDate();

	// ���b�Z�[�W
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

	//�^�C�g���ڍs
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		if (keyFlg == 0)
		{
			Reset();
			keyFlg = 1;
			sceneType = eSceneTitle;//�^�C�g����
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

//�Q�[��:�`��
void Scene::GameDraw()
{
	//�}�b�v
	m_map.Draw();

	//�A�C�e��
	m_item.Draw();

	//�G
	m_enemy.Draw();
	
	//�v���C���[
	m_player.Draw();

	// �G�t�F�N�g
	m_effect.Draw();

	// ���b�Z�[�W
	m_message.Draw();
	
	//UI
	m_ui.Draw();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												����������
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����:�X�V
void Scene::ExplanationUpdate()
{
	GetMousePos(m_map.GetscrollPos());

	////////////////////////////////////////////////////////
	//	��������^�C�g��								///
	//////////////////////////////////////////////////////

	float eLeft = TitleStartPos.x - 80;
	float eRight = TitleStartPos.x + 80;
	float eTop = TitleStartPos.y + 80;
	float eBottom = TitleStartPos.y - 80;

	TitleStartFlg = false;

	//�����g���̔���
	if (m_mouse.cur.x > eLeft && m_mouse.cur.x < eRight)
	{
		if (m_mouse.cur.y > eBottom && m_mouse.cur.y < eTop)
		{
			TitleStartFlg = true;	//�����g�\��

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (clickFlg == false)
				{
					sceneType = eSceneTitle;	//�^�C�g���ڍs
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

//����:�`��
void Scene::ExplanationDraw()
{
	Titlemat = DirectX::XMMatrixTranslation(0, 0, 0);//�����͍��W
	SHADER.m_spriteShader.SetMatrix(Titlemat);
	SHADER.m_spriteShader.DrawTex(&ExpTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	if (TitleStartFlg)
	{
		//�����g
		color = { 0,0,1,1 };
		SHADER.m_spriteShader.DrawBox(TitleStartPos.x, TitleStartPos.y, 80, 80, &color, false);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												���U���g���
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���U���g�F�X�V
void Scene::ResultUpdate()
{
	Resultmat = DirectX::XMMatrixTranslation(0, 0, 0);
	bgmInst->Pause();
}

// ���U���g�F�`��
void Scene::ResultDraw()
{
	SHADER.m_spriteShader.SetMatrix(Resultmat);
	SHADER.m_spriteShader.DrawTex(&resultTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
}

//�}�E�X���W�擾�֐�
void Scene::GetMousePos(Math::Vector2 scrPos)
{
	GetCursorPos(&m_mouse.cur);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse.cur);

	m_mouse.cur.x -= Screen::HalfWidth - scrPos.x;
	m_mouse.cur.y -= Screen::HalfHeight + scrPos.y;
	m_mouse.cur.y *= -1;
}
