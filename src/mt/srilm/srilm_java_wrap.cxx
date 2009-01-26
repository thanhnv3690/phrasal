/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */


#ifdef __cplusplus
template<class T> class SwigValueWrapper {
    T *tt;
public:
    SwigValueWrapper() : tt(0) { }
    SwigValueWrapper(const SwigValueWrapper<T>& rhs) : tt(new T(*rhs.tt)) { }
    SwigValueWrapper(const T& t) : tt(new T(t)) { }
    ~SwigValueWrapper() { delete tt; } 
    SwigValueWrapper& operator=(const T& t) { delete tt; tt = new T(t); return *this; }
    operator T&() const { return *tt; }
    T *operator&() { return tt; }
private:
    SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
};
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC)
#   if (__SUNPRO_CC <= 0x560)
#     define SWIGTEMPLATEDISAMBIGUATOR template
#   else
#     define SWIGTEMPLATEDISAMBIGUATOR 
#   endif
# else
#   define SWIGTEMPLATEDISAMBIGUATOR 
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__)) 
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__)) 
# else
#   define SWIGUNUSED 
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED 
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif 
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif


/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTELC__)
  typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
  SWIG_JavaOutOfMemoryError = 1, 
  SWIG_JavaIOException, 
  SWIG_JavaRuntimeException, 
  SWIG_JavaIndexOutOfBoundsException,
  SWIG_JavaArithmeticException,
  SWIG_JavaIllegalArgumentException,
  SWIG_JavaNullPointerException,
  SWIG_JavaDirectorPureVirtual,
  SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
  SWIG_JavaExceptionCodes code;
  const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
  jclass excep;
  static const SWIG_JavaExceptions_t java_exceptions[] = {
    { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
    { SWIG_JavaIOException, "java/io/IOException" },
    { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
    { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
    { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
    { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
    { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
    { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
    { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
    { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" } };
  const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

  while (except_ptr->code != code && except_ptr->code)
    except_ptr++;

  jenv->ExceptionClear();
  excep = jenv->FindClass(except_ptr->java_exception);
  if (excep)
    jenv->ThrowNew(excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else


/* Include the header files etc. here */
#include "Ngram.h"
#include "Vocab.h"
#include "Prob.h"
#include "srilm.h"


static unsigned *new_unsigned_array(int nelements) { 
  return new unsigned[nelements]; 
}

static void delete_unsigned_array(unsigned *ary) { 
  delete [] ary; 
}

static unsigned unsigned_array_getitem(unsigned *ary, int index) {
    return ary[index];
}
static void unsigned_array_setitem(unsigned *ary, int index, unsigned value) {
    ary[index] = value;
}


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_new_1unsigned_1array(JNIEnv *jenv, jclass jcls, jint jarg1) {
  jlong jresult = 0 ;
  int arg1 ;
  unsigned int *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  result = (unsigned int *)new_unsigned_array(arg1);
  *(unsigned int **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_mt_srilm_srilmJNI_delete_1unsigned_1array(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  unsigned int *arg1 = (unsigned int *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(unsigned int **)&jarg1; 
  delete_unsigned_array(arg1);
}


SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_unsigned_1array_1getitem(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2) {
  jlong jresult = 0 ;
  unsigned int *arg1 = (unsigned int *) 0 ;
  int arg2 ;
  unsigned int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(unsigned int **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (unsigned int)unsigned_array_getitem(arg1,arg2);
  jresult = (jlong)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_mt_srilm_srilmJNI_unsigned_1array_1setitem(JNIEnv *jenv, jclass jcls, jlong jarg1, jint jarg2, jlong jarg3) {
  unsigned int *arg1 = (unsigned int *) 0 ;
  int arg2 ;
  unsigned int arg3 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(unsigned int **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (unsigned int)jarg3; 
  unsigned_array_setitem(arg1,arg2,arg3);
}


SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_initLM(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2, jint jarg3) {
  jlong jresult = 0 ;
  int arg1 ;
  int arg2 ;
  int arg3 ;
  Ngram *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  result = (Ngram *)initLM(arg1,arg2,arg3);
  *(Ngram **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_initVocab(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2) {
  jlong jresult = 0 ;
  int arg1 ;
  int arg2 ;
  Vocab *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  result = (Vocab *)initVocab(arg1,arg2);
  *(Vocab **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_getIndexForWord(JNIEnv *jenv, jclass jcls, jstring jarg1) {
  jlong jresult = 0 ;
  char *arg1 = (char *) 0 ;
  unsigned int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = 0;
  if (jarg1) {
    arg1 = (char *)jenv->GetStringUTFChars(jarg1, 0);
    if (!arg1) return 0;
  }
  result = (unsigned int)getIndexForWord((char const *)arg1);
  jresult = (jlong)result; 
  if (arg1) jenv->ReleaseStringUTFChars(jarg1, (const char *)arg1);
  return jresult;
}


SWIGEXPORT jstring JNICALL Java_mt_srilm_srilmJNI_getWordForIndex(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  jstring jresult = 0 ;
  unsigned int arg1 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (unsigned int)jarg1; 
  result = (char *)getWordForIndex(arg1);
  if(result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}


SWIGEXPORT jint JNICALL Java_mt_srilm_srilmJNI_readLM(JNIEnv *jenv, jclass jcls, jlong jarg1, jstring jarg2) {
  jint jresult = 0 ;
  Ngram *arg1 = (Ngram *) 0 ;
  char *arg2 = (char *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Ngram **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (int)readLM(arg1,(char const *)arg2);
  jresult = (jint)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_mt_srilm_srilmJNI_getWordProb(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2, jlong jarg3) {
  jfloat jresult = 0 ;
  Ngram *arg1 = (Ngram *) 0 ;
  unsigned int arg2 ;
  unsigned int *arg3 = (unsigned int *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Ngram **)&jarg1; 
  arg2 = (unsigned int)jarg2; 
  arg3 = *(unsigned int **)&jarg3; 
  result = (float)getWordProb(arg1,arg2,arg3);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_mt_srilm_srilmJNI_getProb(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2, jint jarg3, jlong jarg4) {
  jfloat jresult = 0 ;
  Ngram *arg1 = (Ngram *) 0 ;
  unsigned int *arg2 = (unsigned int *) 0 ;
  int arg3 ;
  unsigned int arg4 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Ngram **)&jarg1; 
  arg2 = *(unsigned int **)&jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (unsigned int)jarg4; 
  result = (float)getProb(arg1,arg2,arg3,arg4);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_getBOW_1depth(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2, jint jarg3) {
  jlong jresult = 0 ;
  Ngram *arg1 = (Ngram *) 0 ;
  unsigned int *arg2 = (unsigned int *) 0 ;
  int arg3 ;
  unsigned int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Ngram **)&jarg1; 
  arg2 = *(unsigned int **)&jarg2; 
  arg3 = (int)jarg3; 
  result = (unsigned int)getBOW_depth(arg1,arg2,arg3);
  jresult = (jlong)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_mt_srilm_srilmJNI_get_1backoff_1weight_1sum(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2, jint jarg3, jint jarg4) {
  jfloat jresult = 0 ;
  Ngram *arg1 = (Ngram *) 0 ;
  unsigned int *arg2 = (unsigned int *) 0 ;
  int arg3 ;
  int arg4 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Ngram **)&jarg1; 
  arg2 = *(unsigned int **)&jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (int)jarg4; 
  result = (float)get_backoff_weight_sum(arg1,arg2,arg3,arg4);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_mt_srilm_srilmJNI_getVocab_1None(JNIEnv *jenv, jclass jcls) {
  jint jresult = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  result = (int)getVocab_None();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_mt_srilm_srilmJNI_write_1vocab_1map(JNIEnv *jenv, jclass jcls, jlong jarg1, jstring jarg2) {
  Vocab *arg1 = (Vocab *) 0 ;
  char *arg2 = (char *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Vocab **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return ;
  }
  write_vocab_map(arg1,(char const *)arg2);
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
}


SWIGEXPORT void JNICALL Java_mt_srilm_srilmJNI_write_1default_1vocab_1map(JNIEnv *jenv, jclass jcls, jstring jarg1) {
  char *arg1 = (char *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = 0;
  if (jarg1) {
    arg1 = (char *)jenv->GetStringUTFChars(jarg1, 0);
    if (!arg1) return ;
  }
  write_default_vocab_map((char const *)arg1);
  if (arg1) jenv->ReleaseStringUTFChars(jarg1, (const char *)arg1);
}


SWIGEXPORT jstring JNICALL Java_mt_srilm_srilmJNI_getWordForIndex_1Vocab(JNIEnv *jenv, jclass jcls, jlong jarg1, jlong jarg2) {
  jstring jresult = 0 ;
  Vocab *arg1 = (Vocab *) 0 ;
  unsigned int arg2 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Vocab **)&jarg1; 
  arg2 = (unsigned int)jarg2; 
  result = (char *)getWordForIndex_Vocab(arg1,arg2);
  if(result) jresult = jenv->NewStringUTF((const char *)result);
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_mt_srilm_srilmJNI_getIndexForWord_1Vocab(JNIEnv *jenv, jclass jcls, jlong jarg1, jstring jarg2) {
  jlong jresult = 0 ;
  Vocab *arg1 = (Vocab *) 0 ;
  char *arg2 = (char *) 0 ;
  unsigned int result;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Vocab **)&jarg1; 
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  result = (unsigned int)getIndexForWord_Vocab(arg1,(char const *)arg2);
  jresult = (jlong)result; 
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  return jresult;
}


#ifdef __cplusplus
}
#endif

