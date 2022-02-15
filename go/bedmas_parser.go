// You can edit this code!
// Click here and start typing.

// 8-mar-2016 updated order of operation from from BEMDAS to BEDMAS
// A better design would be a data and an operation stack.  This would allow for the removal of the Entry struct

package main

import (
	"flag"
	"fmt"
	"math"
	"strconv"
	"strings"
	"time"
)

// An entry can be an operation or a number
type Entry struct {
	op  rune    // operation, rune is a utf8 symbol, like a char
	num float64 // number
}

var debug bool         // print intermediate stages of loop
const BEDMAS = "^/*+-" // order of operations

func main() {

	boolPtr := flag.Bool("debug", false, "a bool")
	flag.Parse()
	debug = *boolPtr

	arg := "2234*((1+2)^2 + (3-5)*234/7)"
	//	arg := "1*(2+3)^4"

	start := time.Now()
	result := evalBemdas(arg)
	elapsed := time.Since(start)

	fmt.Printf("\n%v\n= %v\n", arg, result)
	fmt.Printf("%s elapsed\n", elapsed)
	fmt.Printf("%v function calls possible per second\n", int(time.Second/elapsed))
	fmt.Println()

}

func evalBemdas(str string) float64 { // (str ...string) defines variadic argument

	var result float64

	// Make Entries from the input string
	entries := []Entry{}
	p1, p2 := 0, 0 // positions

	for {

		// find the next operation character
		p2 = strings.IndexAny(str[p1:], "*/+-^()")
		if p2 == -1 {
			break
		}
		p2 = p1 + p2

		// If there's a number between p1 and p2 then append it
		float, err := strconv.ParseFloat(strings.TrimSpace(str[p1:p2]), 64)
		if err == nil {
			e1 := Entry{num: float}
			entries = append(entries, e1)
		}
		// Append the operation
		e2 := Entry{op: rune(str[p2])}
		entries = append(entries, e2)

		p1 = p2 + 1
	}
	// Add the last number if it's there
	float, err := strconv.ParseFloat(strings.TrimSpace(str[p1:]), 64)
	if err == nil {
		e1 := Entry{num: float}
		entries = append(entries, e1)
	}

	// === Main loop ===
	for len(entries) > 1 {

		if debug {
			fmt.Println(entries)
			// fmt.Scanln() // wait for input between loops
		}

		// 1. Find deepest parenthesis.
		// Find the first closing paren then
		// search backwards for its opening paren.

		start := 0
		end := len(entries)

		for i, v := range entries {
			if v.op == ')' {
				end = i
				break
			}
		}
		for i := end - 1; i >= 0; i -= 1 {
			if entries[i].op == '(' {
				start = i
				break
			}
		}

		// 2. Find the position of the highest priority operation
		// within the deepest paren
		op := 0

		for _, query := range BEDMAS {
			for i, entry := range entries[start:end] {
				if entry.op == query {
					op = start + i
					break
				}
			}
			if op != 0 {
				break
			}
		}

		// 3. Calculate result
		a := entries[op-1].num
		b := entries[op+1].num

		switch entries[op].op {
		case '^':
			result = math.Pow(a, b)
		case '*':
			result = a * b
		case '/':
			result = a / b
		case '+':
			result = a + b
		case '-':
			result = a - b
		default:
			panic("Invalid operation?")
		}

		// Exit loop if there's only three entries left
		if len(entries) <= 3 {
			break
		}

		// 4. Otherwise reform entries, rinse, repeat
		entries2 := []Entry{}
		o1, o2 := -1, 2 // offsets that define span to replace

		// If paren only contains 3 elements then delete parens too
		if op-2 >= 0 && entries[op-2].op == '(' && entries[op+2].op == ')' {
			o1, o2 = -2, 3
		}
		entries2 = append(entries[:op+o1], Entry{num: result}) // insert result
		entries = append(entries2, entries[op+o2:]...)
		// slice tricks
		// http://stackoverflow.com/questions/21326109/why-are-lists-used-infrequently-in-go

	}
	return result
}

// Pretty printing
func (e Entry) String() string {
	if e.op != 0 {
		return fmt.Sprintf("%v", string(e.op))
	} else {
		return fmt.Sprintf("%v", e.num)
	}
}
