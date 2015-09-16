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

typedef boost::multiprecision::cpp_int Int;
typedef unsigned long long int nInt;

#define iPow(a, b) boost::multiprecision::pow(Int(a), Int(b).convert_to<nInt>())
#define iAbs(n) boost::multiprecision::abs(n)

Int cycles = 0;
nInt dbg = 0;

Int Sigma(std::vector<Int> S) {
    return std::accumulate(S.begin(), S.end(), Int(0), std::plus<Int>());
}

std::vector<Int> nPhi(std::vector<Int> U, std::vector<Int> T, Int n) {
    std::vector<Int> S;
    if (!n) return S;
    for (nInt k = 0; k < U.size(); k++) {
        if (U.at(k)) S.push_back(U.at(k));
        else S.push_back(T.at(n.convert_to<nInt>() % T.size()));
        n /= U.size();
    }
    return S;
}

std::vector<Int> ABS(std::vector<Int> U, std::vector<Int> T, Int zero, nInt mM) {
    std::vector<Int> S(U);
    std::vector<Int> C(U);
    Int i, j, k, d, n, e = 0;
    Int m = iAbs(Sigma(S)) - iAbs(Sigma(U));
    Int L = iPow(U.size(), U.size());
    Int l = iPow(U.size() - 1, U.size());
    while (k < L) {
        i = k;
        j = l;
        e = (i + j) / 2;
        while (i < j) {
            cycles++;
            n = (i + j) / 2;
            S = nPhi(U, T, n + e);
            d = iAbs(Sigma(S)) - iAbs(Sigma(U));
            if (d == m) return C;
            if (d < zero) i = n + 1;
            if (d > zero) j = n;
            if (d > m == mM) {
                m = d;
                C = S;
                if (dbg) {
                    std::cout << std::endl;
                    std::cout << "<" << iAbs(Sigma(U)) << " vs " << iAbs(Sigma(S)) << ">" << std::endl;
                    std::cout << "[ ";
                    for (auto u : S) std::cout << u << " ";
                    std::cout << "]" << std::endl;
                }
            }
            e++;
        }
        k++;
        l++;
    }

    return C;
}

int main(int argc, char *argv[]) {

    std::cout << std::endl;
    std::cout << "            Abstract Binary Search Algorithm           " << std::endl;
    std::cout << "Copyright (c) 2015+ Oscar Riveros. All rights reserved." << std::endl;
    std::cout << std::endl;

    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " universe<path> pallete<path> zero<number> <0|1>(min, max) log<0|1>" << std::endl;
        return EXIT_FAILURE;
    }

    Int zero = nInt(std::atoi(argv[3]));
    nInt mM = nInt(std::atoi(argv[4]));
    dbg = nInt(std::atoi(argv[5]));

    std::chrono::time_point<std::chrono::system_clock> start, end;
    Int t;
    Int u;
    std::vector<Int> U;
    std::vector<Int> T;
    try {
        std::ifstream targets_file(argv[1], std::ifstream::in);
        std::ifstream universe_file(argv[2], std::ifstream::in);
        while (targets_file.good()) {
            while (targets_file >> u) {
                U.push_back(u);
            }
        }
        while (universe_file.good()) {
            while (universe_file >> t) {
                T.push_back(t);
            }
        }
    } catch (...) {
        std::cout << "Something is wrong..." << std::endl;
        exit(EXIT_FAILURE);
    }

    cycles = 0;

    start = std::chrono::system_clock::now();
    auto S = ABS(U, T, zero, mM);
    end = std::chrono::system_clock::now();

    std::cout << std::endl;
    std::cout << "<" << iAbs(Sigma(U)) << " vs " << iAbs(Sigma(S)) << ">" << std::endl;
    std::cout << "[ ";
    for (auto u : S) std::cout << u << " ";
    std::cout << "]" << std::endl;

    std::chrono::duration<double> seconds = end - start;
    std::cout << std::endl;
    std::cout << "Time   : " << seconds.count() << std::endl;
    std::cout << "Cycles : " << cycles << std::endl;

    return EXIT_SUCCESS;
}