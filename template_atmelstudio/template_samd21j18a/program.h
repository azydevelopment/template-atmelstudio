#pragma once

class CProgram final
{
public:
	CProgram();
	virtual ~CProgram();
	void Main();

private:
	void OnInit();
	void OnUpdate();
};

