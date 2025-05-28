#include <iostream>
#include <vector>

int findWinner(int n, int k, int k2 = 0) {
    if (n == k2)
        return 1;
    k2 = k2 + 1;
    return (findWinner(n - 1, k), k2 + k - 1) % n + 1;
}

int main() {
    int n, k;
    std::cout << "Введите количество друзей (n): ";
    std::cin >> n;
    std::cout << "Введите число (k): ";
    std::cin >> k;

    int winner = findWinner(n, k);
    std::cout << "Победитель: друг под номером " << winner << " (рекурсивный метод)" << std::endl;

    return 0;
}