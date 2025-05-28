package main

import "fmt"

func canPlaceItemsRec(N, H int, items []int, containers []int, index int) bool {
	if index == len(items) {
		// Все предметы размещены
		return true
	}

	for i := 0; i < N; i++ {
		if containers[i]+items[index] <= H {
			containers[i] += items[index]
			if canPlaceItemsRec(N, H, items, containers, index+1) {
				return true
			}
			containers[i] -= items[index] // откат
		}
	}
	return false
}

func canPlaceItems(N, H int, items []int) bool {
	containers := make([]int, N)
	return canPlaceItemsRec(N, H, items, containers, 0)
}

func main() {
	var N, H, M int
	fmt.Print("Введите количество контейнеров (N): ")
	fmt.Scan(&N)
	fmt.Print("Введите высоту контейнера (H): ")
	fmt.Scan(&H)
	fmt.Print("Введите количество предметов: ")
	fmt.Scan(&M)

	items := make([]int, M)
	fmt.Println("Введите высоты предметов:")
	for i := 0; i < M; i++ {
		fmt.Scan(&items[i])
	}

	if canPlaceItems(N, H, items) {
		fmt.Println("Да, все предметы можно разместить.")
	} else {
		fmt.Println("Нет, не получится разместить все предметы.")
	}
}
