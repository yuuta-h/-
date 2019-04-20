#include "audio.h"
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
Audio::Audio()
{
	xactEngine = NULL;
	waveBank = NULL;
	soundBank = NULL;
	cueI = 0;
	mapWaveBank = NULL;
	soundBankData = NULL;

	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr))
	{
		coInitialized = true;
	}
	else
	{
		coInitialized = false;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Audio::~Audio()
{
	// XACT���V���b�g�_�E��
	if (xactEngine)
	{
		// XACT�G���W�����V���b�g�_�E�����A���\�[�X�����
		xactEngine->ShutDown();
		xactEngine->Release();
	}

	if (soundBankData)
	{
		delete[] soundBankData;
	}
	soundBankData = NULL;

	// xactEngine->ShutDown()����߂�����A�������}�b�v�h�t�@�C�������
	if (mapWaveBank)
	{
		UnmapViewOfFile(mapWaveBank);
	}
	mapWaveBank = NULL;

	// CoInitializeEx�����������ꍇ
	if (coInitialized)
	{
		CoUninitialize();
	}

}

//=============================================================================
// ������
// ���̊֐��͎��̏������s��
//		1.xactEngine->Initialize�ɂ���ČĂяo���ꂽXACT��������
//		2.�g�p����XACT�E�F�C�u�o���N���쐬����
//		3.�g�p����XACT�T�E���h�o���N���쐬����
//		4.�Q�[�����g�p����XACT�L���[�ɃC���f�b�N�X���i�[����
//=============================================================================
HRESULT Audio::initialize()
{
	HRESULT result = E_FAIL;
	HANDLE hFile;
	DWORD fileSize;
	DWORD bytesRead;
	HANDLE hMapFile;

	if (coInitialized == false)
	{
		return E_FAIL;
	}

	result = XACT3CreateEngine(0, &xactEngine);
	if (FAILED(result) || xactEngine == NULL)
	{
		return E_FAIL;
	}

	// XACT�����^�C�������������A�쐬����
	XACT_RUNTIME_PARAMETERS xactParams = { 0 };
	xactParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	result = xactEngine->Initialize(&xactParams);
	if (FAILED(result))
	{
		return result;
	}

	// �������}�b�v�g�t�@�C��IO���g�p���� "�C��������"�� XACT�E�F�C�u�o���N�t�@�C�����쐬
	result = E_FAIL; // ���s���f�t�H���g�Ƃ��āA�������ɒu��������
	hFile = CreateFile(WAVE_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
			if (hMapFile)
			{
				mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				if (mapWaveBank)
				{
					result = xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank);
				}
				CloseHandle(hMapFile);	// mapWaveBank���t�@�C���ւ̃n���h����ێ�����̂ł��̕s�v�ȃn���h�������
			}
		}
		CloseHandle(hFile);		// mapWaveBank�͂��t�@�C���ւ̃n���h����ێ�����̂ł��̕s�v�ȃn���h�������
	}

	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}

	// XACT�ō쐬�����T�E���h�o���N�t�@�C����ǂݍ���ŗ\��
	result = E_FAIL;	// ���s���f�t�H���g�Ƃ��āA�������ɒu��������
	hFile = CreateFile(SOUND_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			soundBankData = new BYTE[fileSize];		// �T�E���h�o���N�̃��������m�ۂ���
			if (soundBankData)
			{
				if (0 != ReadFile(hFile, soundBankData, fileSize, &bytesRead, NULL))
				{
					result = xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank);
				}
			}
		}
		CloseHandle(hFile);
	}
	if (FAILED(result))
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	return S_OK;
}

//=============================================================================
// �����I�ȃT�E���h�G���W���^�X�N�����s
//=============================================================================
void Audio::run()
{
	if (xactEngine == NULL)
	{
		return;
	}
	xactEngine->DoWork();
}

//=============================================================================
// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N�炩��Đ�
// �L���[�����݂��Ȃ��ꍇ�́A�T�E���h���Đ�����Ȃ������ŁA�G���[�͔������Ȃ�
//=============================================================================
void Audio::playCue(const char cue[])
{
	if (soundBank == NULL)
	{
		return;
	}
	// �T�E���h�o���N����L���[�C���f�b�N�X���擾
	cueI = soundBank->GetCueIndex(cue);	
	soundBank->Play(cueI, 0, 0, NULL);
}

//=============================================================================
// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N�Œ�~
// �L���[�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
//=============================================================================
void Audio::stopCue(const char cue[])
{
	if (soundBank == NULL)
	{
		return;
	}
	cueI = soundBank->GetCueIndex(cue);
	soundBank->Stop(cueI, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
}

