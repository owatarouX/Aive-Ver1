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
	case eSceneDescription:
		//����
		DescriptDraw();
		break;
	case eSceneResult:
		//���U���g
		ResultDraw();
		break;
	}

	// �}�E�X�J�[�\��
	MousePointDraw();
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
	case eSceneDescription:
		//����
		DescriptUpdate();
		break;
	case eSceneResult:
		//���U���g
		ResultUpdate();
		break;
	}
}

void Scene::Init()
{
	srand(timeGetTime());


	bgm = std::make_shared<KdSoundEffect>();
	bgm->Load("Resource/Sound/BGM.WAV");
	bgmInst = bgm->CreateInstance(false);
	bgmInst->SetVolume(0.3);
	Reset();
}

void Scene::Release()
{
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
	m_titleTex.Release();
	m_lineTex.Release();
	
	m_descriptTex.Release();
	m_resultTex.Release();
	delete spriteFont;
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

	CBoss* BossList = m_enemy.GetBossList();
	bool a = m_title.bGetToGame();
	bool b = m_title.bGetToDescript();

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
		
		ImGui::Checkbox("gameF", &a);
		ImGui::Checkbox("descF", &b);

	}
	ImGui::End();
}

//���������Z�b�g
void Scene::Reset()
{
	/*�e�N�X�`��*/
	// �^�C�g�����
	m_titleTex.Load("Resource/Texture/Title/Op.png");
	m_lineTex.Load("Resource/Texture/Title/Line.png");

	// �������
	m_descriptTex.Load("Resource/Texture/Description/descript.png");

	// �v���C���[
	m_playerTex.Load("Resource/Texture/Player/player.png");
	m_bulletTex.Load("Resource/Texture/Player/shuriken.png");
	m_bombTex.Load("Resource/Texture/Player/bomb.png");
	m_blastTex.Load("Resource/Texture/Player/blast.png");

	// �G
	m_samuraiTex.Load("Resource/Texture/Enemy/samurai.png");
	m_archerTex.Load("Resource/Texture/Enemy/Archer.png");
	m_arrowTex.Load("Resource/Texture/Enemy/arrow.png");
	m_GiantTex.Load("Resource/Texture/Enemy/giant.png");
	m_bossTex.Load("Resource/Texture/Enemy/idle_0.png");	// �{�X

	// �}�b�v
	m_mapTex.Load("Resource/Texture/Map/Map1.png");
	
	// �A�C�e��
	m_ItemBombTex_t.Load("Resource/Texture/Item/BombStorage_true.png");		// ���e_�L
	m_ItemBombTex_f.Load("Resource/Texture/Item/BombStorage_false.png");		// ���e_��
	m_ItemKeyTex.Load("Resource/Texture/Item/Key.png");						// ��
	m_ItemHealthTex.Load("Resource/Texture/Item/onigirio.png");				// ��
	m_ItemMinoTex.Load("Resource/Texture/Item/hidemino.png");					// �B�ꖪ

	// UI
	m_backTex.Load("Resource/Texture/UI/back.png");
	m_rframeTex.Load("Resource/Texture/UI/frameR.png");
	m_lframeTex.Load("Resource/Texture/UI/frameL.png");
	m_HPTex.Load("Resource/Texture/UI/HP.png");
	m_HPbarTex.Load("Resource/Texture/UI/HPbar.png");
	m_HideTex.Load("Resource/Texture/UI/Hide.png");
	m_HidebarTex.Load("Resource/Texture/UI/Hidebar.png");
	m_katanaTex.Load("Resource/Texture/UI/Katana.png");
	m_shurikenTex.Load("Resource/Texture/UI/Shuriken.png");
	m_iconBombTex.Load("Resource/Texture/UI/Bomb.png");
	m_iconMinoTex.Load("Resource/Texture/UI/Hidemino.png");
	m_stackBombTex.Load("Resource/Texture/UI/bomb_icon.png");
	m_stackKeyTex.Load("Resource/Texture/UI/key.png");

	// �G�t�F�N�g
	m_pSlashTex.Load("Resource/Texture/Effect/p_slash.png");
	m_eSlashTex.Load("Resource/Texture/Effect/e_slash.png");
	m_dmgTex.Load("Resource/Texture/Effect/dmg.png");
	m_darkenTex.Load("Resource/Texture/Effect/Dark.gif");
	m_HealTex.Load("Resource/Texture/Effect/heal.png");

	// ���b�Z�[�W
	m_msgTex.Load("Resource/Texture/Message/AOMessage.png");

	// ���U���g
	m_resultTex.Load("Resource/Texture/Result/clear.png");

	// �}�E�X�J�[�\��
	m_mousePointTex.Load("Resource/Texture/Player/mousepoint.png");

	/*�N���X���Ƃ̏�����*/
	// �^�C�g��
	m_title.Init();
	m_title.SetTexTitle(&m_titleTex);
	m_title.SetTexLine(&m_lineTex);

	// �Q�[������
	m_descript.Init();
	m_descript.SetTexDescript(&m_descriptTex);
	m_descript.SetTexLine(&m_lineTex);

	//�}�b�v
	m_map.SetOwner(this);
	m_map.Init();
	m_map.SetTexture(&m_mapTex);

	//�v���C���[
	m_player.SetOwner(this);
	m_player.Init();
	m_player.SetTexture(&m_playerTex);
	m_player.SetBulletTexture(&m_bulletTex);
	m_player.SetSlashTexture(&m_pSlashTex);
	m_player.SetBombTexture(&m_bombTex);
	m_player.SetBlastTexture(&m_blastTex);

	//�G
	m_enemy.SetOwner(this);
	m_enemy.Init();					// �G�F������
	m_enemy.SetTexture(&m_samuraiTex);		// ��
	m_enemy.SetArcherTexture(&m_archerTex);	// �|��
	m_enemy.SetArrowTexture(&m_arrowTex);	// ��
	m_enemy.SetGiantTexture(&m_GiantTex);	// ��j
	m_enemy.SetBossTexture(&m_bossTex);		// �{�X
	m_enemy.SetSwordTexture(&m_eSlashTex);// �G�a��

	//�A�C�e��
	m_item.SetOwner(this);
	m_item.Init();
	m_item.SetTexBomb_t(&m_ItemBombTex_t);
	m_item.SetTexBomb_f(&m_ItemBombTex_f);
	m_item.SetTexKey(&m_ItemKeyTex);
	m_item.SetTexHealth(&m_ItemHealthTex);
	m_item.SetTexMino(&m_ItemMinoTex);

	//UI
	m_ui.SetOwner(this);
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

	// �G�t�F�N�g
	m_effect.SetOwner(this);
	m_effect.Init();
	m_effect.SetDmgTexture(&m_dmgTex);
	m_effect.SetDarkTexture(&m_darkenTex);
	m_effect.SetHealTexture(&m_HealTex);

	// ���b�Z�[�W
	m_message.Init();
	m_message.SetTexture(&m_msgTex);

	// ���U���g
	m_result.Init();
	m_result.SetTexResult(&m_resultTex);
	m_result.SetTexLine(&m_lineTex);

	//�����V�[���@�^�C�g��
	sceneType = eSceneTitle;

	bgmInst->Play(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												�^�C�g�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�^�C�g��:�X�V
void Scene::TitleUpdate()
{
	GetMousePos({ 0,0 });

	// �X�V����
	m_title.Update(m_mouse.cur);

	int trans = m_title.SceneTransition();
	switch (trans)
	{
	case 1: sceneType = eSceneGame;
		break;
	case 2:sceneType = eSceneDescription;
		break;
	default:
		break;
	}
}
//�^�C�g��:�`��
void Scene::TitleDraw()
{
	m_title.Draw();
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
		darkenList->EmitDark();		// �Ó]�G�t�F�N�g

		//�}�b�v���̐؂�ւ�
		m_map.SetMapData();
		m_map.LoadMapFile();

		//�`�b�v�摜�؂�ւ�
		switch (m_map.GetMapData())
		{
		//��O
		case OutSide:
			m_mapTex.Load("Resource/Texture/Map/Map1.png");
			break;
		//��K�w
		case OneFloor:
			m_mapTex.Load("Resource/Texture/Map/Map2.png");
			break;
		//��K�w
		case TwoFloor:
			m_mapTex.Load("Resource/Texture/Map/Map3.png");
			break;
		//�O�K�w
		case ThreeFloor:
			m_mapTex.Load("Resource/Texture/Map/Map4.png");
			break;
		//�l�K�w
		case FourFloor:
			m_mapTex.Load("Resource/Texture/Map/Map5.png");
			break;
		//�{�X�K�w
		case BossFloor:
			m_mapTex.Load("Resource/Texture/Map/Boss.png");
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
	case 0: m_msgTex.Load("Resource/Texture/Message/Attack description.png");
		break;
	case 1: m_msgTex.Load("Resource/Texture/Message/Weapon change description.png");
		break; 
	case 2: m_msgTex.Load("Resource/Texture/Message/Weapon description.png");
		break; 
	case 3: m_msgTex.Load("Resource/Texture/Message/Door description.png");
		break; 
	case 4: m_msgTex.Load("Resource/Texture/Message/minoMassage.png");
		break;
	case 5: m_msgTex.Load("Resource/Texture/Message/BombMassage.png");
		break;
	case 6: m_msgTex.Load("Resource/Texture/Message/lightbasketMessage.png");
		break;
	}
	m_message.SetScrollPos(m_map.GetscrollPos());
	m_message.Update();

	// ���U���g�ڍs
	if (m_player.GetHp() <= 0)
	{
		m_resultTex.Load("Resource/Texture/Result/GameOver.png");
		sceneType = eSceneResult;
	}
	else if (m_enemy.GetBossHp() <= 0)
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
void Scene::DescriptUpdate()
{
	GetMousePos({ 0,0 });
	m_descript.Update(m_mouse.cur);
	// �V�[���J�ڏ���
	if (m_descript.SceneTransition())
	{
		sceneType = eSceneTitle;
	}
}
//����:�`��
void Scene::DescriptDraw()
{
	m_descript.Draw();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												���U���g���
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���U���g�F�X�V
void Scene::ResultUpdate()
{
	GetMousePos({ 0,0 });
	m_result.Update(m_mouse.cur);
	// �V�[���J�ڏ���
	if (m_result.SceneTransition())
	{
		Reset();
		return;
	}
	bgmInst->Pause();
}

// ���U���g�F�`��
void Scene::ResultDraw()
{
	m_result.Draw();
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

// �}�E�X�|�C���g�`��
void Scene::MousePointDraw()
{
	GetMousePos({ 0,0 });
	Math::Matrix mat;
	int r = 32;
	mat = DirectX::XMMatrixTranslation(m_mouse.cur.x+ r/2, m_mouse.cur.y- r/2, 0);
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_mousePointTex, Math::Rectangle(0,0, r, r),1.0f);
}
