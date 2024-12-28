#pragma once

typedef unsigned long cntsize_t;
typedef unsigned short cnttattr_t;
/**
 *                                                     DDDD DDD 
 *                                                     EEEE EEE 
 *                                                     VVVV VVV 
 *                                                     RRRR RRR T 
 *                                                     EEEE EEE N
 *                                                     SSSS SSS E
 *                                                     EEEE EEE V
 *                                                     RRRR RRR E ROLE TYPE */
#define CNT_RESERVED            (0x00u)             /* 0000 000 0 0000 0000 */
#define CNT_REGION              (0x01u)             /* 0000 000 0 0000 0001 */
#define CNT_LOCATION            (0x02u)             /* 0000 000 0 0000 0010 */
#define CNT_BIT                 (0x03u)             /* 0000 000 0 0000 0011 */
#define CNT_OBJECT              (0x04u)             /* 0000 000 0 0000 0100 */
#define CNT_PARENT_CHILD        (0x10u)             /* 0000 000 0 0001 0000 */
#define CNT_CHILD_PARENT        (0x20u)             /* 0000 000 0 0010 0000 */
#define CNT_PEER_TO_PEER        (0x30u)             /* 0000 000 0 0011 0000 */
#define CNT_EVENT               (1 << 8u)           /* 0000 000 1 0000 0000 */

#define CNT_UNLIMIT     0u