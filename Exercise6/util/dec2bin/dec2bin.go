package main

import (
	"bufio"
	"os"
	"strconv"
)

func main() {
	// read from stdin and write to stdout
	s := bufio.NewScanner(os.Stdin)

	for s.Scan() {
		line := s.Text()
		i, _ := strconv.Atoi(line)
		os.Stdout.Write([]byte{byte(i)})
	}
}