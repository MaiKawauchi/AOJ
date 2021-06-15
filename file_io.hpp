#pragma onece

#include <fstream>
#include <vector>
std::vector<char> ReadFile(const char *filename, std::string *log) {

    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        *log = "Can not open " + std::string{filename} + ".";
        return {};
    }

    // ファイルサイズ取得
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();
    ifs.seekg(0);

    // fixme: あまりにもサイズがでかすぎると new で確保できない場合がある
    std::vector<char> data(size);
    ifs.read(data.data(), size);

    return data;
}

// ---

void WriteFile(const char* filename, const std::vector<char>& data)
{
    std::ofstream ofs(filename, std::ios::binary);
    if(!ofs.is_open())
    {
        // fixme: 対応する
    }
    ofs.write(data.data(), data.size());
    ofs.close();
}
