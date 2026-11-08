/*
 * $Id: Block.c 145 2007-11-19 23:50:24Z michael.haupt $
 *
Copyright (c) 2007 Michael Haupt, Tobias Pape
Software Architecture Group, Hasso Plattner Institute, Potsdam, Germany
http://www.hpi.uni-potsdam.de/swa/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
  */

#include "Block.h"

#include <vmobjects/VMObject.h>
#include <vmobjects/VMFrame.h>
#include <vmobjects/VMMethod.h>

#include <vm/Universe.h>


void  _Block_value(pVMObject object, pVMFrame frame) {
    // intentionally left blank
}


void  _Block_value_(pVMObject object, pVMFrame frame) {
    // intentionally left blank
}


void  _Block_value_with_(pVMObject object, pVMFrame frame) {
    // intentionally left blank
}


void  _Block_restart(pVMObject object, pVMFrame frame) {
#ifdef USE_YK
    // restart is the back edge of whileTrue:, which every built-in loop
    // (whileFalse:, to:do:, timesRepeat:, ...) bottoms out in. Its target,
    // bytecode 0 of the looping method, is the loop header.
    // ponytail: one location per looping method, so all loops share
    // whileTrue:'s; key locations by call site if traces thrash.
    if (yk_is_interpreting() && yk_location_is_null(frame->method->ykloc))
        frame->method->ykloc = yk_location_new();
#endif
    SEND(frame, set_bytecode_index, 0);
    SEND(frame, reset_stack_pointer);    
}
