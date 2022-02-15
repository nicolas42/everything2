// download url(s)
// usage: go run download.go url1 url2 url3

// based on https://gist.github.com/nevermosby/b54d473ea9153bb75eebd14d8d816544

// sync.WaitGroup
// a wait group is basically just the number of threads currently running with a mutex around it
// make sure to pass them as a pointer  (*sync.WaitGroup) or they won't work properly

// How to get image urls with google images
// ----------------------------------------------------------
// Open a browser and make sure your adblocker is off.  Using privacy mode can sometimes be an easy way of disabling all extensions.
// Go to google images and search for your image.  Scroll down to load as many images as you want. 
// Open the console (ctrl+shift+j in chrome) and run the following code.  Make sure adblocker is off or be in privacy mode or some equivalent or the window won't open.
//
//     urls = Array.from(document.querySelectorAll('.rg_di .rg_meta')).map(el=>JSON.parse(el.textContent).ou);
//     window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));
//


package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"strings"
	"sync"
	"strconv"
	"bufio"
)

func download(url string) {
	// take the filename as the last part of the path	
	tokens := strings.Split(url, "/")
	filename := tokens[len(tokens)-1]
	fmt.Println("Downloading", url, "to", filename)
	// create file
	output, err := os.Create(filename)
	if err != nil {
		log.Fatal("Error while creating", filename, "-", err)
	}
	defer output.Close()
	// download with get request
	res, err := http.Get(url)
	if err != nil {
		log.Fatal("http get error: ", err)
	} 
	defer res.Body.Close()
	// copy the response body to the file
	_, err = io.Copy(output, res.Body)
	if err != nil {
		log.Fatal("Error while downloading", url, "-", err)
	} else {
		fmt.Println("Downloaded", filename)
	}
}

func download_multiple(urls []string) {

	var wg sync.WaitGroup
	wg.Add(len(urls))
	for _, url := range urls {
		go func(url string){
			defer wg.Done()
			download(url)
		}(url)
	}
	wg.Wait()

}

func path_exists(path string) bool {
	// os_stat: get status of the specified path
	_, err := os.Stat(path)
	return err == nil
}

func request_make_dir(root_dir string) string {
	// make the directory or a renamed version
	// return the actual path that is made
	// usage: dir := request_make_dir("downloads")
	path := root_dir
	for i:=1; path_exists(path); i+=1 {
		path = strings.Join([]string{root_dir, strconv.Itoa(i)}, " ")
	}
	os.Mkdir(path, 0777)
	return path
}

func read_lines(path string) ([]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines, scanner.Err()
}

func main() {

	// // supply urls through the terminal
	// // go run download.go https://www.outsideonline.com/sites/default/files/styles/full-page/public/2019/09/13/trump-polar-bears_h.jpg https://www.outsideonline.com/sites/default/files/styles/img_600x600/public/2019/09/09/bear-family-in-field_s.jpg
	// urls := os.Args[1:]
	// for _, url := range urls { fmt.Println(url) }


	// supply urls with a file
	urls, err := read_lines("urls.txt")
	if err != nil {
		log.Fatal("couldn't read the urls file", err)
	}


	// // supply urls in program
	// urls := []string{
	// 	"https://www.outsideonline.com/sites/default/files/styles/full-page/public/2019/09/13/trump-polar-bears_h.jpg",
	// 	"https://www.outsideonline.com/sites/default/files/styles/img_600x600/public/2019/09/09/bear-family-in-field_s.jpg",
	// 	"https://www.banffjaspercollection.com/Brewster/media/Images/Stories/2019/04/MBN-Bears-Grizzly-Bear-Dandelions.jpg",
	// 	"https://19mvmv3yn2qc2bdb912o1t2n-wpengine.netdna-ssl.com/science/files/2019/01/bear-featured-image-1200x708.jpg",
	// 	"https://media.npr.org/assets/img/2018/03/26/picture1-femalewithcub_wide-311cc2a65f12f1bed7475c3672944954e60fa85a-s800-c85.jpg",
	// }


	// safely make a directory
	dir := request_make_dir("downloads")

	// change dir and restore it back at the end
	original_dir, err := os.Getwd()
	if err != nil {
		log.Fatal("Error while getting working directory", err)
	}
	defer os.Chdir(original_dir)
	os.Chdir(dir)

	// download 1 file
	// download(urls[0])

	// download a bunch of files in parallel
	download_multiple(urls)

	fmt.Println("Done")
}

