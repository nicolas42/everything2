// usage:
// go run serve.go -d <path>

package main

import (
	"flag"
	"log"
	"net/http"
)

func main() {
	directory := flag.String("d", ".", "the directory of static file to host")
	port := flag.String("p", "8080", "port to serve on")
	flag.Parse()

	http.Handle("/", http.FileServer(http.Dir(*directory)))

	// log.Printf("Serving %s on HTTP port: %s\n", *directory, *port)
	log.Printf("Go to http://localhost:8080\n")
	
	log.Fatal(http.ListenAndServe(":"+*port, nil))
}
