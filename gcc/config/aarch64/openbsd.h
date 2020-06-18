/* Definitions of target machine for GNU compiler, OpenBSD/aarch64 ELF version.
   Copyright (C) 2002 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Run-time Target Specification.  */
//#undef TARGET_VERSION
//#define TARGET_VERSION fputs (" (OpenBSD/arm)", stderr);

/* This is used in ASM_FILE_START.  */
//#undef ARM_OS_NAME
//#define ARM_OS_NAME "OpenBSD"

/* This defaults us to little-endian.  */
#ifndef TARGET_ENDIAN_DEFAULT
#define TARGET_ENDIAN_DEFAULT 0
#endif

#undef MULTILIB_DEFAULTS

#define TARGET_OS_CPP_BUILTINS()	\
  do					\
    {					\
      builtin_define ("__GXX_MERGED_TYPEINFO_NAMES=0"); \
      OPENBSD_OS_CPP_BUILTINS_ELF();	\
    }					\
  while (0)

#undef SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC OBSD_CPP_SPEC

#define LINK_SPEC \
  "%{!shared:%{!nostdlib:%{!r*:%{!e*:-e __start}}}} \
   %{shared:-shared} %{R*} \
   %{static:-Bstatic} \
   %{!static:-Bdynamic} \
   %{rdynamic:-export-dynamic} \
   %{assert*} \
   %{!shared:%{!dynamic-linker:-dynamic-linker /usr/libexec/ld.so}} \
   -L/usr/lib"

#define OPENBSD_ENTRY_POINT "__start"

/* Make GCC agree with <machine/_types.h>.  */

#undef SIZE_TYPE
#define SIZE_TYPE "long unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "long int"

#undef INTMAX_TYPE
#define INTMAX_TYPE "long long int"

#undef UINTMAX_TYPE
#define UINTMAX_TYPE "long long unsigned int"

#undef WCHAR_TYPE
#define WCHAR_TYPE "int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

/* Provide a STARTFILE_SPEC appropriate for OpenBSD ELF.  Here we
   provide support for the special GCC option -static.  On ELF
   targets, we also add the crtbegin.o file, which provides part
   of the support for getting C++ file-scope static objects
   constructed before entering "main".  */

#define OPENBSD_STARTFILE_SPEC	\
  "%{!shared:			\
     %{pg:gcrt0%O%s}		\
     %{!pg:			\
       %{p:gcrt0%O%s}		\
       %{!p:%{!static:crt0%O%s} %{static:%{nopie:crt0%O%s} \
        %{!nopie:rcrt0%O%s}}}}} \
   %:if-exists(crti%O%s)	\
   %{static:%:if-exists-else(crtbeginT%O%s crtbegin%O%s)} \
   %{!static: \
     %{!shared:crtbegin%O%s} %{shared:crtbeginS%O%s}}"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC OPENBSD_STARTFILE_SPEC

/* Provide an ENDFILE_SPEC appropriate for OpenBSD ELF.  Here we
add crtend.o, which provides part of the support for getting
C++ file-scope static objects deconstructed after exiting "main".  */

#define OPENBSD_ENDFILE_SPEC     \
  "%{!shared:crtend%O%s} %{shared:crtendS%O%s} \
   %:if-exists(crtn%O%s)"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC OPENBSD_ENDFILE_SPEC

/* Remove -mcpu=native handling which is Linux specific */
#undef DRIVER_SELF_SPECS
#define DRIVER_SELF_SPECS ""

/* dito */
#undef EXTRA_SPEC_FUNCTIONS
