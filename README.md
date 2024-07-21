# srt2ass

srt2ass is a tool for converting SRT subtitle files to ASS subtitle files. This project is written in C++20 and can be compiled and run in a Windows environment.

#### 上有中文说明
``` https://github.com/yosh20004/srt2ass/blob/main/README-CN.md ```

## Installation

Follow these steps to install and configure the project:

1.  Enter the project directory:
    
    ```bash
    cd srt2ass
    ```
    
2.  Create and enter the build directory:
    
    ```bash
    mkdir build
    cd build
    ```
    
3.  Generate build files:
    
    ```bash
    cmake --build .
    ```
    

Alternatively, you can directly execute `build.bat` on Windows.

## Usage

Enter the command in the terminal to convert a source file to a target file. For example:

```bash
srt2ass ./1.srt
```

This will generate a `1.ass` file in the same directory.

Or:

```bash
srt2ass ./1.srt ../test.ass
```

This will generate `test.ass` in the parent directory.

