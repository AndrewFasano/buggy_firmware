Example FW
----------

Minimal FW that has some buggy network services listening for UDP
traffic on ports 8080 and 9000. Note that this FW will not actually run as
it depends on some assumptions about our internal rehosting tools.

Both network services expect a key, a 32-bit message size, then a message of
that size.  The service on port 8080 has a key of `hi` and the service on 9000
has a key of `foo`.

### Example messages:
```
echo -ne "hi\x00\x00\x00\x04ABCD" | nc firmware 8080
echo -ne "foo\x00\x00\x00\x03ABC" | nc firmware 9000
```

# Compiling
Get a mips cross compilier with g++ (i.e., not the one from Firmadyne).

```
make CC=/opt/cross/mips-linux-gnu-gcc/bin/mips-linux-gnu-g++
```

Your "firmware" will then be created, named image.tar.gz.
