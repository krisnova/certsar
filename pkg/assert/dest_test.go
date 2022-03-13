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

package assert

import (
	"net"
	"testing"
)

func TestDestinationIs(t *testing.T) {
	conn, err := net.Dial("tcp", "localhost:")
	if err != nil {
		t.Errorf("unable to dial: %v", err)
	}
	DestinationIs(conn, conn)
	if !DestinationIs(conn, conn) {
		t.Errorf("Destination is failed")
	}
}

func TestDestinationIsNot(t *testing.T) {
	conn1, err := net.Dial("tcp", "localhost:")
	if err != nil {
		t.Errorf("unable to dial: %v", err)
	}
	conn2, err := net.Dial("tcp", "localhost:")
	if err != nil {
		t.Errorf("unable to dial: %v", err)
	}
	if !DestinationIsNot(conn1, conn2) {
		t.Errorf("Destination is not failed")
	}
}
