package main

import (
	"fmt"
	"math"
	"time"
)

func main() {

	// integers go in, primes come out
	integers := make(chan uint64, 1000)
	primes := make(chan uint64, 1000)

	// I don't know how many cores I have
	for i:=0;i<10;i+=1 {
		go calculatePrimes(integers, primes)
	}

	// Shovel integers into the input buffer
	go func() {
		var i uint64
		for i = 3; ; i += 2 {
			integers <- i
		}
	}()


	// Print the output buffer every second or so
	go func() {
		var i uint64
		i = 0
		for {
			select {
			case prime := <-primes:
				fmt.Printf("%d ", prime)
				i++
			default:
			}
		}
	}()

	// gotta sleep or it doesn't work
	time.Sleep(1 * time.Minute)
}

func calculatePrimes(integers chan uint64, primes chan uint64) {
	for {
		var i uint64 
		i = <-integers
		if isPrime(i) {
			primes <- i
			// fmt.Println(i)
		}
	}
}

func isPrime(arg uint64) bool {
	// checks odd factors up to sqrt(arg)
	if arg%2 == 0 {
		return false
	}
	var i uint64 
	for i = 3; i <= uint64(math.Ceil(math.Sqrt(float64(arg)))); i += 2 {
		if arg%i == 0 {
			return false
		}
	}
	return true
}
