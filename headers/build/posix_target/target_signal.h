/*
 * Copyright 2002-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SIGNAL_H_
#define _SIGNAL_H_


#include <sys/target_types.h>


typedef int							_HAIKU_BUILD_IDENTIFIER(sig_atomic_t);
typedef __haiku_build_haiku_uint64	_HAIKU_BUILD_IDENTIFIER(sigset_t);


/* macros defining the standard signal handling behavior */
// NOTE: #8730 -- does __sighandler_t need to be prefixed?
#define _HAIKU_BUILD_SIG_DFL		((__sighandler_t)0)		/* "default" signal behaviour */
#define _HAIKU_BUILD_SIG_IGN		((__sighandler_t)1)		/* ignore signal */
#define _HAIKU_BUILD_SIG_ERR		((__sighandler_t)-1)	/* an error occurred during signal
																processing */
#define _HAIKU_BUILD_SIG_HOLD		((__sighandler_t)3)		/* the signal was hold */

/* macros specifying the event notification type (sigevent::sigev_notify) */
#define _HAIKU_BUILD_SIGEV_NONE		0	/* no notification */
#define _HAIKU_BUILD_SIGEV_SIGNAL	1	/* notify via queued signal */
#define _HAIKU_BUILD_SIGEV_THREAD	2	/* notify via function called in new thread */


// NOTE: #8730 -- are unions handled in the same was as structs, enums?
union _HAIKU_BUILD_IDENTIFIER(sigval) {
	int		sival_int;
	void*	sival_ptr;
};

struct _HAIKU_BUILD_IDENTIFIER(sigevent) {
	int										sigev_notify;	/* notification type */
	int										sigev_signo;	/* signal number */
	union _HAIKU_BUILD_IDENTIFIER(sigval)	sigev_value;	/* user-defined signal value */
	// NOTE: #8730 -- hmm. No idea as what to do for this.
	void									(*sigev_notify_function)(union _HAIKU_BUILD_IDENTIFIER(sigval));
									/* notification function in case of
										SIGEV_THREAD */
	// TODO: #8730 -- revisit pthread.* after creating target_pthread.h
	pthread_attr_t*	sigev_notify_attributes;
									/* pthread creation attributes in case of
										SIGEV_THREAD */
};

typedef struct _HAIKU_BUILD_IDENTIFIER(__siginfo_t) {
	int										si_signo;	/* signal number */
	int										si_code;	/* signal code */
	int										si_errno;	/* if non zero, an
														error number associated
														with this signal */
	_HAIKU_BUILD_IDENTIFIER(pid_t)				si_pid;		/* sending process ID */
	_HAIKU_BUILD_IDENTIFIER(uid_t)			si_uid;		/* real user ID of
														sending process */
	void*									si_addr;	/* address of faulting
														instruction */
	int										si_status;	/* exit value or signal */
	long									si_band;	/* band event for SIGPOLL */
	union _HAIKU_BUILD_IDENTIFIER(sigval)	si_value;	/* signal value */
} _HAIKU_BUILD_IDENTIFIER(siginfo_t);


/* signal handler function types */
// TODO: #8730 -- Get advice from Ingo on what to do.
typedef void (*__sighandler_t)(int);
typedef void (*__siginfo_handler_t)(int, _HAIKU_BUILD_IDENTIFIER(siginfo_t)*, void*);

#ifdef __USE_GNU
typedef __sighandler_t	sighandler_t;
	/* GNU-like signal handler typedef */
#endif


/* structure used by sigaction() */
struct _HAIKU_BUILD_IDENTIFIER(sigaction) {
	union {
		__sighandler_t					sa_handler;
		__siginfo_handler_t				sa_sigaction;
	};
	_HAIKU_BUILD_IDENTIFIER(sigset_t)	sa_mask;
	int									sa_flags;
	void*								sa_userdata;	/* will be passed to
														the signal handler,
														BeOS extension */
};

