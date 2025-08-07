#pragma once
#include "GameObject.h"
#include "globals.h"
#include <vector>
#include "Piece.h"
class Playarea :
    public GameObject
{
private:
	Rect areaRect_; // �v���C�G���A�̋�`
	std::vector<Piece*> pieces_;
public:
    Playarea();
    ~Playarea();
    void Update() override;
	void Draw() override;
};

