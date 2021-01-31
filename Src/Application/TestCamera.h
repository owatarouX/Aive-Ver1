#pragma once

//======================================================
//
// �}�E�X�ł��肮�蓮������J����
//
//======================================================
class TestCamera {
public:

	// 
	TestCamera()
	{
		m_mCam = Math::Matrix::CreateTranslation(0, 0, -5);
		m_mCam *= Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
		m_mCam *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(20));

		//============================
		// �ˉe�s��
		//============================
		D3D11_TEXTURE2D_DESC desc;
		KdTexture::GetTextureInfo(D3D.GetBackBuffer(), desc);
		m_mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)desc.Width / desc.Height, 0.01f, 1000);
	}

	// ����
	void Update();

	// �r���[�E�ˉe�s����Z�b�g
	void SetToShader();


	Math::Vector3		m_vCamBasePos;

	Math::Matrix		m_mCam;
	Math::Matrix		m_mProj;

private:

	POINT		m_PrevMousePos = { 0, 0 };
};
