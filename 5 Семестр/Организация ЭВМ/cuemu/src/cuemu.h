#ifndef CUEMU_H
#define CUEMU_H

#include <cstdio>
#include <iostream>
#include "cstorage.h"
#include "executer.h"

#include <classlib/thread.h>

namespace std {;}
using namespace std;

extern microcommand *list;
extern cable *connections;

typedef void (*cuemu_notify_func_pointer)(const char *cmd, void *data);

extern cuemu_notify_func_pointer cuemu_notify_func;
extern void *cuemu_notify_data;

extern TCriticalSection cuemu_mutex;

void set_stdout(ostream &ofs);
ostream &get_stdout();
void process_stream(istream &in, bool is_stdin);

#endif
