
#include <errno.h>

#include "strings.h"

#include "error.h"


char * errors_get_errno_name(int err)
{
  switch (err)
  {

#ifdef EPERM
    case EPERM:
      return "EPERM";
#endif
#ifdef ENOENT
    case ENOENT:
      return "ENOENT";
#endif
#ifdef ESRCH
    case ESRCH:
      return "ESRCH";
#endif
#ifdef EINTR
    case EINTR:
      return "EINTR";
#endif
#ifdef EIO
    case EIO:
      return "EIO";
#endif
#ifdef ENXIO
    case ENXIO:
      return "ENXIO";
#endif
#ifdef E2BIG
    case E2BIG:
      return "E2BIG";
#endif
#ifdef ENOEXEC
    case ENOEXEC:
      return "ENOEXEC";
#endif
#ifdef EBADF
    case EBADF:
      return "EBADF";
#endif
#ifdef ECHILD
    case ECHILD:
      return "ECHILD";
#endif
#ifdef EAGAIN
    case EAGAIN:
      return "EAGAIN";
#endif
#ifdef ENOMEM
    case ENOMEM:
      return "ENOMEM";
#endif
#ifdef EACCES
    case EACCES:
      return "EACCES";
#endif
#ifdef EFAULT
    case EFAULT:
      return "EFAULT";
#endif
#ifdef ENOTBLK
    case ENOTBLK:
      return "ENOTBLK";
#endif
#ifdef EBUSY
    case EBUSY:
      return "EBUSY";
#endif
#ifdef EEXIST
    case EEXIST:
      return "EEXIST";
#endif
#ifdef EXDEV
    case EXDEV:
      return "EXDEV";
#endif
#ifdef ENODEV
    case ENODEV:
      return "ENODEV";
#endif
#ifdef ENOTDIR
    case ENOTDIR:
      return "ENOTDIR";
#endif
#ifdef EISDIR
    case EISDIR:
      return "EISDIR";
#endif
#ifdef EINVAL
    case EINVAL:
      return "EINVAL";
#endif
#ifdef ENFILE
    case ENFILE:
      return "ENFILE";
#endif
#ifdef EMFILE
    case EMFILE:
      return "EMFILE";
#endif
#ifdef ENOTTY
    case ENOTTY:
      return "ENOTTY";
#endif
#ifdef ETXTBSY
    case ETXTBSY:
      return "ETXTBSY";
#endif
#ifdef EFBIG
    case EFBIG:
      return "EFBIG";
#endif
#ifdef ENOSPC
    case ENOSPC:
      return "ENOSPC";
#endif
#ifdef ESPIPE
    case ESPIPE:
      return "ESPIPE";
#endif
#ifdef EROFS
    case EROFS:
      return "EROFS";
#endif
#ifdef EMLINK
    case EMLINK:
      return "EMLINK";
#endif
#ifdef EPIPE
    case EPIPE:
      return "EPIPE";
#endif
#ifdef EDOM
    case EDOM:
      return "EDOM";
#endif
#ifdef ERANGE
    case ERANGE:
      return "ERANGE";
#endif
#ifdef ENOTSUP
    case ENOTSUP:
      return "ENOTSUP";
#endif
#ifdef EOWNERDEAD
    case EOWNERDEAD:
      return "EOWNERDEAD";
#endif
#ifdef EHWPOISON
    case EHWPOISON:
      return "EHWPOISON";
#endif
#ifdef EDEADLK
    case EDEADLK:
      return "EDEADLK";
#endif
#ifdef ENAMETOOLONG
    case ENAMETOOLONG:
      return "ENAMETOOLONG";
#endif
#ifdef ENOLCK
    case ENOLCK:
      return "ENOLCK";
#endif
#ifdef ENOSYS
    case ENOSYS:
      return "ENOSYS";
#endif
#ifdef ENOTEMPTY
    case ENOTEMPTY:
      return "ENOTEMPTY";
#endif
#ifdef ELOOP
    case ELOOP:
      return "ELOOP";
#endif
#ifdef ENOMSG
    case ENOMSG:
      return "ENOMSG";
#endif
#ifdef EIDRM
    case EIDRM:
      return "EIDRM";
#endif
#ifdef ECHRNG
    case ECHRNG:
      return "ECHRNG";
#endif
#ifdef EL2NSYNC
    case EL2NSYNC:
      return "EL2NSYNC";
#endif
#ifdef EL3HLT
    case EL3HLT:
      return "EL3HLT";
#endif
#ifdef EL3RST
    case EL3RST:
      return "EL3RST";
#endif
#ifdef ELNRNG
    case ELNRNG:
      return "ELNRNG";
#endif
#ifdef EUNATCH
    case EUNATCH:
      return "EUNATCH";
#endif
#ifdef ENOCSI
    case ENOCSI:
      return "ENOCSI";
#endif
#ifdef EL2HLT
    case EL2HLT:
      return "EL2HLT";
#endif
#ifdef EBADE
    case EBADE:
      return "EBADE";
#endif
#ifdef EBADR
    case EBADR:
      return "EBADR";
#endif
#ifdef EXFULL
    case EXFULL:
      return "EXFULL";
#endif
#ifdef ENOANO
    case ENOANO:
      return "ENOANO";
#endif
#ifdef EBADRQC
    case EBADRQC:
      return "EBADRQC";
#endif
#ifdef EBADSLT
    case EBADSLT:
      return "EBADSLT";
#endif
#ifdef EBFONT
    case EBFONT:
      return "EBFONT";
#endif
#ifdef ENOSTR
    case ENOSTR:
      return "ENOSTR";
#endif
#ifdef ENODATA
    case ENODATA:
      return "ENODATA";
#endif
#ifdef ETIME
    case ETIME:
      return "ETIME";
#endif
#ifdef ENOSR
    case ENOSR:
      return "ENOSR";
#endif
#ifdef ENONET
    case ENONET:
      return "ENONET";
#endif
#ifdef ENOPKG
    case ENOPKG:
      return "ENOPKG";
#endif
#ifdef ENREMOTE
    case ENREMOTE:
      return "ENREMOTE";
#endif
#ifdef ENOLINK
    case ENOLINK:
      return "ENOLINK";
#endif
#ifdef EADV
    case EADV:
      return "EADV";
#endif
#ifdef ESRMNT
    case ESRMNT:
      return "ESRMNT";
#endif
#ifdef ECOMM
    case ECOMM:
      return "ECOMM";
#endif
#ifdef EPROTO
    case EPROTO:
      return "EPROTO";
#endif
#ifdef EMULTIHOP
    case EMULTIHOP:
      return "EMULTIHOP";
#endif
#ifdef EDOTDOT
    case EDOTDOT:
      return "EDOTDOT";
#endif
#ifdef EBADMSG
    case EBADMSG:
      return "EBADMSG";
#endif
#ifdef EOVERFLOW
    case EOVERFLOW:
      return "EOVERFLOW";
#endif
#ifdef ENOTUNIQ
    case ENOTUNIQ:
      return "ENOTUNIQ";
#endif
#ifdef EBADFD
    case EBADFD:
      return "EBADFD";
#endif
#ifdef EREMCHG
    case EREMCHG:
      return "EREMCHG";
#endif
#ifdef ELIBACC
    case ELIBACC:
      return "ELIBACC";
#endif
#ifdef ELIBBAD
    case ELIBBAD:
      return "ELIBBAD";
#endif
#ifdef ELIBSCN
    case ELIBSCN:
      return "ELIBSCN";
#endif
#ifdef ELIBMAX
    case ELIBMAX:
      return "ELIBMAX";
#endif
#ifdef ELIBEXEC
    case ELIBEXEC:
      return "ELIBEXEC";
#endif
#ifdef EILSEQ
    case EILSEQ:
      return "EILSEQ";
#endif
#ifdef ERESTART
    case ERESTART:
      return "ERESTART";
#endif
#ifdef ESTRPIPE
    case ESTRPIPE:
      return "ESTRPIPE";
#endif
#ifdef EUSERS
    case EUSERS:
      return "EUSERS";
#endif
#ifdef ENOTSOCK
    case ENOTSOCK:
      return "ENOTSOCK";
#endif
#ifdef EDESTADDRREQ
    case EDESTADDRREQ:
      return "EDESTADDRREQ";
#endif
#ifdef EMSGSIZE
    case EMSGSIZE:
      return "EMSGSIZE";
#endif
#ifdef EPROTOTYPE
    case EPROTOTYPE:
      return "EPROTOTYPE";
#endif
#ifdef ENOPROTOOPT
    case ENOPROTOOPT:
      return "ENOPROTOOPT";
#endif
#ifdef EPROTONOSUPPORT
    case EPROTONOSUPPORT:
      return "EPROTONOSUPPORT";
#endif
#ifdef ESOCKNOSUPPORT
    case ESOCKNOSUPPORT:
      return "ESOCKNOSUPPORT";
#endif
#ifdef EPFNOSUPPORT
    case EPFNOSUPPORT:
      return "EPFNOSUPPORT";
#endif
#ifdef EAFNOSUPPORT
    case EAFNOSUPPORT:
      return "EAFNOSUPPORT";
#endif
#ifdef EADDRINUSE
    case EADDRINUSE:
      return "EADDRINUSE";
#endif
#ifdef EADDRNOTAVAIL
    case EADDRNOTAVAIL:
      return "EADDRNOTAVAIL";
#endif
#ifdef ENETDOWN
    case ENETDOWN:
      return "ENETDOWN";
#endif
#ifdef ENETUNREACH
    case ENETUNREACH:
      return "ENETUNREACH";
#endif
#ifdef ENETRESET
    case ENETRESET:
      return "ENETRESET";
#endif
#ifdef ECONNABORTED
    case ECONNABORTED:
      return "ECONNABORTED";
#endif
#ifdef ECONNRESET
    case ECONNRESET:
      return "ECONNRESET";
#endif
#ifdef ENOBUFS
    case ENOBUFS:
      return "ENOBUFS";
#endif
#ifdef EISDCONN
    case EISDCONN:
      return "EISDCONN";
#endif
#ifdef ENOTCONN
    case ENOTCONN:
      return "ENOTCONN";
#endif
#ifdef ESUTDOWN
    case ESUTDOWN:
      return "ESUTDOWN";
#endif
#ifdef ETOOMANYREFS
    case ETOOMANYREFS:
      return "ETOOMANYREFS";
#endif
#ifdef ETIMEDOUT
    case ETIMEDOUT:
      return "ETIMEDOUT";
#endif
#ifdef ECONNREFUSED
    case ECONNREFUSED:
      return "ECONNREFUSED";
#endif
#ifdef EHOSTDOWN
    case EHOSTDOWN:
      return "EHOSTDOWN";
#endif
#ifdef EHOSTUNREACH
    case EHOSTUNREACH:
      return "EHOSTUNREACH";
#endif
#ifdef EALREADY
    case EALREADY:
      return "EALREADY";
#endif
#ifdef EINPROGRESS
    case EINPROGRESS:
      return "EINPROGRESS";
#endif
#ifdef ESTALE
    case ESTALE:
      return "ESTALE";
#endif
#ifdef EUCLEAN
    case EUCLEAN:
      return "EUCLEAN";
#endif
#ifdef ENOTNAM
    case ENOTNAM:
      return "ENOTNAM";
#endif
#ifdef ENAVAIL
    case ENAVAIL:
      return "ENAVAIL";
#endif
#ifdef EISNAM
    case EISNAM:
      return "EISNAM";
#endif
#ifdef EREMOTEIO
    case EREMOTEIO:
      return "EREMOTEIO";
#endif
#ifdef EDQUOT
    case EDQUOT:
      return "EDQUOT";
#endif
#ifdef ENOMEDIUM
    case ENOMEDIUM:
      return "ENOMEDIUM";
#endif
#ifdef EMEDIUMTYPE
    case EMEDIUMTYPE:
      return "EMEDIUMTYPE";
#endif
#ifdef ECANCELED
    case ECANCELED:
      return "ECANCELED";
#endif
#ifdef ENOKEY
    case ENOKEY:
      return "ENOKEY";
#endif
#ifdef EKEYEXPIRED
    case EKEYEXPIRED:
      return "EKEYEXPIRED";
#endif
#ifdef EKEYREVOKED
    case EKEYREVOKED:
      return "EKEYREVOKED";
#endif
#ifdef EKEYREJECTED
    case EKEYREJECTED:
      return "EKEYREJECTED";
#endif
#ifdef ENOTRECOVERABLE
    case ENOTRECOVERABLE:
      return "ENOTRECOVERABLE";
#endif
#ifdef ERFKILL
    case ERFKILL:
      return "ERFKILL";
#endif
#ifdef EHWPOSION
    case EHWPOSION:
      return "EHWPOSION";
#endif
    default:
      return "UNKNOWN";

  }
}


