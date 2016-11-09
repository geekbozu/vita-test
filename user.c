#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/message_dialog.h>
#include <psp2/display.h>
#include <psp2/rtc.h>
#include <taihen.h>
#include "henkaku.h"
#include <stdio.h>
#include "threads.h"
#include "blit.h"



#define DISPLAY_VERSION (0x3600000)
#include  <psp2/ctrl.h>
static char titleid[16] = "GEEKTEST";

int thread(SceSize argc,void *args){
	sceKernelDelayThread(5 * 1000 * 1000);
	for(;;){
	//	pauseMainThread();
		blit_setup();
		blit_stringf(0,0,"Test String");
//		sceDisplayWaitVblankStart();
		sceKernelDelayThread(10*1000*1000);
	//	resumeMainThread();
	}
	return 0;
	
}

int module_start(SceSize argc,const void *args){
	SceUID thid = sceKernelCreateThread("testThread", thread, 0x40, 0x40000, 0, 0, NULL);
	if (thid >= 0)
		sceKernelStartThread(thid, 0, NULL);
	return 0;
}
int module_stop(SceSize argc,const void *args){
	return 0;
} 
void module_exit(void) {

}
/**
 * @brief      Alias to inhibit compiler warning
 * @private
 */
void _start() __attribute__ ((weak, alias ("module_start")));
