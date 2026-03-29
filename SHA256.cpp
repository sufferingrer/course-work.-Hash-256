#include "SHA256.h"
#include <iomanip>

inline unsigned int rotr(unsigned int x, int n) {
    return (x >> n) | (x << (32 - n));
}

std::string SHA256::GenerateHash(const char *inputBuffer, unsigned int inputSize)
{
    unsigned int inputBits = (inputSize + 1) * 8;
    unsigned int nChunks;

    for (nChunks = 1; 512 * nChunks < inputBits + 64; nChunks++);

    unsigned int paddingBits = 512 * nChunks - inputBits - 64;
    unsigned int finalSize = inputSize + 1 + (paddingBits/8) + 8;

    unsigned char *buffer = new unsigned char[finalSize];

    for(unsigned int i = 0; i < inputSize; i++)
        buffer[i] = static_cast<unsigned char>(inputBuffer[i]);

    buffer[inputSize] = 1 << 7;

    for (unsigned int i = inputSize+1; i < finalSize-8; i++)
        buffer[i] = 0;

    for (unsigned int i = finalSize-8, pos = 0; i < finalSize; i++, pos++)
        buffer[i] = static_cast<unsigned long long int>(inputSize * 8) >> (8 - pos - 1) * 8;

    unsigned int hashValues[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                                  0x510e527f, 0x9b05688c, 0x1f83d9ab,0x5be0cd19};

    for (unsigned int i = 0; i < nChunks; i++)
    {
        unsigned int integerArray[64];
        for (unsigned int j = 0; j < 64; j++)
        {
            if(j < 16)
            {
                unsigned int startPos = 64 * i + j * 4;
                integerArray[j] = buffer[startPos] << 24 | buffer[startPos+1] << 16 | buffer[startPos+2] << 8 | buffer[startPos+3] << 0;
            }
            else
            {
                unsigned int s0 = rotr(integerArray[j-15], 7) ^ rotr (integerArray[j-15], 18) ^ integerArray [j-15] >> 3;
                unsigned int s1 = rotr(integerArray[j-2], 17) ^ rotr (integerArray[j-2], 19) ^ integerArray[j-2] >> 10;
                integerArray[j] = integerArray[j-16] + s0 + integerArray[j-7] + s1;
            }
        }
        unsigned int a = hashValues[0], b = hashValues[1], c = hashValues[2], d = hashValues[3];
        unsigned int e = hashValues[4], f = hashValues[5], g = hashValues[6], h = hashValues[7];

        for (unsigned int j = 0; j < 64; j++)
        {
            unsigned int s1 = rotr(e,6) ^ rotr(e, 11) ^ rotr(e, 25);
            unsigned int ch = (e & f) ^ (~e & g) ;
            unsigned int temp1 = h + s1 + ch + roundConstants[j] + integerArray[j];

            unsigned int s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            unsigned int maj = (a & (b | c)) | (b & c);
            unsigned int temp2 = s0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hashValues[0] += a;
        hashValues[1] += b;
        hashValues[2] += c;
        hashValues[3] += d;
        hashValues[4] += e;
        hashValues[5] += f;
        hashValues[6] += g;
        hashValues[7] += h;
    }

    std::stringstream ss;
    std::string hash;
    for(unsigned int hashValue : hashValues)
    {
        for(unsigned int i = 0; i < 4; i++)
        {
            unsigned int actualHashValue = static_cast<unsigned char>(hashValue >> (4 - i - 1) * 8);
            ss << std::setfill('0') << std::setw(2) << std::hex << actualHashValue;
        }
    }

    hash = ss.str();
    std::cout << "Hash: " << hash << std::endl;

    delete[] buffer;

    return hash;
}
