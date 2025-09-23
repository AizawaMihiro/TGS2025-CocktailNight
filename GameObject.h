#pragma once
#include <vector>
class GameObject
{
protected:
	bool isAlive_;//生存フラグ
	int drawPriority_;//描画優先度
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool IsAlive() { return isAlive_; }//生存フラグの取得
	void SetAlive(bool alive) { isAlive_ = alive; }//生存フラグの設定
	void SetPriority(int num) { drawPriority_ = num; }//描画優先度の設定
	int GetPriority() const{ return drawPriority_; }//描画優先度の取得
};

extern std::vector<GameObject*> gameObjects;//externはどこかでこの変数が存在することを表す
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj) {
	newObjects.push_back(obj);
}


