#pragma once
#include <string>
#include <vector>

class CsvReader
{
	struct LINEREC {
		std::vector<std::string> record;
	};
	std::vector<LINEREC> csvData;

public:
	CsvReader() {};
	/// <summary>
	/// ���̃N���X�́A�R���X�g���N�^�Ńt�@�C����ǂ݁A
	/// CSV�t�@�C����ǂ�ŁA�l��ێ����܂��B
	/// �R���X�g���N�^�I�����ɂ́A�t�@�C������Ă��܂��B
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	CsvReader(std::string filename);
	~CsvReader();

	/// <summary>
	/// CSV�̍s�����擾���܂�
	/// </summary>
	/// <returns>�s��</returns>
	int GetLines();

	/// <summary>
	/// �w�肵���s�̗v�f�����擾���܂�
	/// </summary>
	/// <param name="line">�s�ԍ�</param>
	/// <returns>�v�f��</returns>
	int GetColumns(int line);

	/// <summary>
	/// �w�肵���s�E��̃f�[�^�𕶎���ŕԂ��܂�
	/// </summary>
	/// <param name="line">�s�ԍ�</param>
	/// <param name="column">��ԍ�</param>
	/// <returns>������</returns>
	std::string GetString(int line, int column);

	/// <summary>
	/// �w�肵���s�E��̃f�[�^��int�^�̐��l�ŕԂ��܂�
	/// �f�[�^�������ĂȂ��ꍇ��0��Ԃ��܂�
	/// </summary>
	/// <param name="line">�s�ԍ�</param>
	/// <param name="column">��ԍ�</param>
	/// <returns>���l</returns>
	int GetInt(int line, int column);

	/// <summary>
	/// �w�肵���s�E��̃f�[�^��float�^�̐��l�ŕԂ��܂�
	/// �f�[�^�������ĂȂ��ꍇ��0��Ԃ��܂�
	/// </summary>
	/// <param name="line">�s�ԍ�</param>
	/// <param name="column">��ԍ�</param>
	/// <returns>�����l</returns>
	float GetFloat(int line, int column);
};

