package main

import (
	"fmt"
	"math"
)

func main() {
	var s string
	fmt.Scan(&s)
	n := len(s)

	var ans float64 = 0.0
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			len := j - i + 1
			if len < 3 {
				continue
			}
			if s[i] != 't' || s[j] != 't' {
				continue
			}

			var local float64 = 0.0
			var cnt int32 = 0
			for k := i + 1; k <= j-1; k++ {
				if s[k] == 't' {
					cnt++
				}
			}
			local = float64(cnt) / float64(len-2)
			ans = math.Max(ans, local)
		}
	}
	fmt.Printf("%.20f\n", ans)
}
