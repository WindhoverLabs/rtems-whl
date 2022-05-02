/* SPDX-License-Identifier: BSD-2-Clause */

/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <tmacros.h>

#include <dlfcn.h>
#include <pthread.h>
#include <errno.h>

void apphello(void);

const char rtems_test_name[] = "HELLO WORLD";

static rtems_task Init(
  rtems_task_argument ignored
)
{
   int status;
   pthread_once_t once = PTHREAD_ONCE_INIT;

/* Loading apphello dynamically and executing  */
/*
  void *handle;
  void (*func_apphello)(void);

//  handle = dlopen("./libapphello.a", RTLD_LAZY);
//  handle = dlopen("./libapphello.a", RTLD_NOW);
  handle = dlopen("./libapphello.a", RTLD_GLOBAL);

  if (!handle) {
    // fail to load the library
    printf("Error: %s\n", dlerror());
    rtems_test_exit( 1 );
  }

  *(void**)(&func_apphello) = dlsym(handle, "apphello");
  if (!func_apphello) {
    // no such symbol
    printf("Error: %s\n", dlerror());
    dlclose(handle);
    rtems_test_exit( 1 );
  }

  func_apphello();
  dlclose(handle);
*/
/* End of Loading apphello dynamically and executing  */

/* Loading apphello statically and executing  */
//   puts("Init: pthread_once create");
   status = pthread_once(&once, apphello);

   switch(status) {
      case 0 :
         printf("Init: pthread_once success\n");
         break;
      case EINVAL :
         printf("Init: Invalid setting in attr\n");
         break;
      default :
         printf("Init: Unknown error\n");
   }
/* End of loading apphello statically and executing */

  rtems_print_printer_fprintf_putc(&rtems_test_printer);
  TEST_BEGIN();
  printf( "Hello World\n" );
  TEST_END();
  rtems_test_exit( 0 );
}


/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_SIMPLE_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            1

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT_TASK_ATTRIBUTES RTEMS_FLOATING_POINT

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