/* values for sa_flags */
#define _HAIKU_BUILD_SA_NOCLDSTOP	0x01
#define _HAIKU_BUILD_SA_NOCLDWAIT	0x02
#define _HAIKU_BUILD_SA_RESETHAND	0x04
#define _HAIKU_BUILD_SA_NODEFER		0x08
#define _HAIKU_BUILD_SA_RESTART		0x10
#define _HAIKU_BUILD_SA_ONSTACK		0x20
#define _HAIKU_BUILD_SA_SIGINFO		0x40
#define _HAIKU_BUILD_SA_NOMASK		SA_NODEFER
#define _HAIKU_BUILD_SA_STACK		SA_ONSTACK
#define _HAIKU_BUILD_SA_ONESHOT		SA_RESETHAND

/* values for ss_flags */
#define _HAIKU_BUILD_SS_ONSTACK		0x1
#define _HAIKU_BUILD_SS_DISABLE		0x2

#define _HAIKU_BUILD_MINSIGSTKSZ	4096
#define _HAIKU_BUILD_SIGSTKSZ		16384

/* for signals using an alternate stack */
typedef struct _HAIKU_BUILD_IDENTIFIER(stack_t) {
	void*	ss_sp;
	size_t	ss_size;
	int		ss_flags;
} _HAIKU_BUILD_IDENTIFIER(stack_t);

/* for the 'how' arg of sigprocmask() */
#define _HAIKU_BUILD_SIG_BLOCK		1
#define _HAIKU_BUILD_SIG_UNBLOCK	2
#define _HAIKU_BUILD_SIG_SETMASK	3

/*
 * The list of all defined signals:
 *
 * The numbering of signals for Haiku attempts to maintain
 * some consistency with UN*X conventions so that things
 * like "kill -9" do what you expect.
 */
#define	_HAIKU_BUILD_SIGHUP			1	/* hangup -- tty is gone! */
#define _HAIKU_BUILD_SIGINT			2	/* interrupt */
#define _HAIKU_BUILD_SIGQUIT		3	/* `quit' special character typed in tty */
#define _HAIKU_BUILD_SIGILL			4	/* illegal instruction */
#define _HAIKU_BUILD_SIGCHLD		5	/* child process exited */
#define _HAIKU_BUILD_SIGABRT		6	/* abort() called, dont' catch */
#define _HAIKU_BUILD_SIGPIPE		7	/* write to a pipe w/no readers */
#define _HAIKU_BUILD_SIGFPE			8	/* floating point exception */
#define _HAIKU_BUILD_SIGKILL		9	/* kill a team (not catchable) */
#define _HAIKU_BUILD_SIGSTOP		10	/* suspend a thread (not catchable) */
#define _HAIKU_BUILD_SIGSEGV		11	/* segmentation violation (read: invalid pointer) */
#define _HAIKU_BUILD_SIGCONT		12	/* continue execution if suspended */
#define _HAIKU_BUILD_SIGTSTP		13	/* `stop' special character typed in tty */
#define _HAIKU_BUILD_SIGALRM		14	/* an alarm has gone off (see alarm()) */
#define _HAIKU_BUILD_SIGTERM		15	/* termination requested */
#define _HAIKU_BUILD_SIGTTIN		16	/* read of tty from bg process */
#define _HAIKU_BUILD_SIGTTOU		17	/* write to tty from bg process */
#define _HAIKU_BUILD_SIGUSR1		18	/* app defined signal 1 */
#define _HAIKU_BUILD_SIGUSR2		19	/* app defined signal 2 */
#define _HAIKU_BUILD_SIGWINCH		20	/* tty window size changed */
#define _HAIKU_BUILD_SIGKILLTHR		21	/* be specific: kill just the thread, not team */
#define _HAIKU_BUILD_SIGTRAP		22	/* Trace/breakpoint trap */
#define _HAIKU_BUILD_SIGPOLL		23	/* Pollable event */
#define _HAIKU_BUILD_SIGPROF		24	/* Profiling timer expired */
#define _HAIKU_BUILD_SIGSYS			25	/* Bad system call */
#define _HAIKU_BUILD_SIGURG			26	/* High bandwidth data is available at socket */
#define _HAIKU_BUILD_SIGVTALRM		27	/* Virtual timer expired */
#define _HAIKU_BUILD_SIGXCPU		28	/* CPU time limit exceeded */
#define _HAIKU_BUILD_SIGXFSZ		29	/* File size limit exceeded */
#define _HAIKU_BUILD_SIGBUS			30	/* access to undefined portion of a memory object */
#define _HAIKU_BUILD_SIGRESERVED1	31	/* reserved for future use */
#define _HAIKU_BUILD_SIGRESERVED2	32	/* reserved for future use */

