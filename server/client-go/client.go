// A simple example of a client in Go.

package main

import (
	"log"
	"net"
)

func main() {
	// Print the file and line number to each log call.
	log.SetFlags(log.Lshortfile)

	// Open connexion
	serverAddr, err := net.ResolveUDPAddr("udp", ":5000")
	if err != nil {
		log.Fatalln("Resolve server addr fail:", err)
	}
	conn, err := net.DialUDP("udp", nil, serverAddr)
	if err != nil {
		log.Fatalln("Open UDP fail:", err)
	}
	defer conn.Close()

	// Send a request
	// Uncomment one of these followed line
	// _, err = conn.Write([]byte("exe:reset 0 0"))
	// _, err = conn.Write([]byte("exe:stop 0 0"))
	// _, err = conn.Write([]byte("exe:axe 42 93"))
	_, err = conn.Write([]byte("exe:move 42 93"))
	if err != nil {
		log.Fatalln("Fail to send a request to the server:", err)
	}

	// Read the response
	buff := make([]byte, 1024)
	nbReaded, err := conn.Read(buff)
	if err != nil {
		log.Fatalln("Fail to read response", err)
	}
	buff = buff[:nbReaded]
	log.Printf("buff: %q\n", buff)
}
