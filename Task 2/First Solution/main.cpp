#include <iostream>
#include "tour.h"

int main(int argc, char *argv[]) {
    int trials = 0;
    int x = std::stoi(argv[1]);
    int y = std::stoi(argv[2]);
    while (!searchClosedKnightTour(x, y)) {
        trials++;
        if (trials == 10000000) {
            std::cout << "NO ANSWER!" << std::endl;
            break;
        }
    }
    return 0;
}


