#ifndef _bulwers_h
#define _bulwers_h

#define IMG_NORMAL  0

#include "defines.hxx"

struct core_stats
{
    uint32  core_day,                 //get_time ().day;
            core_dnum,                //get_time ().day_num;
            core_month,               //get_time ().month;
            core_year,                //get_time ().year;
            core_time,                //get_time ().hour;
            core_battery_plugged,     //bat_plugged ();
            core_temperature,         //temperatura ();
            core_battery,             //bateria();
            core_cpu_load,            /* (cpu_probes[0] +
                                                cpu_probes[1] +
                                                cpu_probes[2] +
                                                cpu_probes[3] +
                                                cpu_probes[4] +
                                                cpu_probes[5] +
                                                cpu_probes[6] +
                                                cpu_probes[7] +
                                                cpu_probes[8] +
                                                cpu_probes[9]) / 10;*/
            current_probe,            //0
            cpu_probes[10],           //20 / C_LOAD ();
            core_memory,              //M_LOAD ();
            core_proclist,            //P_LIST ();
            core_uptime,              //U_TIME ();
            energy,                   //54000
            prev_bat_plug,            //core_battery_plugged
            battery_buffer,           //0
            temp_t,                   //0
            flu_timer,                //360
            prev_happy;               //0
    bool    once_plugged;             //false

};

struct bulwers_core
{
    int special;
    int longev;
    int happy;
    int step;
};

struct pict_layers
{
int bulwers;
char * outline;
int eye;
int tired;
int hot;
int shy;
int layer2;
int layer3;
int layer4;

friend int operator== (pict_layers& left, int& right );
friend int operator!= (pict_layers& a, pict_layers& b );

};

#endif // bulwers_h