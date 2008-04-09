/**
 * @file   hoinfo.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2007-06-12 00:14:59+0200
 * 
 * @brief  Handover information
 * @licence GNU GPLv2
 * 
 */

#ifndef HOINFO_H
#define HOINFO_H

/* useful macros */
#define CLEAR(x) memset(x, 0, sizeof(*x));


/* as defined in 802.16 Corr2 Draft3, table 367, section 11.5 */
#define WMAX_HO_OPTIM_OMIT_SBC_REQ              1   /* bit #0 */
#define WMAX_HO_OPTIM_SKIP_SA_TEK               6   /* bits #1 and #2 */
#define WMAX_HO_OPTIM_NETWORK_ACCESS_AQUISITION 8   /* bit #3 */
#define WMAX_HO_OPTIM_OMIT_TIME_OF_DAY          16  /* bit #4 */
#define WMAX_HO_OPTIM_TFTP                      32  /* bit #5 */
#define WMAX_HO_OPTIM_FULL_STATE_TRANSFER       64  /* bit #6 */
#define WMAX_HO_OPTIM_OMIT_REG_REQ              128 /* bit #7 */
#define WMAX_HO_OPTIM_OMIT_UNSOL_SBC_RSP        256 /* bit #8 */
#define WMAX_HO_OPTIM_DL_DATA_WAITING           512 /* bit #9 */
#define WMAX_HO_OPTIM_OMIT_UNSL_REG_RSP         (1 << 10) /* bit #10 */
#define WMAX_HO_OPTIM_SDU_SN                    (1 << 11) /* bit #11 */
#define WMAX_HO_OPTIM_REENTRY_CONFIRM           (1 << 12) /* bit #12 */
#define WMAX_HO_OPTIM_TRIGGER_HIGHER_LAYER      (1 << 13) /* bit #13 */

typedef enum {
    DHCP_DAD_TYPE_NORMAL=0,
    DHCP_DAD_TYPE_NONE=1,
    DHCP_DAD_TYPE_SERVER_SIDE=2,
    DHCP_DAD_TYPE_OPTIMISTIC=3
} DhcpDadType;

/* handover related parameters on the WiMAX layer */
typedef struct {
    int hoOptim; /* see table 367 in 802.16 Corr2 Draft3, pg. 405, section 11.5 */
    int nextBS;
} HoWMax_t;

/* handover related parameters on IPv6 layer */
typedef struct {
    int tbd;
} HoIPv6_t;

/* handover related parameters on DHCPv6 layer */
typedef struct {
    bool skipInitialDelay; /* delay 0..1s */
    bool pref255;          /* set preference to 255 */
    bool rapidCommit;      /* use rapid-commit option */
    bool sendConfirm;      /* use CONFIRM instead of SOLICIT */
    bool addrParams;       /* should addr-params extension be used? */
    bool remoteAutoconf;   /* should Remote autoconf be used? */

    DhcpDadType DadType;
} HoDHCPv6_t;

/* handover related parameters on MobileIPv6 layer */
typedef struct {
    bool remoteLocUpdate;
} HoMobileIPv6_t;


/* general structure describing handover procedure */
typedef struct HoInfo_s {
    int            isMobile;
    HoWMax_t       wmax;
    HoIPv6_t       ip;
    HoDHCPv6_t     dhcp;
    HoMobileIPv6_t mip;

} HoInfo_t;


// Media Independent Handover communication
// @TODO: Use 802.21

typedef enum {
  MIH_EVENT_ENTRY_START,
  MIH_EVENT_ENTRY_END,
  MIH_EVENT_HANDOVER_START,
  MIH_EVENT_HANDOVER_END,
  MIH_EVENT_REENTRY_START,
  MIH_EVENT_REENTRY_END
} MihInfo_t;

#endif
