/*$file${.::dpp.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: dpp.qm
* File:  ${.::dpp.h}
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
/*$endhead${.::dpp.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#ifndef dpp_h
#define dpp_h

enum DPPSignals {
    EAT_SIG = Q_USER_SIG, /* published by Table to let a philosopher eat */
    DONE_SIG,       /* published by Philosopher when done eating */
    PAUSE_SIG,      /* published by BSP to pause serving forks */
    SERVE_SIG,      /* published by BSP to serve re-start serving forks */
    TEST_SIG,       /* published by BSP to test the application */
    MAX_PUB_SIG,    /* the last published signal */

    HUNGRY_SIG,     /* posted direclty to Table from hungry Philo */
    TIMEOUT_SIG,    /* used by Philosophers for time events */
    MAX_SIG         /* the last signal */
};

/*$declare${Events::TableEvt} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${Events::TableEvt} ......................................................*/
typedef struct {
/* protected: */
    QEvt super;

/* public: */
    uint8_t philoNum;
} TableEvt;
/*$enddecl${Events::TableEvt} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* number of philosophers */
#define N_PHILO ((uint8_t)5)

/*$declare${AOs::Philo_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${AOs::Philo_ctor} .......................................................*/
void Philo_ctor(void);
/*$enddecl${AOs::Philo_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$declare${AOs::AO_Philo[N_PHILO]} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
extern QActive * const AO_Philo[N_PHILO];
/*$enddecl${AOs::AO_Philo[N_PHILO]} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$declare${AOs::Table_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${AOs::Table_ctor} .......................................................*/
void Table_ctor(void);
/*$enddecl${AOs::Table_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$declare${AOs::AO_Table} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
extern QActive * const AO_Table;
/*$enddecl${AOs::AO_Table} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#ifdef qxk_h
    void Test1_ctor(void);
    extern QXThread * const XT_Test1;
    void Test2_ctor(void);
    extern QXThread * const XT_Test2;
#endif /* qxk_h */

#endif /* dpp_h */