int errors_get_errno_integer(char * name)
{
  if (!name)
    return -1;
#ifdef EPERM
  else if (strings_equals_ignore_case(name, "EPERM"))
    return EPERM;
#endif
#ifdef ENOENT
  else if (strings_equals_ignore_case(name, "ENOENT"))
    return ENOENT;
#endif
#ifdef ESRCH
  else if (strings_equals_ignore_case(name, "ESRCH"))
    return ESRCH;
#endif
#ifdef EINTR
  else if (strings_equals_ignore_case(name, "EINTR"))
    return EINTR;
#endif
#ifdef EIO
  else if (strings_equals_ignore_case(name, "EIO"))
    return EIO;
#endif
#ifdef ENXIO
  else if (strings_equals_ignore_case(name, "ENXIO"))
    return ENXIO;
#endif
#ifdef E2BIG
  else if (strings_equals_ignore_case(name, "E2BIG"))
    return E2BIG;
#endif
#ifdef ENOEXEC
  else if (strings_equals_ignore_case(name, "ENOEXEC"))
    return ENOEXEC;
#endif
#ifdef EBADF
  else if (strings_equals_ignore_case(name, "EBADF"))
    return EBADF;
#endif
#ifdef ECHILD
  else if (strings_equals_ignore_case(name, "ECHILD"))
    return ECHILD;
#endif
#ifdef EAGAIN
  else if (strings_equals_ignore_case(name, "EAGAIN"))
    return EAGAIN;
#endif
#ifdef ENOMEM
  else if (strings_equals_ignore_case(name, "ENOMEM"))
    return ENOMEM;
#endif
#ifdef EACCES
  else if (strings_equals_ignore_case(name, "EACCES"))
    return EACCES;
#endif
#ifdef EFAULT
  else if (strings_equals_ignore_case(name, "EFAULT"))
    return EFAULT;
#endif
#ifdef ENOTBLK
  else if (strings_equals_ignore_case(name, "ENOTBLK"))
    return ENOTBLK;
#endif
#ifdef EBUSY
  else if (strings_equals_ignore_case(name, "EBUSY"))
    return EBUSY;
#endif
#ifdef EEXIST
  else if (strings_equals_ignore_case(name, "EEXIST"))
    return EEXIST;
#endif
#ifdef EXDEV
  else if (strings_equals_ignore_case(name, "EXDEV"))
    return EXDEV;
#endif
#ifdef ENODEV
  else if (strings_equals_ignore_case(name, "ENODEV"))
    return ENODEV;
#endif
#ifdef ENOTDIR
  else if (strings_equals_ignore_case(name, "ENOTDIR"))
    return ENOTDIR;
#endif
#ifdef EISDIR
  else if (strings_equals_ignore_case(name, "EISDIR"))
    return EISDIR;
#endif
#ifdef EINVAL
  else if (strings_equals_ignore_case(name, "EINVAL"))
    return EINVAL;
#endif
#ifdef ENFILE
  else if (strings_equals_ignore_case(name, "ENFILE"))
    return ENFILE;
#endif
#ifdef EMFILE
  else if (strings_equals_ignore_case(name, "EMFILE"))
    return EMFILE;
#endif
#ifdef ENOTTY
  else if (strings_equals_ignore_case(name, "ENOTTY"))
    return ENOTTY;
#endif
#ifdef ETXTBSY
  else if (strings_equals_ignore_case(name, "ETXTBSY"))
    return ETXTBSY;
#endif
#ifdef EFBIG
  else if (strings_equals_ignore_case(name, "EFBIG"))
    return EFBIG;
#endif
#ifdef ENOSPC
  else if (strings_equals_ignore_case(name, "ENOSPC"))
    return ENOSPC;
#endif
#ifdef ESPIPE
  else if (strings_equals_ignore_case(name, "ESPIPE"))
    return ESPIPE;
#endif
#ifdef EROFS
  else if (strings_equals_ignore_case(name, "EROFS"))
    return EROFS;
#endif
#ifdef EMLINK
  else if (strings_equals_ignore_case(name, "EMLINK"))
    return EMLINK;
#endif
#ifdef EPIPE
  else if (strings_equals_ignore_case(name, "EPIPE"))
    return EPIPE;
#endif
#ifdef EDOM
  else if (strings_equals_ignore_case(name, "EDOM"))
    return EDOM;
#endif
#ifdef ERANGE
  else if (strings_equals_ignore_case(name, "ERANGE"))
    return ERANGE;
#endif
#ifdef ENOTSUP
  else if (strings_equals_ignore_case(name, "ENOTSUP"))
    return ENOTSUP;
#endif
#ifdef EOWNERDEAD
  else if (strings_equals_ignore_case(name, "EOWNERDEAD"))
    return EOWNERDEAD;
#endif
#ifdef EHWPOISON
  else if (strings_equals_ignore_case(name, "EHWPOISON"))
    return EHWPOISON;
#endif
#ifdef EDEADLK
  else if (strings_equals_ignore_case(name, "EDEADLK"))
    return EDEADLK;
#endif
#ifdef ENAMETOOLONG
  else if (strings_equals_ignore_case(name, "ENAMETOOLONG"))
    return ENAMETOOLONG;
#endif
#ifdef ENOLCK
  else if (strings_equals_ignore_case(name, "ENOLCK"))
    return ENOLCK;
#endif
#ifdef ENOSYS
  else if (strings_equals_ignore_case(name, "ENOSYS"))
    return ENOSYS;
#endif
#ifdef ENOTEMPTY
  else if (strings_equals_ignore_case(name, "ENOTEMPTY"))
    return ENOTEMPTY;
#endif
#ifdef ELOOP
  else if (strings_equals_ignore_case(name, "ELOOP"))
    return ELOOP;
#endif
#ifdef ENOMSG
  else if (strings_equals_ignore_case(name, "ENOMSG"))
    return ENOMSG;
#endif
#ifdef EIDRM
  else if (strings_equals_ignore_case(name, "EIDRM"))
    return EIDRM;
#endif
#ifdef ECHRNG
  else if (strings_equals_ignore_case(name, "ECHRNG"))
    return ECHRNG;
#endif
#ifdef EL2NSYNC
  else if (strings_equals_ignore_case(name, "EL2NSYNC"))
    return EL2NSYNC;
#endif
#ifdef EL3HLT
  else if (strings_equals_ignore_case(name, "EL3HLT"))
    return EL3HLT;
#endif
#ifdef EL3RST
  else if (strings_equals_ignore_case(name, "EL3RST"))
    return EL3RST;
#endif
#ifdef ELNRNG
  else if (strings_equals_ignore_case(name, "ELNRNG"))
    return ELNRNG;
#endif
#ifdef EUNATCH
  else if (strings_equals_ignore_case(name, "EUNATCH"))
    return EUNATCH;
#endif
#ifdef ENOCSI
  else if (strings_equals_ignore_case(name, "ENOCSI"))
    return ENOCSI;
#endif
#ifdef EL2HLT
  else if (strings_equals_ignore_case(name, "EL2HLT"))
    return EL2HLT;
#endif
#ifdef EBADE
  else if (strings_equals_ignore_case(name, "EBADE"))
    return EBADE;
#endif
#ifdef EBADR
  else if (strings_equals_ignore_case(name, "EBADR"))
    return EBADR;
#endif
#ifdef EXFULL
  else if (strings_equals_ignore_case(name, "EXFULL"))
    return EXFULL;
#endif
#ifdef ENOANO
  else if (strings_equals_ignore_case(name, "ENOANO"))
    return ENOANO;
#endif
#ifdef EBADRQC
  else if (strings_equals_ignore_case(name, "EBADRQC"))
    return EBADRQC;
#endif
#ifdef EBADSLT
  else if (strings_equals_ignore_case(name, "EBADSLT"))
    return EBADSLT;
#endif
#ifdef EBFONT
  else if (strings_equals_ignore_case(name, "EBFONT"))
    return EBFONT;
#endif
#ifdef ENOSTR
  else if (strings_equals_ignore_case(name, "ENOSTR"))
    return ENOSTR;
#endif
#ifdef ENODATA
  else if (strings_equals_ignore_case(name, "ENODATA"))
    return ENODATA;
#endif
#ifdef ETIME
  else if (strings_equals_ignore_case(name, "ETIME"))
    return ETIME;
#endif
#ifdef ENOSR
  else if (strings_equals_ignore_case(name, "ENOSR"))
    return ENOSR;
#endif
#ifdef ENONET
  else if (strings_equals_ignore_case(name, "ENONET"))
    return ENONET;
#endif
#ifdef ENOPKG
  else if (strings_equals_ignore_case(name, "ENOPKG"))
    return ENOPKG;
#endif
#ifdef ENREMOTE
  else if (strings_equals_ignore_case(name, "ENREMOTE"))
    return ENREMOTE;
#endif
#ifdef ENOLINK
  else if (strings_equals_ignore_case(name, "ENOLINK"))
    return ENOLINK;
#endif
#ifdef EADV
  else if (strings_equals_ignore_case(name, "EADV"))
    return EADV;
#endif
#ifdef ESRMNT
  else if (strings_equals_ignore_case(name, "ESRMNT"))
    return ESRMNT;
#endif
#ifdef ECOMM
  else if (strings_equals_ignore_case(name, "ECOMM"))
    return ECOMM;
#endif
#ifdef EPROTO
  else if (strings_equals_ignore_case(name, "EPROTO"))
    return EPROTO;
#endif
#ifdef EMULTIHOP
  else if (strings_equals_ignore_case(name, "EMULTIHOP"))
    return EMULTIHOP;
#endif
#ifdef EDOTDOT
  else if (strings_equals_ignore_case(name, "EDOTDOT"))
    return EDOTDOT;
#endif
#ifdef EBADMSG
  else if (strings_equals_ignore_case(name, "EBADMSG"))
    return EBADMSG;
#endif
#ifdef EOVERFLOW
  else if (strings_equals_ignore_case(name, "EOVERFLOW"))
    return EOVERFLOW;
#endif
#ifdef ENOTUNIQ
  else if (strings_equals_ignore_case(name, "ENOTUNIQ"))
    return ENOTUNIQ;
#endif
#ifdef EBADFD
  else if (strings_equals_ignore_case(name, "EBADFD"))
    return EBADFD;
#endif
#ifdef EREMCHG
  else if (strings_equals_ignore_case(name, "EREMCHG"))
    return EREMCHG;
#endif
#ifdef ELIBACC
  else if (strings_equals_ignore_case(name, "ELIBACC"))
    return ELIBACC;
#endif
#ifdef ELIBBAD
  else if (strings_equals_ignore_case(name, "ELIBBAD"))
    return ELIBBAD;
#endif
#ifdef ELIBSCN
  else if (strings_equals_ignore_case(name, "ELIBSCN"))
    return ELIBSCN;
#endif
#ifdef ELIBMAX
  else if (strings_equals_ignore_case(name, "ELIBMAX"))
    return ELIBMAX;
#endif
#ifdef ELIBEXEC
  else if (strings_equals_ignore_case(name, "ELIBEXEC"))
    return ELIBEXEC;
#endif
#ifdef EILSEQ
  else if (strings_equals_ignore_case(name, "EILSEQ"))
    return EILSEQ;
#endif
#ifdef ERESTART
  else if (strings_equals_ignore_case(name, "ERESTART"))
    return ERESTART;
#endif
#ifdef ESTRPIPE
  else if (strings_equals_ignore_case(name, "ESTRPIPE"))
    return ESTRPIPE;
#endif
#ifdef EUSERS
  else if (strings_equals_ignore_case(name, "EUSERS"))
    return EUSERS;
#endif
#ifdef ENOTSOCK
  else if (strings_equals_ignore_case(name, "ENOTSOCK"))
    return ENOTSOCK;
#endif
#ifdef EDESTADDRREQ
  else if (strings_equals_ignore_case(name, "EDESTADDRREQ"))
    return EDESTADDRREQ;
#endif
#ifdef EMSGSIZE
  else if (strings_equals_ignore_case(name, "EMSGSIZE"))
    return EMSGSIZE;
#endif
#ifdef EPROTOTYPE
  else if (strings_equals_ignore_case(name, "EPROTOTYPE"))
    return EPROTOTYPE;
#endif
#ifdef ENOPROTOOPT
  else if (strings_equals_ignore_case(name, "ENOPROTOOPT"))
    return ENOPROTOOPT;
#endif
#ifdef EPROTONOSUPPORT
  else if (strings_equals_ignore_case(name, "EPROTONOSUPPORT"))
    return EPROTONOSUPPORT;
#endif
#ifdef ESOCKNOSUPPORT
  else if (strings_equals_ignore_case(name, "ESOCKNOSUPPORT"))
    return ESOCKNOSUPPORT;
#endif
#ifdef EPFNOSUPPORT
  else if (strings_equals_ignore_case(name, "EPFNOSUPPORT"))
    return EPFNOSUPPORT;
#endif
#ifdef EAFNOSUPPORT
  else if (strings_equals_ignore_case(name, "EAFNOSUPPORT"))
    return EAFNOSUPPORT;
#endif
#ifdef EADDRINUSE
  else if (strings_equals_ignore_case(name, "EADDRINUSE"))
    return EADDRINUSE;
#endif
#ifdef EADDRNOTAVAIL
  else if (strings_equals_ignore_case(name, "EADDRNOTAVAIL"))
    return EADDRNOTAVAIL;
#endif
#ifdef ENETDOWN
  else if (strings_equals_ignore_case(name, "ENETDOWN"))
    return ENETDOWN;
#endif
#ifdef ENETUNREACH
  else if (strings_equals_ignore_case(name, "ENETUNREACH"))
    return ENETUNREACH;
#endif
#ifdef ENETRESET
  else if (strings_equals_ignore_case(name, "ENETRESET"))
    return ENETRESET;
#endif
#ifdef ECONNABORTED
  else if (strings_equals_ignore_case(name, "ECONNABORTED"))
    return ECONNABORTED;
#endif
#ifdef ECONNRESET
  else if (strings_equals_ignore_case(name, "ECONNRESET"))
    return ECONNRESET;
#endif
#ifdef ENOBUFS
  else if (strings_equals_ignore_case(name, "ENOBUFS"))
    return ENOBUFS;
#endif
#ifdef EISDCONN
  else if (strings_equals_ignore_case(name, "EISDCONN"))
    return EISDCONN;
#endif
#ifdef ENOTCONN
  else if (strings_equals_ignore_case(name, "ENOTCONN"))
    return ENOTCONN;
#endif
#ifdef ESUTDOWN
  else if (strings_equals_ignore_case(name, "ESUTDOWN"))
    return ESUTDOWN;
#endif
#ifdef ETOOMANYREFS
  else if (strings_equals_ignore_case(name, "ETOOMANYREFS"))
    return ETOOMANYREFS;
#endif
#ifdef ETIMEDOUT
  else if (strings_equals_ignore_case(name, "ETIMEDOUT"))
    return ETIMEDOUT;
#endif
#ifdef ECONNREFUSED
  else if (strings_equals_ignore_case(name, "ECONNREFUSED"))
    return ECONNREFUSED;
#endif
#ifdef EHOSTDOWN
  else if (strings_equals_ignore_case(name, "EHOSTDOWN"))
    return EHOSTDOWN;
#endif
#ifdef EHOSTUNREACH
  else if (strings_equals_ignore_case(name, "EHOSTUNREACH"))
    return EHOSTUNREACH;
#endif
#ifdef EALREADY
  else if (strings_equals_ignore_case(name, "EALREADY"))
    return EALREADY;
#endif
#ifdef EINPROGRESS
  else if (strings_equals_ignore_case(name, "EINPROGRESS"))
    return EINPROGRESS;
#endif
#ifdef ESTALE
  else if (strings_equals_ignore_case(name, "ESTALE"))
    return ESTALE;
#endif
#ifdef EUCLEAN
  else if (strings_equals_ignore_case(name, "EUCLEAN"))
    return EUCLEAN;
#endif
#ifdef ENOTNAM
  else if (strings_equals_ignore_case(name, "ENOTNAM"))
    return ENOTNAM;
#endif
#ifdef ENAVAIL
  else if (strings_equals_ignore_case(name, "ENAVAIL"))
    return ENAVAIL;
#endif
#ifdef EISNAM
  else if (strings_equals_ignore_case(name, "EISNAM"))
    return EISNAM;
#endif
#ifdef EREMOTEIO
  else if (strings_equals_ignore_case(name, "EREMOTEIO"))
    return EREMOTEIO;
#endif
#ifdef EDQUOT
  else if (strings_equals_ignore_case(name, "EDQUOT"))
    return EDQUOT;
#endif
#ifdef ENOMEDIUM
  else if (strings_equals_ignore_case(name, "ENOMEDIUM"))
    return ENOMEDIUM;
#endif
#ifdef EMEDIUMTYPE
  else if (strings_equals_ignore_case(name, "EMEDIUMTYPE"))
    return EMEDIUMTYPE;
#endif
#ifdef ECANCELED
  else if (strings_equals_ignore_case(name, "ECANCELED"))
    return ECANCELED;
#endif
#ifdef ENOKEY
  else if (strings_equals_ignore_case(name, "ENOKEY"))
    return ENOKEY;
#endif
#ifdef EKEYEXPIRED
  else if (strings_equals_ignore_case(name, "EKEYEXPIRED"))
    return EKEYEXPIRED;
#endif
#ifdef EKEYREVOKED
  else if (strings_equals_ignore_case(name, "EKEYREVOKED"))
    return EKEYREVOKED;
#endif
#ifdef EKEYREJECTED
  else if (strings_equals_ignore_case(name, "EKEYREJECTED"))
    return EKEYREJECTED;
#endif
#ifdef ENOTRECOVERABLE
  else if (strings_equals_ignore_case(name, "ENOTRECOVERABLE"))
    return ENOTRECOVERABLE;
#endif
#ifdef ERFKILL
  else if (strings_equals_ignore_case(name, "ERFKILL"))
    return ERFKILL;
#endif
#ifdef EHWPOSION
  else if (strings_equals_ignore_case(name, "EHWPOSION"))
    return EHWPOSION;
#endif
  else
    return -1;

}
