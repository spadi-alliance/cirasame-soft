## Install hul-common-lib
### Build example

```
mkdir cirasame-soft
cd  cirasame-soft
mkdir build install

git clone https://github.com/spadi-alliance/cirasame-soft.git cirasame-soft.src.git 

cmake \
   -S ./cirasame-soft.src.git \
   -B ./build \
   -DCMAKE_INSTALL_PREFIX=./install \
   -DCMAKE_PREFIX_PATH=<your hul_core_lib install dir>/install
cd build
make
make install
```

### Practical usage

We recommend to make a symbolic link the to hul-core-lib install directory inside the cirasame-soft install directory.
