/*
 * Copyright 2005-2011, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */


#include <target_errno.h>
#include <target_string.h>

#include <map>

using namespace std;

static map<int, int> sToHaikuErrorMap;
static map<int, int> sToHostErrorMap;
static bool sErrorMapsInitialized = false;

// init_error_map
static void
init_error_map()
{
	if (sErrorMapsInitialized)
		return;

	#define ADD_ERROR(error) \
		sToHaikuErrorMap[error] = _HAIKU_BUILD_##error; \
		sToHostErrorMap[_HAIKU_BUILD_##error] = error;

	ADD_ERROR(E2BIG);
	ADD_ERROR(ECHILD);
	ADD_ERROR(EDEADLK);
	ADD_ERROR(EFBIG);
	ADD_ERROR(EMLINK);
	ADD_ERROR(ENFILE);
	ADD_ERROR(ENODEV);
	ADD_ERROR(ENOLCK);
	ADD_ERROR(ENOSYS);
	ADD_ERROR(ENOTTY);
	ADD_ERROR(ENXIO);
	ADD_ERROR(ESPIPE);
	ADD_ERROR(ESRCH);
	#ifdef EFPOS
		ADD_ERROR(EFPOS);
	#endif
	#ifdef ESIGPARM
		ADD_ERROR(ESIGPARM);
	#endif
	ADD_ERROR(EDOM);
	ADD_ERROR(ERANGE);
	ADD_ERROR(EPROTOTYPE);
	ADD_ERROR(EPROTONOSUPPORT);
	ADD_ERROR(EPFNOSUPPORT);
	ADD_ERROR(EAFNOSUPPORT);
	ADD_ERROR(EADDRINUSE);
	ADD_ERROR(EADDRNOTAVAIL);
	ADD_ERROR(ENETDOWN);
	ADD_ERROR(ENETUNREACH);
	ADD_ERROR(ENETRESET);
	ADD_ERROR(ECONNABORTED);
	ADD_ERROR(ECONNRESET);
	ADD_ERROR(EISCONN);
	ADD_ERROR(ENOTCONN);
	ADD_ERROR(ESHUTDOWN);
	ADD_ERROR(ECONNREFUSED);
	ADD_ERROR(EHOSTUNREACH);
	ADD_ERROR(ENOPROTOOPT);
	ADD_ERROR(ENOBUFS);
	ADD_ERROR(EINPROGRESS);
	ADD_ERROR(EALREADY);
	ADD_ERROR(EILSEQ);
	ADD_ERROR(ENOMSG);
	ADD_ERROR(ESTALE);
	ADD_ERROR(EOVERFLOW);
	ADD_ERROR(EMSGSIZE);
	ADD_ERROR(EOPNOTSUPP);
	ADD_ERROR(ENOTSOCK);
	ADD_ERROR(EHOSTDOWN);
	ADD_ERROR(EBADMSG);
	#ifdef ECANCELED
		ADD_ERROR(ECANCELED);
	#endif
	ADD_ERROR(EDESTADDRREQ);
	ADD_ERROR(EDQUOT);
	ADD_ERROR(EIDRM);
	ADD_ERROR(EMULTIHOP);
	#ifdef ENODATA
		ADD_ERROR(ENODATA);
	#endif
	ADD_ERROR(ENOLINK);
	#ifdef ENOSR
		ADD_ERROR(ENOSR);
	#endif
	#ifdef ENOSTR
		ADD_ERROR(ENOSTR);
	#endif
	ADD_ERROR(ENOTSUP);
	ADD_ERROR(EPROTO);
	#ifdef ETIME
		ADD_ERROR(ETIME);
	#endif
	ADD_ERROR(ETXTBSY);
	ADD_ERROR(ENOMEM);
	ADD_ERROR(EACCES);
	ADD_ERROR(EINTR);
	ADD_ERROR(EIO);
	ADD_ERROR(EBUSY);
	ADD_ERROR(EFAULT);
	ADD_ERROR(ETIMEDOUT);
	ADD_ERROR(EAGAIN);
	ADD_ERROR(EWOULDBLOCK);
	ADD_ERROR(EBADF);
	ADD_ERROR(EEXIST);
	ADD_ERROR(EINVAL);
	ADD_ERROR(ENAMETOOLONG);
	ADD_ERROR(ENOENT);
	ADD_ERROR(EPERM);
	ADD_ERROR(ENOTDIR);
	ADD_ERROR(EISDIR);
	ADD_ERROR(ENOTEMPTY);
	ADD_ERROR(ENOSPC);
	ADD_ERROR(EROFS);
	ADD_ERROR(EMFILE);
	ADD_ERROR(EXDEV);
	ADD_ERROR(ELOOP);
	ADD_ERROR(ENOEXEC);
	ADD_ERROR(EPIPE);
	#ifdef ENOATTR
		ADD_ERROR(ENOATTR);
	#endif

	sErrorMapsInitialized = true;
}

// to_host_error
static int
to_host_error(int error)
{
	init_error_map();

	map<int, int>::iterator it = sToHostErrorMap.find(error);
	return (it != sToHostErrorMap.end() ? it->second : error);
}

// to_haiku_error
static int
to_haiku_error(int error)
{
	init_error_map();

	map<int, int>::iterator it = sToHaikuErrorMap.find(error);
	if (it != sToHaikuErrorMap.end())
		return it->second;

	return (error > 0 ? -error : error);
}

static char *
_haiku_build_error_description(int error)
{
	switch (error) {
		// General Errors

		case _HAIKU_BUILD_B_NO_ERROR:
		case _HAIKU_BUILD_B_POSIX_ENOMEM:
			return "No error";
		case _HAIKU_BUILD_B_ERROR:
			return "General system error";

		case _HAIKU_BUILD_B_NO_MEMORY:
			// _HAIKU_BUILD_ENOMEM
			return "Out of memory";
		case _HAIKU_BUILD_B_IO_ERROR:
			// _HAIKU_BUILD_EIO
			return "I/O error";
		case _HAIKU_BUILD_B_PERMISSION_DENIED:
			// _HAIKU_BUILD_EACCES
			return "Permission denied";
		case _HAIKU_BUILD_B_BAD_INDEX:
			return "Index not in range for the data set";
		case _HAIKU_BUILD_B_BAD_TYPE:
			return "Bad argument type passed to function";
		case _HAIKU_BUILD_B_BAD_VALUE:
			// _HAIKU_BUILD_EINVAL
			return "Invalid Argument";
		case _HAIKU_BUILD_B_MISMATCHED_VALUES:
			return "Mismatched values passed to function";
		case _HAIKU_BUILD_B_NAME_NOT_FOUND:
			return "Name not found";
		case _HAIKU_BUILD_B_NAME_IN_USE:
			return "Name in use";
		case _HAIKU_BUILD_B_TIMED_OUT:
			// _HAIKU_BUILD_ETIMEDOUT
			return "Operation timed out";
		case _HAIKU_BUILD_B_INTERRUPTED:
			// _HAIKU_BUILD_EINTR
			return "Interrupted system call";
		case _HAIKU_BUILD_B_WOULD_BLOCK:
			// _HAIKU_BUILD_EAGAIN
			// _HAIKU_BUILD_EWOULDBLOCK
			return "Operation would block";
		case _HAIKU_BUILD_B_CANCELED:
			return "Operation canceled";
		case _HAIKU_BUILD_B_NO_INIT:
			return "Initialization failed";
		case _HAIKU_BUILD_B_BUSY:
			// _HAIKU_BUILD_EBUSY
			return "Device/File/Resource busy";
		case _HAIKU_BUILD_B_NOT_ALLOWED:
			// _HAIKU_BUILD_EPERM
			return "Operation not allowed";
		case _HAIKU_BUILD_B_BAD_DATA:
			return "Bad data";

		// Kernel Kit Errors

		case _HAIKU_BUILD_B_BAD_SEM_ID:
			return "Bad semaphore ID";
		case _HAIKU_BUILD_B_NO_MORE_SEMS:
			return "No more semaphores";

		case _HAIKU_BUILD_B_BAD_THREAD_ID:
			return "Bad thread ID";
		case _HAIKU_BUILD_B_NO_MORE_THREADS:
			return "No more threads";
		case _HAIKU_BUILD_B_BAD_THREAD_STATE:
			return "Thread is inappropriate state";
		case _HAIKU_BUILD_B_BAD_TEAM_ID:
			return "Operation on invalid team";
		case _HAIKU_BUILD_B_NO_MORE_TEAMS:
			return "No more teams";

		case _HAIKU_BUILD_B_BAD_PORT_ID:
			return "Bad port ID";
		case _HAIKU_BUILD_B_NO_MORE_PORTS:
			return "No more ports available";	// "No more ports"

		case _HAIKU_BUILD_B_BAD_IMAGE_ID:
			return "Bad image ID";
		case _HAIKU_BUILD_B_BAD_ADDRESS:
			// _HAIKU_BUILD_EFAULT
			return "Bad address";
		case _HAIKU_BUILD_B_NOT_AN_EXECUTABLE:
			// _HAIKU_BUILD_ENOEXEC
			return "Not an executable";
		case _HAIKU_BUILD_B_MISSING_LIBRARY:
			return "Missing library";
		case _HAIKU_BUILD_B_MISSING_SYMBOL:
			return "Symbol not found";

		case _HAIKU_BUILD_B_DEBUGGER_ALREADY_INSTALLED:
			return "Debugger already installed for this team";

		// Application Kit Errors

		case _HAIKU_BUILD_B_BAD_REPLY:
			return "Invalid or unwanted reply";
		case _HAIKU_BUILD_B_DUPLICATE_REPLY:
			return "Duplicate reply";
		case _HAIKU_BUILD_B_MESSAGE_TO_SELF:
			return "Can't send message to self";
		case _HAIKU_BUILD_B_BAD_HANDLER:
			return "Bad handler";
		case _HAIKU_BUILD_B_ALREADY_RUNNING:
			return "Already running";
		case _HAIKU_BUILD_B_LAUNCH_FAILED:
			return "Launch failed";
		case _HAIKU_BUILD_B_AMBIGUOUS_APP_LAUNCH:
			return "Ambiguous app launch";
		case _HAIKU_BUILD_B_UNKNOWN_MIME_TYPE:
			return "Unknown MIME type";
		case _HAIKU_BUILD_B_BAD_SCRIPT_SYNTAX:
			return "Bad script syntax";
		case _HAIKU_BUILD_B_LAUNCH_FAILED_NO_RESOLVE_LINK:
			return "Could not resolve a link";
		case _HAIKU_BUILD_B_LAUNCH_FAILED_EXECUTABLE:
			return "File is mistakenly marked as executable";
		case _HAIKU_BUILD_B_LAUNCH_FAILED_APP_NOT_FOUND:
			return "Application could not be found";
		case _HAIKU_BUILD_B_LAUNCH_FAILED_APP_IN_TRASH:
			return "Application is in the trash";
		case _HAIKU_BUILD_B_LAUNCH_FAILED_NO_PREFERRED_APP:
			return "There is no preferred application for this type of file";
		case _HAIKU_BUILD_B_LAUNCH_FAILED_FILES_APP_NOT_FOUND:
			return "This file has a preferred app, but it could not be found";
		case _HAIKU_BUILD_B_BAD_MIME_SNIFFER_RULE:
			return "Bad sniffer rule";
		case _HAIKU_BUILD_B_NOT_A_MESSAGE:
			return "Data is not a message";
		case _HAIKU_BUILD_B_SHUTDOWN_CANCELLED:
			return "System shutdown cancelled";
		case _HAIKU_BUILD_B_SHUTTING_DOWN:
			return "System shutting down";

		// Storage Kit Errors

		case _HAIKU_BUILD_B_FILE_ERROR:
			// _HAIKU_BUILD_EBADF
			return "Bad file descriptor";
		case _HAIKU_BUILD_B_FILE_NOT_FOUND:
		case _HAIKU_BUILD_B_ENTRY_NOT_FOUND:
			// _HAIKU_BUILD_ENOENT
			return "No such file or directory";
		case _HAIKU_BUILD_B_FILE_EXISTS:
			// _HAIKU_BUILD_EEXIST
			return "File or Directory already exists";
		case _HAIKU_BUILD_B_NAME_TOO_LONG:
			//	_HAIKU_BUILD_ENAMETOOLONG
			return "File name too long";
		case _HAIKU_BUILD_B_NOT_A_DIRECTORY:
			// _HAIKU_BUILD_ENOTDIR
			return "Not a directory";
		case _HAIKU_BUILD_B_DIRECTORY_NOT_EMPTY:
			// _HAIKU_BUILD_ENOTEMPTY
			return "Directory not empty";
		case _HAIKU_BUILD_B_DEVICE_FULL:
			// _HAIKU_BUILD_ENOSPC
			return "No space left on device";
		case _HAIKU_BUILD_B_READ_ONLY_DEVICE:
			// _HAIKU_BUILD_EROFS:
			return "Read-only file system";
		case _HAIKU_BUILD_B_IS_A_DIRECTORY:
			// _HAIKU_BUILD_EISDIR
			return "Is a directory";
		case _HAIKU_BUILD_B_NO_MORE_FDS:
			// _HAIKU_BUILD_EMFILE
			return "Too many open files";
		case _HAIKU_BUILD_B_CROSS_DEVICE_LINK:
			// _HAIKU_BUILD_EXDEV
			return "Cross-device link";
		case _HAIKU_BUILD_B_LINK_LIMIT:
			// _HAIKU_BUILD_ELOOP
			return "Too many symbolic links";
		case _HAIKU_BUILD_B_BUSTED_PIPE:
			// _HAIKU_BUILD_EPIPE
			return "Broken pipe";
		case _HAIKU_BUILD_B_UNSUPPORTED:
			return "Operation not supported";
		case _HAIKU_BUILD_B_PARTITION_TOO_SMALL:
			return "Partition too small to contain filesystem";

		// Media Kit Errors

		case _HAIKU_BUILD_B_STREAM_NOT_FOUND:
			return "Stream not found";
		case _HAIKU_BUILD_B_SERVER_NOT_FOUND:
			return "Server not found";
		case _HAIKU_BUILD_B_RESOURCE_NOT_FOUND:
			return "Resource not found";
		case _HAIKU_BUILD_B_RESOURCE_UNAVAILABLE:
			return "Resource unavailable";
		case _HAIKU_BUILD_B_BAD_SUBSCRIBER:
			return "Bad subscriber";
		case _HAIKU_BUILD_B_SUBSCRIBER_NOT_ENTERED:
			return "Subscriber not entered";
		case _HAIKU_BUILD_B_BUFFER_NOT_AVAILABLE:
			return "Buffer not available";
		case _HAIKU_BUILD_B_LAST_BUFFER_ERROR:
			return "Last buffer";
		case _HAIKU_BUILD_B_MEDIA_SYSTEM_FAILURE:
			return "System failure";
		case _HAIKU_BUILD_B_MEDIA_BAD_NODE:
			return "Bad media node";
		case _HAIKU_BUILD_B_MEDIA_NODE_BUSY:
			return "Media node busy";
		case _HAIKU_BUILD_B_MEDIA_BAD_FORMAT:
			return "Bad media format";
		case _HAIKU_BUILD_B_MEDIA_BAD_BUFFER:
			return "Bad buffer";
		case _HAIKU_BUILD_B_MEDIA_TOO_MANY_NODES:
			return "Too many nodes";
		case _HAIKU_BUILD_B_MEDIA_TOO_MANY_BUFFERS:
			return "Too many buffers";
		case _HAIKU_BUILD_B_MEDIA_NODE_ALREADY_EXISTS:
			return "Media node already exists";
		case _HAIKU_BUILD_B_MEDIA_BUFFER_ALREADY_EXISTS:
			return "Buffer already exists";
		case _HAIKU_BUILD_B_MEDIA_CANNOT_SEEK:
			return "Cannot seek";
		case _HAIKU_BUILD_B_MEDIA_CANNOT_CHANGE_RUN_MODE:
			return "Cannot change run mode";
		case _HAIKU_BUILD_B_MEDIA_APP_ALREADY_REGISTERED:
			return "Application already registered";
		case _HAIKU_BUILD_B_MEDIA_APP_NOT_REGISTERED:
			return "Application not registered";
		case _HAIKU_BUILD_B_MEDIA_CANNOT_RECLAIM_BUFFERS:
			return "Cannot reclaim buffers";
		case _HAIKU_BUILD_B_MEDIA_BUFFERS_NOT_RECLAIMED:
			return "Buffers not reclaimed";
		case _HAIKU_BUILD_B_MEDIA_TIME_SOURCE_STOPPED:
			return "Time source stopped";
		case _HAIKU_BUILD_B_MEDIA_TIME_SOURCE_BUSY:
			return "Time source busy";
		case _HAIKU_BUILD_B_MEDIA_BAD_SOURCE:
			return "Bad source";
		case _HAIKU_BUILD_B_MEDIA_BAD_DESTINATION:
			return "Bad destination";
		case _HAIKU_BUILD_B_MEDIA_ALREADY_CONNECTED:
			return "Already connected";
		case _HAIKU_BUILD_B_MEDIA_NOT_CONNECTED:
			return "Not connected";
		case _HAIKU_BUILD_B_MEDIA_BAD_CLIP_FORMAT:
			return "Bad clipping format";
		case _HAIKU_BUILD_B_MEDIA_ADDON_FAILED:
			return "Media addon failed";
		case _HAIKU_BUILD_B_MEDIA_ADDON_DISABLED:
			return "Media addon disabled";
		case _HAIKU_BUILD_B_MEDIA_CHANGE_IN_PROGRESS:
			return "Change in progress";
		case _HAIKU_BUILD_B_MEDIA_STALE_CHANGE_COUNT:
			return "Stale change count";
		case _HAIKU_BUILD_B_MEDIA_ADDON_RESTRICTED:
			return "Media addon restricted";
		case _HAIKU_BUILD_B_MEDIA_NO_HANDLER:
			return "No handler";
		case _HAIKU_BUILD_B_MEDIA_DUPLICATE_FORMAT:
			return "Duplicate format";
		case _HAIKU_BUILD_B_MEDIA_REALTIME_DISABLED:
			return "Realtime disabled";
		case _HAIKU_BUILD_B_MEDIA_REALTIME_UNAVAILABLE:
			return "Realtime unavailable";

		// Mail Kit Errors

		case _HAIKU_BUILD_B_MAIL_NO_DAEMON:
			return "No mail daemon";
		case _HAIKU_BUILD_B_MAIL_UNKNOWN_USER:
			return "Unknown mail user";
		case _HAIKU_BUILD_B_MAIL_WRONG_PASSWORD:
			return "Wrong password (mail)";
		case _HAIKU_BUILD_B_MAIL_UNKNOWN_HOST:
			return "Mail unknown host";
		case _HAIKU_BUILD_B_MAIL_ACCESS_ERROR:
			return "Mail access error";
		case _HAIKU_BUILD_B_MAIL_UNKNOWN_FIELD:
			return "Unknown mail field";
		case _HAIKU_BUILD_B_MAIL_NO_RECIPIENT:
			return "No mail recipient";
		case _HAIKU_BUILD_B_MAIL_INVALID_MAIL:
			return "Invalid mail";

		// Printing Errors

		case _HAIKU_BUILD_B_NO_PRINT_SERVER:
			return "No print server";

		// Device Kit Errors

		case _HAIKU_BUILD_B_DEV_INVALID_IOCTL:
			return "Invalid device ioctl";
		case _HAIKU_BUILD_B_DEV_NO_MEMORY:
			return "No device memory";
		case _HAIKU_BUILD_B_DEV_BAD_DRIVE_NUM:
			return "Bad drive number";
		case _HAIKU_BUILD_B_DEV_NO_MEDIA:
			return "No media present";
		case _HAIKU_BUILD_B_DEV_UNREADABLE:
			return "Device unreadable";
		case _HAIKU_BUILD_B_DEV_FORMAT_ERROR:
			return "Device format error";
		case _HAIKU_BUILD_B_DEV_TIMEOUT:
			return "Device timeout";
		case _HAIKU_BUILD_B_DEV_RECALIBRATE_ERROR:
			return "Device recalibrate error";
		case _HAIKU_BUILD_B_DEV_SEEK_ERROR:
			return "Device seek error";
		case _HAIKU_BUILD_B_DEV_ID_ERROR:
			return "Device ID error";
		case _HAIKU_BUILD_B_DEV_READ_ERROR:
			return "Device read error";
		case _HAIKU_BUILD_B_DEV_WRITE_ERROR:
			return "Device write error";
		case _HAIKU_BUILD_B_DEV_NOT_READY:
			return "Device not ready";
		case _HAIKU_BUILD_B_DEV_MEDIA_CHANGED:
			return "Device media changed";
		case _HAIKU_BUILD_B_DEV_MEDIA_CHANGE_REQUESTED:
			return "Device media change requested";
		case _HAIKU_BUILD_B_DEV_RESOURCE_CONFLICT:
			return "Resource conflict";
		case _HAIKU_BUILD_B_DEV_CONFIGURATION_ERROR:
			return "Configuration error";
		case _HAIKU_BUILD_B_DEV_DISABLED_BY_USER:
			return "Disabled by user";
		case _HAIKU_BUILD_B_DEV_DOOR_OPEN:
			return "Drive door open";

		// the commented out ones are really strange error codes...
		//case _HAIKU_BUILD_B_DEV_INVALID_PIPE:

		case _HAIKU_BUILD_B_DEV_CRC_ERROR:
			return "Device check-sum error";
		case _HAIKU_BUILD_B_DEV_STALLED:
			return "Device stalled";

		//case _HAIKU_BUILD_B_DEV_BAD_PID:
		//case _HAIKU_BUILD_B_DEV_UNEXPECTED_PID:

		case _HAIKU_BUILD_B_DEV_DATA_OVERRUN:
			return "Device data overrun";
		case _HAIKU_BUILD_B_DEV_DATA_UNDERRUN:
			return "Device data underrun";
		case _HAIKU_BUILD_B_DEV_FIFO_OVERRUN:
			return "Device FIFO overrun";
		case _HAIKU_BUILD_B_DEV_FIFO_UNDERRUN:
			return "Device FIFO underrun";
		case _HAIKU_BUILD_B_DEV_PENDING:
			return "Device pending";
		case _HAIKU_BUILD_B_DEV_MULTIPLE_ERRORS:
			return "Multiple device errors";
		case _HAIKU_BUILD_B_DEV_TOO_LATE:
			return "Device too late";

		// Translation Kit Errors

		case _HAIKU_BUILD_B_NO_TRANSLATOR:
			return "No translator found";
		case _HAIKU_BUILD_B_ILLEGAL_DATA:
			return "Illegal data";

		// Other POSIX Errors

		case _HAIKU_BUILD_ENFILE:
			return "File table overflow";
		case _HAIKU_BUILD_ENXIO:
			return "Device not accessible";
		case _HAIKU_BUILD_ESPIPE:
			return "Seek not allowed on file descriptor";
		case _HAIKU_BUILD_ENOSYS:
			return "Function not implemented";
		case _HAIKU_BUILD_EDOM:
			return "Numerical argument out of range";	// "Domain Error"
		case _HAIKU_BUILD_ENOBUFS:
			return "No buffer space available";
		case _HAIKU_BUILD_E2BIG:
			return "Argument too big";
		case _HAIKU_BUILD_ECHILD:
			return "No child process";
		case _HAIKU_BUILD_EDEADLK:
			return "Resource deadlock";
		case _HAIKU_BUILD_EFBIG:
			return "File too large";
		case _HAIKU_BUILD_EMLINK:
			return "Too many links";
		case _HAIKU_BUILD_ENODEV:
			return "No such device";
		case _HAIKU_BUILD_ENOLCK:
			return "No record locks available";
		case _HAIKU_BUILD_ENOTTY:
			return "Not a tty";
		case _HAIKU_BUILD_ESRCH:
			return "No such process";
		case _HAIKU_BUILD_EFPOS:
			return "File Position Error";
		case _HAIKU_BUILD_ESIGPARM:
			return "Signal Error";
		case _HAIKU_BUILD_ERANGE:
			return "Range Error";

		case _HAIKU_BUILD_EPROTOTYPE:
			return "Protocol wrong type for socket";
		case _HAIKU_BUILD_EPROTONOSUPPORT:
			return "Protocol not supported";
		case _HAIKU_BUILD_EPFNOSUPPORT:
			return "Protocol family not supported";
		case _HAIKU_BUILD_EAFNOSUPPORT:
			return "Address family not supported by protocol family";
		case _HAIKU_BUILD_EADDRINUSE:
			return "Address already in use";
		case _HAIKU_BUILD_EADDRNOTAVAIL:
			return "Can't assign requested address";
		case _HAIKU_BUILD_ENETDOWN:
			return "Network is down";
		case _HAIKU_BUILD_ENETUNREACH:
			return "Network is unreachable";
		case _HAIKU_BUILD_ENETRESET:
			return "Network dropped connection on reset";
		case _HAIKU_BUILD_ECONNABORTED:
			return "Software caused connection abort";
		case _HAIKU_BUILD_ECONNRESET:
			return "Connection reset by peer";
		case _HAIKU_BUILD_EISCONN:
			return "Socket is already connected";
		case _HAIKU_BUILD_ENOTCONN:
			return "Socket is not connected";
		case _HAIKU_BUILD_ESHUTDOWN:
			return "Can't send after socket shutdown";
		case _HAIKU_BUILD_ECONNREFUSED:
			return "Connection refused";
		case _HAIKU_BUILD_EHOSTUNREACH:
			return "No route to host";
		case _HAIKU_BUILD_ENOPROTOOPT:
			return "Protocol option not available";
		case _HAIKU_BUILD_EINPROGRESS:
			return "Operation now in progress";
		case _HAIKU_BUILD_EALREADY:
			return "Operation already in progress";
		case _HAIKU_BUILD_EILSEQ:
			return "Illegal byte sequence";
		case _HAIKU_BUILD_ENOMSG:
			return "No message of desired type";
		case _HAIKU_BUILD_ESTALE:
			return "Stale file handle";

		case _HAIKU_BUILD_EOVERFLOW:
			return "Value too large for defined type";
		case _HAIKU_BUILD_EMSGSIZE:
			return "Message too long";
		case _HAIKU_BUILD_EOPNOTSUPP:
			return "Operation not supported";
		case _HAIKU_BUILD_ENOTSOCK:
			return "Socket operation on non-socket";
		case _HAIKU_BUILD_EBADMSG:
			return "Bad message";
		case _HAIKU_BUILD_ECANCELED:
			return "Operation canceled";
		case _HAIKU_BUILD_EDESTADDRREQ:
			return "Destination address required";
		case _HAIKU_BUILD_EDQUOT:
			return "Reserved";
		case _HAIKU_BUILD_EIDRM:
			return "Identifier removed";
		case _HAIKU_BUILD_EMULTIHOP:
			return "Reserved";
		case _HAIKU_BUILD_ENODATA:
			return "No message available";
		case _HAIKU_BUILD_ENOLINK:
			return "Reserved";
		case _HAIKU_BUILD_ENOSR:
			return "No STREAM resources";
		case _HAIKU_BUILD_ENOSTR:
			return "Not a STREAM";
		case _HAIKU_BUILD_ENOTSUP:
			return "Not supported";
		case _HAIKU_BUILD_EPROTO:
			return "Protocol error";
		case _HAIKU_BUILD_ETIME:
			return "STREAM ioctl() timeout";
		case _HAIKU_BUILD_ETXTBSY:
			return "Text file busy";
		case _HAIKU_BUILD_ENOATTR:
			return "No such attribute";

		default:
			return NULL;
	}
}


// _haiku_build_strerror
char *
_haiku_build_strerror(int errnum)
{
	static char unknown[48];
	_haiku_build_uint32 i;

	char *description = _haiku_build_error_description(error);
	if (description != NULL)
		return description;

	if (error < _HAIKU_BUILD_B_OK) {
		const char *system = "";
		for (i = 0; i < kNumErrorBases; i++) {
			if (kErrorBases[i].base <= error
				&& ((i + 1 < kNumErrorBases && kErrorBases[i + 1].base > error)
					|| i + 1 == kNumErrorBases)) {
				system = kErrorBases[i].name;
				break;
			}
		}
		sprintf(unknown, "Unknown %sError (%d)", system, error);
	} else
		sprintf(unknown, "No Error (%d)", error);

	return unknown;
}

// _haiku_build_errno
int *
_haiku_build_errno()
{
	/* TODO: #8730 -- _haiku_build_errno() can simply return the pointer to a
		static int variable (let's call it sErrno). See ticket/8730#comment:15
	*/
	static int previousErrno = 0;
	static int localErrno = 0;
	static int previousLocalErrno = 0;

	// If the localErrno has been changed and the real errno has not changed
	// in the meantime, we update errno itself, so that the local update will
	// be reflected. If errno has changed we always update localErrno.
	int currentErrno = errno;
	if (currentErrno == previousErrno) {
		if (localErrno != previousLocalErrno) {
			errno = previousErrno = to_host_error(localErrno);
			previousLocalErrno = localErrno;
		}
	} else {
		previousErrno = currentErrno;
		previousLocalErrno = localErrno = to_haiku_error(errno);
	}

	return &localErrno;
}

// _haiku_to_host_error
int
_haiku_to_host_error(int error)
{
	return to_host_error(error);
}
