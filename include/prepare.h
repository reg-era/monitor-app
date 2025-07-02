#ifndef prepare_H
#define prepare_H

#include "header.h"
#include "cpu.h"
#include "memory.h"
#include "process.h"

int HeaderNavigation(ImVec2 size);
int SectionWindows(int section, CPU cpu, Memory mem, Process &proc);
#endif