#define _HAIKU_BUILD_SIGRTMIN		(__signal_get_sigrtmin())
							/* lowest realtime signal number */
#define _HAIKU_BUILD_SIGRTMAX		(__signal_get_sigrtmax())
							/* greatest realtime signal number */

#define __HAIKU_BUILD_MAX_SIGNO		64	/* greatest possible signal number, can be used (+1)
								as size of static arrays */
#define _HAIKU_BUILD_NSIG			(__MAX_SIGNO + 1)
							/* BSD extension, size of the sys_siglist table,
								obsolete */


/* Signal code values appropriate for siginfo_t::si_code: */
/* any signal */
#define _HAIKU_BUILD_SI_USER		0	/* signal sent by user */
#define _HAIKU_BUILD_SI_QUEUE		1	/* signal sent by sigqueue() */
#define _HAIKU_BUILD_SI_TIMER		2	/* signal sent on timer_settime() timeout */
#define _HAIKU_BUILD_SI_ASYNCIO		3	/* signal sent on asynchronous I/O completion */
#define _HAIKU_BUILD_SI_MESGQ		4	/* signal sent on arrival of message on empty
								message queue */
/* SIGILL */
#define _HAIKU_BUILD_ILL_ILLOPC		10	/* illegal opcode */
#define _HAIKU_BUILD_ILL_ILLOPN		11	/* illegal operand */
#define _HAIKU_BUILD_ILL_ILLADR		12	/* illegal addressing mode */
#define _HAIKU_BUILD_ILL_ILLTRP		13	/* illegal trap */
#define _HAIKU_BUILD_ILL_PRVOPC		14	/* privileged opcode */
#define _HAIKU_BUILD_ILL_PRVREG		15	/* privileged register */
#define _HAIKU_BUILD_ILL_COPROC		16	/* coprocessor error */
#define _HAIKU_BUILD_ILL_BADSTK		17	/* internal stack error */
/* SIGFPE */
#define _HAIKU_BUILD_FPE_INTDIV		20	/* integer division by zero */
#define _HAIKU_BUILD_FPE_INTOVF		21	/* integer overflow */
#define _HAIKU_BUILD_FPE_FLTDIV		22	/* floating-point division by zero */
#define _HAIKU_BUILD_FPE_FLTOVF		23	/* floating-point overflow */
#define _HAIKU_BUILD_FPE_FLTUND		24	/* floating-point underflow */
#define _HAIKU_BUILD_FPE_FLTRES		25	/* floating-point inexact result */
#define _HAIKU_BUILD_FPE_FLTINV		26	/* invalid floating-point operation */
#define _HAIKU_BUILD_FPE_FLTSUB		27	/* subscript out of range */
/* SIGSEGV */
#define _HAIKU_BUILD_SEGV_MAPERR	30	/* address not mapped to object */
#define _HAIKU_BUILD_SEGV_ACCERR	31	/* invalid permissions for mapped object */
/* SIGBUS */
#define _HAIKU_BUILD_BUS_ADRALN		40	/* invalid address alignment */
#define _HAIKU_BUILD_BUS_ADRERR		41	/* nonexistent physical address */
#define _HAIKU_BUILD_BUS_OBJERR		42	/* object-specific hardware error */
/* SIGTRAP */
#define _HAIKU_BUILD_TRAP_BRKPT		50	/* process breakpoint */
#define _HAIKU_BUILD_TRAP_TRACE		51	/* process trace trap. */
/* SIGCHLD */
#define _HAIKU_BUILD_CLD_EXITED		60	/* child exited */
#define _HAIKU_BUILD_CLD_KILLED		61	/* child terminated abnormally without core dump */
#define _HAIKU_BUILD_CLD_DUMPED		62	/* child terminated abnormally with core dump */
#define _HAIKU_BUILD_CLD_TRAPPED	63	/* traced child trapped */
#define _HAIKU_BUILD_CLD_STOPPED	64	/* child stopped */
#define _HAIKU_BUILD_CLD_CONTINUED	65	/* stopped child continued */
/* SIGPOLL */
#define _HAIKU_BUILD_POLL_IN		70	/* input available */
#define _HAIKU_BUILD_POLL_OUT		71	/* output available */
#define _HAIKU_BUILD_POLL_MSG		72	/* input message available */
#define _HAIKU_BUILD_POLL_ERR		73	/* I/O error */
#define _HAIKU_BUILD_POLL_PRI		74	/* high priority input available */
#define _HAIKU_BUILD_POLL_HUP		75	/* device disconnected */


