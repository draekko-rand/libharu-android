LibHaru for Android
---

This is port for Android containing libharu, libpng and JNI bindings as an NDK project and a sample Android Studio project with code to work with the .so library.

LibHaru is a free, cross platform, open source library for generating PDF files, whose site can be found at http://libharu.org.  


Requirements
---

Requires setting up the latest Android NDK to compile the project .so files.  


Compiling .so library files
---

(Assuming Linux & bash shell)  

export PATH=/opt/android-ndk-10re:$PATH  
cd /pathto/libharu-android/ndk-project
ndk-build  


Usage
---

Copy the .so files that are generated to your jniLibs folder in your Android Studio studio project. Make sure to have one folder per architecture types supported as below.  

```
ASProject  
    +---+module  
        +---+src  
            +---+main  
                +---+jniLibs  
                    +--->armeabi  
                    +--->armeab-v7a  
                    +--->arm64-v8a  
                    +--->x86  
                    +--->x86_64  
                    +--->mips  
                    +--->mips64  
```

Extra
---

Included with the low level code is a sample Android Studio project to demonstrate usage.

