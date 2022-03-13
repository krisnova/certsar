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

const (
	// TCAP_MAX_DIGEST_PACKET is taken from tcap.h
	TCAP_MAX_DIGEST_PACKET int = 32
)

// TCAPDigest corresponds to the digest offered in the tcap.h header file.
// This represents a TLS digest being snigged off the network using tcpdump.
type TCAPDigest struct {
	Packets [TCAP_MAX_DIGEST_PACKET]*C.uchar
}

// TCAPNext can be perpetually called to find the next TLS digest from the network.
func TCAPNext() *TCAPDigest {
	tcapdigest := &TCAPDigest{}
	d := C.tcap_next()
	tcapdigest.Packets = d.packets
	return tcapdigest
}
