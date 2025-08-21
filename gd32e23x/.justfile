
binary_dir := "./build"

init:
    cmake -S . -B {{binary_dir}} -G Ninja \
        -DDEVICE=GD32E230K8T6 \
        -DGD32E23X_USE_GPIO=ON

build *arg:
    cmake --build {{binary_dir}} {{arg}}