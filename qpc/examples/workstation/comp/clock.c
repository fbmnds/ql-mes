/*$file${.::clock.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: comp.qm
* File:  ${.::clock.c}
*
* This code has been generated by QM 4.5.0 (https://www.state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*$endhead${.::clock.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpc.h"
#include "bsp.h"
#include "alarm.h"
#include "clock.h"

#include <stdio.h>

Q_DEFINE_THIS_FILE

/* Active object class -----------------------------------------------------*/
/*$declare${Components::AlarmClock} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${Components::AlarmClock} ................................................*/
typedef struct {
/* protected: */
    QActive super;

/* private: */
    uint32_t current_time;
    Alarm alarm;

/* public: */
    QTimeEvt timeEvt;
} AlarmClock;

/* protected: */
static QState AlarmClock_initial(AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_timekeeping(AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_mode24h(AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_mode12h(AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_final(AlarmClock * const me, QEvt const * const e);
/*$enddecl${Components::AlarmClock} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* Local objects -----------------------------------------------------------*/
static AlarmClock l_alarmClock; /* the single inst of the AO */

/* Global-scope objects ----------------------------------------------------*/
/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 650U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.5.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${Components::APP_alarmClock} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${Components::APP_alarmClock} ............................................*/
QActive * const APP_alarmClock = &l_alarmClock.super;
/*$enddef${Components::APP_alarmClock} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${Components::AlarmClock_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${Components::AlarmClock_ctor} ...........................................*/
void AlarmClock_ctor(void) {
    AlarmClock * const me = &l_alarmClock;

    QActive_ctor(&me->super, Q_STATE_CAST(&AlarmClock_initial));
    Alarm_ctor(&me->alarm); /* orthogonal component ctor */

    /* private time event ctor */
    QTimeEvt_ctorX(&me->timeEvt, &me->super, TICK_SIG, 0U);
}
/*$enddef${Components::AlarmClock_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*..........................................................................*/
/*$define${Components::AlarmClock} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${Components::AlarmClock} ................................................*/
/*${Components::AlarmClock::SM} ............................................*/
static QState AlarmClock_initial(AlarmClock * const me, QEvt const * const e) {
    /*${Components::AlarmClock::SM::initial} */
    (void)e; /* avoid compiler warning about unused parameter */
    me->current_time = 0U;

    /* (!) trigger the initial transition in the component */
    QHSM_INIT((QHsm *)&me->alarm, (QEvt *)0);
    return Q_TRAN(&AlarmClock_timekeeping);
}
/*${Components::AlarmClock::SM::timekeeping} ...............................*/
static QState AlarmClock_timekeeping(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Components::AlarmClock::SM::timekeeping} */
        case Q_ENTRY_SIG: {
            /* periodic timeout every second */
            QTimeEvt_armX(&me->timeEvt, BSP_TICKS_PER_SEC,
                                        BSP_TICKS_PER_SEC);
            status_ = Q_HANDLED();
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping} */
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->timeEvt);
            status_ = Q_HANDLED();
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&AlarmClock_mode24h);
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::CLOCK_24H} */
        case CLOCK_24H_SIG: {
            status_ = Q_TRAN(&AlarmClock_mode24h);
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::CLOCK_12H} */
        case CLOCK_12H_SIG: {
            status_ = Q_TRAN(&AlarmClock_mode12h);
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::ALARM} */
        case ALARM_SIG: {
            BSP_showMsg("Wake up!!!");
            status_ = Q_HANDLED();
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::ALARM_SET, ALARM_ON, ALARM_OFF} */
        case ALARM_SET_SIG: /* intentionally fall through */
        case ALARM_ON_SIG: /* intentionally fall through */
        case ALARM_OFF_SIG: {
            /* (!) synchronously dispatch to the orthogonal component */
            QHSM_DISPATCH((QHsm *)&me->alarm, e);
            status_ = Q_HANDLED();
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::TERMINATE} */
        case TERMINATE_SIG: {
            BSP_showMsg("--> final");
            status_ = Q_TRAN(&AlarmClock_final);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${Components::AlarmClock::SM::timekeeping::mode24h} ......................*/
static QState AlarmClock_mode24h(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Components::AlarmClock::SM::timekeeping::mode24h} */
        case Q_ENTRY_SIG: {
            BSP_showMsg("*** 24-hour mode");
            status_ = Q_HANDLED();
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::mode24h::TICK} */
        case TICK_SIG: {
            TimeEvt pe; /* temporary synchronous event for the component */

            /* roll over in 24-hr mode? */
            if (++me->current_time == 24U*60U) {
                me->current_time = 0U;
            }
            BSP_showTime24H("", me->current_time, 60U);
            pe.super.sig = TIME_SIG;
            pe.current_time = me->current_time;

            /* (!) synchronously dispatch to the orthogonal component */
            QHSM_DISPATCH(&me->alarm.super, &pe.super);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&AlarmClock_timekeeping);
            break;
        }
    }
    return status_;
}
/*${Components::AlarmClock::SM::timekeeping::mode12h} ......................*/
static QState AlarmClock_mode12h(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Components::AlarmClock::SM::timekeeping::mode12h} */
        case Q_ENTRY_SIG: {
            BSP_showMsg("*** 12-hour mode");
            status_ = Q_HANDLED();
            break;
        }
        /*${Components::AlarmClock::SM::timekeeping::mode12h::TICK} */
        case TICK_SIG: {
            TimeEvt pe; /* temporary synchronous event for the component */

            /* roll over in 12-hr mode? */
            if (++me->current_time == 12U*60U) {
                me->current_time = 0U;
            }
            BSP_showTime12H("", me->current_time, 60U);
            pe.super.sig = TIME_SIG;
            pe.current_time = me->current_time;

            /* (!) synchronously dispatch to the orthogonal component */
            QHSM_DISPATCH(&me->alarm.super, &pe.super);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&AlarmClock_timekeeping);
            break;
        }
    }
    return status_;
}
/*${Components::AlarmClock::SM::final} .....................................*/
static QState AlarmClock_final(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Components::AlarmClock::SM::final} */
        case Q_ENTRY_SIG: {
            QF_stop(); /* terminate the application */
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*$enddef${Components::AlarmClock} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
