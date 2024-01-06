# C_pico_skelett
Skeleton project in C (using some C23 features) for Raspberry Pi Pico.


### Regenerate build files:
```console
[anders@dat-stordator C_pico_skelett]$ ./regenerate
```

### Compile:
```console
[anders@dat-stordator C_pico_skelett]$ ./rebuild
```

### Resulting files:
```console
[anders@dat-stordator C_pico_skelett]$ file build/skelett.*
build/skelett.bin:     data
build/skelett.dis:     ASCII text
build/skelett.elf:     ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), statically linked, with debug_info, not stripped
build/skelett.elf.map: assembler source, ASCII text
build/skelett.hex:     ASCII text, with CRLF line terminators
build/skelett.uf2:     UF2 firmware image, family Raspberry Pi RP2040, address 0x10000000, 35 total blocks
```

### Upload:
```console
[anders@dat-stordator C_pico_skelett]$ ./reflash
```