/* the global table of text strings containing descriptions for each signal */
_HAIKU_BUILD_DECLARE_VARIABLE_ETC(const char* const, sys_siglist, [NSIG])
	/* BSD extension, obsolete, use strsignal() instead */


#ifdef __cplusplus
extern "C" {
#endif


/* signal management (actions and block masks) */
_HAIKU_BUILD_DECLARE_FUNCTION(__sighandler_t, signal,
	(int _signal, __sighandler_t signalHandler))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigaction,
	(int _signal, const struct _HAIKU_BUILD_IDENTIFIER(sigaction)* action,
		struct _HAIKU_BUILD_IDENTIFIER(sigaction)* oldAction))
_HAIKU_BUILD_DECLARE_FUNCTION(__sighandler_t, sigset,
	(int _signal, __sighandler_t signalHandler))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigignore, (int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, siginterrupt, (int _signal, int flag))

_HAIKU_BUILD_DECLARE_FUNCTION(int, sigprocmask,
	(int how, const _HAIKU_BUILD_IDENTIFIER(sigset_t)* set, _HAIKU_BUILD_IDENTIFIER(sigset_t)* oldSet))
_HAIKU_BUILD_DECLARE_FUNCTION(int, pthread_sigmask,
	(int how, const _HAIKU_BUILD_IDENTIFIER(sigset_t)* set, _HAIKU_BUILD_IDENTIFIER(sigset_t)* oldSet))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sighold, (int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigrelse, (int _signal))

/* sending signals */
_HAIKU_BUILD_DECLARE_FUNCTION(int, raise, (int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, kill, (_haiku_build_pid_t pid, int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, killpg, (_haiku_build_pid_t processGroupID, int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigqueue,
	(_haiku_build_pid_t pid, int _signal, const union _HAIKU_BUILD_IDENTIFIER(sigval) userValue))
_HAIKU_BUILD_DECLARE_FUNCTION(int, pthread_kill,
	(pthread_t thread, int _signal))

/* querying and waiting for signals */
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigpending, (_HAIKU_BUILD_IDENTIFIER(sigset_t)* set))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigsuspend, (const _HAIKU_BUILD_IDENTIFIER(sigset_t)* mask))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigpause, (int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigwait,
	(const _HAIKU_BUILD_IDENTIFIER(sigset_t)* set, int* _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigwaitinfo,
	(const _HAIKU_BUILD_IDENTIFIER(sigset_t)* set, _HAIKU_BUILD_IDENTIFIER(siginfo_t)* info))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigtimedwait,
	(const _HAIKU_BUILD_IDENTIFIER(sigset_t)* set, _HAIKU_BUILD_IDENTIFIER(siginfo_t)* info,
		const struct _HAIKU_BUILD_IDENTIFIER(timespec)* timeout))

/* setting the per-thread signal stack */
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigaltstack,
	(const stack_t* stack, stack_t* oldStack))

