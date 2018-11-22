GCCPARAMS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
-nostartfiles  -nodefaultlibs

NASMPARAMS = -f elf

LDPARAMS = -melf_i386 

BOOT = boot.o

OBJECT = boot.o main.o console.o string.o kprint.o v_print.o segment.o gdt.o \
idt.o interrupt.o pic.o pit.o keyboard.o sched.o do_shell.o syscall.o mm.o \
malloc.o heap.o list.o panic.o assert.o do_login.o heap_list.o fs.o\
vgacontroller.o ramdisk.o

%.o: boot/%.asm
	nasm $(NASMPARAMS) -o $@ $<

%.o: init/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: fs/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: kernel/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: drivers/ramdisk/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: drivers/gpu/vga/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: kernel/asm/%.asm
	nasm $(NASMPARAMS) -o $@ $<

%.o: app/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: library/%.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: library/heap/%.c
	gcc $(GCCPARAMS) -o $@ -c $<


nadia.bin: linker.ld $(OBJECT)
	ld $(LDPARAMS) -T $< -o $@ $(OBJECT)

install: nadia.bin
	sudo cp $< /boot/nadia.bin
	

nadia.iso: nadia.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My operating system" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/nadia.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
	rm -f *.o *.img *.bin
qemu:
	qemu-system-x86_64 -cdrom nadia.iso
clean: 
	rm -f *.o *.img *.bin
	sudo rm -f /boot/nadia.bin

build:
	make clean
	make install
	make nadia.iso
	make qemu