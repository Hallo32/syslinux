#include <stdio.h>
#include <stdlib.h>
#include <console.h>
#include <string.h>
#include <com32.h>
#include <syslinux/adv.h>
#include <syslinux/config.h>
#include <setjmp.h>
#include "../../com32/libutil/include/sha1.h"
#include <netinet/in.h>	

#include <sys/exec.h>
#include <sys/module.h>
#include "common.h"
#include "menu.h"

typedef void (*constructor_t)(void);
constructor_t __ctors_start[], __ctors_end[];

extern char 		__dynstr_start[];
extern char 		__dynstr_len[], __dynsym_len[];
extern char 		__dynsym_start[];
extern char		__got_start[];
extern Elf32_Dyn 	__dynamic_start[];
extern Elf32_Word	__gnu_hash_start[];

struct elf_module core_module =
{
	.name = 		"(core)",
	.shallow = 		1,
	.required= 		LIST_HEAD_INIT( (core_module.required) ),
	.dependants= 		LIST_HEAD_INIT( (core_module.dependants) ),
	.list= 			LIST_HEAD_INIT( (core_module.list) ),
	.module_addr = 		(void *)0x0,
	.base_addr = 		(Elf32_Addr)0x0,
	.ghash_table = 		__gnu_hash_start,
	.str_table = 		__dynstr_start,
	.sym_table = 		__dynsym_start,
	.got = 			__got_start,
	.dyn_table = 		__dynamic_start,
	.strtable_size = 	(size_t)__dynstr_len,
	.syment_size =		sizeof(Elf32_Sym),
	.symtable_size = 	(size_t)__dynsym_len
};

/*
	Initializes the module subsystem by taking the core module ( shallow module ) and placing
	it on top of the modules_head_list. Since the core module is initialized when declared
	we technically don't need the exec_init() and module_load_shallow() procedures
*/
void init_module_subsystem(struct elf_module *module)
{
	list_add(&module->list, &modules_head);
}

/*
	call_constr: initializes sme things related
*/
static void call_constr()
{
	constructor_t *p;
	for (p = __ctors_start; p < __ctors_end; p++)
	{
		(*p)();
	}
}

/* note to self: do _*NOT*_ use static key word on this function */
void load_env32(com32sys_t * regs)
{
	openconsole(&dev_stdcon_r, &dev_stdcon_w);
	printf("Calling initilization constructor procedures...\n");
	call_constr();
	printf("Starting 32 bit elf module subsystem...\n");
	init_module_subsystem(&core_module);

	printf("Str table address: %d\n",core_module.str_table);
	printf("Sym table address: %d\n",core_module.sym_table);
	printf("Str table size: %d\n",core_module.strtable_size);
	printf("Sym table size: %d\n",core_module.symtable_size);

	int i,n=5;
	char **argv;
	argv=(char**)malloc(n*sizeof(char*));
	argv[1]=(char*)malloc(100*sizeof(char));//(char *)(regs->edi.w[0]);
	strcpy(argv[1],"extlinux.conf");
	
	/*__divdi3(0,0);
	__syslinux_get_config_file_name();
	strnlen(argv,0);
	fgets(0,0,stdin);
	calloc(0,0);
	sprintf(0,"");
	lrand48();
	puts("");
	putchar(' ');	//+---- we have to force these symbols to exist in teh core module
	strtoul(0,0,0);
	strncmp(0,0,0);
	realloc(0,0);
	syslinux_getadv(0,0);
	atoi(0);
	atoll(0);
	syslinux_ipappend_strings();
	syslinux_setadv(0,0,0);
	syslinux_adv_write();
	__syslinux_get_ipappend_strings();
	strchr(0,0);
	getscreensize(0,0,0);
	memmove(0,0,0);
	ntohl(0);
	snprintf(0,0,0);
	memcpy(0,0,0);
	mempcpy(0,0,0);
	strcspn(0,0);
	strncpy(0,0,0);
	stpncpy(0,0,0);
	strcpy(0,0);
	memcmp(0,0,0);
	static jmp_buf timeout_jump;
	fgets(&n,2,stdin);
	if(!n)
	{
		setjmp(timeout_jump);
		longjmp(timeout_jump, 1);
	}*/

	
	/*printf("\nBegin dynamic module test...\n");
	printf("\n\nTrying to laod 'dyn/sort.dyn'\n\n");*/
	//printf("%d\n",load_library("dyn/sort.dyn"));
	//printf("Loading refstr.c32\n%d\n",load_library("dyn/refstr.c32"));
	//printf("Loading colors.c32\n%d\n",load_library("dyn/colors.c32"));
	//printf("Loading readconfig.c32\n%d\n",load_library("dyn/readconfig.c32"));
	printf("Loading background.c32\n%d\n",load_library("dyn/background.c32"));
	printf("Loading printmsg.c32\n%d\n",load_library("dyn/printmsg.c32"));
	printf("Loading drain.c32\n%d\n",load_library("dyn/drain.c32"));
	printf("Loading sha1hash.c32\n%d\n",load_library("dyn/sha1hash.c32"));
	printf("Loading unbase64.c32\n%d\n",load_library("dyn/unbase64.c32"));
	printf("Loading sha512crypt\n%d\n",load_library("dyn/sha512crypt.c32"));
	printf("Loading sha256crypt\n%d\n",load_library("dyn/sha256crypt.c32"));
	printf("Loading md5.c32\n%d\n",load_library("dyn/md5.c32"));
	printf("Loading crypt-md5.c32\n%d\n",load_library("dyn/crypt-md5.c32"));
	printf("Loading passwd.c32\n%d\n",load_library("dyn/passwd.c32"));
	printf("Loading execute.c32\n%d\n",load_library("dyn/execute.c32"));
	printf("Loading get_key.c32\n%d\n",load_library("dyn/get_key.c32"));
	printf("Loading menumain.c32\n%d\n",load_library("dyn/menumain.c32"));
	printf("Loading ansiraw.c32\n%d\n",load_library("dyn/ansiraw.c32"));

	/*printf("\n\nTrying to spawn 'dyn/hello.dyn'\n\n"); 
	spawnv("dyn/hello.dyn",0);
	printf("\nTest done\n");*/
	printf("%d\n",spawnv("dyn/mytest.c32",argv));
	printf("Done\n");
	
	while(1) 1; /* we don't have anything better to do so hang around for a bit */
}

