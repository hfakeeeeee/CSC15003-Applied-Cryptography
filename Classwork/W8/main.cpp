#include <iostream>
#include <cstring>

unsigned char* PKCS7(const unsigned char* message, size_t blockSize, size_t messageLength) {
    if (blockSize == 0) {
        throw std::invalid_argument("Block size không thể bằng 0.");
    }

    size_t paddingLength = blockSize - (messageLength % blockSize);
    size_t targetLength = messageLength + paddingLength;

    unsigned char* paddedMessage = new unsigned char[targetLength];

    memcpy(paddedMessage, message, messageLength);

    for (size_t i = messageLength; i < targetLength; ++i) {
        paddedMessage[i] = static_cast<unsigned char>(paddingLength);
    }

    return paddedMessage;
}

int main() {
    unsigned char* messages[] = {
        (unsigned char*)"0", (unsigned char*)"01",
        (unsigned char*)"012", (unsigned char*)"0123",
        (unsigned char*)"01234", (unsigned char*)"012345",
        (unsigned char*)"0123456", (unsigned char*)"01234567",
        (unsigned char*)"012345678", (unsigned char*)"0123456789",
        (unsigned char*)"0123456789a", (unsigned char*)"0123456789ab",
        (unsigned char*)"0123456789abc", (unsigned char*)"0123456789abcd",
        (unsigned char*)"0123456789abcde", (unsigned char*)"0123456789abcdef"
    };

    size_t blockSize = 16;

    for (size_t i = 0; i < 16; i++) {
        size_t messageLength = strlen((const char*)messages[15 - i]);
        unsigned char* paddedMessage = PKCS7(messages[15 - i], blockSize, messageLength);

        for (size_t j = 0; j < messageLength + blockSize - (messageLength % blockSize); j++) {
            printf("%02x", paddedMessage[j]);
        }

        printf("\n");

        delete[] paddedMessage;
    }

    return 0;
}