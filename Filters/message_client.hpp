#pragma once

#include "logger.hpp"
#include <wtypes.h>

class message_client
{
public:
	template <typename M>
	void send_message(M& message)
	{
		auto pipe_handle = CreateFile(TEXT("\\\\.\\pipe\\StbVirtualCameraPipeline"),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		DWORD dwWritten;
		if (pipe_handle != INVALID_HANDLE_VALUE)
		{
			WriteFile(pipe_handle,
				(uint8_t*)&message,
				sizeof(M),
				&dwWritten,
				nullptr);
			CloseHandle(pipe_handle);
		}
	}
};