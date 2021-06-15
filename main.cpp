#include "file_io.hpp"
#include "operation_mode.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

// ---

std::vector<char> RunLengthEncoding(const std::vector<char> &data) {

    int n = (int) data.size();
    std::vector<std::pair<char, uint8_t>> tmp;
    for (int i = 0; i < n;) {
        int j = i + 1;
        /*
        fixme: 256回以上繰り返されるとオーバーフローするのでとりあえず対応
        */
        for (;j < n && (j - i < 255) && data[i] == data[j]; j++){}
        uint8_t cnt = j - i;
        assert(cnt != 0);
        tmp.emplace_back(data[i], cnt);
        i = j;
    }

    std::vector<char> ret(tmp.size() * 2);
    for(int i = 0; i < tmp.size(); ++i)
    {
        ret[2 * i + 0] = tmp[i].first;
        ret[2 * i + 1] = static_cast<char>(tmp[i].second);
    }
    return ret;
}

// ---

std::vector<char> RunLengthDecoding(const std::vector<char> &data) {

    assert(data.size() % 2 == 0);

    std::vector<char> ret;
    for(int i = 0; i < data.size() / 2; ++i)
    {
        char c = data[2 * i + 0];
        auto n = static_cast<uint8_t>(data[2 * i + 1]);
        assert(n != 0);
        for(int j = 0; j < n; ++j)
        {
            ret.push_back(c);
        }
    }

    return ret;
}

// ---

int main(int argc, char *argv[]) {

    if (argc != 3 ){
        std::cout << "Usage: ./ash [input file name] [output file name]" << std::endl;
        return 0;
    }

    // ファイル読み込み
    std::string log;
    auto data = ReadFile(argv[1], &log);
    if (data.empty()) {
        std::cerr << log << std::endl;
        return 0;
    }

    // 圧縮 or 展開を拡張子から判断
    auto op = AutoDetectOperation(argv[1]);
    if(op == OperationMode::eEncoding)
    {
        // 圧縮
        auto compressed = RunLengthEncoding(data);
        WriteFile(argv[2], compressed);
    }
    else if(op == OperationMode::eDecoding)
    {
        // 解凍
        auto uncompressed = RunLengthDecoding(data);
        WriteFile(argv[2], uncompressed);
    }

}
