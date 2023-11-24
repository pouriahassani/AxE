# AxE

The AxE project, initiated by Prof. Nima TaheriNejad and his group several years ago, is a long-term exploration of an SoC incorporating both exact and approximate CPU cores. This repository presents the SoC modules and the environment for assessing the design. The "soc_frame" directory serves as a framework tailored for easy adaptation in a test environment, encompassing Verilog hardware designs, executable C software, and a streamlined build system. This framework supports PicoRV32 and PiXoRV32 CPUs with approximate multiplication, the framework is designed for simplicity and compatibility with Multi-Processor SoCs (MPSoCs). Python-based build tools automate the test environment setup, while Verilator aids in hardware simulation. The README provides detailed installation instructions. We strongly recommend using the docker image, as all the tools are already installed and ready to explore the SoC.

## Installation Using Docker Image
Clone to AxE repository and move to the cloned repo:
```bash
git clone https://github.com/pouriahassani/AxE.git
cd AxE
```
Run the following in your Ubuntu system to pull the docker image from the docker hub:
```bash
docker pull poria19964214/axe:original
```
Now you can run an interactive docker container:
```bash
docker run -it -v $(pwd):/home/user/ axe:original
```
Using the `-v` option you use a docker volume where the current directory of your local machine is mapped to the `/home/user/` directory of the container. Any changes to this directory are reflected on both sides. 

## Installation without docker image
### Prerequisites
- Ubuntu 18.04
- Set the username to "user" (without quotation)

<details>
<summary>Steps for RISC-V Toolchain (rv32i)</summary>

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

</details>

<details>
<summary>Steps for RISC-V Toolchain (rv32im)</summary>

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

</details>

<details>
<summary>Verilator Installation</summary>

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

</details>

<details>
<summary>SOC Frame Setup</summary>

1. Extract the SOC_FRAME tar files.
2. Rename the folder to "soc_frame."
3. Ensure the full address is "/home/user/soc_frame."
   - If not feasible, search for "/home/user/soc_frame" in all files and replace it with the desired path.
   - The path should not have spaces in it.

</details>

## Note

The simulation method described in the videos is not visible to the debugger. To debug, bypass `main.py` and modify `run_mpsoc.py`. Debug it in a suitable IDE, such as VSCode.