/* signal set (sigset_t) manipulation */
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigemptyset, (_HAIKU_BUILD_IDENTIFIER(sigset_t)* set))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigfillset, (_HAIKU_BUILD_IDENTIFIER(sigset_t)* set))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigaddset, (_HAIKU_BUILD_IDENTIFIER(sigset_t)* set, int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigdelset, (_HAIKU_BUILD_IDENTIFIER(sigset_t)* set, int _signal))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sigismember,
	(const _HAIKU_BUILD_IDENTIFIER(sigset_t)* set, int _signal))

/* printing signal names */
_HAIKU_BUILD_DECLARE_FUNCTION(void, psiginfo,
	(const _HAIKU_BUILD_IDENTIFIER(siginfo_t)* info, const char* message))
_HAIKU_BUILD_DECLARE_FUNCTION(void, psignal, (int _signal, const char* message))

/* implementation private */
_HAIKU_BUILD_DECLARE_FUNCTION(int, __signal_get_sigrtmin, ())
_HAIKU_BUILD_DECLARE_FUNCTION(int, __signal_get_sigrtmax, ())


#ifdef __cplusplus
}
#endif


/* TODO: move this into the documentation!
 * ==================================================
 * !!! SPECIAL NOTES CONCERNING NON-POSIX EXTENSIONS:
 * ==================================================
 *
 * The standard Posix interface for signal handlers is not as useful
 * as it could be. The handler can define only one single argument
 * (the signal number). For example:
 *	void
 *	my_signal_handler(int sig)
 *	{
 *	. . .
 *	}
 *
 *	// install the handler
 *	signal(SIGINT, &my_signal_handler);
 *
 * The sigaction() function allows finer grained control of the signal
 * handling. It also allows an opportunity, via the 'sigaction' struct, to
 * enable additional data to be passed to the handler. For example:
 *	void
 *	my_signal_handler(int sig, char* userData, vregs* regs)
 *	{
 *	. . .
 *	}
 *
 *	struct sigaction sa;
 *	char data_buffer[32];
 *
 *	sa.sa_handler = (__sighandler_t)my_signal_handler;
 *	sigemptyset(&sa.sa_mask);
 *	sa.sa_userdata = userData;
 *
 *	// install the handler
 *	sigaction(SIGINT, &sa, NULL);
 *
 * The two additional arguments available to the signal handler are extensions
 * to the Posix standard. This feature was introduced by the BeOS and retained
 * by Haiku. However, to remain compatible with Posix and ANSI C, the type
 * of the sa_handler field is defined as '__sighandler_t'. This requires the
 * handler to be cast when assigned to the sa_handler field, as in the example
 * above.
 *
 * The 3 arguments that Haiku provides to signal handlers are as follows:
 * 1) The first argument is the (usual) signal number.
 *
 * 2) The second argument is whatever value is put in the sa_userdata field
 *	of the sigaction struct.
 *
 * 3) The third argument is a pointer to a vregs struct (defined below).
 *	The vregs struct contains the contents of the volatile registers at
 *	the time the signal was delivered to your thread. You can change the
 *	fields of the structure. After your signal handler completes, the OS uses
 *	this struct to reload the registers for your thread (privileged registers
 *	are not loaded of course). The vregs struct is of course terribly machine
 *	dependent.
 *	Note that in BeOS the vregs argument was passed by value, not by pointer.
 *	While Haiku retains binary compability with code compiled for BeOS, code
 *	built under Haiku must use the pointer argument.
 */

/*
 * the vregs struct:
 *
 * signal handlers get this as the last argument
 */
typedef struct _HAIKU_BUILD_IDENTIFIER(vregs) vregs;
	/* BeOS extension */


/* include architecture specific definitions */
#include __HAIKU_BUILD_HAIKU_ARCH_HEADER(target_signal.h)



typedef struct _HAIKU_BUILD_IDENTIFIER(vregs) mcontext_t;

