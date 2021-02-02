#pragma once

#include"CBullet.h"
#include"CSword.h"
#include"CBomb.h"
#include"CHidden.h"

//クラスの前方宣言
class Scene;

enum eDirection	//向いている方向
{
	Up,
	Down,
	Left,
	Right
};

//武器セレクト
enum eClick
{
	eShuriken,	//0.手裏剣
	eSword,		//1.刀
	eBomb,		//2.爆弾
	eHidden		//3.隠れ身	
};

enum eStatus
{
	eIdle,
	eWalking,
	eAttack
};

//手裏剣の要素数
constexpr int BULLET_MAX = 2;

//爆弾の要素数
constexpr int BOMB_MAX = 5;

//プレイヤークラス
class CPlayer
{
public:

	CPlayer();	//コンストラクタ
	~CPlayer();	//デストラクタ

	//プレイヤー
	void Init();
	void ReInit(int mapData);
	void Updata();
	void UpDatePlayer(Math::Vector2 ScrollPos);
	void Draw();

	//セッター
	void SetTexture(KdTexture* apTexture);
	void SetBulletTexture(KdTexture* apTexture);
	void SetSlashTexture(KdTexture* apTexture);
	void SetBombTexture(KdTexture* apTexture);
	void SetBlastTexture(KdTexture* apTexture);
	void SetOwner(Scene* apOwner);
	void SetDamage(int dmg);	// 体力減少
	void SetHeal(int heal);		// 体力回復
	void SetHitFlg();			// ヒットフラグセット
	void SetPosX(float x);	// 座標セットX(現在座標に足し算)
	void SetPosY(float y);	// 座標セットY(現在座標に足し算)
	void SetMovevalX(float movex);	// 移動量セットX(移動量を入力)
	void SetMovevalY(float movey);	// 移動量セットY(移動量を入力)

	//ゲッター
	const bool IsAlive() { return m_bAlive; }
	const Math::Vector2 GetPos() { return m_pos; }				//プレイヤー座標取得
	const Math::Vector2 GetMove() { return m_moveVal; }			//プレイヤー移動量取得
	const int GetHp() { return m_hp; }							//体力量取得
	const int GetBombPossession() { return m_BombPossession; }	//爆弾所持数取得
	const int GetKeyPossession() { return m_KeyPossession; }	//鍵所持数取得
	const bool bGetHit() { return m_HitFlg; }					// 無敵状態取得
	const bool bGetHidden() { return m_hiddenList.bGetHidden(); }	// 隠れ身フラグ取得
	const float GetHideCnt() { return m_hiddenList.GetHiddenCnt(); }

	//キー内容取得
	const int GetR();
	const int GetL();

private:		//外部からアクセス不可

	eDirection		m_direction;	//プレイヤーの向き
	eClick			m_LClick;
	eClick			m_RClick;

	KdTexture*		 m_pTexture;	//画像(テクスチャ)
	Math::Vector2	 m_pos;			//座標
	Math::Vector2	 m_moveVal;		//移動量
	Math::Matrix	 m_mat;			//行列
	Math::Matrix	 m_transMat;	//移動行列
	Math::Matrix	 m_scaleMat;	//拡大行列
	Math::Vector2	 m_size;		//拡大サイズ
	
	bool			 m_bAlive;		//生存フラグ
	int				 m_hp;			//HP
	bool			 m_bHeal;		//HP回復ポイントフラグ
	int				 m_hpCount;		//無敵時間
	float			 m_alpha;		//画像の透明度
	bool			 m_HitFlg;		//当たり判定フラグ
	float			 m_slashCnt;	//斬撃攻撃のクールタイム
	float			 m_shurikenCnt;	//手裏剣クールタイム

	bool			 m_bRClick;	//右クリックフラグ
	bool			 m_bLClick;	//左クリックフラグ
	bool			 m_bRChange;//右武器変更フラグ
	bool			 m_bLChange;//左武器変更フラグ

	int	 m_aCnt;	//アニメーションカウント
	int m_aTimer;	//アニメーションを何fに1枚動かす
	int m_aflame;	//アニメーション枚数

	int				 m_BombPossession;		//爆弾所持数
	int				 m_KeyPossession;		//鍵所持数
	bool			 m_bMinoPossession;		//隠れ蓑所持フラグ


	void KeyOperation();	// キー操作一覧

	/* 当たり判定 */
	void HitCheckMap();			// マップ
	void HitCheckEnemy();		// 敵
	void HitCheckBomb();		// 爆弾
	void HitCheckItem();		// アイテム

	void InviTime();			//無敵時間
	eClick ChangeItem(eClick click);		//武器変更関数
	void Attack(bool flg, eClick click);
	void SetShuriken();		//手裏剣攻撃
	void SetSword();		//刀攻撃
	void SetBomb();			//爆弾攻撃
	void SetHidden();		//隠れ身 

	Scene*			 m_pOwner;			//オーナー取得用
	CBullet m_bulletList[BULLET_MAX];	//手裏剣クラス取得
	CSword  m_swordList;				//斬撃クラス取得
	CBomb  m_bombList;					//爆弾クラス取得
	CHidden m_hiddenList;				//隠れ身クラス取得

	//音
	std::shared_ptr<KdSoundEffect> katanase;
	std::shared_ptr<KdSoundInstance> katanaseInst;

	std::shared_ptr<KdSoundEffect> shurikense;
	std::shared_ptr<KdSoundInstance> shurikenseInst;

	std::shared_ptr<KdSoundEffect> hitse;
	std::shared_ptr<KdSoundInstance> hitseInst;

	int Animation(int cnt, const int xtex);
	std::shared_ptr<KdSoundInstance> Sound_Loading(std::shared_ptr<KdSoundEffect> se, const std::string &seName);
};