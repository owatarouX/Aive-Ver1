#pragma once
#include "CPlayer.h"
#include "CEnemy.h"
#include "CMap.h"
#include"CItem.h"
#include"UI.h"
#include"CEffect.h"
#include"CMessage.h"

//�V�[���̎��
enum eSceneType
{
	eSceneTitle,		//0	Title
	eSceneGame,			//1	�Q�[��
	eSceneExplanation,	//2	����
	eSceneResult		//3���U���g
};

//�}�E�X�̍\����
struct t_Mouse
{
	POINT cur;			//�}�E�X�J�[�\�����W
	POINT clickPoint;	//�N���b�N�������W
	bool clickFlg;		//click�t���O
};

class Scene
{
private:

	//�v���C���[
	CPlayer m_player;
	
	//�}�b�v
	CMap m_map;

	//�G
	CEnemy m_enemy;
	
	//�A�C�e��
	CItem m_item;

	//UI
	CUI m_ui;

	//�G�t�F�N�g
	CEffect m_effect;

	//���b�Z�[�W
	CMessage m_message;


	//�e�N�X�`���֘A
	//�v���C���[
	KdTexture m_playerTex;
	KdTexture m_bulletTex;
	KdTexture m_bombTex;
	KdTexture m_blastTex;

	//�G	
	KdTexture m_samuraiTex;
	KdTexture m_archerTex;
	KdTexture m_arrowTex;
	KdTexture m_GiantTex;
	KdTexture m_bossTex;
	KdTexture m_bossSwordTex;
	
	//�}�b�v
	KdTexture m_mapTex;

	//�A�C�e��
	KdTexture m_ItemBombTex_t;
	KdTexture m_ItemBombTex_f;
	KdTexture m_ItemKeyTex;
	KdTexture m_ItemHealthTex;
	KdTexture m_ItemMinoTex;

	//UI
	KdTexture m_backTex;
	KdTexture m_rframeTex;
	KdTexture m_lframeTex;
	KdTexture m_HPTex;
	KdTexture m_HPbarTex;
	KdTexture m_HideTex;
	KdTexture m_HidebarTex;
	KdTexture m_katanaTex;
	KdTexture m_shurikenTex;
	KdTexture m_iconBombTex;
	KdTexture m_iconMinoTex;
	KdTexture m_stackBombTex;
	KdTexture m_stackKeyTex;


	// �G�t�F�N�g
	KdTexture m_pSlashTex;
	KdTexture m_eSlashTex;
	KdTexture m_dmgTex;
	KdTexture m_darkenTex;
	KdTexture m_HealTex;

	// ���b�Z�[�W
	KdTexture m_msgTex;

	// ���̑�
	KdTexture titleTex;
	KdTexture resultTex;
	KdTexture ExpTex;


	eSceneType sceneType;	//0:�^�C�g���@1:�Q�[���{��

	//�}�E�X�\����
	t_Mouse mouse;

	//�L�[����
	int keyFlg;		//0:�����ĂȂ�1:�����Ă���
	int clickFlg;	//�}�E�X�N���b�N�t���O

	
	Math::Matrix Titlemat;
	Math::Color color;

	//�^�C�g���V�[��
	Math::Vector2 gameStartPos;			//�^�C�g��:�Q�[���X�^�[�g���W
	bool gameStartFlg;					//�^�C�g��:�Q�[���X�^�[�g�t���O
	Math::Vector2 ExplanationStartPos;	//�^�C�g��:����
	bool ExplanationStartFlg;			//�^�C�g��:����

	//�����V�[��
	Math::Vector2 TitleStartPos;		//����:�^�C�g��
	bool TitleStartFlg;					//����:�^�C�g��

	//�@���U���g�s��
	Math::Matrix Resultmat;

	std::shared_ptr<KdSoundEffect> bgm;
	std::shared_ptr<KdSoundInstance> bgmInst;

public:

	// �����ݒ�
	void Init();
	// ���
	void Release();

