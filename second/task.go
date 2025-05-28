package main

import "fmt"

func findWinner(n, k int) int {
	if n == 1 {
		return 1
	}
	return (findWinner(n-1, k)+k-1)%n + 1
}

func main() {
	var n, k int
	fmt.Print("Введите количество друзей (n): ")
	fmt.Scan(&n)
	fmt.Print("Введите число (k): ")
	fmt.Scan(&k)

	winner := findWinner(n, k)
	fmt.Printf("Победитель: друг под номером %d\n", winner)
}
