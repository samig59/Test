/*
	EMAIN.TEMPLATE - Main entry point template for Windows. 
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "eif_macros.h"
#include "eif_sig.h"

extern void emain(int, char **);
extern int main(int, char **, char **);
extern void egc_init_plug(void);
extern void egc_rcdt_init (void); 
extern void eif_retrieve_root (int *argc, char **argv);
extern void eif_init_root (void);

int main (int argc, char ** argv, char ** envp)
{

	int eif_argc = argc;

	eif_alloc_init();
#ifdef EIF_THREADS
	eif_thr_init_root();
#endif
{
	GTCX
	struct ex_vect *exvect;
	jmp_buf exenv;

	egc_init_plug();
	initsig();
	initstk();
	exvect = exset((char *) 0, 0, (char *) 0);
	exvect->ex_jbuf = &exenv;
	if (setjmp(exenv))
		failure();

	eif_retrieve_root (&eif_argc, argv);
	eif_rtinit(eif_argc, argv, envp);
	eif_init_root();
	egc_rcdt_init (); 
	emain(eif_argc, argv);
	reclaim();
	exit(0);
}
	return 0;
}

#ifdef __cplusplus
}
#endif
