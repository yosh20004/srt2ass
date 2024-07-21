需求：
    '''c++20
    '''

安装

按照以下步骤来安装和配置项目：

1.  进入项目目录：
    
    ```bash
    cd srt2ass
    ```
    
2.  创建并进入构建目录：
    
    ```bash
    mkdir build
    cd build
    ```
    
3.  生成构建文件：
    
    ```bash
    cmake --build .
    ```

或是在windows下直接执行build.bat

运行

    在命令行中输入srt2ass 源文件地址 目标文件地址
    例如 srt2ass ./1.srt 会在同目录下生成一个1.ass
    或是srt2ass ./1.srt ../test.ass 会在上一目录下生成test.ass
    

