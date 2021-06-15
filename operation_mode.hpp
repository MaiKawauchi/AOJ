#pragma once

namespace {
    const std::string kExtension{".ash"};

    enum OperationMode {
        eEncoding,
        eDecoding,
        eUnknown
    };

    OperationMode AutoDetectOperation(const char *filename) {
        // シンプルに拡張から判断する
        // .ash だったら解凍
        // それ以外なら圧縮

        std::string str(filename);
        auto found = str.find_first_of(".");
        if (found) {
            auto sub = str.substr(found);
            if (sub == ::kExtension) {
                return OperationMode::eDecoding;
            }
            return OperationMode::eEncoding;
        }

        return OperationMode::eUnknown;
    }

}// namespace