typedef struct _HAIKU_BUILD_IDENTIFIER(__ucontext_t) {
	struct _HAIKU_BUILD_IDENTIFIER(__ucontext_t)*	uc_link;
	_HAIKU_BUILD_IDENTIFIER(sigset_t)				uc_sigmask;
	_HAIKU_BUILD_IDENTIFIER(stack_t)				uc_stack;
	_HAIKU_BUILD_IDENTIFIER(mcontext_t)				uc_mcontext;
} _HAIKU_BUILD_IDENTIFIER(ucontext_t);

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
	/* macros defining the standard signal handling behavior */
#	define SIG_DFL			_HAIKU_BUILD_SIG_DFL	/* "default" signal behaviour */
#	define SIG_IGN			_HAIKU_BUILD_SIG_IGN	/* ignore signal */
#	define SIG_ERR			_HAIKU_BUILD_SIG_ERR	/* an error occurred during signal
												   processing */
#	define SIG_HOLD			_HAIKU_BUILD_SIG_HOLD	/* the signal was hold */

	/* macros specifying the event notification type (sigevent::sigev_notify) */
#	define SIGEV_NONE		_HAIKU_BUILD_SIGEV_NONE	/* no notification */
#	define SIGEV_SIGNAL		_HAIKU_BUILD_SIGEV_SIGNAL	/* notify via queued signal */
#	define SIGEV_THREAD		_HAIKU_BUILD_SIGEV_THREAD	/* notify via function called in new thread */

	/* values for sa_flags */
#	define SA_NOCLDSTOP		_HAIKU_BUILD_SA_NOCLDSTOP
#	define SA_NOCLDWAIT		_HAIKU_BUILD_SA_NOCLDWAIT
#	define SA_RESETHAND		_HAIKU_BUILD_SA_RESETHAND
#	define SA_NODEFER		_HAIKU_BUILD_SA_NODEFER
#	define SA_RESTART		_HAIKU_BUILD_SA_RESTART
#	define SA_ONSTACK		_HAIKU_BUILD_SA_ONSTACK
#	define SA_SIGINFO		_HAIKU_BUILD_SA_SIGINFO
#	define SA_NOMASK		_HAIKU_BUILD_SA_NOMASK
#	define SA_STACK			_HAIKU_BUILD_SA_STACK
#	define SA_ONESHOT		_HAIKU_BUILD_SA_ONESHOT

	/* values for ss_flags */
#	define SS_ONSTACK		_HAIKU_BUILD_SS_ONSTACK
#	define SS_DISABLE		_HAIKU_BUILD_SS_DISABLE

#	define MINSIGSTKSZ		_HAIKU_BUILD_MINSIGSTKSZ
#	define SIGSTKSZ			_HAIKU_BUILD_SIGSTKSZ

	/* for the 'how' arg of sigprocmask() */
#	define SIG_BLOCK		_HAIKU_BUILD_SIG_BLOCK
#	define SIG_UNBLOCK		_HAIKU_BUILD_SIG_UNBLOCK
#	define SIG_SETMASK		_HAIKU_BUILD_SIG_SETMASK

	/*
	 * The list of all defined signals:
	 *
	 * The numbering of signals for Haiku attempts to maintain
	 * some consistency with UN*X conventions so that things
	 * like "kill -9" do what you expect.
	 */
