// Usage:
// finder some words here
// case insensitive

package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

var root = "."
var search_terms []string


func visit(path string, f os.FileInfo, err error) error {

	contains_all_search_terms := true
	for i := range search_terms {
		if !strings.Contains(strings.ToLower(f.Name()), strings.ToLower(search_terms[i])) {
			contains_all_search_terms = false
			break
		}
	}
	if contains_all_search_terms {
		fmt.Println(path)
	}

	return nil
}


func main() {

	fmt.Printf("usage: find dir search terms\r\n")

	root = os.Args[1]
	search_terms = os.Args[2:]

	filepath.Walk(root, visit)

}

