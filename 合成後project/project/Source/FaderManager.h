#pragma once
class FaderManager {
public:
	static void SetFader(bool flag);
	static int GetFader();
private:
	static bool faderflag;
};