#pragma once
#include <vector>
class GameObject
{
protected:
	bool isAlive_;
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool IsAlive() { return isAlive_; }
	void SetAlive(bool alive) { isAlive_ = alive; }
};

extern std::vector<GameObject*> gameObjects;//extern‚Í‚Ç‚±‚©‚Å‚±‚Ì•Ï”‚ª‘¶İ‚·‚é‚±‚Æ‚ğ•\‚·
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj) {
	newObjects.push_back(obj);
}
