#include <jni.h>
#include <string>

//日志输出
#include <android/log.h>
#define TAG "wan"

// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);

extern "C" JNIEXPORT jstring

JNICALL
Java_com_transcendence_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    LOGD("hello.c_str()输出：\n", hello.c_str())
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

// jobject == MainActivity this 实例调用的
// jclass == MainActivity class 类调用的
extern "C"
JNIEXPORT void JNICALL
Java_com_transcendence_jni_MainActivity_changeAge(JNIEnv *env, jclass clazz) {
    //  jfieldID GetStaticFieldID(jclass clazz, const char* name, const char* sig)
    jfieldID ageFid = env->GetStaticFieldID(clazz, "age", "I");

    // jint 背后就是int，所以可以直接用，  但是String 必须用 jstring
    int age = env->GetStaticIntField(clazz, ageFid); // 获取之前的age

    //  void SetStaticIntField(jclass clazz, jfieldID fieldID, jint value)
    env->SetStaticIntField(clazz, ageFid, age+10);
}