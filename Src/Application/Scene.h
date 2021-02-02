#pragma once
#include "CPlayer.h"
#include "CEnemy.h"
#include "CMap.h"
#include"CItem.h"
#include"UI.h"
#include"CEffect.h"
#include"CMessage.h"

//シーンの種類
enum eSceneType
{
	eSceneTitle,		//0	Title
	eSceneGame,			//1	ゲーム
	eSceneExplanation,	//2	説明
	eSceneResult		//3リザルト
};

//マウスの構造体
struct t_Mouse
{
	POINT cur;			//マウスカーソル座標
	POINT clickPoint;	//クリックした座標
	bool clickFlg;		//clickフラグ
};

class Scene
{
private:

	//プレイヤー
	CPlayer m_player;
	
	//マップ
	CMap m_map;

	//敵
	CEnemy m_enemy;
	
	//アイテム
	CItem m_item;

	//UI
	CUI m_ui;

	//エフェクト
	CEffect m_effect;

	//メッセージ
	CMessage m_message;


	//テクスチャ関連
	//プレイヤー
	KdTexture m_playerTex;
	KdTexture m_bulletTex;
	KdTexture m_bombTex;
	KdTexture m_blastTex;

	//敵	
	KdTexture m_samuraiTex;
	KdTexture m_archerTex;
	KdTexture m_arrowTex;
	KdTexture m_GiantTex;
	KdTexture m_bossTex;
	KdTexture m_bossSwordTex;
	
	//マップ
	KdTexture m_mapTex;

	//アイテム
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


	// エフェクト
	KdTexture m_pSlashTex;
	KdTexture m_eSlashTex;
	KdTexture m_dmgTex;
	KdTexture m_darkenTex;
	KdTexture m_HealTex;

	// メッセージ
	KdTexture m_msgTex;

	// その他
	KdTexture titleTex;
	KdTexture resultTex;
	KdTexture ExpTex;


	eSceneType sceneType;	//0:タイトル　1:ゲーム本編

	//マウス構造体
	t_Mouse mouse;

	//キー制御
	int keyFlg;		//0:押してない1:押している
	int clickFlg;	//マウスクリックフラグ

	
	Math::Matrix Titlemat;
	Math::Color color;

	//タイトルシーン
	Math::Vector2 gameStartPos;			//タイトル:ゲームスタート座標
	bool gameStartFlg;					//タイトル:ゲームスタートフラグ
	Math::Vector2 ExplanationStartPos;	//タイトル:説明
	bool ExplanationStartFlg;			//タイトル:説明

	//説明シーン
	Math::Vector2 TitleStartPos;		//説明:タイトル
	bool TitleStartFlg;					//説明:タイトル

	//　リザルト行列
	Math::Matrix Resultmat;

	std::shared_ptr<KdSoundEffect> bgm;
	std::shared_ptr<KdSoundInstance> bgmInst;

public:

	// 初期設定
	void Init();
	// 解放
	void Release();

	// 更新処理
	void Update();
	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	//初期化リセット
	void Reset();

	//敵クラス取得
	CEnemy* GetEnemy(){ return &m_enemy; }

	//マップクラス取得
	CMap* GetMap(){ return &m_map; }
	
	//プレイヤークラス取得
	CPlayer* GetPlayer(){ return &m_player; }
	
	//アイテムクラス取得
	CItem* GetItem() { return &m_item; }

	// エフェクト
	CEffect* GetEffect() { return &m_effect; }

	// メッセージ
	CMessage* GetMsg() { return &m_message; }

	//タイトル
	void TitleUpdate();//更新
	void TitleDraw();//描画

	//ゲーム　
	void GameUpdate(); //更新
	void GameDraw();//描画

	//説明　
	void ExplanationUpdate(); //更新
	void ExplanationDraw(); //描画

	//リザルト
	void ResultUpdate();
	void ResultDraw();

	//マウス座標取得
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

// 点とOBBとの最近接点を求める
inline void PointToBox(const Math::Vector2& point, const Math::Vector2& obbCenterPos, const Math::Vector2& obbHalfSize, const Math::Matrix& obbMat, Math::Vector2& outNearestPos)
{
	// ※参考:[書籍]「ゲームプログラミングのためのリアルタイム衝突判定」
	Math::Vector2 d = point - obbCenterPos;
	// ボックスの中心における結果から開始、そのから段階的に進める。
	outNearestPos = obbCenterPos;
	// 各OBBの軸に対して
	for (int i = 0; i < 2; i++)
	{
		// dをその軸に投影して
		// ボックスの中心からdの軸に沿った距離を得る
		float dist = d.Dot((Math::Vector2&)obbMat.m[i]);
		// ボックスの範囲よりも距離が大きい場合、ボックスまでクランプ
		if (dist > (&obbHalfSize.x)[i]) dist = (&obbHalfSize.x)[i];
		if (dist < -(&obbHalfSize.x)[i]) dist = -(&obbHalfSize.x)[i];
		// ワールド座標を得るためにその距離だけ軸に沿って進める
		outNearestPos += dist * (Math::Vector2&)obbMat.m[i];
	}

}


//========================
// オブジェクト基本クラス
//========================
class ObjectBase
{
public:
	virtual ~ObjectBase() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual bool HitTest_Circle(const Math::Vector2& pos, float radius, Math::Vector2* hitPos) { return false; }

	virtual void DebugDraw() {}

	// 座標
	Math::Vector2	m_pos;
	float			m_z = 0;
};

//========================
// キャラ
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

	// 更新処理
	virtual void Update() override
	{
		// キー移動
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pos.x -= 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pos.x += 5.0f;

		}

	}

	// 描画処理
	virtual void Draw() override
	{
		Math::Matrix m;
		// キャラの行列
		m = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);

		// 行列セット
		SHADER.m_spriteShader.SetMatrix(m);
		// 描画
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, 48, 48, &Math::Rectangle(0, 0, 48, 48), &Math::Color(1,1,1,1), Math::Vector2(0.5f, 0.5f));
	}

private:
	KdTexture*	m_pTex = nullptr;
};
