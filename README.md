# perfect spatial hash demo

## 运行说明

首先安装好tbb，并进入当前目录

```bash
mkdir build
cd build
cmake ..
make -j4 && ./psh_proj
```

## 已知问题
1. res和precision需手动确定
2. 一些模型的exhaustive test未通过(fish_512)
3. PosInt和HashInt类型的选取
4. 偶现浮点数意外
5. psh的迭代器
6. teapot有问题
