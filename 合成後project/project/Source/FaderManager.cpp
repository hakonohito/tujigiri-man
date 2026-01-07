#include "FaderManager.h"

bool FaderManager::faderflag = false;

void FaderManager::SetFader(bool flag)
{
	faderflag = flag;
}

int FaderManager::GetFader()
{
	return faderflag;
}
