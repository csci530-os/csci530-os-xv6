# Xv6 Repositories

The Xv6 source repositories for the code, and the companion
textbook will reside here.

- [xv6-riscv code repository](https://github.com/mit-pdos/xv6-riscv)
- [xv6-riscv-book](https://github.com/mit-pdos/xv6-riscv-book)

## Testing Your Installation

The riscv gnu gcc toolchain and qemu emulator are installed as part
of the class container.  Check you have the correct tools available using the
following commands.

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ riscv64-linux-gnu-gcc --version
riscv64-linux-gnu-gcc (Debian 14.2.0-19) 14.2.0
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ qemu-system-riscv64 --version
QEMU emulator version 10.0.11 (Debian 1:10.0.11+ds-0+deb13u1)
Copyright (c) 2003-2025 Fabrice Bellard and the QEMU Project developers

```

## Compiling and Running xv6-riscv Code

Change into the repository 

```bash
$ cd xv6/xvc-riscv
```

If the correct riscv toolchain are installed, the make of the
qemu target will compile everything and start xv6 running in the
qemu emulator.  Use <Ctrl-a x> to exit (<Ctrl-a ?> to get qemu emulator help).

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ make qemu
qemu-system-riscv64 -machine virt -bios none -kernel kernel/kernel -m 128M -smp 3 -nographic -global virtio-mmio.force-legacy=false -drive file=fs.img,if=none,format=raw,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0

xv6 kernel is booting

hart 2 starting
hart 1 starting
init: starting sh
$ 
C-a h    print this help
C-a x    exit emulator
C-a s    save disk data back to file (if -snapshot)
C-a t    toggle console timestamps
C-a b    send break (magic sysrq)
C-a c    switch between console and monitor
C-a C-a  sends C-a
$ QEMU: Terminated

```

## Running xv6 with `gdb` Debugger

To step through xv6 code using gdb, in first terminal use the following
command to start xv6 as a gdb service that can be connected to remotely.
The `CPUS=1` flag limits the emulator to a single cpu, which makes
debugging much easier usually:

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ make CPUS=1 qemu-gdb
sed "s/:1234/:26000/" < .gdbinit.tmpl-riscv > .gdbinit
*** Now run 'gdb' in another window.
qemu-system-riscv64 -machine virt -bios none -kernel kernel/kernel -m 128M -smp 1 -nographic -global virtio-mmio.force-legacy=false -drive file=fs.img,if=none,format=raw,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 -S -gdb tcp::26000

```

Then open anohter terminal, ando perform the following.  A file named .gdbinit should have been created in the
`xv6-riscv` source code directory, as shown in the output above,

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6$ cd xv6/xv6-riscv
(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ cat .gdbinit
set confirm off
set architecture riscv:rv64
target remote 127.0.0.1:26000
symbol-file kernel/kernel
set disassemble-next-line auto
set riscv use-compressed-breakpoints yes
```

You may get a warning if you don't specify a `safe-path` for gdb.  So before
running gdb, perform the following to create a global gdbinit configuration file
that will always allow you to connect a gdb session:

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6$ mkdir -p ~/.config/gdb; echo "set auto-load safe-path /" >> ~/.config/gdb/gdbinit
```

You could also modify the `.gdbinit` file that was created ppreviously to add this
command, however this file is (re)generated each time you run the gdb debugger
like this, so it is more convenient to add the `safe-path` setting to
a global configuration one time.

Now from the same directory where the `.gdbinit` file was generated, run
the command:

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ gdb-multiarch -tui
```

Some basic `gdb` commands:

| **command**               | ** What it does **                                                |
| ------------------------- | ----------------------------------------------------------------- |
| `b param` / `break param` | Adds a breakpoint on symbol `param`                               |
| `c` / `continue`          | Will continue execution until next breakpoint                     |
| `s` / `step`              | Step into the current line, entering function call if needed      |
| `n` / `next`              | Continue to next line, not entering function call on current line |
| `watch expression`        | Will stop (break) when value of expression changes                |
| `rwatch expression`       | Will stop (break) when value of expression is read                |

I usually set a break on the `_entry` and/or on the `start` then do a
`continue` to jump to that point and step from there.

```bash
(base) student@93745a5fd049:/workspaces/csci530-os-xv6/xv6/xv6-riscv$ gdb-multiarch     
GNU gdb (Debian 16.3-1) 16.3
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
The target architecture is set to "riscv:rv64".
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x0000000000001000 in ?? ()
(gdb) b _entry
Breakpoint 1 at 0x80000000: file kernel/entry.S, line 12.
(gdb) b start
Breakpoint 2 at 0x80000058: file kernel/start.c, line 16.
(gdb) c
Continuing.

Breakpoint 1, _entry () at kernel/entry.S:12
12              la sp, stack0

```