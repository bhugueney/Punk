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
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int Int;
typedef unsigned long long int nInt;

#define iPow(a, b) boost::multiprecision::pow(Int(a), Int(b).convert_to<nInt>())
#define iMin(a, b) a < b ? a : b

Int cycles = 0;

Int Sigma(std::vector<Int> S) {
    return std::accumulate(S.begin(), S.end(), Int(0), std::plus<Int>());
}

std::vector<Int> Phi(std::vector<Int> U, Int n) {
    std::vector<Int> S;
    if (!n) return S;
    nInt k = 0;
    while (n) {
        if (n % 2) S.push_back(U.at(k));
        n /= 2;
        k++;
    }
    return S;
}

std::vector<Int> ABS(std::vector<Int> U, Int t, nInt log) {
    std::vector<Int> S(U);
    std::sort(U.begin(), U.end());
    t = iMin(t, Sigma(U) - t);
    if (!t) return U;
    if (std::binary_search(U.begin(), U.end(), t)) return std::vector<Int>({t});
    for (nInt k = 0; k < U.size(); k++) {
        if (U.at(k) > t) {
            U.erase(U.begin() + k, U.end());
        }
    }
    if (U.size() == 1) return U;
    Int L = iMin(iPow(U.size(), 4), iPow(2, U.size() - 1));
    Int i, j, s, d, n, e = 0;
    Int k = 0;
    Int l = iPow(2, U.size() - 1);
    while (k < L) {
        i = k;
        j = l;
        e = (i + j) / 2;
        while (i < j) {
            cycles++;
            n = (i + j) / 2;
            S = Phi(U, n + e);
            s = Sigma(S);
            d = s - t;
            if (log) {
                std::cout << "(<" << Sigma(S) << ", " << Sigma(U) - Sigma(S) << ">, [ ";
                for (auto u : S) std::cout << u << " ";
                std::cout << "])" << std::endl;
            }
            if (d == 0) return S;
            if (d < 0) i = n + 1;
            if (d > 0) j = n;
            e++;
        }
        k++;
        l++;
    }

    return std::vector<Int>();
}

int main(int argc, char *argv[]) {

    std::cout << std::endl;
    std::cout << "            Abstract Binary Search Algorithm           " << std::endl;
    std::cout << "Copyright (c) 2015+ Oscar Riveros. All rights reserved." << std::endl;
    std::cout << std::endl;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " universe<path> log<0|1>" << std::endl;
        return EXIT_FAILURE;
    }

    nInt log = nInt(std::atoi(argv[2]));
    std::chrono::time_point<std::chrono::system_clock> start, end;
    Int t;
    Int u;
    std::vector<Int> U;
    try {
        std::ifstream file(argv[1], std::ifstream::in);
        while (file.good()) {
            file >> t;
            while (file >> u) {
                U.push_back(u);
            }
        }
        std::sort(U.begin(), U.end());
    } catch (...) {
        std::cout << "Something is wrong..." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << std::endl;
    std::cout << "(<" << t << ", " << Sigma(U) - t << ">, [ ";
    for (auto u : U) std::cout << u << " ";
    std::cout << "])" << std::endl;
    std::cout << std::endl;

    start = std::chrono::system_clock::now();
    auto S = ABS(U, t, log);
    end = std::chrono::system_clock::now();

    std::cout << std::endl;
    std::cout << "(<" << Sigma(S) << ", " << Sigma(U) - Sigma(S) << ">, [ ";
    for (auto u : S) std::cout << u << " ";
    std::cout << "])" << std::endl;
    std::cout << std::endl;

    std::chrono::duration<double> seconds = end - start;
    std::cout << "Time   : " << seconds.count() << std::endl;
    std::cout << "Cycles : " << cycles << std::endl;
    std::cout << std::endl;


    return EXIT_SUCCESS;
}