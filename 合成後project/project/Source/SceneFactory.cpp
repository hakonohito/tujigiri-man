#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TujigiriTitleScene.h"
#include "TujigiriPlayScene.h"
#include "SelectScene.h"
#include "HeartScene.h"
#include "RankingScene.h"
#include "TitleScene.h"

SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TUJIGIRITITLE")
	{
		return new TujigiriTitleScene();
	}
	if (name == "TUJIGIRIPLAY")
	{
		return new TujigiriPlayScene();
	}
	if (name == "SELECT") {
		return new SelectScene();
	}
	if (name == "HEART")
	{
		return new HeartScene();
	}
	if (name == "RANKING")
	{
		return new RankingScene();
	}
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
