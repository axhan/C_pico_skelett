# C_pico_skelett
Skeleton project in C for Raspberry Pi Pico


### Regenerate build files:
```console
[anders@dat-stordator C_pico_skelett]$ ./regenerate
PICO_SDK_PATH is /home/anders/src/pico-sdk
Defaulting PICO_PLATFORM to rp2040 since not specified.
Defaulting PICO platform compiler to pico_arm_gcc since not specified.
-- Defaulting build type to 'Release' since not specified.
PICO compiler is pico_arm_gcc
-- The C compiler identification is GNU 13.2.0
-- The CXX compiler identification is GNU 13.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/arm-none-eabi-gcc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/arm-none-eabi-g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- The ASM compiler identification is GNU
-- Found assembler: /usr/bin/arm-none-eabi-gcc
Build type is Release
Defaulting PICO target board to pico since not specified.
Using board configuration from /home/anders/src/pico-sdk/src/boards/include/boards/pico.h
-- Found Python3: /usr/bin/python3.11 (found version "3.11.5") found components: Interpreter
TinyUSB available at /home/anders/src/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040; enabling build support for USB.
BTstack available at /home/anders/src/pico-sdk/lib/btstack
cyw43-driver available at /home/anders/src/pico-sdk/lib/cyw43-driver
Pico W Bluetooth build support available.
lwIP available at /home/anders/src/pico-sdk/lib/lwip
mbedtls available at /home/anders/src/pico-sdk/lib/mbedtls
-- Configuring done (0.9s)
-- Generating done (0.1s)
-- Build files have been written to: /mnt/ssd2p1/anders/Dropbox/projekt/C_pico_skelett/build
```

