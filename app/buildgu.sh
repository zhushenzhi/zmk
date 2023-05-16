rm -rf build_left
rm -rf build_right

west build -d build_left -b nice_nano_v2 -- -DSHIELD=corne_left
west build -d build_right -b nice_nano_v2 -- -DSHIELD=corne_right

cp ./build_left/zephyr/zmk.uf2 aaa/zmk_left.uf2 
cp ./build_right/zephyr/zmk.uf2 aaa/zmk_right.uf2 