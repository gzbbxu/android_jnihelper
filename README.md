####  每个native 函数，都至少有两个参数（JNIEnv* ,jclass 或者 jobject）

1. 当native 方法为静态方法时候 ，jcalss 待办native 方法所属的class 对象（JNITest.class
2. 当native 方法为非静态方法时：jobject代表native 方法所属的对象

### jni基本类型



```
typedef uint8_t  jboolean; /* unsigned 8 bits */   boolean
typedef int8_t   jbyte;    /* signed 8 bits */     byte
typedef uint16_t jchar;    /* unsigned 16 bits */  jchat
typedef int16_t  jshort;   /* signed 16 bits */    short
typedef int32_t  jint;     /* signed 32 bits */	   int 
typedef int64_t  jlong;    /* signed 64 bits */	   long
typedef float    jfloat;   /* 32-bit IEEE 754 */   float
typedef double   jdouble;  /* 64-bit IEEE 754 */   double
```

| java 类型 | jni类型  | c/c++类型      | 大小       |
| --------- | -------- | -------------- | ---------- |
| Boolean   | jboolean | unsigned char  | 无符号8位  |
| Byte      | jbyte    | char           | 有符号8为  |
| Char      | jchar    | unsigned short | 无符号16为 |
| Short     | jshort   | short          | 有符号16位 |
| Int       | jint     | int            | 有符号32位 |
| Long      | jlong    | long long      | 有符号64位 |
| Float     | jfloat   | float          | 32位       |
| Double    | jdouble  | double         | 64位       |



### jni 引用类型对象

| java类型            | 原生类型      |
| ------------------- | ------------- |
| Java.lang.Class     | jclass        |
| java.lang.Throwable | jthrowable    |
| java.lang.String    | jstring       |
| Other objects       | jobjects      |
| java.lang.Object[]  | jobjectArray  |
| boolean[]           | jbooleanArray |
| byte[]              | jbyteArray    |
| char[]              | jcharArray    |
| short[]             | jshortArray   |
| int[]               | jintArray     |
| long[]              | jlongArray    |
| float[]             | jfloatArray   |
| double[]            | jdoubleArray  |
| other arrays        | jarray        |

### cmake 头文件，编译，链接

1. 添加**头文件**目录**INCLUDE_DIRECTORIES**  **所有的 .h 文件不用再去以路径的形式 引入**

   **语法**

   ```
   include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
   它相当于g++选项中的-I参数的作用，也相当于环境变量中增加路径到CPLUS_INCLUDE_PATH变量的作用
   include_directories(../../../thirdparty/comm/include)
   g++ -I 
   编译程序按照-I指定的路进去搜索头文件。
   -I/home/include/表示将-I/home/include/目录作为第一个寻找头文件的目录，寻找的顺序是：
    /home/include/ -->/usr/include-->/usr/local/include 
    
   ```

### 设置so动态最后的输出路径

```
#设置生成的so动态库最后输出的路径 
方式1
# set(jnilibs "${CMAKE_SOURCE_DIR}/src/main/jniLibs")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${jnilibs}/${ANDROID_ABI})
#方式2
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
```

### Cmake 个人遇到的错误

1.  android ndk error :undefined reference to.AS做了编译缓存，你需要重新clean一下你的project。 然后refresh linked c++ project.即可！

2. More than one file was found with OS independent path. gradle 配置增加 

   ```
   packagingOptions{
       pickFirst  '**'
   }
   ```

3. cause executing external native build for cmake cmakelists.txt  生成多个so 文件的时候，字模块的cmakelists.txt  addLibray 如下。

   **正确的方式**

   ```
   include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
   file(GLOB_RECURSE jni_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
   add_library( # Sets the name of the library.
                jnihelper-lib
   
                # Sets the library as a shared library.
                SHARED
   
                # Provides a relative path to your source file(s).
                 ${jni_src}
                )
   ```

   **错误的方式**

   ```
   add_library( # Sets the name of the library.
                native-lib
   
                # Sets the library as a shared library.
                SHARED
   
                # Provides a relative path to your source file(s).
                src/main/cpp/native-lib.cpp
                src/main/cpp/JNIHelp.cpp
                 )
   ```

   

4. 









