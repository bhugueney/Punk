///////////////////////////////////////////////////////////////////////////////////
//             Copyright (c) 2015+ Oscar Riveros. All rights reserved.           //
//                            oscar.riveros@gmail.com                            //
//                                                                               //
//      Without any restriction, Oscar Riveros reserved rights, patents and      //
// commercialization of this knowledge and which derive directly from this work. //
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
#include <cryptopp/sha3.h>
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>

typedef boost::multiprecision::cpp_int Int;
typedef unsigned long long int nInt;

#define iPow(a, b) boost::multiprecision::pow(Int(a), Int(b).convert_to<nInt>())

Int CYCLES;

nInt dbg;
nInt ker0;
nInt ker1;
nInt algorithm;

struct HexToInt {
    Int value;

    operator Int() const { return value; }

    friend std::istream &operator>>(std::istream &in, HexToInt &out) {
        in >> std::hex >> out.value;
        return in;
    }
};

std::string HashString(std::string message) {
    std::string digest;

    CryptoPP::HexEncoder *hexenc = new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest));

    if (algorithm == 224) {
        CryptoPP::SHA3_224 hash0;
        CryptoPP::StringSource source0(message, true, new CryptoPP::HashFilter(hash0, hexenc));
    }
    if (algorithm == 256) {
        CryptoPP::SHA3_256 hash1;
        CryptoPP::StringSource source1(message, true, new CryptoPP::HashFilter(hash1, hexenc));
    }
    if (algorithm == 384) {
        CryptoPP::SHA3_384 hash2;
        CryptoPP::StringSource source2(message, true, new CryptoPP::HashFilter(hash2, hexenc));
    }
    if (algorithm == 512) {
        CryptoPP::SHA3_512 hash3;
        CryptoPP::StringSource source3(message, true, new CryptoPP::HashFilter(hash3, hexenc));
    }

    return digest;
}

Int Key(std::vector<Int> S) {
    std::string message;
    for (nInt i = 0; i < S.size(); i++) {
        message.push_back(S.at(i).convert_to<char>());
    }

    return boost::lexical_cast<HexToInt>(HashString(message));
}

std::vector<Int> nPhi(std::vector<Int> U, Int n) {
    std::vector<Int> S;
    if (!n) return S;
    while (n) {
        S.push_back(U.at(n.convert_to<nInt>() % U.size()));
        n /= U.size();
    }
    return S;
}

std::vector<Int> Phi(std::vector<Int> U, Int n) {
    std::vector<Int> S;
    if (!n) return S;
    nInt k = 0;
    while (n) {
        if (n % 2 && k < U.size()) S.push_back(U.at(k));
        n /= 2;
        k++;
    }
    return S;
}

std::vector<Int> ABS(std::vector<Int> U, Int t) {
    std::vector<Int> S(U);
    Int L = iPow(U.size(), U.size());
    Int i, j, s, d, n, e = 0;
    Int k = 0;
    Int l = iPow(ker0, ker1);
    while (k < L) {
        i = k;
        j = l;
        e = (i + j) / 2;
        while (i < j) {
            CYCLES++;
            n = (i + j) / 2;
            S = Phi(nPhi(U, n + e), n + e);
            s = Key(S);
            d = s - t;
            if (dbg) {
                for (auto u : S) std::cout << char(u);
                std::cout << std::endl;
            }
            if (d == 0) return S;
            if (d < 0) i = n + 1;
            if (d > 0) j = n;
            e++;
        }
        k++;
        l += k;
    }

    return std::vector<Int>();
}

int main(int argc, char *argv[]) {

    std::cout << std::endl;
    std::cout << "            Abstract Binary Search Algorithm           " << std::endl;
    std::cout << "Copyright (c) 2015+ Oscar Riveros. All rights reserved." << std::endl;
    std::cout << std::endl;

    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " hash<path> alphabet<path> kel<number> ker<number> algorithm<224|256|384|512> log<0|1>" << std::endl;
        return EXIT_FAILURE;
    }

    ker0 = nInt(std::atoi(argv[3]));
    ker1 = nInt(std::atoi(argv[4]));
    algorithm = nInt(std::atoi(argv[5]));
    dbg = nInt(std::atoi(argv[6]));

    std::chrono::time_point<std::chrono::system_clock> start, end;
    try {
        std::string s;
        char u;
        std::vector<Int> U;
        std::ifstream hash_file(argv[1], std::ifstream::in);
        std::ifstream alphabeth_file(argv[2], std::ifstream::in);
        while (hash_file.good()) {
            hash_file >> s;
            while (alphabeth_file >> u) {
                U.push_back(Int(nInt(u)));
            }

            CYCLES = 0;
            Int t = boost::lexical_cast<HexToInt>(s);

            std::cout << "<" << t << ">" << std::endl;
            start = std::chrono::system_clock::now();
            auto S = ABS(U, t);
            end = std::chrono::system_clock::now();
            std::cout << "<";
            for (auto u : S) std::cout << char(u);
            std::cout << ">" << std::endl;

            std::chrono::duration<double> seconds = end - start;
            std::cout << std::endl;
            std::cout << "Time   : " << seconds.count() << std::endl;
            std::cout << "Cycles : " << CYCLES << std::endl;

        }
    } catch (...) {
        std::cout << "Format Exception..." << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}