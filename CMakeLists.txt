cmake_minimum_required(VERSION 2.8)
PROJECT(KrzysiekKomp)

INCLUDE_DIRECTORIES(lib)
INCLUDE_DIRECTORIES(src)

SET(CMAKE_CXX_FLAGS "-m32 -std=gnu++98 -ffreestanding -fno-rtti -fno-exceptions -fnostdlib -fnostdinc -fno-stack-protector")
SET(CMAKE_C_FLAGS "-m32 -std=gnu99 -ffreestanding -fno-exceptions -nostdlib -nostdinc -fno-stack-protector")
SET(CMAKE_EXE_LINKER_FLAGS "-m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/linker.ld")
SET(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
ENABLE_LANGUAGE(ASM_NASM)

SET(SRC
src/boot.asm
src/main.c
src/screen/text_screen.c
src/arch/gdt.c
src/arch/gdt.asm
src/arch/idt.c
src/arch/idt.asm
src/arch/exceptions.c
src/arch/exceptions.asm
src/services/clock.c
src/services/clock.asm
src/services/keyboard.c
src/services/keyboard.asm
src/memory/memory.c
)

ADD_LIBRARY(kernel.img STATIC ${SRC})
ADD_CUSTOM_COMMAND(TARGET kernel.img POST_BUILD COMMAND ld -m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/linker.ld -o ${CMAKE_BINARY_DIR}/KrzysiekKomp.bin ${CMAKE_BINARY_DIR}/libkernel.img.a)
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_BINARY_DIR}/KrzysiekKomp.bin)
