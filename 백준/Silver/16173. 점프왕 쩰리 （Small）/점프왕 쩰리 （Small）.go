package main

import "fmt"

func main() {
	var n int
	_, _ = fmt.Scan(&n)

	dp := make([][]int, n)
	for y := 0; y < n; y++ {
		dp[y] = make([]int, n)
	}
	dp[0][0] = 1

	for y := 0; y < n; y++ {
		for x := 0; x < n; x++ {
			var tmp int
			_, _ = fmt.Scan(&tmp)
			if tmp == -1 {
				break
			}
			if y+tmp < n {
				dp[y+tmp][x] += dp[y][x]
			}
			if x+tmp < n {
				dp[y][x+tmp] += dp[y][x]
			}
		}
	}

	if dp[n-1][n-1] != 0 {
		fmt.Println("HaruHaru")
	} else {
		fmt.Println("Hing")
	}
}
