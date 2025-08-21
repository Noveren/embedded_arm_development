
binary_dir := "./build"

init:
    cmake -S . -B {{binary_dir}} -G Ninja \
        -DDEVICE=GD32F303CCT6 \
        -DGD32F30X_USE_GPIO=ON

build *arg:
    cmake --build {{binary_dir}} {{arg}}