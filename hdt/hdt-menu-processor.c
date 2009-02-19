/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Erwan Velu - All Rights Reserved
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 *
 * -----------------------------------------------------------------------
*/

#include "hdt-menu.h"

/* Compute Processor menu */
void compute_processor(struct s_my_menu *menu,s_cpu *cpu, s_dmi *dmi) {
  char buffer[SUBMENULEN+1];
  char buffer1[SUBMENULEN+1];
  char statbuffer[STATLEN+1];

  menu->menu = add_menu(" Main Processor ",-1);
  menu->items_count=0;
  set_menu_pos(SUBMENU_Y,SUBMENU_X);

  snprintf(buffer,sizeof buffer,"Vendor    : %s",cpu->vendor);
  snprintf(statbuffer,sizeof statbuffer,"Vendor: %s",cpu->vendor);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  snprintf(buffer,sizeof buffer,"Model     : %s",cpu->model);
  snprintf(statbuffer,sizeof statbuffer,"Model: %s",cpu->model);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  snprintf(buffer,sizeof buffer,"Vendor ID : %d",cpu->vendor_id);
  snprintf(statbuffer,sizeof statbuffer,"Vendor ID: %d",cpu->vendor_id);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  snprintf(buffer,sizeof buffer,"Family ID : %d",cpu->family);
  snprintf(statbuffer,sizeof statbuffer,"Family ID: %d",cpu->family);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  snprintf(buffer,sizeof buffer,"Model  ID : %d",cpu->model_id);
  snprintf(statbuffer,sizeof statbuffer,"Model  ID: %d",cpu->model_id);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  snprintf(buffer,sizeof buffer,"Stepping  : %d",cpu->stepping);
  snprintf(statbuffer,sizeof statbuffer,"Stepping: %d",cpu->stepping);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  if (is_dmi_valid) {
   snprintf(buffer,sizeof buffer,"FSB       : %d",dmi->processor.external_clock);
   snprintf(statbuffer,sizeof statbuffer,"Front Side Bus (MHz): %d",dmi->processor.external_clock);
   add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
   menu->items_count++;

   snprintf(buffer,sizeof buffer,"Cur. Speed: %d",dmi->processor.current_speed);
   snprintf(statbuffer,sizeof statbuffer,"Current Speed (MHz): %d",dmi->processor.current_speed);
   add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
   menu->items_count++;

   snprintf(buffer,sizeof buffer,"Max Speed : %d",dmi->processor.max_speed);
   snprintf(statbuffer,sizeof statbuffer,"Max Speed (MHz): %d",dmi->processor.max_speed);
   add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
   menu->items_count++;

   snprintf(buffer,sizeof buffer,"Upgrade   : %s",dmi->processor.upgrade);
   snprintf(statbuffer,sizeof statbuffer,"Upgrade: %s",dmi->processor.upgrade);
   add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
   menu->items_count++;
  }

  if (cpu->flags.smp) {
          snprintf(buffer,sizeof buffer,"SMP       : Yes");
          snprintf(statbuffer,sizeof statbuffer,"SMP: Yes");
  }
  else {
          snprintf(buffer,sizeof buffer,"SMP       : No");
          snprintf(statbuffer,sizeof statbuffer,"SMP: No");
  }
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  if (cpu->flags.lm) {
          snprintf(buffer,sizeof buffer,"x86_64    : Yes");
          snprintf(statbuffer,sizeof statbuffer,"x86_64 compatible processor: Yes");
  }
  else {
          snprintf(buffer,sizeof buffer,"X86_64    : No");
          snprintf(statbuffer,sizeof statbuffer,"X86_64 compatible processor: No");
  }
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  buffer1[0]='\0';
  if (cpu->flags.fpu) strcat(buffer1,"fpu ");
  if (cpu->flags.vme) strcat(buffer1,"vme ");
  if (cpu->flags.de)  strcat(buffer1,"de ");
  if (cpu->flags.pse) strcat(buffer1,"pse ");
  if (cpu->flags.tsc) strcat(buffer1,"tsc ");
  if (cpu->flags.msr) strcat(buffer1,"msr ");
  if (cpu->flags.pae) strcat(buffer1,"pae ");
  snprintf(buffer,sizeof buffer,"Flags     : %s",buffer1);
  snprintf(statbuffer,sizeof statbuffer,"Flags: %s",buffer1);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  buffer1[0]='\0';
  if (cpu->flags.mce) strcat(buffer1,"mce ");
  if (cpu->flags.cx8) strcat(buffer1,"cx8 ");
  if (cpu->flags.apic) strcat(buffer1,"apic ");
  if (cpu->flags.sep) strcat(buffer1,"sep ");
  if (cpu->flags.mtrr) strcat(buffer1,"mtrr ");
  if (cpu->flags.pge) strcat(buffer1,"pge ");
  if (cpu->flags.mca) strcat(buffer1,"mca ");
  snprintf(buffer,sizeof buffer,"Flags     : %s",buffer1);
  snprintf(statbuffer,sizeof statbuffer,"Flags: %s",buffer1);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  buffer1[0]='\0';
  if (cpu->flags.cmov) strcat(buffer1,"cmov ");
  if (cpu->flags.pat)  strcat(buffer1,"pat ");
  if (cpu->flags.pse_36) strcat(buffer1,"pse_36 ");
  if (cpu->flags.psn)  strcat(buffer1,"psn ");
  if (cpu->flags.clflsh) strcat(buffer1,"clflsh ");
  snprintf(buffer,sizeof buffer,"Flags     : %s",buffer1);
  snprintf(statbuffer,sizeof statbuffer,"Flags: %s",buffer1);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  buffer1[0]='\0';
  if (cpu->flags.dts)  strcat(buffer1,"dts ");
  if (cpu->flags.acpi) strcat(buffer1,"acpi ");
  if (cpu->flags.mmx)  strcat(buffer1,"mmx ");
  if (cpu->flags.sse)  strcat(buffer1,"sse ");
  snprintf(buffer,sizeof buffer,"Flags     : %s",buffer1);
  snprintf(statbuffer,sizeof statbuffer,"Flags: %s",buffer1);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  buffer1[0]='\0';
  if (cpu->flags.sse2) strcat(buffer1,"sse2 ");
  if (cpu->flags.ss)   strcat(buffer1,"ss ");
  if (cpu->flags.htt)  strcat(buffer1,"ht ");
  if (cpu->flags.acc)  strcat(buffer1,"acc ");
  if (cpu->flags.syscall) strcat(buffer1,"syscall ");
  if (cpu->flags.mp)   strcat(buffer1,"mp ");
  snprintf(buffer,sizeof buffer,"Flags     : %s",buffer1);
  snprintf(statbuffer,sizeof statbuffer,"Flags: %s",buffer1);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  buffer1[0]='\0';
  if (cpu->flags.nx)    strcat(buffer1,"nx ");
  if (cpu->flags.mmxext) strcat(buffer1,"mmxext ");
  if (cpu->flags.lm)     strcat(buffer1,"lm ");
  if (cpu->flags.nowext) strcat(buffer1,"3dnowext ");
  if (cpu->flags.now)    strcat(buffer1,"3dnow! ");
  snprintf(buffer,sizeof buffer,"Flags     : %s",buffer1);
  snprintf(statbuffer,sizeof statbuffer,"Flags: %s",buffer1);
  add_item(buffer,statbuffer,OPT_INACTIVE,NULL,0);
  menu->items_count++;

  printf("MENU: Processor menu done (%d items)\n",menu->items_count);
}
