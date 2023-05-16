#/bin/env sh

# zmk/app path
app_path="/workspaces/zmk/app"
# firmware files storage path
result_dir_name="0_uf2"

build() {
    cd ${app_path}
    # origin fiemware file storage path
    origin_file="./build/zephyr/zmk.uf2"
    # current firmware file storage path
    current_file="${result_dir_name}/$2_$(date +%Y-%m-%d'_'%H-%M-%S).uf2"
    firmware_file_path="${app_path}/${current_file}"
    # init 清理 build 文件夹防止出现缓存问题
    if [[ -d "./build" ]]; then
        rm -rf ./build
    fi
    if [[ ! -d "./${result_dir_name}" ]]; then
        mkdir -p ./${result_dir_name}
    fi

    # 编译固件
    if [[ "$3" == "" ]]; then
        echo -e "\033[36m==> ⚙ Build board:$1 shield:${2/_/ }\033[0m"
        west build -b $1 -- -DSHIELD=$2
    else
        echo -e "\033[36m==> ⚙ Build board:$1 shield:${2/_/ } \n dir: $3\033[0m"
        west build -b $1 -- -DSHIELD=$2 -DZMK_CONFIG="$3"
    fi

    # 将编译好的固件移动至指定位置并删除 build 文件夹
    if [[ -f "${origin_file}" ]]; then
        cp ${origin_file} ./${current_file}
        echo -e "\033[32m==> Build Success! Frimware in ${firmware_file_path}\033[0m"
    fi

    if [[ -d "./build" ]]; then
        rm -rf ./build
    fi
}

if [[ "$#" < 1 || "$#" > 3 ]]; then
    echo -e "\033[31m==> ❌ Please check input! \033[0m"
elif [[ "$1" == "m2" ]]; then
    build "weekin840_m2" $2
elif [[ "$1" == "redox_manuform" ]]; then
    build "nrfmicro_13" "${1}_left"
    build "nrfmicro_13" "${1}_right"
elif [[ 
    "$1" == "jorne" ||
    "$1" == "corne" ||
    "$1" == "swoop" ||
    "$1" == "scylla" ||
    "$1" == "am_hatsu" ||
    "$1" == "dilemma" ]] \
    ; then
    build "nice_nano_v2" "${1}_left"
    build "nice_nano_v2" "${1}_right"
else
    build $1 $2 $3
fi
