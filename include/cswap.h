/*
	CSWAP.H
*/

#ifdef FEATURE_XMS_SWAP

#ifndef __XMS_SWAP_H
#define __XMS_SWAP_H

#include "../include/misc.h"

#include "algnbyte.h"
struct ParamDosExec {
	unsigned short envSeg;
	void far *cmdtail;
	void far *FCB1;
	void far *FCB2;
	void far *overlPtr1;
	void far *overlPtr2;	
	};
#include "algndflt.h"

#ifdef __GNUC__
extern char dosFCB1[128];
extern char dosFCB2[128];

extern struct ParamDosExec dosParamDosExec;

#define dosFCB1 RESIDENT(dosFCB1)
#define dosFCB2 RESIDENT(dosFCB2)
#define dosParamDosExec RESIDENT(dosParamDosExec)

extern unsigned char dosCMDNAME[128];
#define dosCMDNAME RESIDENT(dosCMDNAME)
#else
extern char far dosFCB1[128];			/* must be setup correctly */
extern char far dosFCB2[128];		

extern struct ParamDosExec far dosParamDosExec;

extern unsigned char far dosCMDNAME[128];
#endif
/*extern unsigned char far dosCMDTAIL[128];*/
#define dosCMDTAIL  ((char far*)MK_FP(_psp, 0x80))

#ifdef __GNUC__
extern void far * termAddr;
extern word myPID;
extern word origPPID;

extern int XMSexec(void);
extern void terminateFreeCOMHook(void);

#define termAddr RESIDENT(termAddr)
#define myPID RESIDENT(myPID)
#define origPPID RESIDENT(origPPID)
#else
extern byte far canexit;
extern void far * far termAddr;
extern word far myPID;
extern word residentCS;
extern word far origPPID;

extern int cdecl XMSexec(void);	
extern void far cdecl terminateFreeCOMHook(void);
extern void far XMSrequest(void);
#endif

#ifdef __WATCOMC__
extern unsigned long (far *far XMSdriverAdress)(unsigned request,
						unsigned dx, void *si);
#pragma aux XMSdriverAdress = parm [ax] [dx] [si]
#elif defined(__GNUC__)
extern unsigned far *XMSdriverAdress;
#define XMSdriverAdress RESIDENT(XMSdriverAdress)
extern unsigned long XMSrequest(unsigned request, unsigned dx, void *si);
#else
extern unsigned (far *far XMSdriverAdress)(void);
#endif
	
#ifdef __GNUC__
extern unsigned char SWAPresidentEnd;          /* label: end of resident code */
extern unsigned short SwapResidentSize;	  /* paras of the swap handler */
extern unsigned short SwapTransientSize;  /* paras of total command */
#define SWAPresidentEnd RESIDENT(SWAPresidentEnd)
#define SwapTransientSize RESIDENT(SwapTransientSize)
#else
extern unsigned char far SWAPresidentEnd;          /* label: end of resident code */
extern unsigned short SwapResidentSize;	  /* paras of the swap handler */	
extern unsigned short far SwapTransientSize;  /* paras of total command */	
#endif

struct XMScopy{
        long length;
        short shandle;
        long soffset;
        short dhandle;
        long  doffset;
        } ;

extern struct XMScopy XMSsave;
#ifdef __GNUC__
extern struct XMScopy XMSrestore;
#define XMSrestore RESIDENT(XMSrestore)
#else
extern struct XMScopy far XMSrestore;
#endif

/* Handlers in resident portion for external program execution */
#ifdef __GNUC__
extern void ASMINTERRUPT lowlevel_cbreak_handler();
extern void ASMINTERRUPT lowlevel_err_handler();
extern void ASMINTERRUPT autofail_err_handler();
extern void ASMINTERRUPT lowlevel_int_2e_handler();
#else
extern void far ASMINTERRUPT lowlevel_cbreak_handler();
extern void far ASMINTERRUPT lowlevel_err_handler();
extern void far ASMINTERRUPT autofail_err_handler();
extern void far ASMINTERRUPT lowlevel_int_2e_handler();
#endif

/* functions */
word XMSswapmessagesIn(loadStatus *status);
void XMSinit(void);
int XMSisactive(void);
void XMSexit(void);

#endif

#endif
