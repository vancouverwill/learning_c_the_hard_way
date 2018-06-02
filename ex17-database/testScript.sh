set -e

rm ex17_variable_size || true
echo 'removed old version'

make

echo '$./ex17_variable_size db.testScript.dat c';
 ./ex17_variable_size db.testScript.dat c 
echo '-----'
echo '$./ex17_variable_size db.testScript.dat s 1 zed zed@zedshaw.com';
 ./ex17_variable_size db.testScript.dat s 1 zed zed@zedshaw.com 
echo '-----'
 ./ex17_variable_size db.testScript.dat s 2 frank frank@zedshaw.com 
echo '-----'
 ./ex17_variable_size db.testScript.dat s 3 joe joe@zedshaw.com 
echo '-----'
 ./ex17_variable_size db.testScript.dat l 

echo '\n\nSafely completed!'
