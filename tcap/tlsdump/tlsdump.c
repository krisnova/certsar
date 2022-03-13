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

// Include the global tcap header
#include "tcap.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void usage(void) {
    printf("\n");
    printf("tlsdump: TLS capture utility\n");
    printf("\n");
    about(); //tcap details
    printf("\n");
    printf("tlsdump [options...] \n");
    printf("\n");
    printf("[Options]\n");
    printf("\n");
    printf("  -h               print the usage and help screen.\n");
    printf("\n");

}

// main
//
// Main entrypoint for tlsdump
//
int main (int argc, char **argv) {

    int help = 0;
    int option;

    while (optind < argc) {
        if ((option = getopt(argc, argv, "hjrx")) != -1) {
            switch (option) {
                case 'h':
                    usage();
                    return 1;
                default:
                    usage();
                    return 1;
            }
        } else {
            // This is the system that will handle
            // command line values other than flags
            // optind = 0 : tlsdump
            // optind = 1 : <input>
            if (optind == 1) {
                // Parse input
            }
        }
        optind++;
    }

    usage();

}
