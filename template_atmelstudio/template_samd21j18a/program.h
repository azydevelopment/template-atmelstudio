#pragma once

#include "abdeveng_core_service_logger.h"

#include <asf.h>

class CProgram final :
public ILogger
{
	public:

	CProgram();
	virtual ~CProgram();
	void Main();

	// ILogger
	virtual void InitLogger();
	virtual void SetEnabledLogger(bool);
	virtual bool IsEnabledLogger();
	virtual void LogEol();
	virtual void Log(const char[], bool eol = true);

	private:

	struct usart_module m_usart;
	bool m_enable_logger;

	void OnInit();
	void OnUpdate();
};

