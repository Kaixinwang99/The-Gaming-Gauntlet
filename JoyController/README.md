## JoyLib Library usage with CMake

### Building JoyController
JoyController is an executable that includes and implements the JoyLib library.
It is mainly to be used for tesing with HW 

#### Usage
Make sure the current working directory is JoyController and run:

``` 
mkdir build && cd build 
cmake ..
make 
```
On successful build it will create an exxecutable named JoyController and you can run this:
```
./JoyController
```
  
For using the library with other modules, copy the JoyLib folder to the required module/project folder and make sure the root CMakeLists.txt of that module
adds the library by adding the following:

```
add_subdirectory(JoyLib)
target_include_directories(${PROJECT_NAME} PUBLIC JoyLib)

target_link_libraries(${PROJECT_NAME} JoyLib)
```
