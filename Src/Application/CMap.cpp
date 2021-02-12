#include"CMap.h"
#include"Scene.h"
#include"Utility.h"

CMap::CMap()
	:m_pTexture(nullptr)	//�摜(�e�N�X�`��)
	, m_ChipData()			//�}�b�v�f�[�^
	, m_chipX()				//���WX
	, m_chipY()				//���WY
	, m_mat()				//�s��
	, m_scroll(0,0)			//�X�N���[����
	, m_mapData(OutSide)
	, m_bMapSwitch(false)	//�}�b�v�؂�ւ��t���O
	, m_pOwner(nullptr)
	, m_bGimmick(false)
{
}

CMap::~CMap()
{
}

//������
void CMap::Init()
{
	m_mapData = OutSide;
	m_bMapSwitch = false;
	m_bGimmick = false;
	//�}�b�v��񃍁[�h
	LoadMapFile();

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			m_chipX[h][w] = (64.0f * w) - 640;
			m_chipY[h][w] = (-64.0f * h) + 360;
		}
	}
}

//�X�V
void CMap::Update()
{
	//�}�b�v�X�V
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			//�X�N���[������
			Scroll();

			//��ʒ[�̃��~�b�g��`
			ScrollRemit();

		}
	}
	
	// �f�o�b�O
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) SetUnlock();
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) SetLock();

	const int GMAX = 60;
	gimmickcount++;
	if (gimmickcount > GMAX)
	{
		gimmickcount = GMAX;
	}

	if (gimmickcount >= GMAX)
	{
		m_bGimmick = !m_bGimmick;

		gimmickcount = 0;
	}

	if (m_bGimmick == false)
	{
		switch (m_mapData)
		{
		case OutSide:
			break;
		case OneFloor:	
			break;
		case TwoFloor:
			m_ChipData[21][33] = 95;
			m_ChipData[22][33] = 95;
			m_ChipData[21][34] = 95;
			m_ChipData[22][34] = 95;
			m_ChipData[21][35] = 95;
			m_ChipData[22][35] = 95;
			m_ChipData[21][36] = 95;
			m_ChipData[22][36] = 95;
			m_ChipData[21][37] = 95;
			m_ChipData[22][37] = 95;
			m_ChipData[21][38] = 95;
			m_ChipData[22][38] = 95;

			m_ChipData[25][33] = 101;
			m_ChipData[26][33] = 101;
			m_ChipData[25][34] = 101;
			m_ChipData[26][34] = 101;
			m_ChipData[25][35] = 101;
			m_ChipData[26][35] = 101;
			m_ChipData[25][36] = 101;
			m_ChipData[26][36] = 101;
			m_ChipData[25][37] = 101;
			m_ChipData[26][37] = 101;
			m_ChipData[25][38] = 101;
			m_ChipData[26][38] = 101;

			m_ChipData[30][33] = 95;
			m_ChipData[29][33] = 95;
			m_ChipData[30][34] = 95;
			m_ChipData[29][34] = 95;
			m_ChipData[30][35] = 95;
			m_ChipData[29][35] = 95;
			m_ChipData[30][36] = 95;
			m_ChipData[29][36] = 95;
			m_ChipData[30][37] = 95;
			m_ChipData[29][37] = 95;
			m_ChipData[30][38] = 95;
			m_ChipData[29][38] = 95;

			m_ChipData[32][31] = 101;
			m_ChipData[32][32] = 101;
			m_ChipData[33][31] = 101;
			m_ChipData[33][32] = 101;
			m_ChipData[34][31] = 101;
			m_ChipData[34][32] = 101;
			m_ChipData[35][31] = 101;
			m_ChipData[35][32] = 101;
			m_ChipData[36][31] = 101;
			m_ChipData[36][32] = 101;
			m_ChipData[37][31] = 101;
			m_ChipData[37][32] = 101;

			m_ChipData[32][27] = 95;
			m_ChipData[32][28] = 95;
			m_ChipData[33][27] = 95;
			m_ChipData[33][28] = 95;
			m_ChipData[34][27] = 95;
			m_ChipData[34][28] = 95;
			m_ChipData[35][27] = 95;
			m_ChipData[35][28] = 95;
			m_ChipData[36][27] = 95;
			m_ChipData[36][28] = 95;
			m_ChipData[37][27] = 95;
			m_ChipData[37][28] = 95;

			m_ChipData[32][23] = 101;
			m_ChipData[32][24] = 101;
			m_ChipData[33][23] = 101;
			m_ChipData[33][24] = 101;
			m_ChipData[34][23] = 101;
			m_ChipData[34][24] = 101;
			m_ChipData[35][23] = 101;
			m_ChipData[35][24] = 101;
			m_ChipData[36][23] = 101;
			m_ChipData[36][24] = 101;
			m_ChipData[37][23] = 101;
			m_ChipData[37][24] = 101;

			break;
		case ThreeFloor:
			break;
		case BossFloor:
			break;
		default:
			break;
		}
	}
	else if (m_bGimmick == true)
	{
		switch (m_mapData)
		{
		case OutSide:
			break;
		case OneFloor:
			break;
		case TwoFloor:
			m_ChipData[21][33] = 101;
			m_ChipData[22][33] = 101;
			m_ChipData[21][34] = 101;
			m_ChipData[22][34] = 101;
			m_ChipData[21][35] = 101;
			m_ChipData[22][35] = 101;
			m_ChipData[21][36] = 101;
			m_ChipData[22][36] = 101;
			m_ChipData[21][37] = 101;
			m_ChipData[22][37] = 101;
			m_ChipData[21][38] = 101;
			m_ChipData[22][38] = 101;

			m_ChipData[25][33] = 95;
			m_ChipData[26][33] = 95;
			m_ChipData[25][34] = 95;
			m_ChipData[26][34] = 95;
			m_ChipData[25][35] = 95;
			m_ChipData[26][35] = 95;
			m_ChipData[25][36] = 95;
			m_ChipData[26][36] = 95;
			m_ChipData[25][37] = 95;
			m_ChipData[26][37] = 95;
			m_ChipData[25][38] = 95;
			m_ChipData[26][38] = 95;

			m_ChipData[30][33] = 101;
			m_ChipData[29][33] = 101;
			m_ChipData[30][34] = 101;
			m_ChipData[29][34] = 101;
			m_ChipData[30][35] = 101;
			m_ChipData[29][35] = 101;
			m_ChipData[30][36] = 101;
			m_ChipData[29][36] = 101;
			m_ChipData[30][37] = 101;
			m_ChipData[29][37] = 101;
			m_ChipData[30][38] = 101;
			m_ChipData[29][38] = 101;

			m_ChipData[32][31] = 95;
			m_ChipData[32][32] = 95;
			m_ChipData[33][31] = 95;
			m_ChipData[33][32] = 95;
			m_ChipData[34][31] = 95;
			m_ChipData[34][32] = 95;
			m_ChipData[35][31] = 95;
			m_ChipData[35][32] = 95;
			m_ChipData[36][31] = 95;
			m_ChipData[36][32] = 95;
			m_ChipData[37][31] = 95;
			m_ChipData[37][32] = 95;

			m_ChipData[32][27] = 101;
			m_ChipData[32][28] = 101;
			m_ChipData[33][27] = 101;
			m_ChipData[33][28] = 101;
			m_ChipData[34][27] = 101;
			m_ChipData[34][28] = 101;
			m_ChipData[35][27] = 101;
			m_ChipData[35][28] = 101;
			m_ChipData[36][27] = 101;
			m_ChipData[36][28] = 101;
			m_ChipData[37][27] = 101;
			m_ChipData[37][28] = 101;

			m_ChipData[32][23] = 95;
			m_ChipData[32][24] = 95;
			m_ChipData[33][23] = 95;
			m_ChipData[33][24] = 95;
			m_ChipData[34][23] = 95;
			m_ChipData[34][24] = 95;
			m_ChipData[35][23] = 95;
			m_ChipData[35][24] = 95;
			m_ChipData[36][23] = 95;
			m_ChipData[36][24] = 95;
			m_ChipData[37][23] = 95;
			m_ChipData[37][24] = 95;

			break;
		case ThreeFloor:
			break;
		case BossFloor:
			break;
		default:
			break;
		}
	}

	//�s��쐬
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			m_mat[h][w] = DirectX::XMMatrixTranslation(
				m_chipX[h][w] - m_scroll.x, m_chipY[h][w] - m_scroll.y, 0.0f);
		}
	}
}

