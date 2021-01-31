#pragma once

#include"CItem_Bomb.h"
#include"CItem_Key.h"
#include"CItem_Health.h"
class Scene;

// 爆弾配置数
constexpr int BOMB_SETMAX = 3;
// 鍵設置数
constexpr int KEY_SETMAX = 3;
// 回復設置上限
constexpr int HEALTH_SETMAX = 3;

class CItem
{
public:
	CItem();
	~CItem();

	void Init();
	void Update();
	void Draw();

	void SetOwner(Scene* apOwner);

	//アイテム：爆弾
	void SetBomb();
	//アイテム：鍵
	void SetKey();

	CItem_Bomb* GetBombItem() { return m_bombList; }	//爆弾リスト取得
	CItem_Key* GetKeyItem() { return m_keyList; }		//鍵リスト取得
	CItem_Health* GetHealehItem() { return m_healthList; }	// 回復リスト取得

	/* テクスチャ設定 */
	// 爆弾
	void SetTexBomb_t(KdTexture* apTexture);
	void SetTexBomb_f(KdTexture* apTexture);
	// 鍵
	void SetTexKey(KdTexture* apTexture);
	// 回復
	void SetHealthTex(KdTexture* apTexture);

	bool DropHealth(bool bDrop, Math::Vector2 pos);	// アイテムドロップ処理
	bool DropKey(bool bDrop, Math::Vector2 pos);	// アイテムドロップ処理

private:


	Scene* m_pOwner;			//オーナー取得用

	CItem_Bomb		m_bombList[BOMB_SETMAX];		// 爆弾クラス取得
	CItem_Key		m_keyList[KEY_SETMAX];			// 鍵クラス取得
	CItem_Health	m_healthList[HEALTH_SETMAX];	// 回復クラス取得

};

