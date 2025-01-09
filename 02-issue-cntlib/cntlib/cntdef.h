#pragma once

typedef unsigned char cntstatus_t;
typedef unsigned long cntint_t;
typedef unsigned int cntattr_t;
typedef char* cntptr_t;
typedef void* cntany_t;

#define CNT_SUCCESS     0x0
#define CNT_ERROR       0x1

/**
 *                                                                                            N
 *                                                                               T            O
 *                                                     DDDD DDDD DDDD DDDD       P     T      I
 *                                                     EEEE EEEE EEEE EEEE       U     N D    T
 *                                                     VVVV VVVV VVVV VVVV       R   R E L    A
 *                                                     RRRR RRRR RRRR RRRR       R   E R I  T T T
 *                                                     EEEE EEEE EEEE EEEE       E T E A H  N I A
 *                                                     SSSS SSSS SSSS SSSS       T O P P C  E M O  E T  E
 *                                                     EEEE EEEE EEEE EEEE       N O DIDIDI V I L  L I  P
 *                                                     RRRR RRRR RRRR RRRR       I R  LINK  E L F RO B TY 
 * 
 *                                                     1098 7654 3210 9876       5 4 3210
 *                                                     3322 2222 2222 1111       1 1 111198 7 6 5 34 2 10
 */
#define CNT_REGION              (1 << 0u)           /* .... .... .... .... */ /* . . ...... . . . .. . 01 */
#define CNT_LOCATION            (2 << 0u)           /* .... .... .... .... */ /* . . ...... . . . .. . 10 */
#define CNT_OBJECT              (3 << 0u)           /* .... .... .... .... */ /* . . ...... . . . .. . 11 */

#define CNT_BIT                 (4 << 0u)           /* .... .... .... .... */ /* . . ...... . . . .. 1 .. */

#define CNT_PARENT_CHILD        (1 << 3u)           /* .... .... .... .... */ /* . . ...... . . . 01 . .. */
#define CNT_CHILD_PARENT        (2 << 3u)           /* .... .... .... .... */ /* . . ...... . . . 10 . .. */
#define CNT_PEER_TO_PEER        (3 << 3u)           /* .... .... .... .... */ /* . . ...... . . . 11 . .. */

#define CNT_FLOAT               (1 << 5u)           /* .... .... .... .... */ /* . . ...... . . 1 .. . .. */

#define CNT_LIMITATION          (1 << 6u)           /* .... .... .... .... */ /* . . ...... . 1 . .. . .. */
#define CNT_EVENT               (1 << 7u)           /* .... .... .... .... */ /* . . ...... 1 . . .. . .. */

#define CNT_CHILD_INF           (1 << 8u)           /* .... .... .... .... */ /* . . ----01 . . . .. . .. */
#define CNT_CHILD_DEP           (1 << 9u)           /* .... .... .... .... */ /* . . ----10 . . . .. . .. */ 
#define CNT_PARENT_INF          (1 << 10u)          /* .... .... .... .... */ /* . . --01-- . . . .. . .. */
#define CNT_PARENT_DEP          (1 << 11u)          /* .... .... .... .... */ /* . . --10-- . . . .. . .. */
#define CNT_PEER_INF            (1 << 12u)          /* .... .... .... .... */ /* . . 01---- . . . .. . .. */
#define CNT_PEER_DEP            (1 << 13u)          /* .... .... .... .... */ /* . . 10---- . . . .. . .. */

#define CNT_ROOT                (1 << 14u)          /* .... .... .... .... */ /* . 1 ...... . . . .. . .. */
#define CNT_INTERRUPT           (1 << 15u)          /* .... .... .... .... */ /* 1 . ...... . . . .. . .. */