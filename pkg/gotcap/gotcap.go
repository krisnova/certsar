// Copyright © 2022 The Certsar Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//   ██████╗███████╗██████╗ ████████╗███████╗ █████╗ ██████╗
//  ██╔════╝██╔════╝██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██╔══██╗
//  ██║     █████╗  ██████╔╝   ██║   ███████╗███████║██████╔╝
//  ██║     ██╔══╝  ██╔══██╗   ██║   ╚════██║██╔══██║██╔══██╗
//  ╚██████╗███████╗██║  ██║   ██║   ███████║██║  ██║██║  ██║
//   ╚═════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝

package gotcap

// #cgo LDFLAGS: -ltcap -lpcap
//
// #include "tcap.h"
// #include "pcap.h"
import "C"
import (
	"fmt"
	"net"
)

const (
	// TCAP_MAX_DIGEST_PACKET is taken from tcap.h
	TCAP_MAX_DIGEST_PACKET int = 32
)

// TCAPDigest corresponds to the digest offered in the tcap.h header file.
// This represents a TLS digest being snigged off the network using tcpdump.
type TCAPDigest struct {
	Destination *net.Conn
	Dest        [6]*C.uchar
	Packets     [TCAP_MAX_DIGEST_PACKET]*C.uchar
}

// TCAPNext can be perpetually called to find the next TLS digest from the network.
func TCAPNext() *TCAPDigest {
	tcapdigest := &TCAPDigest{}
	d := C.tcap_next()
	tcapdigest.Packets = d.packets
	tcapdigest.Dest = d.destination

	// Find source and destination
	px := tcapdigest.Packets[0]

	fmt.Println(px)
	fmt.Println(tcapdigest.Dest)
	return tcapdigest
}

//func ucharToString(c *C.uchar) string {
//	var buf []byte
//	for *c != 0 {
//		buf = append(buf, *c)
//		c = (*C.uchar)(unsafe.Pointer(uintptr(unsafe.Pointer(c)) + 1))
//	}
//	return string(buf)
//}
