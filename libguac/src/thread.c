
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is libguac.
 *
 * The Initial Developer of the Original Code is
 * Michael Jumper.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "thread.h"

#ifdef HAVE_LIBPTHREAD
#include <pthread.h>
#elif defined(__MINGW32__)
#include <windows.h>
#include <process.h>
#endif

void guac_thread_create(guac_thread_t* thread, void*(*function)(void*), void* data) {
#ifdef HAVE_LIBPTHREAD
    pthread_create(thread, NULL, function, data);
#elif defined(__MINGW32__)
    *thread = _beginthreadex(NULL, 0,
            function, data, 0 /* Create running */, NULL);
#endif
}

void guac_thread_join(guac_thread_t thread) {
#ifdef HAVE_LIBPTHREAD
    pthread_join(thread, NULL);
#elif defined(__MINGW32__)
    WaitForSingleObject(thread, INFINITE);
#endif
}
