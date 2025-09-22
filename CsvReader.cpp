#include "CsvReader.h"
#include <fstream>
#include <assert.h>
//本プログラムは花井先生のプログラムの写しになります。

CsvReader::CsvReader(std::string filename)
{
    csvData.clear();
    std::ifstream file(filename);
    if (!file)//fileが読み込めなかった場合
    {
        return;
    }
    //BOMの確認
    unsigned char BOMS[] = { 0xEF, 0xBB, 0xBF };
    bool found = true;
    for (int i = 0; i < 3; i++) {
        if (file.get() != BOMS[i]) {
            found = false;
            break;
        }
    }
    if (!found)
        file.seekg(std::ios_base::beg);

    std::string line;
    while (std::getline(file, line)) {
		//「"」の排除
		while (true) {
			int dq = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '"')
					dq++;
			}
			if (dq % 2 == 0)
				break;
			std::string s;
			getline(file, s);
			line += "\n" + s;
		}
		for (auto it = line.begin(); it != line.end();) {
			if (*it == '"')
				it = line.erase(it);
			if (it != line.end())
				it++;
		}

		// 行内を,で切り分ける
		LINEREC lineRecord;
		int top = 0;
		bool indq = false;
		for (int n = 0; n < line.size(); n++) {
			if (line[n] == ',') {
				if (!indq) {
					lineRecord.record.emplace_back(line.substr(top, (size_t)(n - top)));
					top = n + 1;
				}
			}
			else if (line[n] == '"')
				indq = !indq;
		}
		lineRecord.record.emplace_back(line.substr(top, line.size() - top));
		csvData.emplace_back(lineRecord);
    }
	file.close();

}

CsvReader::~CsvReader()
{
	for (auto rec : csvData)
		rec.record.clear();
	csvData.clear();
}

int CsvReader::GetLines()
{
	return csvData.size();
}

int CsvReader::GetColumns(int line)
{
	assert(line < GetLines());
	return csvData[line].record.size();
}

std::string CsvReader::GetString(int line, int column)
{
	assert(line < GetLines());
	if (column >= GetColumns(line))
		return "";
	return csvData[line].record[column];
}

int CsvReader::GetInt(int line, int column)
{
	std::string str = GetString(line, column);
	if (str == "") {
		return 0;
	}
	return std::stoi(str);
}

float CsvReader::GetFloat(int line, int column)
{
	std::string str = GetString(line, column);
	if (str == "") {
		return 0.0f;
	}
	return std::stof(str);
}