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
	/// このクラスは、コンストラクタでファイルを読み、
	/// CSVファイルを読んで、値を保持します。
	/// コンストラクタ終了時には、ファイルを閉じています。
	/// </summary>
	/// <param name="filename">ファイル名</param>
	CsvReader(std::string filename);
	~CsvReader();

	/// <summary>
	/// CSVの行数を取得します
	/// </summary>
	/// <returns>行数</returns>
	int GetLines();

	/// <summary>
	/// 指定した行の要素数を取得します
	/// </summary>
	/// <param name="line">行番号</param>
	/// <returns>要素数</returns>
	int GetColumns(int line);

	/// <summary>
	/// 指定した行・列のデータを文字列で返します
	/// </summary>
	/// <param name="line">行番号</param>
	/// <param name="column">列番号</param>
	/// <returns>文字列</returns>
	std::string GetString(int line, int column);

	/// <summary>
	/// 指定した行・列のデータをint型の数値で返します
	/// データが入ってない場合は0を返します
	/// </summary>
	/// <param name="line">行番号</param>
	/// <param name="column">列番号</param>
	/// <returns>数値</returns>
	int GetInt(int line, int column);

	/// <summary>
	/// 指定した行・列のデータをfloat型の数値で返します
	/// データが入ってない場合は0を返します
	/// </summary>
	/// <param name="line">行番号</param>
	/// <param name="column">列番号</param>
	/// <returns>小数値</returns>
	float GetFloat(int line, int column);
};

