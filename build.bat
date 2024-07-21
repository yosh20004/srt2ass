@echo off

:: 设置项目根目录
set PROJECT_DIR=%~dp0

:: 设置构建目录
set BUILD_DIR=%PROJECT_DIR%build

:: 如果构建目录不存在，则创建它
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

:: 进入构建目录
cd "%BUILD_DIR%"

:: 运行 CMake 配置
cmake .. || goto :error

:: 运行编译
cmake --build . || goto :error

:: 成功消息
echo Build succeeded!
goto :end

:error
:: 错误消息
echo Build failed!

:end
:: 保持命令提示符窗口打开
pause("")

