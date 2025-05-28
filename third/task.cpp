#include <iostream>
#include <vector>
#include <algorithm>

bool canPlaceItemsRec(int N, int H, const std::vector<int>& items, std::vector<int>& containers, int index) {
    if (index == items.size()) {
        // Все предметы размещены
        return true;
    }
    
    for (int i = 0; i < N; ++i) {
        if (containers[i] + items[index] <= H) {
            containers[i] += items[index];
            if (canPlaceItemsRec(N, H, items, containers, index + 1)) {
                return true;
            }
            containers[i] -= items[index]; // откат
        }
    }
    return false;
}

bool canPlaceItems(int N, int H, const std::vector<int>& items) {
    std::vector<int> containers(N, 0);
    return canPlaceItemsRec(N, H, items, containers, 0);
}

int main() {
    int N, H, M;
    std::cout << "Введите количество контейнеров (N): ";
    std::cin >> N;
    std::cout << "Введите высоту контейнера (H): ";
    std::cin >> H;
    std::cout << "Введите количество предметов: ";
    std::cin >> M;

    std::vector<int> items(M);
    std::cout << "Введите высоты предметов:\n";
    for (int i = 0; i < M; ++i) {
        std::cin >> items[i];
    }

    if (canPlaceItems(N, H, items)) {
        std::cout << "Да, все предметы можно разместить." << std::endl;
    } else {
        std::cout << "Нет, не получится разместить все предметы." << std::endl;
    }

    return 0;
}