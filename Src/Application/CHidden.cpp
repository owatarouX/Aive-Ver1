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

// ������
void CHidden::Init()
{
	m_bHidden = false;
	m_hiddenCnt = 0;
}

// �X�V
void CHidden::Updata()
{
	if (m_bHidden)
	{
		m_hiddenCnt++;
		// �g�p����
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

// �t���O��ԕύX
void CHidden::bSetHidden()
{
	m_bHidden = false;
}

// �B��g����
void CHidden::Hidden()
{
	// �t���O��Ԑ؂�ւ�
	if(!m_bHidden) m_bHidden = true;
	else m_bHidden = false;
}
