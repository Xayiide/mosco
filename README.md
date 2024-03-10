# Mosco
Implementación de un broker MQTT, inspirado en [Sol](https://github.com/codepr/sol). Tiene una [página](https://codepr.github.io/posts/sol-mqtt-broker/) donde explica cómo se hizo.


# Documentación
- [Documentación oficial de MQTT](http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/errata01/os/mqtt-v3.1.1-errata01-os-complete.html)


# Compilar
En el directorio `mosco`:  
## Sin Eclipse
`mkdir -p build && cd build && cmake .. && make`
## Con Eclipse
En el directorio mosco:  
`mkdir -p build`
`cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j12 .`  
Luego hay que importar el proyecto: `File > Import > Existing Projects into Workspace`
