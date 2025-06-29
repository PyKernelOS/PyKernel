# PyKernel
PyKernel Is MicroPython Based Operating System SDK. PyKernel Compile Python To Slandone Operating System. But Project Is Incomplete

## Features
- Low Level Access
- High Quality Graphics
- Python Based
- Custom Drivers
- Graphics Support
- Elf Support
- UEFI Support

## Get Started

### 1. Get The Repo
```bash
git clone https://github.com/PyKernelOS/PyKernel.git
```
### 2. Compile The Source Code
```bash
make -j$(nproc) # Compile For OS On Host Computer
# make OS=WIN -j$(nproc) # Compile For Windows With Installer .exe file
# make OS=MAC -j$(nproc) # Compile For MacOS
# make OS=LINUX -j$(nproc) # Compile For Linux
sudo make install
```

## How To Use This SDK

### New Project
```bash
pykernel new <ProjectName>
cd <ProjectName>
```
Replace <ProjectName> With Your OS Name

### Debug
```bash
cd path\to\your\project
pykernel debug
```
Replace path\to\your\project with path of Your OS Project

### Compile Project
```bash
cd path\to\your\project
pykernel compile
```
Replace path\to\your\project with path of Your OS Project

### Access GUI Editor
```bash
pykernel Start
```
