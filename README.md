# custom-label

# 编译

```shell
mkdir build && cd build
cmake ..
make -j4
sudo make install  # optional
```

# 链接

```shell
cd /usr/lib/x86_64-linux-gnu/qt5/plugins/designer
sudo ln -s xx/build/calib-plugin/libcalib_plugin.so .
```
