#include"CHidden.h"
#include"Utility.h"

CHidden::CHidden()
	:m_bHidden(false)
	, m_hiddenCnt(0)
{
}

CHidden::~CHidden()
{
}

// 初期化
void CHidden::Init()
{
	m_bHidden = false;
	m_hiddenCnt = 0;
}

// 更新
void CHidden::Updata()
{
	if (m_bHidden)
	{
		m_hiddenCnt++;
		// 使用期限
		if (m_hiddenCnt > HIDDEN_CNT_MAX)
		{
			m_bHidden = false;
		}
	}
	else
	{
		m_hiddenCnt--;
		if (m_hiddenCnt <= 0)
		{
			m_hiddenCnt = 0;
		}
	}
}

// フラグ状態変更
void CHidden::bSetHidden()
{
	m_bHidden = false;
}

// 隠れ身発動
void CHidden::Hidden()
{
	// フラグ状態切り替え
	if (!m_bHidden) m_bHidden = true;
	else m_bHidden = false;
}