### Compile:
```console
[anders@dat-stordator C_pico_skelett]$ ./rebuild
[  1%] Building ASM object pico-sdk/src/rp2_common/boot_stage2/CMakeFiles/bs2_default.dir/compile_time_choice.S.obj
[  2%] Linking ASM executable bs2_default.elf
[  2%] Built target bs2_default
[  4%] Generating bs2_default.bin
[  5%] Generating bs2_default_padded_checksummed.S
[  5%] Built target bs2_default_padded_checksummed_asm
[  6%] Creating directories for 'ELF2UF2Build'
[  8%] No download step for 'ELF2UF2Build'
[  9%] No update step for 'ELF2UF2Build'
[ 10%] No patch step for 'ELF2UF2Build'
[ 12%] Performing configure step for 'ELF2UF2Build'
-- The C compiler identification is GNU 13.2.1
-- The CXX compiler identification is GNU 13.2.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/lib/ccache/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/lib/ccache/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.5s)
-- Generating done (0.0s)
-- Build files have been written to: /mnt/ssd2p1/anders/Dropbox/projekt/C_pico_skelett/build/elf2uf2
[ 13%] Performing build step for 'ELF2UF2Build'
[ 50%] Building CXX object CMakeFiles/elf2uf2.dir/main.cpp.o
[100%] Linking CXX executable elf2uf2
[100%] Built target elf2uf2
[ 14%] No install step for 'ELF2UF2Build'
[ 16%] Completed 'ELF2UF2Build'
[ 16%] Built target ELF2UF2Build
[ 17%] Building C object CMakeFiles/skelett.dir/source/config.c.obj
[ 18%] Building C object CMakeFiles/skelett.dir/source/debug.c.obj
[ 20%] Building C object CMakeFiles/skelett.dir/source/globals.c.obj
[ 21%] Building C object CMakeFiles/skelett.dir/source/memory.c.obj
[ 22%] Building C object CMakeFiles/skelett.dir/source/module1.c.obj
[ 24%] Building C object CMakeFiles/skelett.dir/source/module2.c.obj
[ 25%] Building C object CMakeFiles/skelett.dir/source/skelett.c.obj
[ 27%] Building C object CMakeFiles/skelett.dir/source/timer.c.obj
[ 28%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c.obj
[ 29%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_gpio/gpio.c.obj
[ 31%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_platform/platform.c.obj
[ 32%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_claim/claim.c.obj
[ 33%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_sync/sync.c.obj
[ 35%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_irq/irq.c.obj
[ 36%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_irq/irq_handler_chain.S.obj
[ 37%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_sync/sem.c.obj
[ 39%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_sync/lock_core.c.obj
[ 40%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_sync/mutex.c.obj
[ 41%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_sync/critical_section.c.obj
[ 43%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_time/time.c.obj
[ 44%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_time/timeout_helper.c.obj
[ 45%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_timer/timer.c.obj
[ 47%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_util/datetime.c.obj
[ 48%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_util/pheap.c.obj
[ 50%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/common/pico_util/queue.c.obj
[ 51%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_uart/uart.c.obj
[ 52%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_clocks/clocks.c.obj
[ 54%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_pll/pll.c.obj
[ 55%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_vreg/vreg.c.obj
[ 56%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c.obj
[ 58%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_xosc/xosc.c.obj
[ 59%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/hardware_divider/divider.S.obj
[ 60%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_runtime/runtime.c.obj
[ 62%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_printf/printf.c.obj
[ 63%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S.obj
[ 64%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c.obj
[ 66%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_divider/divider.S.obj
[ 67%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_double/double_aeabi.S.obj
[ 68%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_double/double_init_rom.c.obj
[ 70%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_double/double_math.c.obj
[ 71%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_double/double_v1_rom_shim.S.obj
[ 72%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_int64_ops/pico_int64_ops_aeabi.S.obj
[ 74%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_float/float_aeabi.S.obj
[ 75%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_float/float_init_rom.c.obj
[ 77%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_float/float_math.c.obj
[ 78%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_float/float_v1_rom_shim.S.obj
[ 79%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_malloc/pico_malloc.c.obj
[ 81%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_mem_ops/mem_ops_aeabi.S.obj
[ 82%] Building ASM object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_standard_link/crt0.S.obj
[ 83%] Building CXX object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_standard_link/new_delete.cpp.obj
[ 85%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_standard_link/binary_info.c.obj
[ 86%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_stdio/stdio.c.obj
[ 87%] Building C object CMakeFiles/skelett.dir/home/anders/src/pico-sdk/src/rp2_common/pico_stdio_uart/stdio_uart.c.obj
[ 89%] Linking CXX executable skelett.elf
[ 89%] Built target skelett
[ 90%] Creating directories for 'PioasmBuild'
[ 91%] No download step for 'PioasmBuild'
[ 93%] No update step for 'PioasmBuild'
[ 94%] No patch step for 'PioasmBuild'
[ 95%] Performing configure step for 'PioasmBuild'
loading initial cache file /mnt/ssd2p1/anders/Dropbox/projekt/C_pico_skelett/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp/PioasmBuild-cache-Release.cmake
-- The CXX compiler identification is GNU 13.2.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/lib/ccache/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /mnt/ssd2p1/anders/Dropbox/projekt/C_pico_skelett/build/pioasm
[ 97%] Performing build step for 'PioasmBuild'
[ 10%] Building CXX object CMakeFiles/pioasm.dir/main.cpp.o
[ 20%] Building CXX object CMakeFiles/pioasm.dir/pio_assembler.cpp.o
[ 30%] Building CXX object CMakeFiles/pioasm.dir/pio_disassembler.cpp.o
[ 40%] Building CXX object CMakeFiles/pioasm.dir/gen/lexer.cpp.o
[ 50%] Building CXX object CMakeFiles/pioasm.dir/gen/parser.cpp.o
[ 60%] Building CXX object CMakeFiles/pioasm.dir/c_sdk_output.cpp.o
[ 70%] Building CXX object CMakeFiles/pioasm.dir/python_output.cpp.o
[ 80%] Building CXX object CMakeFiles/pioasm.dir/hex_output.cpp.o
[ 90%] Building CXX object CMakeFiles/pioasm.dir/ada_output.cpp.o
[100%] Linking CXX executable pioasm
[100%] Built target pioasm
[ 98%] No install step for 'PioasmBuild'
[100%] Completed 'PioasmBuild'
[100%] Built target PioasmBuild
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