//�`��
void CMap::Draw()
{
	Math::Rectangle chipRect;

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			if (m_ChipData[h][w] == 0)
			{
				chipRect = { 0,0,64,64 };
			}
			else if (m_ChipData[h][w] == 1)
			{
				chipRect = { 64,0,64,64 };
			}
			else if (m_ChipData[h][w] == 2)
			{
				chipRect = { 128,0,64,64 };
			}
			else if (m_ChipData[h][w] == 3)
			{
				chipRect = { 192,0,64,64 };
			}
			else if (m_ChipData[h][w] == 4)
			{
				chipRect = { 256,0,64,64 };
			}
			else if (m_ChipData[h][w] == 5)
			{
				chipRect = { 320,0,64,64 };
			}
			else if (m_ChipData[h][w] == 7)
			{
				chipRect = { 384,0,64,64 };
			}
			else if (m_ChipData[h][w] == 6)
			{
				chipRect = { 448 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 9)
			{
				chipRect = { 512 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 8)
			{
				chipRect = { 576,0,64,64 };
			}
			else if (m_ChipData[h][w] == 10)
			{
				chipRect = { 0 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 11)
			{
				chipRect = { 64,64,64,64 };
			}
			else if (m_ChipData[h][w] == 12)
			{
				chipRect = { 128,64,64,64 };
			}
			else if (m_ChipData[h][w] == 13)
			{
				chipRect = { 192,64,64,64 };
			}
			else if (m_ChipData[h][w] == 14)
			{
				chipRect = { 256,64,64,64 };
			}
			else if (m_ChipData[h][w] == 15)
			{
				chipRect = { 320,64,64,64 };
			}
			else if (m_ChipData[h][w] == 16)
			{
				chipRect = { 384,64,64,64 };
			}
			else if (m_ChipData[h][w] == 17)
			{
				chipRect = { 448 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 18)
			{
				chipRect = { 512 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 19)
			{
				chipRect = { 576,64,64,64 };
			}
			else if (m_ChipData[h][w] == 20)
			{
				chipRect = { 640 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 21)
			{
				chipRect = { 0 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 22)
			{
				chipRect = { 64,128,64,64 };
			}
			else if (m_ChipData[h][w] == 23)
			{
				chipRect = { 128,128,64,64 };
			}
			else if (m_ChipData[h][w] == 24)
			{
				chipRect = { 192,128,64,64 };
			}
			else if (m_ChipData[h][w] == 25)
			{
				chipRect = { 256,128,64,64 };
			}
			else if (m_ChipData[h][w] == 26)
			{
				chipRect = { 320,128,64,64 };
			}
			else if (m_ChipData[h][w] == 27)
			{
				chipRect = { 384,128,64,64 };
			}
			else if (m_ChipData[h][w] == 28)
			{
				chipRect = { 448 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 29)
			{
				chipRect = { 512 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 30)
			{
				chipRect = { 576,128,64,64 };
			}
			else if (m_ChipData[h][w] == 31)
			{
				chipRect = { 0 ,192,64,64 };
			}
			else if (m_ChipData[h][w] == 32)
			{
				chipRect = { 64,192,64,64 };
			}
			else if (m_ChipData[h][w] == 33)
			{
				chipRect = { 128,192,64,64 };
			}
			else if (m_ChipData[h][w] == 34)
			{
				chipRect = { 192,192,64,64 };
			}
			else if (m_ChipData[h][w] == 35)
			{
				chipRect = { 256,192,64,64 };
			}
			else if (m_ChipData[h][w] == 36)
			{
				chipRect = { 320,192,64,64 };
			}
			else if (m_ChipData[h][w] == 37)
			{
				chipRect = { 384,192,64,64 };
			}
			else if (m_ChipData[h][w] == 38)
			{
				chipRect = { 448 ,192,64,64 };
			}
			else if (m_ChipData[h][w] == 39)
			{
				chipRect = { 512 ,192,64,64 };
			}
			else if (m_ChipData[h][w] == 40)
			{
				chipRect = { 576,192,64,64 };
			}
			else if (m_ChipData[h][w] == 41)
			{
				chipRect = { 0 ,256,64,64 };
			}
			else if (m_ChipData[h][w] == 42)
			{
				chipRect = { 64,256,64,64 };
			}
			else if (m_ChipData[h][w] == 43)
			{
				chipRect = { 128,256,64,64 };
			}
			else if (m_ChipData[h][w] == 44)
			{
				chipRect = { 192,256,64,64 };
			}
			else if (m_ChipData[h][w] == 45)
			{
				chipRect = { 256,256,64,64 };
			}
			else if (m_ChipData[h][w] == 46)
			{
				chipRect = { 320,256,64,64 };
			}
			else if (m_ChipData[h][w] == 47)
			{
				chipRect = { 384,256,64,64 };
			}
			else if (m_ChipData[h][w] == 48)
			{
				chipRect = { 448 ,256,64,64 };
			}
			else if (m_ChipData[h][w] == 49)
			{
				chipRect = { 128,0,64,64 };
			}
			else if (m_ChipData[h][w] == 51)
			{
				chipRect = { 448 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 52)
			{
				chipRect = { 384,0,64,64 };
			}
			else if (m_ChipData[h][w] == 53)
			{
				chipRect = { 320,0,64,64 };
			}
			else if (m_ChipData[h][w] == 54)
			{
				chipRect = { 256,0,64,64 };
			}
			else if (m_ChipData[h][w] == 55)
			{
				chipRect = { 576,0,64,64 };
			}
			else if (m_ChipData[h][w] == 56)
			{
				chipRect = { 512 ,0,64,64 };
			}
			else if (m_ChipData[h][w] == 57)
			{
				chipRect = { 512 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 58)
			{
				chipRect = { 576,64,64,64 };
			}
			else if (m_ChipData[h][w] == 60)
			{
				chipRect = { 0 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 61)
			{
				chipRect = { 0 ,256,64,64 };
			}
			else if (m_ChipData[h][w] == 62)
			{
				chipRect = { 128,256,64,64 };
			}
			else if (m_ChipData[h][w] == 63)
			{
			    chipRect = { 64,256,64,64 };
			}
			else if (m_ChipData[h][w] == 64)
			{
			    chipRect = { 576,128,64,64 };
			}
			else if (m_ChipData[h][w] == 65)
			{
				chipRect = { 512 ,128,64,64 };
			}
			else if (m_ChipData[h][w] == 66)
			{
			    chipRect = { 512 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 70)
			{
				chipRect = { 64,64,64,64 };
			}
			else if (m_ChipData[h][w] == 78)
			{
				chipRect = { 256,64,64,64 };
			}
			else if (m_ChipData[h][w] == 79)
			{
				chipRect = { 320,64,64,64 };
			}
			else if (m_ChipData[h][w] >= 80 && m_ChipData[h][w] <= 83)
			{
				chipRect = { 0 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 91)
			{
				chipRect = { 0,128,64,64 };
			}
			else if (m_ChipData[h][w] == 90)
			{
				chipRect = { 64,128,64,64 };
			}
			else if (m_ChipData[h][w] == 95)
			{
			    chipRect = { 128,128,64,64 };
			}
			else if (m_ChipData[h][w] == 96)
			{
			    chipRect = { 320,128,64,64 };
			}
			else if (m_ChipData[h][w] == 97)
			{
			    chipRect = { 384,128,64,64 };
			}
			else if (m_ChipData[h][w] == 101)
			{
			    chipRect = { 192,128,64,64 };
			}
			else if (m_ChipData[h][w] == 111)
			{
			    chipRect = { 256,64,64,64 };
			}
			else if (m_ChipData[h][w] == 112)
			{
			    chipRect = { 320,64,64,64 };
			}
			else if (m_ChipData[h][w] == 113)
			{
			    chipRect = { 384,64,64,64 };
			}
			else if (m_ChipData[h][w] == 114)
			{
			    chipRect = { 448 ,64,64,64 };
			}
			else if (m_ChipData[h][w] == 115)
			{
			    chipRect = { 64,128,64,64 };
			}
			else if (m_ChipData[h][w] == 116)
			{
			    chipRect = { 256,192,64,64 };
			}
			else if (m_ChipData[h][w] == 117)
			{
			    chipRect = { 320,192,64,64 };
			}
			else if (m_ChipData[h][w] == 118)
			{
			    chipRect = { 320,256,64,64 };
			}
			else if (m_ChipData[h][w] == 119)
			{
			    chipRect = { 128,192,64,64 };
			}

			SHADER.m_spriteShader.SetMatrix(m_mat[h][w]);
			SHADER.m_spriteShader.DrawTex(m_pTexture, chipRect, 1.0f);

		}
	}
}

//�e�N�X�`���ݒ�
void CMap::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pTexture = apTexture;
}

//�}�b�vX���W�擾
float(*CMap::GetPosX())[MAP_CHIP_W]
{
	return m_chipX;
}

//�}�b�vY���W�擾
float(*CMap::GetPosY())[MAP_CHIP_W]
{
	return m_chipY;
}

//�}�b�v�f�[�^�擾
int(*CMap::GetChipData())[MAP_CHIP_W]
{
	return m_ChipData;
}

//�X�N���[���ʎ擾
Math::Vector2 CMap::GetscrollPos()
{
	return m_scroll;
}

//�I�[�i�[�ݒ�
void CMap::SetOwner(Scene* apOwner)
{
	if (apOwner == nullptr) return;

	m_pOwner = apOwner;
}

//�}�b�v�f�[�^�̕ύX
void CMap::SetMapData()
{
	switch (m_mapData)
	{
	case OutSide:
		m_mapData =OneFloor;
		break;
	case OneFloor:
		m_mapData = TwoFloor;
		break;
	case TwoFloor:
		m_mapData = ThreeFloor;
		break;
	case ThreeFloor:
		m_mapData = FourFloor;
		break;
	case FourFloor:
		m_mapData = BossFloor;
		break;
	}

}

//�}�b�v�؂�ւ��t���O���]
void CMap::SetMapSwitchFlg(bool flg)
{
	m_bMapSwitch = flg;
}

//���J������
void CMap::SetUnlock()
{
	const int ch = 10;
	switch (m_mapData)
	{
	case OutSide:
		break;
	case OneFloor:
		m_ChipData[19][21] = ch;
		m_ChipData[19][22] = ch;
		m_ChipData[20][21] = ch;
		m_ChipData[20][22] = ch;
		m_ChipData[5][1] = ch;
		m_ChipData[5][2] = ch;
		m_ChipData[6][1] = ch;
		m_ChipData[6][2] = ch;
		break;
	case TwoFloor:
		m_ChipData[34][1] = 19;
		m_ChipData[34][2] = 19;
		m_ChipData[35][1] = 19;
		m_ChipData[35][2] = 19;
		break;
	case ThreeFloor:
		m_ChipData[11][3] = ch;
		m_ChipData[12][3] = ch;
		m_ChipData[11][4] = ch;
		m_ChipData[12][4] = ch;
		break;
	case FourFloor:
		break;
	case BossFloor:
		break;
	default:
		break;
	}
}

// �J�M��
void CMap::SetLock()
{
	const int ch = 49;
	switch (m_mapData)
	{
	case OutSide:
		break;
	case OneFloor:
		m_ChipData[19][21] = 51;
		m_ChipData[19][22] = 52;
		m_ChipData[20][21] = 53;
		m_ChipData[20][22] = 54;
		m_ChipData[5][1] = 51;
		m_ChipData[5][2] = 52;
		m_ChipData[6][1] = 53;
		m_ChipData[6][2] = 54;
		break;
	case TwoFloor:
		m_ChipData[11][3] = 55;
		m_ChipData[12][3] = 51;
		m_ChipData[11][4] = 56;
		m_ChipData[12][4] = 52;
		break;
	case ThreeFloor:
		break;
	case FourFloor:
		break;
	case BossFloor:
		break;
	default:
		break;
	}
}

//�X�N���[������
void CMap::Scroll()
{
	//�v���C���[���W�擾
	CPlayer* player = m_pOwner->GetPlayer();
	Math::Vector2 playerPos = player->GetPos();

	//�X�N���[�����W
	m_scroll = playerPos;
}

//��ʒ[���~�b�g��`
void CMap::ScrollRemit()
{
	if (m_mapData == BossFloor)
	{
		static const float SCR_X_MIN = m_chipX[1][6] + Screen::HalfWidth;
		static const float SCR_X_MAX = m_chipX[1][32] - Screen::HalfWidth;
		static const float SCR_Y_MIN = m_chipY[31][1] + Screen::HalfHeight;
		static const float SCR_Y_MAX = m_chipY[1][1] - Screen::HalfHeight;

		//���[����
		if (m_scroll.x < SCR_X_MIN)	 m_scroll.x = SCR_X_MIN;  //�[�ɓ��B���Œ�
		//�E�[����
		else if (m_scroll.x > SCR_X_MAX)	m_scroll.x = SCR_X_MAX; //�[�ɓ��B���Œ�
		//���[����
		if (m_scroll.y < SCR_Y_MIN)		m_scroll.y = SCR_Y_MIN; //�[�ɓ��B���Œ�
		//��[����
		else if (m_scroll.y > SCR_Y_MAX)	m_scroll.y = SCR_Y_MAX; //�[�ɓ��B���Œ�
	}
	else
	{
		static const float SCR_X_MIN = m_chipX[0][0] + Screen::HalfWidth;
		static const float SCR_X_MAX = m_chipX[0][MAP_CHIP_W - 1] - Screen::HalfWidth;
		static const float SCR_Y_MIN = m_chipY[MAP_CHIP_H - 1][0] + Screen::HalfHeight;
		static const float SCR_Y_MAX = m_chipY[0][0] - Screen::HalfHeight;

		//���[����
		if (m_scroll.x < SCR_X_MIN)	 m_scroll.x = SCR_X_MIN;  //�[�ɓ��B���Œ�
		//�E�[����
		else if (m_scroll.x > SCR_X_MAX)	m_scroll.x = SCR_X_MAX; //�[�ɓ��B���Œ�
		//���[����
		if (m_scroll.y < SCR_Y_MIN)		m_scroll.y = SCR_Y_MIN; //�[�ɓ��B���Œ�
		//��[����
		else if (m_scroll.y > SCR_Y_MAX)	m_scroll.y = SCR_Y_MAX; //�[�ɓ��B���Œ�
	}
}

//�}�b�v�ǂݍ���
void CMap::LoadMapFile()
{
	FILE* fp; // �t�@�C���̏���i�[����\����

	// �t�@�C���ǂݍ���
	switch (m_mapData)
	{
	case OutSide:
		fp = fopen("Resource/MapData/Map1.csv", "r");
		break;
	case OneFloor:
		fp = fopen("Resource/MapData/Map2.csv", "r");
		break;
	case TwoFloor:
		fp = fopen("Resource/MapData/Map3.csv", "r");
		break;
	case ThreeFloor:
		fp = fopen("Resource/MapData/Map4.csv", "r");
		break;
	case FourFloor:
		fp = fopen("Resource/MapData/Map5.csv", "r");
		break;
	case BossFloor:
		fp = fopen("Resource/MapData/Boss.csv", "r");
		break;
	default:
		break;
	}

	if (fp != nullptr)
	{
		for (int h = 0; h < MAP_CHIP_H; h++)
		{
			for (int w = 0; w < MAP_CHIP_W; w++)
			{
				fscanf(fp, "%d,", &m_ChipData[h][w]);
			}
		}
		fclose(fp);
	}
}
