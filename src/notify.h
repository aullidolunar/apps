#ifndef NOTIFY_H_INCLUDED
#define NOTIFY_H_INCLUDED

#ifdef WITH_LIBNOTIFY
#include <libnotify/notify.h>
#include "main.h"

NotifyNotification* notify_up ();
void notify_popup (NotifyNotification *, gboolean);

#endif

#endif
