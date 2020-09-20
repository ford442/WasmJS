# WasmJS  
This is a C++ layer that simplifies working with web API such as: Console, DOM, IndexedDB, CSSOM, Websockets etc. This layer provides only a minimal set of functions, which will expand over time. You can see examples in the 'examples' folder. Read the wiki for more details on the implemented features.
# Compiling and running examples on Linux  
git clone https://github.com/dmsmdms/WasmJS  
cd WasmJS  
git submodule init  
git submodule update  
make emscripten_install  
make nginx_configure  
make nginx_build  
source ./emsdk/emsdk_env.sh  
mkdir build/public_html/js/
mkdir build/logs/  
make  
./nginx/objs/nginx  
(See result on:  
http://localhost:8000/console.html  
http://localhost:8000/dom.html  
http://localhost:8000/indexed_db.html  
)
