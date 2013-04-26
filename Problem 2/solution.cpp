#include <cstdlib>
#include <random>
#include <algorithm>

using uint = uint32_t;
using uint64 = uint64_t;

constexpr uint64 seed = 9723543535354;
constexpr uint iterations = 100000;

std::default_random_engine eng(seed);
std::uniform_real_distribution<> ran(0,1);

auto walkCarlo (uint steps, double l, double r) -> double {

    double result;
    double lr = l + r;
    int rightmost = 0;
    int present = 0;
    for (uint i = 0; i < steps; ++i) {
        result = ran(eng);
        if (result < l) {
            --present;
        } else if (result < lr) {
            ++present;
            rightmost = std::max (rightmost, present);
        }
    }
    return rightmost;
}

int main () {
    uint steps;
    double l, r;
    double total = 0;

    while (scanf(" walk(%i,%lf,%lf) ", &steps, &l, &r) == 3) {
        total = 0;

        for (uint i = 0; i < iterations; ++i) {
           total += walkCarlo(steps, l, r);
        }
        total /= iterations;

        printf ("walk(%d,%.1f,%.1f) returns %.4f ", steps, l, r, total);
    }
}