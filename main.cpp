#include <random>
#include <vector>
#include <chrono>
#include <iostream>

int main() {
    // lambda returning pseudo-random integer
    auto roll = []() { return rand() % 6 + 1; };

    std::vector<int> container;

    container.push_back(roll());
    const int* pItemZeroAddress = &(*container.begin());

    std::chrono::duration<double> durInsertTime(0);

    do {
        // get address of first item
        const int* pItemZeroAddress = &(*container.begin());

        std::cout << "Contains " << container.size() << " elements, took " <<
            std::chrono::duration_cast<std::chrono::microseconds>(durInsertTime).count() << "us\n";

        for (const auto& i : container)
        {
            const int* pAddressOfNewItem = &i;
            int pItemOffset = pAddressOfNewItem - pItemZeroAddress;
            int pItemOffsetOriginal = pAddressOfNewItem - pItemZeroAddress;
            std::cout << "Offset from original: " << pItemOffsetOriginal << "  Offset from zero: " << pItemOffset <<
                "   :   Content: " << i << "\n";
        }

        auto tp1 = std::chrono::high_resolution_clock::now();
        container.push_back(roll());
        auto tp2 = std::chrono::high_resolution_clock::now();
        durInsertTime = (tp2 - tp1);
    } while (getc(stdin));
}
