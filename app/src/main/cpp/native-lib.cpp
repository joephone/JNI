#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_com_transcendence_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"  //代表下面的代码采用C的编译方式
JNIEXPORT
void  //代表Java中的void
JNICALL  //也是一个关键字，可以少， 约束函数入栈顺序，和堆栈内存清理的规则
Java_com_transcendence_jni_MainActivity_changeName(JNIEnv *env, jobject thiz) {  //1代表java的下划线
    //如果当前是  c   (*env)->xxx函数   如果是CPP env-> xxx函数   因为如果是C  *env是二级指针  JNINativeInterface*是一级指针 又加了个*所以成为二级指针  别名+* 所以CPP是一级指针
    jclass mainActivityCls = env->FindClass("com/transcendence/jni/MainActivity");

    jfieldID  nameFid = env->GetFieldID(mainActivityCls,"name","Ljava/lang/String;");

    jstring  value = env->NewStringUTF("修改为joe");
    env->SetObjectField(thiz,nameFid,value);
}