# Copyright © 2022 The Certsar Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#   ██████╗███████╗██████╗ ████████╗███████╗ █████╗ ██████╗
#  ██╔════╝██╔════╝██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██╔══██╗
#  ██║     █████╗  ██████╔╝   ██║   ███████╗███████║██████╔╝
#  ██║     ██╔══╝  ██╔══██╗   ██║   ╚════██║██╔══██║██╔══██╗
#  ╚██████╗███████╗██║  ██║   ██║   ███████║██║  ██║██║  ██║
#   ╚═════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝

 ifeq (, $(shell which clang))
 $(error "No clang found. Please install clang for compiling!")
 endif

CC=clang
CFLAGS=-ltcap
DEPS = tlsdump.c
OBJ = tlsdump.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tlsdump: $(OBJ) ## Generate the main tlsdump program
	$(CC) -o $@ $^ $(CFLAGS)

clean:  ## Show help messages for make targets
		rm -rf *.o
		rm -rf tlsdump

install:  ## Install tlsdump to /usr/local/bin
		chmod +x tlsdump
		cp tlsdump /usr/bin/tlsdump

.PHONY: help
help:  ## Show help messages for make targets
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-30s\033[0m %s\n", $$1, $$2}'