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
#define iPowMod(c, e, n) boost::multiprecision::powm(Int(c), Int(e), Int(n))
#define iMin(a, b) a < b ? a : b

Int cycles = 0;

Int Sigma(std::vector<Int> S) {
    return std::accumulate(S.begin(), S.end(), Int(0), std::plus<Int>());
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

bool ABS(std::vector<Int> U, Int t) {
    std::vector<Int> S(U);
    std::sort(U.begin(), U.end());
    Int i, j, s, r, d, n, e = 0;
    Int k = 1;
    Int l = 2;
    while (k < t) {
        i = k;
        j = l;
        e = (i + j) / 2;
        while (i < j) {
            cycles++;
            if (cycles > 1) return false;
            n = (i + j) / 2;
            S = nPhi(U, n + e);
            s = Sigma(S);
            r = iPowMod(s, t - 1, t);
            d = 1 - r;
            if (d == 0) return true;
            if (d < 0) i = n + 1;
            if (d > 0) j = n;
            e++;
        }
        k++;
        l++;
    }

    return false;
}

int main(int argc, char *argv[]) {

    std::cout << std::endl;
    std::cout << "            Abstract Binary Search Algorithm           " << std::endl;
    std::cout << "Copyright (c) 2015+ Oscar Riveros. All rights reserved." << std::endl;
    std::cout << std::endl;


    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " numbers<path>" << std::endl;
        return EXIT_FAILURE;
    }

    Int t;

    std::ifstream number_file(argv[1], std::ifstream::in);
    while (number_file.good()) {
        number_file >> t;

        std::vector <Int> U;
        Int k = t;
        Int bits = 0;
        while (k) {
            k /= 2;
            U.push_back(iPow(2, bits));
            bits++;
        }

        cycles = 0;

        std::chrono::time_point <std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        bool isPrime = ABS(U, t);
        end = std::chrono::system_clock::now();

        std::string message = isPrime ? "Prime" : "Composite";

        std::cout << std::endl;
        std::cout << "<" << t << " | " << message << ">";
        std::cout << std::endl;

        std::chrono::duration<double> seconds = end - start;
        std::cout << "Time   : " << seconds.count() << std::endl;
        std::cout << std::endl;
    }


    return EXIT_SUCCESS;
}