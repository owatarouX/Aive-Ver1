#pragma once

constexpr int HIDDEN_CNT_MAX = 300;		// �B��g��Ԏ���

class CHidden
{
public:
	CHidden();
	~CHidden();

	void Init();
	void Updata();

	const bool bGetHidden() { return m_bHidden; }		//�t���O��Ԏ擾
	const int GetHiddenCnt() { return m_hiddenCnt; }	//�J�E���g�擾
	
	void bSetHidden();		// �t���O��ԕύX

	void Hidden();	// �B��g

private:
	Math::Matrix	 m_mat;			//�s��
	bool			 m_bHidden;		//�B��g��ԃt���O
	int				 m_hiddenCnt;	//�B��g��������
};
