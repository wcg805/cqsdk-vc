#pragma once

class Chat
{
public:
	Chat();
	Chat(int32_t AuthCode, int64_t fromGroup, int64_t fromQQ, const char *msg);
	~Chat();

public:
	int32_t m_nAuthCode;
	int64_t m_nFromGroup;
	int64_t m_nFromQQ;
	const char * m_pMsg;

public:
	int m_nChatSwitch;

public:
	void SetAuthCode(int32_t AuthCode);
	void SetChatSwitch(int state);
	int GroupMessage(int32_t AuthCode, int64_t fromGroup, int64_t fromQQ, const char *msg);

public:
	//HWND     m_hWnd;
	//wchar_t  m_szWindowClass[256];

public:
	void init();
	//void MyCreateWindow();
};
