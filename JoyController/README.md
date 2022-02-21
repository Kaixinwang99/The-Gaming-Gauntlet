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
### Testing
Unit tests are written in the GTest framework. tests/JoyTest.cpp contains all the tests. 
The testing framework depends on GoogleTest, so to install and set up the gtest library, run the following commands:
```
sudo apt install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```
This will install and set up gtest to be used with cmake. Refer to the CMakeLists.txt in the tests folder to see implementation.

#### Running tests
To build and run tests, go to the root project folder which is JoyController. Build all the libraries and then run the test.
```
cd buld          #go to the build dir to keep the root dir clean 
cmake ..         #build all the objects
make             #create executables
./tests/JoyTest  #run the test
```