#	define SIGHUP			_HAIKU_BUILD_SIGHUP		/* hangup -- tty is gone! */
#	define SIGINT			_HAIKU_BUILD_SIGINT		/* interrupt */
#	define SIGQUIT			_HAIKU_BUILD_SIGQUIT	/* `quit' special character typed in tty  */
#	define SIGILL			_HAIKU_BUILD_SIGILL		/* illegal instruction */
#	define SIGCHLD			_HAIKU_BUILD_SIGCHLD	/* child process exited */
#	define SIGABRT			_HAIKU_BUILD_SIGABRT	/* abort() called, dont' catch */
#	define SIGPIPE			_HAIKU_BUILD_SIGPIPE	/* write to a pipe w/no readers */
#	define SIGFPE			_HAIKU_BUILD_SIGFPE		/* floating point exception */
#	define SIGKILL			_HAIKU_BUILD_SIGKILL	/* kill a team (not catchable) */
#	define SIGSTOP			_HAIKU_BUILD_SIGSTOP	/* suspend a thread (not catchable) */
#	define SIGSEGV			_HAIKU_BUILD_SIGSEGV	/* segmentation violation (read: invalid pointer) */
#	define SIGCONT			_HAIKU_BUILD_SIGCONT	/* continue execution if suspended */
#	define SIGTSTP			_HAIKU_BUILD_SIGTSTP	/* `stop' special character typed in tty */
#	define SIGALRM			_HAIKU_BUILD_SIGALRM	/* an alarm has gone off (see alarm()) */
#	define SIGTERM			_HAIKU_BUILD_SIGTERM	/* termination requested */
#	define SIGTTIN			_HAIKU_BUILD_SIGTTIN	/* read of tty from bg process */
#	define SIGTTOU			_HAIKU_BUILD_SIGTTOU	/* write to tty from bg process */
#	define SIGUSR1			_HAIKU_BUILD_SIGUSR1	/* app defined signal 1 */
#	define SIGUSR2			_HAIKU_BUILD_SIGUSR2	/* app defined signal 2 */
#	define SIGWINCH			_HAIKU_BUILD_SIGWINCH	/* tty window size changed */
#	define SIGKILLTHR		_HAIKU_BUILD_SIGKILLTHR	/* be specific: kill just the thread, not team */
#	define SIGTRAP			_HAIKU_BUILD_SIGTRAP	/* Trace/breakpoint trap */
#	define SIGPOLL			_HAIKU_BUILD_SIGPOLL	/* Pollable event */
#	define SIGPROF			_HAIKU_BUILD_SIGPROF	/* Profiling timer expired */
#	define SIGSYS			_HAIKU_BUILD_SIGSYS		/* Bad system call */
#	define SIGURG			_HAIKU_BUILD_SIGURG		/* High bandwidth data is available at socket */
#	define SIGVTALRM		_HAIKU_BUILD_SIGVTALRM	/* Virtual timer expired */
#	define SIGXCPU			_HAIKU_BUILD_SIGXCPU	/* CPU time limit exceeded */
#	define SIGXFSZ			_HAIKU_BUILD_SIGXFSZ	/* File size limit exceeded */
#	define SIGBUS			_HAIKU_BUILD_SIGBUS		/* access to undefined portion of a memory object */
#	define SIGRESERVED1		_HAIKU_BUILD_SIGRESERVED1	/* reserved for future use */
#	define SIGRESERVED2		_HAIKU_BUILD_SIGRESERVED2	/* reserved for future use */

#	define SIGRTMIN			_HAIKU_BUILD_SIGRTMIN
								/* lowest realtime signal number */
#	define SIGRTMAX			_HAIKU_BUILD_SIGRTMAX
								/* greatest realtime signal number */

#	define __MAX_SIGNO		__HAIKU_BUILD_MAX_SIGNO	/* greatest possible signal
													number, can be used (+1) as
													size of static arrays */
#	define NSIG				_HAIKU_BUILD_NSIG
								/* BSD extension, size of the sys_siglist table,
								   obsolete */


	/* Signal code values appropriate for siginfo_t::si_code: */
	/* any signal */
#	define SI_USER			_HAIKU_BUILD_SI_USER	/* signal sent by user */
#	define SI_QUEUE			_HAIKU_BUILD_SI_QUEUE	/* signal sent by sigqueue() */
#	define SI_TIMER			_HAIKU_BUILD_SI_TIMER	/* signal sent on timer_settime() timeout */
#	define SI_ASYNCIO		_HAIKU_BUILD_SI_ASYNCIO	/* signal sent on asynchronous I/O completion */
#	define SI_MESGQ			_HAIKU_BUILD_SI_MESGQ	/* signal sent on arrival of message on empty
								   message queue */
	/* SIGILL */
