#pragma once

//�}�b�v�V�[��
enum eMapData
{
	OutSide,	//��O
	OneFloor,	//1�K�w
	TwoFloor,	//2�K�w
	ThreeFloor,	//3�K�w
	FourFloor,	//4�K�w
	BossFloor	//�{�X����
};

class Scene;

constexpr int MAP_CHIP_H = 40;					//�c�T�C�Y
constexpr int MAP_CHIP_W = 40;					//���T�C�Y

class CMap
{
public:
	CMap();
	~CMap();

	void Init();
	void Update();
	void Draw();
	void SetTexture(KdTexture* apTexture);
	float (*GetPosX())[MAP_CHIP_W];		//X���W�擾
	float (*GetPosY())[MAP_CHIP_W];		//Y���W�擾
	int (*GetChipData())[MAP_CHIP_W];	//�}�b�v�f�[�^�擾
	Math::Vector2 GetscrollPos();		//�X�N���[���ʎ擾
	int GetMapData() { return m_mapData; }	//�}�b�v�̏�ʏ��擾
	bool GetMapSwitchFlg() { return m_bMapSwitch; }	//�}�b�v�؂�ւ��t���O�擾
		
	void SetOwner(Scene* apOwner);		//�I�[�i�[�ݒ�
	void SetMapData();					//�}�b�v�f�[�^�̕ύX
	void SetMapSwitchFlg(bool flg);		//�}�b�v�؂�ւ��t���O���]
	void SetUnlock();					//���J��
	void SetLock();						//�J�M��

	void LoadMapFile();		//�}�b�v�t�@�C���ǂݍ���

private:

	KdTexture*			m_pTexture;								//�摜(�e�N�X�`��)
	int					m_ChipData[MAP_CHIP_H][MAP_CHIP_W];		//�}�b�v�f�[�^
	float				m_chipX[MAP_CHIP_H][MAP_CHIP_W];		//���W
	float				m_chipY[MAP_CHIP_H][MAP_CHIP_W];		//���W
	Math::Matrix		m_mat[MAP_CHIP_H][MAP_CHIP_W];			//�s��
	Math::Vector2		m_scroll;								//�X�N���[����

	eMapData			m_mapData;			//�}�b�v
	bool				m_bMapSwitch;		//�}�b�v�؂�ւ��t���O
	int gimmickcount;
	Scene* m_pOwner;		//�I�[�i�[�擾�p
	bool			    m_bGimmick;         //�M�~�b�Nflg

	void Scroll();			//�X�N���[������
	void ScrollRemit();		//��ʒ[���~�b�g
};
