# AxE

Brief description or purpose of the project.

## Installation

### Prerequisites
- Ubuntu 18.04
- Set the username to "user" (without quotation)

### Steps for RISC-V Toolchain (rv32i)

```bash
cd
sudo mkdir /opt/riscv32i
sudo chown $USER /opt/riscv32i
git clone https://github.com/riscv/riscv-gnu-toolchain riscv-gnu-toolchain-rv32i
cd riscv-gnu-toolchain-rv32i/
git checkout 411d134
git submodule update --init --recursive
mkdir build; cd build
../configure --with-arch=rv32i --prefix=/opt/riscv32i
make -j$(nproc)
```

### Steps for RISC-V Toolchain (rv32im)

```bash
cd
sudo mkdir /opt/riscv32im
sudo chown $USER /opt/riscv32im
git clone https://github.com/riscv/riscv-gnu-toolchain riscv-gnu-toolchain-rv32im
cd riscv-gnu-toolchain-rv32im/
git checkout 411d134
git submodule update --init --recursive
mkdir build; cd build
../configure --with-arch=rv32im --prefix=/opt/riscv32im
make -j$(nproc)
```

### Verilator Installation

```bash
cd
sudo apt-get install git perl python3 make autoconf g++ flex bison ccache libfl2 libfl-dev  zlibc zlib1g zlib1g-dev libgoogle-perftools-dev numactl perl-doc
git clone https://github.com/verilator/verilator 
unset VERILATOR_ROOT
cd verilator
git pull
git checkout v4.028
autoconf
./configure
make -j `nproc`
sudo make install
```

### SOC Frame Setup

1. Extract the SOC_FRAME tar files.
2. Rename the folder to "soc_frame."
3. Ensure the full address is "/home/user/soc_frame."
   - If not feasible, search for "/home/user/soc_frame" in all files and replace it with the desired path.
   - The path should not have spaces in it.

## Note

The simulation method described in the videos is not visible to the debugger. To debug, bypass `main.py` and modify `run_mpsoc.py`. Debug it in a suitable IDE, such as VSCode.
```

Replace "Project Name" with the actual name of your project and add a brief description or purpose. Make sure to adjust any specific details based on the requirements of your project. Copy and paste this into your README file in your GitHub repository.
