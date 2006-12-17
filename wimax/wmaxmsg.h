#ifndef WMAXMSG_H
#define WMAXMSG_H

#include <omnetpp.h>


typedef enum {
    WMAX_ULMAP_UIUC_FAST_FEEDBACK = 0,
    WMAX_ULMAP_UIUC_DATA_1    = 1,
    WMAX_ULMAP_UIUC_DATA_2    = 2,
    WMAX_ULMAP_UIUC_DATA_3    = 3,
    WMAX_ULMAP_UIUC_DATA_4    = 4,
    WMAX_ULMAP_UIUC_DATA_5    = 5,
    WMAX_ULMAP_UIUC_DATA_6    = 6,
    WMAX_ULMAP_UIUC_DATA_7    = 7,
    WMAX_ULMAP_UIUC_DATA_8    = 8,
    WMAX_ULMAP_UIUC_DATA_9    = 9,
    WMAX_ULMAP_UIUC_DATA_10   = 10,
    WMAX_ULMAP_UIUC_EXTENDED2 = 11,
    WMAX_ULMAP_UIUC_CDMA_BWR  = 12,
    WMAX_ULMAP_UIUC_PAPR      = 13, // not used
    WMAX_ULMAP_UIUC_CDMA_ALLOC= 14,
    WMAX_ULMAP_UIUC_EXTENDED  = 15
} WMaxUlMapUiuc;

/* Information Element (simplified version) */
typedef struct  {
    uint16_t duration;
} WMaxDataIE;

typedef struct  {
    uint8_t         duration;
    WMaxUlMapUiuc   uiuc;
    uint8_t         rangingCode;
    uint8_t         rangingSymbol;
    uint8_t         rangingSubchannel;
} WMaxCdmaAllocationIE;

typedef enum {
    WMAX_RANGING_METHOD_INITIAL = 0,
    WMAX_RANGING_METHOD_BWR = 1
} WMaxRangingMethod;

typedef struct {
    uint8_t symbolOffset;
    uint8_t ofdmaSymbols;
    uint8_t subchannels;
    WMaxRangingMethod rangingMethod;
} WMaxCdmaIE;

// see table 287, IEEE 802.16-2004
typedef struct {
    uint16_t cid;
    WMaxUlMapUiuc uiuc;

    // uiuc 1..11
    WMaxDataIE dataIE;

    // uiuc=12
    WMaxCdmaIE cdmaIE;

    // uiuc=14 (cdma allocation IE)
    WMaxCdmaAllocationIE cdmaAllocIE;

    // uiuc=15 (extended uiuc)
    /// @todo - code this
} WMaxUlMapIE;


typedef struct {
    /// @todo - implement this for real
    uint16_t cid;
    uint32_t length;
} WMaxDlMapIE;

#endif
