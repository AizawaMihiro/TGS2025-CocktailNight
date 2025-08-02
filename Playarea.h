#pragma once
#include "GameObject.h"
#include "globals.h"
class Playarea :
    public GameObject
{
private:
	Rect areaRect_; // �v���C�G���A�̋�`
public:
    Playarea();
    ~Playarea();
    void Update() override;
	void Draw() override;
};

