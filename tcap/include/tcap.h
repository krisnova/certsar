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

#include "pcap.h"

#ifndef LIBTCAP_H
#define LIBTCAP_H

#define TCAP_MAX_DIGEST_PACKET 32

typedef struct tcap_digest {
    const u_char *destination[6];
    const u_char *packets[TCAP_MAX_DIGEST_PACKET];
} tcap_digest;

extern void about(void);
extern struct tcap_digest tcap_next(void);


#endif