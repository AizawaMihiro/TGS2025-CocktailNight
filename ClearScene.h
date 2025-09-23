#pragma once
#include "SceneBase.h"
#include <string>
#include "CsvReader.h"

class Playarea;
class ClearScene : public SceneBase
{
private:
	int hImage_;
	int cocktailImagte_;
	CsvReader csv_;
	int stagenum_;
	std::string infomation_;
	int content_;
	std::string message_;
	
public:
	ClearScene();
	~ClearScene();
	void Update() override;
	void Draw() override;
};
