#pragma once

class CMessage
{
public:
	CMessage();
	~CMessage();

	void Init();
	void Update();
	void Draw();
	
	bool GetAlive() { return m_bAlive; }
	Math::Vector2 GetPos(){ return m_pos; }
	int GetMsgNum() { return m_msg; }

	void SetTexture(KdTexture* apTexture);
	void SetAlive();
	void SetMessage(Math::Vector2 pos, int number);
	void SetScrollPos(Math::Vector2 scrPos);

private:
	KdTexture* m_pTexture;		//�摜
	Math::Matrix m_mat;			//�s��
	Math::Vector2 m_pos;		//���W
	bool m_bAlive;				//�����t���O
	int m_msg;					//���b�Z�[�W�̎�ޔ���
	Math::Vector2	 m_scrollPos;	//�X�N���[���ʎ擾�p
};

