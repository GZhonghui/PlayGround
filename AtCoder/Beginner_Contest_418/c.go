package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

const maxn int64 = 3e5 + 10
const maxq int64 = 3e5 + 10

var n, q int64
var a [maxn]int64
var b [maxq]int64
var ans [int64(1e6 + 10)]int64
var sum [maxn]int64

func main() {
	in := bufio.NewReaderSize(os.Stdin, 1<<20) // 1MB 缓冲，随意
	out := bufio.NewWriterSize(os.Stdout, 1<<20)
	defer out.Flush()

	var n, q int64
	fmt.Fscan(in, &n, &q)

	for i := int64(1); i <= n; i++ {
		fmt.Fscan(in, &a[i])
	}

	slice := a[1 : n+1]
	sort.Slice(slice, func(i, j int) bool {
		return slice[i] < slice[j]
	})

	sum[0] = 0
	for i := int64(1); i <= n; i++ {
		sum[i] = sum[i-1] + a[i]
	}

	for i := int64(1); i <= q; i++ {
		fmt.Fscan(in, &b[i])
	}

	var r, k int64 = 0, int64(1e6 + 10)
	for i := int64(1); i <= int64(1e6); i++ {
		for r < n && a[r+1] < i {
			r++
		}
		ans[i] = sum[r] + (n-r)*(i-1) + 1
		if r == n {
			k = i
			break
		}
	}

	for i := int64(1); i <= q; i++ {
		if b[i] >= k {
			fmt.Fprintln(out, -1)
		} else {
			fmt.Fprintln(out, ans[b[i]])
		}
	}
}
