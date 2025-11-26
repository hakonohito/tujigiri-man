#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TujigiriTitleScene.h"
#include "PlayScene.h"
#include "SelectScene.h"

SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TujigiriTITLE")
	{
		return new TujigiriTitleScene();
	}
	if (name == "PLAY")
	{
		return new PlayScene();
	}
	if (name == "SELECT") {
		return new SelectScene();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
