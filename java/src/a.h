#ifndef J_A_H
#define J_A_H

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#endif /* __GNUC__ */
#include "a/a.h"
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif /* -Wreserved-id-macro */
#if __has_warning("-Wreserved-identifier")
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* -Wreserved-identifier */
#include <jni.h>

#define JPACKAGE(F) Java_liba_##F

#endif /* a.h */
