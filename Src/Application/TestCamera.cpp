#include "main.h"

#include "TestCamera.h"

void TestCamera::Update()
{
	//============================
	// �r���[�s��
	//============================
	POINT nowPos;
	GetCursorPos(&nowPos);

	// Shift�ő傫��
	float ratio = 1.0f;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
		ratio = 5;
	}
	// Control�ŏ�����
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
		ratio = 0.2f;
	}

	// �}�E�X�̉E�{�^��
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		// �}�E�X�̑O�񂩂�̈ړ���
		float deltaX = (float)(nowPos.x - m_PrevMousePos.x) * 0.5f * ratio;
		float deltaY = (float)(nowPos.y - m_PrevMousePos.y) * 0.5f * ratio;

		// �J������] Y����]
		Math::Matrix mR;
		mR = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deltaX));
		m_mCam *= mR;

		// �J������] X����]

		m_mCam._31;
		mR = Math::Matrix::CreateFromAxisAngle(m_mCam.Right(), DirectX::XMConvertToRadians(deltaY));
		m_mCam *= mR;
	}

	// �z�C�[���h���b�O
	if (GetAsyncKeyState(VK_MBUTTON) & 0x8000) {
		float deltaX = (float)(nowPos.x - m_PrevMousePos.x) * 0.05f * ratio;
		float deltaY = (float)(nowPos.y - m_PrevMousePos.y) * 0.05f * ratio;

		m_vCamBasePos -= m_mCam.Right() * deltaX;
		m_vCamBasePos += m_mCam.Up() * deltaY;
	}

	// �z�C�[��
	if (APP.m_window.GetMouseWheelVal()) {
		Math::Matrix mT;
		mT = Math::Matrix::CreateTranslation(0, 0, (float)APP.m_window.GetMouseWheelVal() * 0.01f * ratio);

		m_mCam = mT * m_mCam;
	}

	m_PrevMousePos = nowPos;
}

void TestCamera::SetToShader()
{
	// �J�����s�񂩂�r���[�s��֕ϊ�
	Math::Matrix mCam = m_mCam;
	mCam *= Math::Matrix::CreateTranslation(m_vCamBasePos);

	SHADER.m_cb7_Camera.Work().CamPos = mCam.Translation();
	SHADER.m_cb7_Camera.Work().mV = mCam.Invert();
	SHADER.m_cb7_Camera.Work().mP = m_mProj;

	// �J�������(�r���[�s��A�ˉe�s��)���A�e�V�F�[�_�̒萔�o�b�t�@�փZ�b�g
	SHADER.m_cb7_Camera.Write();
}
