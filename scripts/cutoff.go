package main

// Right now, this program merely provides a transparent or translucent proxy.

import (
	"flag"
	"net"
	"log"
)

// Right now this merely provides a transparent or translucent proxy.
func handleConnection(in net.Conn, outaddr string) {
	defer in.Close()

	out, err := net.Dial("tcp", outaddr)
	if err != nil {
		log.Printf("From %v: Could not forward connection: %v\n",
			in.RemoteAddr(), err)
		return
	}
	defer out.Close()

	log.Printf("connect %v on %v: %v -> %v\n", in.RemoteAddr(), in.LocalAddr(), in, out)
	buf := make([]byte, 4096)
	for {
		nread, err := in.Read(buf)
		if err != nil {
			log.Printf("Read error on %v: %v\n", in, err)
			return
		}

		nwritten, err := out.Write(buf[:nread])
		if err != nil {
			log.Printf("Write error on %v: %v\n", in, out, err)
			return
		}
		if nwritten != nread {
			log.Printf("Short write on %v: %v\n", in, out, err)
			return
		}
	}
}

func main() {
	var inaddr = flag.String("in", ":12015", "listening port")
	var outaddr = flag.String("out", ":29015", "connecting port")
	flag.Parse()

	ln, err := net.Listen("tcp", *inaddr)
	if err != nil {
		log.Fatal(err)
	}

	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
			continue
		}

		log.Println(
			"Connected from",
			conn.RemoteAddr(),
			"on",
			conn.LocalAddr())
		go handleConnection(conn, *outaddr)
	}
}
