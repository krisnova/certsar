all: compile

# Global release version.
# Change this to bump the build version!
version="0.0.1"

compile: ## Compile for the local architecture ⚙
	@echo "Compiling..."
	go build -ldflags "-X 'github.com/kris-nova/certsar.Version=$(version)'" -o certsar cmd/*.go
