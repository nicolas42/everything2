// Update 2-Sept-2012 removed almost all math.Sqrt references

// Update 11-April-2016
// removed security from http.Get("https...")
// apparently the certificate was valid but for a different domain
// panic: Get https://Problem.net/project/resources/p022_names.txt: x509: certificate is valid for cc.sedoparking.com, not Problem.net
// @ bytes := ReadUrl("http://Problem.net/project/resources/p022_names.txt")



// List of answers available at
// https://github.com/nayuki/Project-Euler-solutions/blob/master/Answers.txt

package projectEuler

import (
	"math"
	"strconv"
	"strings"
	"fmt"
	"net/http"
	"io/ioutil"
	"sort"
	"time"
)

func Demo() {
	t0 := time.Now()
	Problem1()
	Problem2()
	Problem3()
	Problem4()
	Problem5()
	Problem6()
	Problem7()
	Problem8()
	Problem9()
	Problem10()
	Problem11()
	Problem12()
	Problem13()
	Problem14()
	Problem15()
	Problem16()
	Problem17()
	Problem18()
	Problem19()
	Problem20()
	Problem21()
	Problem22()
	Problem23()
	Problem24()	
	fmt.Println("Time Taken:", time.Since(t0) )
}

//24. What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

func Problem24(){

	o := []int{}
	for i := 9; i >= 0; i-- {
		o = append(o, fac(i))  //integer factorial
	}
	
	p := []int{}
	n := 999999
	for _, o := range o {
		p = append(p, int(n/o))
		n = n%o
	}
	
	a := []int{0,1,2,3,4,5,6,7,8,9}
	b := []int{}
	for _, p := range p {
		b = append(b, a[p])
		a = remove(a, p)
	}
	print("24 ")
	for _,b := range b {print(b)}
	println()
	
}

func remove(a []int, p int) []int {
//	a := []int{0,1,2,3,4,5,6,7,8,9}
	b := []int{}
	for _, a := range a[:p] {b = append(b, a)}
	for _, a := range a[p+1:] {b = append(b, a)}
	return b
}

func fac(a int) (t int) {
	t = 1
	for ;a >= 1; a-- {
		t = t * a
	}
	return
}

//23. Find the sum of all the positive integers which CANNOT be written as the sum of two abundant numbers.

func Problem23() {

	//make abundants
	a := []int{}
	for i := 1; i <= 28123; i++ {
		if isAbundant(i) {a = append(a, i)}
	}	

	t := 0
	for i := 1; i <= 28123; i++ {
		lo := 0
		hi := len(a)-1
		for ;lo <= hi; {
			s := a[lo] + a[hi]	//s sum of two abundants
			if s == i {break}
			if s > i {hi--} else {lo++}
		}
		if lo> hi {t += i}
	}
	println(23, t)
}

func isAbundant(a int) bool {
	s := 1
	for i := 2; i*i <= a; i++ {
		if a%i == 0 {
			if a/i == i {s += i} else {s += i + a/i}
		}
	}
	return s > a
}

//22. What is the total of all the name scores in the file?

func Problem22() {

	// Names scores
	// Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
	// For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
	// What is the total of all the name scores in the file?

	bytes := ReadUrl("http://Problem.net/project/resources/p022_names.txt")

	// parse "name","name2" list
	names := strings.Split(string(bytes), ",")
	for i,_ := range names {
		names[i] = strings.Trim(names[i], "\"")
	}
	
    sort.Strings(names)
		
	total := 0
	for i, name := range names {
		nameScore := 0
		for _, byte := range name {
			nameScore += int(byte -64)
		}
		total += (i+1) * nameScore
	}
	
	fmt.Println(22, total) // 871198282 :)
	
}

func ReadUrl(url string) []byte {
	// To Do: error handling
	fmt.Printf("Reading %v...\n", url)
	resp, err := http.Get(url)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		panic(err)
	}
	return body
}

//21. Evaluate the sum of all the amicable numbers under 10000.


