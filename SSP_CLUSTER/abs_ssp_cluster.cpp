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
#include <boost/dynamic_bitset.hpp>
#include <boost/mpi.hpp>

typedef boost::multiprecision::cpp_int Int;
typedef int nInt;
typedef std::vector<Int> nVector;

#define iPow(a, b) boost::multiprecision::pow(Int(a), Int(b).convert_to<nInt>())
#define iMin(a, b) a < b ? a : b

boost::mpi::communicator world;

Int Sigma(nVector S) {
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

nVector ABS(nVector U, Int t, nInt log) {
    nVector S(U);
    std::sort(U.begin(), U.end());
    t = iMin(t, Sigma(U) - t);
    if (!t) return U;
    if (std::binary_search(U.begin(), U.end(), t)) return nVector({t});
    for (nInt k = 0; k < U.size(); k++) {
        if (U.at(k) > t) {
            U.erase(U.begin() + k, U.end());
        }
    }
    if (U.size() == 1) return U;

    nInt num_nodes = static_cast<nInt>(world.size());
    nInt node  = static_cast<nInt>(world.rank());

    Int step = U.size() * (node + 1) / num_nodes;

    Int L = iMin(iPow(U.size(), 4), iPow(2, U.size() - 1));
    Int i, j, s, d, n, e = 0;
    Int k = 0;
    Int l = iPow(2, U.size() - 1);
    while (k < L) {
        i = k;
        j = l;
        e = (i + j) / 2;
        while (i < j) {
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
        k += step;
        l += step;
    }

    return nVector();
}

int main(int argc, char *argv[]) {

    boost::mpi::environment env(argc, argv);

    if (world.rank() == 0) {
        std::cout << std::endl;
        std::cout << "            Abstract Binary Search Algorithm           " << std::endl;
        std::cout << "Copyright (c) 2015+ Oscar Riveros. All rights reserved." << std::endl;
        std::cout << std::endl;

        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " universe<path> log<0|1>" << std::endl;
            return EXIT_FAILURE;
        }
    }

    nInt log = nInt(std::atoi(argv[2]));
    std::chrono::time_point<std::chrono::system_clock> start, end;
    Int t;
    Int u;
    nVector U;
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

    if (world.rank() == 0) {
        std::cout << std::endl;
        std::cout << "(<" << t << ", " << Sigma(U) - t << ">, [ ";
        for (auto u : U) std::cout << u << " ";
        std::cout << "])" << std::endl;
        std::cout << std::endl;
    }

    start = std::chrono::system_clock::now();
    auto S = ABS(U, t, log);
    end = std::chrono::system_clock::now();

    if (!S.empty()) {

        std::cout << std::endl;
        std::cout << "(<" << Sigma(S) << ", " << Sigma(U) - Sigma(S) << ">, [ ";
        for (auto u : S) std::cout << u << " ";
        std::cout << "])" << std::endl;
        std::cout << std::endl;

        std::chrono::duration<double> seconds = end - start;
        std::cout << "Time   : " << seconds.count() << std::endl;
        std::cout << std::endl;

        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}