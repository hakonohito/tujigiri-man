#pragma once
class FaderManager {
public:
	static void SetFader(bool flag);
	static int GetFader() { return faderflag; }
private:
	static bool faderflag;
};