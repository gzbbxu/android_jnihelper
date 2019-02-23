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

























