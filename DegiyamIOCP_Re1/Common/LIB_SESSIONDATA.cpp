
#include "LIB_SESSIONDATA.h"

using namespace COMMONLIB;

LIB_SESSIONDATA::LIB_SESSIONDATA(WORD wSessionID)
{
	m_wSessionID	= wSessionID;
	m_bIsReference	= FALSE;

	m_SocketCtx.recvContext = new PerIoContext;
	m_SocketCtx.sendContext = new PerIoContext;

	m_SocketCtx.clntSocket = INVALID_SOCKET;
	ClearSocketContext();
}

LIB_SESSIONDATA::~LIB_SESSIONDATA()
{
	SAFE_DELETE_POINT(m_SocketCtx.recvContext);
	SAFE_DELETE_POINT(m_SocketCtx.sendContext);
}

const WORD LIB_SESSIONDATA::GetSessionID()
{
	return m_wSessionID;
}

const VOID LIB_SESSIONDATA::SetReference()
{
	m_bIsReference = TRUE;
}

const BOOL LIB_SESSIONDATA::GetReference()
{
	return m_bIsReference;
}

const VOID LIB_SESSIONDATA::ClearSession()
{
	ClearSocketContext();

	m_bIsReference = FALSE;
}

const VOID LIB_SESSIONDATA::SetClientAddr(SOCKADDR_IN* pClntAddr)
{
	ZeroMemory(&m_SocketCtx.clntAddrInfo, sizeof(SOCKADDR_IN));

	m_SocketCtx.clntAddrInfo.sin_family			= pClntAddr->sin_family;
	m_SocketCtx.clntAddrInfo.sin_port			= pClntAddr->sin_port;
	m_SocketCtx.clntAddrInfo.sin_addr.s_addr	= pClntAddr->sin_addr.s_addr;
}

const VOID LIB_SESSIONDATA::CreateCryptKey()
{
	DWORD	dwTickCount = GetTickCount();
	srand(dwTickCount);
	wCryptKey = rand() & 255;
}

const VOID LIB_SESSIONDATA::ClearSocketContext()
{
	ZeroMemory(&m_SocketCtx.clntAddrInfo, sizeof(SOCKADDR_IN));

	ZeroMemory(&m_SocketCtx.recvContext->Buffer, MAX_BUFFER);
	ZeroMemory(&m_SocketCtx.recvContext->wsaBuf, sizeof(WSABUF));
	ZeroMemory(&m_SocketCtx.recvContext->overlapped, sizeof(WSAOVERLAPPED));

	ZeroMemory(&m_SocketCtx.sendContext->Buffer, MAX_BUFFER);
	ZeroMemory(&m_SocketCtx.sendContext->wsaBuf, sizeof(WSABUF));
	ZeroMemory(&m_SocketCtx.sendContext->overlapped, sizeof(WSAOVERLAPPED));

	SAFE_CLOSE_SOCKET(m_SocketCtx.clntSocket);

	m_SocketCtx.recvContext->wsaBuf.buf = m_SocketCtx.recvContext->Buffer;
	m_SocketCtx.recvContext->wsaBuf.len = MAX_BUFFER;

	m_SocketCtx.sendContext->wsaBuf.buf = m_SocketCtx.sendContext->Buffer;
	m_SocketCtx.sendContext->wsaBuf.len	= MAX_BUFFER;
}