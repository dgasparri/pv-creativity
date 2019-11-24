

#define FLTK_DATADIR "C:/Program Files (x86)/FLTK/share/fltk"
#define FLTK_DOCDIR "C:/Program Files (x86)/FLTK/share/doc/fltk"


#define BORDER_WIDTH 2


#define HAVE_GL 1


#define HAVE_GL_GLU_H 1

#define USE_COLORMAP 1


#define HAVE_XINERAMA 0


#define USE_XFT 0


#define USE_PANGO 0


#define HAVE_XDBE 0


#define USE_XDBE HAVE_XDBE


#define HAVE_XFIXES 0


#define HAVE_XCURSOR 0


#define HAVE_XRENDER 0


#define HAVE_X11_XREGION_H 0

#define HAVE_OVERLAY 0
#define HAVE_GL_OVERLAY HAVE_OVERLAY

#ifdef __APPLE__
#include <mac_endianness.h>
#else
#define WORDS_BIGENDIAN 0
#endif

/*
 * U16, U32, U64:
 *
 * Types used by fl_draw_image.  One of U32 or U64 must be defined.
 * U16 is optional but FLTK will work better with it!
 */

#define U16 unsigned short
#define U32 unsigned
/* #undef U64 */

/*
 * HAVE_DIRENT_H, HAVE_SYS_NDIR_H, HAVE_SYS_DIR_H, HAVE_NDIR_H,
 * HAVE_SCANDIR, HAVE_SCANDIR_POSIX:
 *
 * Where is <dirent.h> (used only by fl_file_chooser and scandir).
 */

/* #undef HAVE_DIRENT_H */
/* #undef HAVE_SYS_NDIR_H */
/* #undef HAVE_SYS_DIR_H */
/* #undef HAVE_NDIR_H */
/* #undef HAVE_SCANDIR */
/* #undef HAVE_SCANDIR_POSIX */

/*
 * Possibly missing sprintf-style functions:
 */

/* #undef HAVE_VSNPRINTF */
/* #undef HAVE_SNPRINTF */

/*
 * String functions and headers...
 */

/* #undef HAVE_STRINGS_H */
#define HAVE_STRCASECMP 1
/* #undef HAVE_STRLCAT */
/* #undef HAVE_STRLCPY */

/*
 * Do we have POSIX locale support?
 */

#define HAVE_LOCALE_H 1
#define HAVE_LOCALECONV 1

/*
 * HAVE_SYS_SELECT_H:
 *
 * Whether or not select() call has its own header file.
 */

#define HAVE_SYS_SELECT_H 0

/*
 * HAVE_SYS_STDTYPES_H:
 *
 * Whether or not we have the <sys/stdtypes.h> header file.
 */

/* #undef HAVE_SYS_STDTYPES_H */

/*
 * USE_POLL:
 *
 * Use the poll() call provided on Linux and Irix instead of select()
 */

#define USE_POLL 0

/*
 * Do we have various image libraries?
 */

#define HAVE_LIBPNG 1
#define HAVE_LIBZ 1
#define HAVE_LIBJPEG 1

/*
 * FLTK_USE_CAIRO
 *
 * Do we have the cairo library available and want extended cairo use in FLTK ?
 * This implies to link cairo.lib in all FLTK based apps.
 */

/* #undef FLTK_USE_CAIRO */

/*
 * FLTK_HAVE_CAIRO
 *
 * Do we have the cairo library available?
 */

/* #undef FLTK_HAVE_CAIRO */

/*
 * Which header file do we include for libpng?
 */

#define HAVE_PNG_H 1
/* #undef HAVE_LIBPNG_PNG_H */

/*
 * Do we have the png_xyz() functions?
 */

#define HAVE_PNG_GET_VALID 1
#define HAVE_PNG_SET_TRNS_TO_ALPHA 1

/*
* FLTK_USE_NANOSVG
*
* Do we want FLTK to support SVG images with nanosvg ?
*/

#define FLTK_USE_NANOSVG 1

/*
 * Do we have POSIX threading?
 */

/* #undef HAVE_PTHREAD */
/* #undef HAVE_PTHREAD_H */

/*
 * Do we have the ALSA library?
 */

/* #undef HAVE_ALSA_ASOUNDLIB_H */

/*
 * Do we have the long long type?
 */

#define HAVE_LONG_LONG 1

#ifdef HAVE_LONG_LONG
#  define FLTK_LLFMT	"%lld"
#  define FLTK_LLCAST	(long long)
#else
#  define FLTK_LLFMT	"%ld"
#  define FLTK_LLCAST	(long)
#endif /* HAVE_LONG_LONG */

/*
 * Do we have the dlsym() function and header?
 */

#define HAVE_DLFCN_H 0
#define HAVE_DLSYM 0

/*
 * Do we want print support?
 */

/* #undef FL_NO_PRINT_SUPPORT */

/*
 * Do we want filename handling and a filechooser?
 */

/* #undef FL_CFG_NO_FILESYSTEM_SUPPORT */

/*
 * End of "$Id$".
 */