func Problem21() {

	a := []int{0} //zero important for positioning
	for i := 1; i < 10000; i++ {
		a = append(a, sumofproperdivisors(i))
	}

	o := []int{}
	for i, v := range a {
		if 1 < v && v < 10000 {
			if i == a[v] && i != v {
				o = append(o, i, a[v])
			}
		}
	}
	ans := sum(unique(o))
	println(21, ans)
}

func sumofproperdivisors(a int) (s int) {

	s = 1
	for i := 2; i*i <= a; i++ {	
		if a%i == 0 {
			s +=  i + (a/i)  
//BUG if i and a/i are same number then they're added twice
		}
	}
	return
}


//Find the sum of the digits in the number 100!

func Problem20() {

	a := make([]int, 1000)
	a[len(a)-1] = 1
	for i := 100; i >= 1; i-- {
		for j := range a {a[j] *= i}
		carry(a)
	}
	println(20, sum(a))

}

func carry(a []int) {
	
	for i := len(a)-1; i >= 10; i-- {
	
		r := []rune(strconv.Itoa(a[i]))
		a[i] = int(r[len(r)-1])-48
	
		//add []r []a starting at a[c]
		c := i+1-len(r)
		for i := 0; i < len(r)-1; i++ {
			a[c+i] += int(r[i])-48
		}
	}
}

//19. How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

