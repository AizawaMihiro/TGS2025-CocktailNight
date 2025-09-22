#pragma once
#include <vector>
class GameObject
{
protected:
	bool isAlive_;//�����t���O
	int drawPriority_;//�`��D��x
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool IsAlive() { return isAlive_; }//�����t���O�̎擾
	void SetAlive(bool alive) { isAlive_ = alive; }//�����t���O�̐ݒ�
	void SetPriority(int num) { drawPriority_ = num; }//�`��D��x�̐ݒ�
};

extern std::vector<GameObject*> gameObjects;//extern�͂ǂ����ł��̕ϐ������݂��邱�Ƃ�\��
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj) {
	newObjects.push_back(obj);
}


