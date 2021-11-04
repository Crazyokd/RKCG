# RKCG

计算机图形学课程的相关实践

# 前言

计算机图形学的理论课程虽没有怎么听，但对实验课程的相关内容还是饶有兴趣的。

- 使用_DDA算法/中点画线法/Bresenham算法_实现直线画法。

    * 由于我完全不会Bresenham算法[~~啥？问我上课干什么去了？当然是上课啦！~~],所以仅实现了前两种算法，尤其集中在中点画线法上。

    * 使用中点画线法时，不同的斜率范围也对应着不同的递推公式，所以实现起来也没那么顺手，特别是我这种数学菜鸡。:cry:

- 由于主机上的MFC框架搭在VS2017上，VS2017的重量级自不必说:dizzy_face:，更重要的是其自带的那套快捷键简直和我相生相克:sob:，于是就只好折腾vscode上的计算机图形学了:punch::punch:

  * 图形库这块我选择了[EGE](https://github.com/wysaid/xege)

  * 本以为就是配个`include`，没想到还涉及很多问题【~~哎，头发怎么又变稀了？？
  ~~】，当然收获也颇为丰厚！关于总结可以戳这个[:point_up_2:](https://crazyokd.github.io/2021/10/10/%E8%A7%A3%E5%86%B3vscode%E5%BC%95%E7%94%A8c++%E5%A4%96%E9%83%A8%E5%BA%93%E6%8A%A5%E9%94%99/)

- 使用了中点算法实现了画圆和画椭圆（中点算法yyds）。

    * 在此过程中出于必要又封装了一个`putpixelRK`方法。

- 更新了扫描转换多边形。

    * 其实没有必要非要使用链表，但是这种数据结构虽然容易爆空指针但玩起来同样也很有意思。

# 目录结构

- [examples/](examples/)

    包含了一些配置文件的例子，比如 [.vscode/](examples/.vscode/)，在不同的计算机上配置一般不同（比如编译器路径），所以这里的文件仅作参考，你可以在你的项目根目录新建一个 `.vscode` 文件夹，将[该文件夹](examples/.vscode/)内的文件复制进去，再根据自己的环境适当更改。

# 如何运行

1. 使用 VS Code 调试

    使用该方法可以在 VS Code 里按 F5 运行调试任意源文件，首先你需要如上所属配置好 `.vscode` 文件夹，再打开你写的源文件，比如 [hello.cpp](hello.cpp)，然后按 F5 即可运行。

2. 使用命令行编译

    考虑到学校的机器没有 `make`，所以给出了编译脚本 [make_hello.bat](make_hello.bat)，只能编译 [hello.cpp]，但是可以替换脚本中的源文件名 `hello.cpp` 和输出文件 `hello.exe` 来编译其他源文件。

    编译完成后你会得到一个 [hello.exe](hello.exe) 可执行文件，直接运行即可。