func Problem19() {

	//1 jan 1900 was a monday
	//7 jan 1900 was a sunday
	//365%7 == 1 so 1-jan-1901 is a tuesday
	//sundays have remainder 6

	ny := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	ly := []int{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	n, fm, m := 0, 1, ny //first of the month, 

	for y := 1901; y <= 2000; y++ {
		if y%4 == 0 {m = ly} else {m = ny}
		for _, m := range m {
			fm += m
			if fm%7 == 6 {n += 1}
		}
	}
	if fm%7 == 6 {n -= 1}
	println(19, n)
}

func isLeapYear(y int) bool {
	switch {
	case y%400 == 0: return true
	case y%100 == 0: return false
	case y%4 == 0: return true
	}
	return false
}



//18. If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

func Problem18() {

	/*
	a: parse/all a "^/" 
	reverse a
	forall a [change a rejoin ["{" (replace/all form to-block a/1 " " ", ") "}, "]]
	*/
	
	a := [][]int {{4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23}, {63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31}, {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48}, {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57}, {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14}, {41, 48, 72, 33, 47, 32, 37, 16, 94, 29}, {41, 41, 26, 56, 83, 40, 80, 70, 33}, {99, 65, 4, 28, 6, 16, 70, 92}, {88, 2, 77, 73, 7, 63, 67}, {19, 1, 23, 75, 3, 34}, {20, 4, 82, 47, 65}, {18, 35, 87, 10}, {17, 47, 82}, {95, 64}, {75}}
	
	for i := 0; i < len(a)-1; i++ {
		fl, sl := a[i], a[i+1]	//first line, second line
		for i := range sl {
			sl[i] += max(fl[i], fl[i+1])
		}
	}
	ans := a[len(a)-1][0]
	println(18, ans)
}

//If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

func Problem17() {

	a := len([]rune("onetwothreefourfivesixseveneightnine"))
	b := len([]rune("teneleventwelvethirteenfourteenfifteensixteenseventeeneighteennineteen"))
	c := len([]rune("twentythirtyfortyfiftysixtyseventyeightyninety"))
	d := len([]rune("onehundredandtwohundredandthreehundredandfourhundredandfivehundredandsixhundredandsevenhundredandeighthundredandninehundredand"))
	e := len([]rune("onehundredtwohundredthreehundredfourhundredfivehundredsixhundredsevenhundredeighthundredninehundredonethousand"))
	
	l99 := a + b + (10 * c) + (8 * a)  	//length from 1 to 99
	ans := e + (99 * d) + (10 * l99)
	println(17, ans)
}

//16. What is the sum of the digits of the number 21000?

func Problem16() {
	a := 1.0
	for i := 1; i <= 1000; i++ {
		a = 2*a
	}
	s := strconv.FormatFloat(a, 'f', 0, 64)
	r := []rune(s)
	t := 0
	for _, r := range r {
		t = t + int(r-48)
	}
	println(16, t)	
}	


//15. How many routes are there through a 2020 grid?

func Problem15() {
	f := binomialCoefficient(40, 20)
	println(15, strconv.FormatFloat(f, 'f', 0, 64))
}

func factorial(a float64) (t float64) {
	for t = 1;a >= 1; a-- {
		t = t * a
	}
	return
}

func binomialCoefficient(n, k float64) float64 {
	return factorial(n) / factorial(n - k) / factorial(k)
}

//14. Which starting number, under one million, produces the longest chain?


//14. Which starting number, under one million, produces the longest chain?
//http://stackoverflow.com/questions/2643260/project-euler-question-14-collatz-problem

func Problem14() {

	//m max, v value, cl chain length
	var i, mi, cl, mcl, v uint

	var lookup[1000000] uint

	for i = 1; i < 1000000; i++ {
		v = i
		cl = 0
		for ; v > 1; {
			if v%2 == 0 {
				v = v / 2
			} else {
				v = 3*v + 1
			}
			cl++ 
			if v < 1000000 {
				if lookup[v] != 0 {
					cl += lookup[v]
					break
				}
			}			
		}
		lookup[i] = cl
		if cl > mcl {
			mcl = cl
			mi = i
		}
	}
	println(14, mi)
//	println(14, strconv.FormatFloat(mi, 'f', 0, 64))
}


//1. Add all the natural numbers below one thousand that are multiples of 3 or 5.

func Problem1() {
	s := 0
	for n := 1; n < 1000; n++ {
		switch {
		case n%5 == 0: s += n
		case n%3 == 0: s += n
		}
	}
	println(1, s)
}

//2. By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.

func Problem2() {
	a, b, c, s := 0, 1, 0, 0
	
	for ;c <= 4000000; {
		c = a + b		
		if c%2 == 0 {s += c}
		a = b
		b = c
	}
	println(2, s)
}

//3. What is the largest prime factor of the number 600851475143 ?

func Problem3() {

	a := 600851475143.0
	for i := 2.0; i*i <= a; i++ {
		if math.Mod(a, i) == 0 {
			a = a / i
		}
	} 
	println(3, int(a))
}


//4. Find the largest palindrome made from the product of two 3-digit numbers.

func isPalindrome(a string) bool {
	for i, j := 0, len(a)-1; i < j; i, j = i+1, j-1 {
	    if a[i] != a[j] {return false}
	}
	return true
}
//equivalent rebol is   s: form s s = reverse s 

func Problem4() {
	m, ij := 0, 0
	for i := 999; i > 99; i-- {
		for j := 999; j > 99; j-- {
			ij = i*j
			s := strconv.Itoa(ij)
			if isPalindrome(s) && ij>m {
				m = ij
			}
		}
	}
	println(4, m)
}


//5. What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

func Problem5() {
	a, b, c := [][]int{}, []int{}, []int{} 
	for i := 1; i <= 20; i++ {
		pf := primeFactorsOf(i)
		a = append(a, pf)
		for _, pf := range pf {b = append(b, pf)}
	}
	for _, b := range unique(b) {
		m := 1
		for _, a := range a {m = max(m, howMany(a, b))}
		for i  := 1; i <= m; i++ {c = append(c, b)}
	}
	println(5, product(c))
}

func Problem5b() {
	a := 1
	for i := 2; i <= 20; i++ {a = lcm(a, i)}
	println(a)
}
	
//6. Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

func Problem6() {
	s := 0
	for i := 1; i <= 100; i++ {s = s + i}
	
	t := 0
	for i := 1; i <= 100; i++ {
		t = t + (i*s) - (i*i)
	}
	println(6, t)
}

//7. What is the 10 001st prime number?

func Problem7() {
	p := []int{}
	isPrime := false
	for i := 2; len(p)<=10000; i++ {
		isPrime = true
		for _, v := range p {
			if i%v == 0 {
				isPrime = false
				break
			}
		}
		if isPrime {p = append(p, i)}
	}
	println(7, p[len(p)-1])
}


//8. Find the greatest product of five consecutive digits in the 1000-digit number.

func Problem8() {
	s := "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"	
	a := stringToInts(s)
	
	m := 0
	for i := 0; i < len(a)-5; i++ {
		m = max(m, product(a[i:i+5]))
	}
	println(8, m)
}

func stringToInts(s string) (o []int) {
	a := []byte(s)
	for _, v := range a {
		o = append(o, int(v-48))
	}
	return
}

//9. Find the product abc where a<b<c, a2+b2=c2, and a+b+c=1000

func Problem9() {
	var a, b, c, ans float64
	
	for a = 1; a <= 1000; a++ {
		for b = 1; b <= 1000; b++ {
		
			c = math.Sqrt((a*a)+(b*b))
			if 1000 == a+b+c {ans = a*b*c}
		}
		if ans != 0 {break}
	}
	println(9, int(ans))
}

//10. Find the sum of all the primes below two million. Slow

func isPrime(a int) bool {
	for i := 3; i*i <= a; i = i + 2 {
		if a%i == 0 {return false}
	}
	return true
}

func Problem10() {
	
	t := 0.
	for i := 3; i < 2000000; i = i + 2 {
		if isPrime(i) {t += float64(i)}
	}
	println(10, strconv.FormatFloat(t, 'f', 0, 64)) //fmt.

}

//What is the greatest product of four adjacent numbers in any direction (up, down, left, right, or diagonally) in the 2020 grid? Grid at http://Problem.net/problem=11

func Problem11() {
	a := []int{8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8, 49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, 0, 81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65, 52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91, 22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80, 24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50, 32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70, 67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21, 24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72, 21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95, 78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92, 16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57, 86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58, 19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40, 4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66, 88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69, 4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36, 20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16, 20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54, 1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48}

	m := 0
	
	for i := 0; i < len(a)-3; i++ {
		m = max(m, a[i] * a[i+1] * a[i+2] * a[i+3])
	}
	
	for i := 0; i < len(a)-60; i++ {
		m = max(m, a[i] * a[i+20] * a[i+40] * a[i+60])
	}
	
	for i := 0; i < len(a)-63; i++ {
		m = max(m, a[i] * a[i+21] * a[i+42] * a[i+63])
	}

	for i := 3; i < len(a)-57; i++ {
		m = max(m, a[i] * a[i+19] * a[i+38] * a[i+57])
	}
	println(11, m) //70600674
}

//12. What is the value of the first triangle number to have over five hundred divisors? Ans 7.65765e+07


func Problem12() {
	tn := 0
	for i := 1;; i++ {
		tn = tn + i
		
		d := 0
		for i := 1; i*i <=tn; i++ {
			if tn%i == 0 {d = d + 2}
		} 
		if d>500 {
			println(12, tn)
			break
		}
	}
}

//13. Work out the first ten digits of the sum of the following one-hundred 50-digit numbers. Ans 5537376230 

func Problem13() {
	a := []float64 {3.71072875339021E+49, 4.637693767749E+49, 7.43249861995247E+49, 9.19422133635742E+49, 2.30675882075393E+49, 8.92616706966236E+49, 2.811287981285E+49, 4.42742289174325E+49, 4.74514457360013E+49, 7.0386486105843E+49, 6.21764571418566E+49, 6.49063524627419E+49, 9.25758677183372E+49, 5.82035653253594E+49, 8.01811993848263E+49, 3.53986643728271E+49, 8.65155060062959E+49, 7.16938887077155E+49, 5.43700705768267E+49, 5.32826541087568E+49, 3.61232725250003E+49, 4.5876576172411E+49, 1.74237069058519E+49, 8.11426604180868E+49, 5.19343254517284E+49, 6.24672216484351E+49, 1.57324443869081E+49, 5.50376875256788E+49, 1.83363848253302E+49, 8.03862875928785E+49, 7.81828337579931E+49, 1.67263201004369E+49, 4.84030981290778E+49, 8.70869875513927E+49, 5.99594068957565E+49, 6.97939506796527E+49, 4.10526847082991E+49, 6.53786073615011E+49, 3.58290353174347E+49, 9.49537597651053E+49, 8.89028025717332E+49, 2.5267680276078E+49, 3.62702185404977E+49, 2.40744869082312E+49, 9.14302881971033E+49, 3.44130655780161E+49, 2.30530811728164E+49, 1.14876969321549E+49, 6.37832994906363E+49, 6.77201869716985E+49, 9.55482553002635E+49, 7.60853271322857E+49, 3.77742425354113E+49, 2.37019132757257E+49, 2.97988602722583E+49, 1.84957014548793E+49, 3.82982037830315E+49, 3.48295438291999E+49, 4.09579530664052E+49, 2.97461521855024E+49, 4.1698116222073E+49, 6.24679571944013E+49, 2.31897067725479E+49, 8.61880882258753E+49, 1.13067397083047E+49, 8.29591747671404E+49, 9.76233310448184E+49, 4.28462801835171E+49, 5.51216035469812E+49, 3.22381957343293E+49, 7.55061649651848E+49, 6.21778427521926E+49, 3.29241857071473E+49, 9.95186714302352E+49, 7.32674608005915E+49, 7.68418225246744E+49, 9.71426179103426E+49, 8.77836461827993E+49, 1.08488025216747E+49, 7.13296124747825E+49, 6.21840735723998E+49, 6.66278919814881E+49, 6.06618262936828E+49, 8.5786944089553E+49, 6.60243964099054E+49, 6.4913982680033E+49, 1.67309393198728E+49, 9.48093772450488E+49, 7.86391670211875E+49, 1.53687137119366E+49, 4.07899231155356E+49, 4.48899115014406E+49, 4.15031288803395E+49, 8.12348806732101E+49, 8.26165707739483E+49, 2.29188020587773E+49, 7.71585425020165E+49, 7.21078384350692E+49, 2.0849603980134E+49, 5.35035342264725E+49}
	s := 0.0
	for _, v := range a {
		s = s + v
	}
	//println(s) //fmt.

	r := []rune(strconv.FormatFloat(s, 'f', 0, 64))
	println(13, string(r[0:9]))
}

func product(a []int) (t int) {
	t = 1
	for _, v := range a {
		t = t * v
	}
	return
}

func max(a, b int) int {
	if b > a {a = b}
	return a
}

func unique(a []int) (o []int) {
	for i := range a {
		if not(find(o, a[i])) {
			o = append(o, a[i])
		}
	}
	return
}

func find(a []int, b int) bool {
	for i := range a {
		if a[i] == b {return true}
	}
	return false
}

func not(a bool) bool {
	return !a
}

func exclude(a []int, b []int) (o []int) {
	for i := range a {
		if not(find(b, a[i])) {
			o = append(o, a[i])
		}
	}
	return
}	

func howMany(a []int, b int) (n int) {
	for _, v := range a {
		if b == v {n = n + 1}
	}
	return 
}
//howMany(3, {3, 4, 3}} == 2 
//how many 3's are there in the slice

func primeFactorsOf(a int) (o []int){
	for i := 2; a != 1; {
		if a%i == 0 {
			a = a / i
			o = append(o, i)
		} else {
			i++
		}
	} 
	return
}

func lcm(n, m int) (i int) {
	i = min(n, m)
	for ;;i++ {
		if i%n == 0 && i%m == 0 {break}
	}
	return
}

func min(a, b int) int {
	if a <= b {return a}
	return b
}

func maximumOf(a []int) (mx int) {
	for _, v := range a {
		if v > mx {mx = v}
	}
	return
}

func factorize(a float64) (o []float64){

	for i := 1.0; i*i <= a; i++ {
		if math.Mod(a, i) == 0 {
			o = append(o, i, a/i)
		}
	} 
	return
}

func sum(a []int) (t int) {
	t = 0.
	for _, v := range a {
		t = t + v
	}
	return
}


