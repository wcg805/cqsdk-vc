#include "stdafx.h"

int isSendMsg = 1;
sqlite3* mpDB;

CppSQLite3DB db;
CppSQLite3Query query;

extern string strRunningDir;

Chat::Chat()
{
	init();
}

Chat::Chat(int32_t AuthCode, int64_t fromGroup, int64_t fromQQ, const char *msg)
{
	m_nAuthCode = AuthCode;
	m_nFromGroup = fromGroup;
	m_nFromQQ = fromQQ;
	m_pMsg = msg;

	init();
}

Chat::~Chat()
{
	sqlite3_close(mpDB);
}

void Chat::SetAuthCode(int32_t AuthCode)
{
	m_nAuthCode = AuthCode;
}

void Chat::SetChatSwitch(int state)
{
	m_nChatSwitch = state;
	//CHAT_SWITCH_STATE_OPEN
}

void Chat::init()
{
	string strDbPath = strRunningDir+"minho_chat.db";
	//MessageBoxA(NULL, strDbPath.c_str(), "", MB_OK);
	//sqlite3_open(strDbPath.c_str(), &mpDB);
	db.open(strDbPath.c_str());
}

int Chat::GroupMessage(int32_t AuthCode, int64_t fromGroup, int64_t fromQQ, const char *msg)
{
	string sql_create = "create table if not exists t_b_preset_message (id INTEGER PRIMARY KEY ASC AUTOINCREMENT, key_word TEXT, value_word TEXT, isdel INT DEFAULT (0));";

	char * errmsg = NULL;
	sqlite3_exec(mpDB, sql_create.c_str(), 0, 0, &errmsg );

	if(fromGroup == 194106997)
	{
		char szOutput[2] = {0};
		strncpy(szOutput, msg, 1);

		if(strcmp("#", szOutput) == 0)
		{
			//CQ_sendGroupMsg(AuthCode, fromGroup, "OK");
			char *instructionSet[4096];
			int nSetSize = 0;
			MySplit((char*)msg, "#",instructionSet, &nSetSize);

			char *order = instructionSet[0];
			if(strcmp("关闭", order) == 0)
			{
				CQ_sendGroupMsg(AuthCode, fromGroup, "再见, 再也不见!");
				isSendMsg = 0;
				return EVENT_BLOCK;
			}
			else if(strcmp("开启", order) == 0)
			{
				CQ_sendGroupMsg(AuthCode, fromGroup, "AV8D, 我回来啦!!!");
				isSendMsg = 1;
				return EVENT_BLOCK;
			}
			else if(strcmp("教学", order) == 0)
			{
				string question = instructionSet[1];
				string answer = instructionSet[2];

				char szInsertSQL[1000] = {0};
				sprintf(szInsertSQL, "INSERT INTO t_b_preset_message (key_word, value_word) VALUES('%s', '%s');", question.c_str(), answer.c_str());
				db.execDML(szInsertSQL);
				CQ_sendGroupMsg(AuthCode, fromGroup, "又学了一句!");
				return EVENT_BLOCK;
			}
		}
	}

	if (isSendMsg == 1)
	{
		char szSelectSQL[200] = {0};
		sprintf(szSelectSQL, "select value_word from t_b_preset_message where key_word='%s' and isdel=0", msg);
		query = db.execQuery(szSelectSQL);
		int sendNum = MyRand(query.numFields());
		int index = 0;
		while (!query.eof())
		{
			if (index++ == sendNum)
			{
				CQ_sendGroupMsg(AuthCode, fromGroup, query.fieldValue(0));
				return EVENT_BLOCK;
			}
			query.nextRow();
		}

		CQ_getLoginNick(AuthCode);
		const char * szInfo = CQ_getGroupMemberInfoV2(AuthCode, fromGroup, fromQQ, FALSE);
		return EVENT_IGNORE;
	}
	return EVENT_IGNORE;
}

