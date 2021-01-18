=== the asys operating system ===

A basic, bare-metal microkernel + distributed OS.
Locality-transparent, simple, sensible.

You can run this thing over docker to get a feel for how it 
works (even though as of this writing the system doesn't do 
much! haha), via:

`docker run -it jaytlang/asys make sim`

Alternatively, you can install a toolchain and do serious
development! You'll need a bare-bones riscv64-unknown-elf-gcc
toolchain, which can be had via the following:

```
git clone https://github.com/riscv/riscv-gnu-toolchain

# install the build prereqs listed at the above URL! then,

cd riscv-gnu-toolchain/
sudo mkdir /opt/riscv
sudo chown -R $USER:$USER /opt/riscv
./configure --prefix=/opt/riscv
make -j$(nproc)
```

I also host a set of compiler binaries you can install:
https://web.mit.edu/jaytlang/www/ethwinter/toolchain.txz
You will need a working copy of libmpc, which can be had
via your system's package manager, along with obvious
stuff like a text editor, make, etc.

You'll also need qemu-system-riscv64, which can be installed
via your system's package manager pretty easily. Once
that's done, type `make sim` and you're off and running --
along with any other top-level makefile you command you want to.

One more thing! I welcome contributions. Run `make format` before
you commit on your branch (I'll make this a pre-commit hook
eventually) and then send me a patch!

