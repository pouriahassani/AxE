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
docker run -it -v $(pwd):/home/user/ poria19964214/axe:original
```
Using the `-v` option you use a docker volume where the current directory of your local machine is mapped to the `/home/user/` directory of the container. Any changes to this directory are reflected on both sides. 

For use with Docker Desktop and Windows Powershell analogously use 
```bash
docker run -it -v ${pwd}:/home/user/ poria19964214/axe:original
```
with curly brackets instead.

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

## Acknowledgments

This project was initiated and developed by Stefan Huemer during his time as a master's student collaborating with Prof. Nima TaheiNejad's research group. Subsequently, Ahmad Sedigh Baroughi made significant contributions to the project. Presently, Pouria Hasani is actively involved in extending the project.

## Citation

If you use this code in your research, please consider citing the following papers:

```bibtex
@inproceedings{Baroughi2022AxE,
  author = {Baroughi, A. S. and Huemer, S. and Shahhoseini, H. S. and TaheriNejad, N.},
  booktitle = {2022 25th Euromicro Conference on Digital System Design (DSD)},
  title = {{AxE}: An Approximate-Exact Multi-Processor System-on-Chip Platform},
  year = {2022},
  pages = {60--66},
  doi = {10.1109/DSD57027.2022.00018},
  keywords = {Energy consumption;Program processors;Digital systems;Approximate computing;Gray-scale;Software;Hardware;Approximation Computing;Multi-Processor System-on-Chip (MPSoC);Approximate and Exact MPSoC;Task Mapping;RISC-V},
}
```
[Link to the paper](https://eclectx.org/Publications/2022_DSD_AxEmpsoc.pdf)

```bibtex
@inproceedings{HuemerBST23,
  author = {Huemer, Sini and Baroughi, Ahmad Sadigh and Shahhoseini, Hadi Shahriar and TaheriNejad, Nima},
  title = {Approximation-aware Task Partitioning on an Approximate-Exact MPSoC ({AxE})},
  booktitle = {{IEEE} Nordic Circuits and Systems Conference, NorCAS 2023, Aalborg, Denmark, October 31 - Nov. 1, 2023},
  year = {2023},
  pages = {1--7},
  publisher = {{IEEE}},
  doi = {10.1109/NORCAS58970.2023.10305464},
  url = {https://doi.org/10.1109/NorCAS58970.2023.10305464},
}
```
[Link to the paper](https://eclectx.org/Publications/C50.pdf)

## Note

The simulation method described in the videos is not visible to the debugger. To debug, bypass `main.py` and modify `run_mpsoc.py`. Debug it in a suitable IDE, such as VSCode.