#	define ILL_ILLOPC		_HAIKU_BUILD_ILL_ILLOPC	/* illegal opcode */
#	define ILL_ILLOPN		_HAIKU_BUILD_ILL_ILLOPN	/* illegal operand */
#	define ILL_ILLADR		_HAIKU_BUILD_ILL_ILLADR	/* illegal addressing mode */
#	define ILL_ILLTRP		_HAIKU_BUILD_ILL_ILLTRP	/* illegal trap */
#	define ILL_PRVOPC		_HAIKU_BUILD_ILL_PRVOPC	/* privileged opcode */
#	define ILL_PRVREG		_HAIKU_BUILD_ILL_PRVREG	/* privileged register */
#	define ILL_COPROC		_HAIKU_BUILD_ILL_COPROC	/* coprocessor error */
#	define ILL_BADSTK		_HAIKU_BUILD_ILL_BADSTK	/* internal stack error */
	/* SIGFPE */
#	define FPE_INTDIV		_HAIKU_BUILD_FPE_INTDIV	/* integer division by zero */
#	define FPE_INTOVF		_HAIKU_BUILD_FPE_INTOVF	/* integer overflow */
#	define FPE_FLTDIV		_HAIKU_BUILD_FPE_FLTDIV	/* floating-point division by zero */
#	define FPE_FLTOVF		_HAIKU_BUILD_FPE_FLTOVF	/* floating-point overflow */
#	define FPE_FLTUND		_HAIKU_BUILD_FPE_FLTUND	/* floating-point underflow */
#	define FPE_FLTRES		_HAIKU_BUILD_FPE_FLTRES	/* floating-point inexact result */
#	define FPE_FLTINV		_HAIKU_BUILD_FPE_FLTINV	/* invalid floating-point operation */
#	define FPE_FLTSUB		_HAIKU_BUILD_FPE_FLTSUB	/* subscript out of range */
	/* SIGSEGV */
#	define SEGV_MAPERR		_HAIKU_BUILD_SEGV_MAPERR	/* address not mapped to object */
#	define SEGV_ACCERR		_HAIKU_BUILD_SEGV_ACCERR	/* invalid permissions for mapped object */
	/* SIGBUS */
#	define BUS_ADRALN		_HAIKU_BUILD_BUS_ADRALN	/* invalid address alignment */
#	define BUS_ADRERR		_HAIKU_BUILD_BUS_ADRERR	/* nonexistent physical address */
#	define BUS_OBJERR		_HAIKU_BUILD_BUS_OBJERR	/* object-specific hardware error */
	/* SIGTRAP */
#	define TRAP_BRKPT		_HAIKU_BUILD_TRAP_BRKPT	/* process breakpoint */
#	define TRAP_TRACE		_HAIKU_BUILD_TRAP_TRACE	/* process trace trap. */
	/* SIGCHLD */
#	define CLD_EXITED		_HAIKU_BUILD_CLD_EXITED	/* child exited */
#	define CLD_KILLED		_HAIKU_BUILD_CLD_KILLED	/* child terminated abnormally without core dump */
#	define CLD_DUMPED		_HAIKU_BUILD_CLD_DUMPED	/* child terminated abnormally with core dump */
#	define CLD_TRAPPED		_HAIKU_BUILD_CLD_TRAPPED	/* traced child trapped */
#	define CLD_STOPPED		_HAIKU_BUILD_CLD_STOPPED	/* child stopped */
#	define CLD_CONTINUED	_HAIKU_BUILD_CLD_CONTINUED	/* stopped child continued */
	/* SIGPOLL */
#	define POLL_IN			_HAIKU_BUILD_POLL_IN	/* input available */
#	define POLL_OUT			_HAIKU_BUILD_POLL_OUT	/* output available */
#	define POLL_MSG			_HAIKU_BUILD_POLL_MSG	/* input message available */
#	define POLL_ERR			_HAIKU_BUILD_POLL_ERR	/* I/O error */
#	define POLL_PRI			_HAIKU_BUILD_POLL_PRI	/* high priority input available */
#	define POLL_HUP			_HAIKU_BUILD_POLL_HUP	/* device disconnected */

#	endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */
#endif /* _SIGNAL_H_ */
