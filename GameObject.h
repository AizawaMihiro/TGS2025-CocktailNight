#pragma once
#include <vector>
class GameObject
{
protected:
	bool isAlive_;//�����t���O
	int drawPriority_;//�`��D��x
	int stagenum_;   // �X�e�[�W�ԍ�
	int score_;      // �X�R�A
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool IsAlive() { return isAlive_; }//�����t���O�̎擾
	void SetAlive(bool alive) { isAlive_ = alive; }//�����t���O�̐ݒ�
	void SetPriority(int num) { drawPriority_ = num; }//�`��D��x�̐ݒ�
	int GetPriority() const{ return drawPriority_; }//�`��D��x�̎擾

	// �X�R�A�̃Z�b�^�[ / �Q�b�^�[
	void setScore(int score) { score_ = score; }
	int getScore() const { return score_; }

	// �X�e�[�W�ԍ��̃Z�b�^�[ / �Q�b�^�[
	void setStageNum(int stage) { stagenum_ = stage; }
	int getStageNum() const { return stagenum_; }
};

extern std::vector<GameObject*> gameObjects;//extern�͂ǂ����ł��̕ϐ������݂��邱�Ƃ�\��
extern std::vector<GameObject*> newObjects;

inline void AddGameObject(GameObject* obj) {
	newObjects.push_back(obj);
}