	// �X�V����
	void Update();
	// �`�揈��
	void Draw2D();

	// GUI����
	void ImGuiUpdate();

	//���������Z�b�g
	void Reset();

	//�G�N���X�擾
	CEnemy* GetEnemy(){ return &m_enemy; }

	//�}�b�v�N���X�擾
	CMap* GetMap(){ return &m_map; }
	
	//�v���C���[�N���X�擾
	CPlayer* GetPlayer(){ return &m_player; }
	
	//�A�C�e���N���X�擾
	CItem* GetItem() { return &m_item; }

	// �G�t�F�N�g
	CEffect* GetEffect() { return &m_effect; }

	// ���b�Z�[�W
	CMessage* GetMsg() { return &m_message; }

	//�^�C�g��
	void TitleUpdate();//�X�V
	void TitleDraw();//�`��

	//�Q�[���@
	void GameUpdate(); //�X�V
	void GameDraw();//�`��

	//�����@
	void ExplanationUpdate(); //�X�V
	void ExplanationDraw(); //�`��

	//���U���g
	void ResultUpdate();
	void ResultDraw();

	//�}�E�X���W�擾
	void GetMousePos();

private:
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;

	Scene() {}
public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()

// �_��OBB�Ƃ̍ŋߐړ_�����߂�
inline void PointToBox(const Math::Vector2& point, const Math::Vector2& obbCenterPos, const Math::Vector2& obbHalfSize, const Math::Matrix& obbMat, Math::Vector2& outNearestPos)
{
	// ���Q�l:[����]�u�Q�[���v���O���~���O�̂��߂̃��A���^�C���Փ˔���v
	Math::Vector2 d = point - obbCenterPos;
	// �{�b�N�X�̒��S�ɂ����錋�ʂ���J�n�A���̂���i�K�I�ɐi�߂�B
	outNearestPos = obbCenterPos;
	// �eOBB�̎��ɑ΂���
	for (int i = 0; i < 2; i++)
	{
		// d�����̎��ɓ��e����
		// �{�b�N�X�̒��S����d�̎��ɉ����������𓾂�
		float dist = d.Dot((Math::Vector2&)obbMat.m[i]);
		// �{�b�N�X�͈̔͂����������傫���ꍇ�A�{�b�N�X�܂ŃN�����v
		if (dist > (&obbHalfSize.x)[i]) dist = (&obbHalfSize.x)[i];
		if (dist < -(&obbHalfSize.x)[i]) dist = -(&obbHalfSize.x)[i];
		// ���[���h���W�𓾂邽�߂ɂ��̋����������ɉ����Đi�߂�
		outNearestPos += dist * (Math::Vector2&)obbMat.m[i];
	}

}


//========================
// �I�u�W�F�N�g��{�N���X
//========================
class ObjectBase
{
public:
	virtual ~ObjectBase() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual bool HitTest_Circle(const Math::Vector2& pos, float radius, Math::Vector2* hitPos) { return false; }

	virtual void DebugDraw() {}

	// ���W
	Math::Vector2	m_pos;
	float			m_z = 0;
};

//========================
// �L����
//========================
class Chara : public ObjectBase
{
public:

	void Init(KdTexture* tex, float x, float y)
	{
		m_pTex = tex;
		m_pos.x = x;
		m_pos.y = y;
	}

	// �X�V����
	virtual void Update() override
	{
		// �L�[�ړ�
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pos.x -= 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pos.x += 5.0f;

		}

	}

	// �`�揈��
	virtual void Draw() override
	{
		Math::Matrix m;
		// �L�����̍s��
		m = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);

		// �s��Z�b�g
		SHADER.m_spriteShader.SetMatrix(m);
		// �`��
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, 48, 48, &Math::Rectangle(0, 0, 48, 48), &Math::Color(1,1,1,1), Math::Vector2(0.5f, 0.5f));
	}

private:
	KdTexture*	m_pTex = nullptr;
};
