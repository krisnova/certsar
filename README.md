# Certsar

TLS Cert capture, prevention and detection.

Send operational context to the runtime, block and alert when specific TLS material is identified at runtime.

For those "Special Encryption Operations"

```bash
sudo -E make tcap compile install 
sudo -E LD_LIBRARY_PATH=/usr/local/lib certsar
```

## tcap (c)

TLS Capture Library. 

Responsible for reporting when the TLS handshake occurs on a system.

Current implementations: 

 - `libpcap` which parses userspace via `tcpdump`. 

## certsar (go) 

TLS Cert assertion, validation, verification, and control mechanism written in Go.

Block certs, alert on certs, lookup certs.