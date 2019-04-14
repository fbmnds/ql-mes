# test-script for QUTest unit testing harness
# see https://www.state-machine.com/qtools/qutest.html

# preamble...
proc on_reset {} {
    expect_pause
    continue
}

# tests...
test "tick"
glb_filter ON
current_obj TE l_philo<2>.timeEvt
tick
expect "           Tick<0>  Ctr=*"
expect "           TE0-ADis Obj=l_philo<2>.timeEvt,AO=AO_Philo<2>"
expect "@timestamp TE0-Post Obj=l_philo<2>.timeEvt,Sig=TIMEOUT_SIG,AO=AO_Philo<2>"
expect "@timestamp AO-Post  Sdr=QS_RX,Obj=AO_Philo<2>,Evt<Sig=TIMEOUT_SIG,Pool=0,Ref=0>,*"
expect "@timestamp AO-GetL  Obj=AO_Philo<2>,Evt<Sig=TIMEOUT_SIG,Pool=0,Ref=0>"
expect "@timestamp Disp===> Obj=AO_Philo<2>,Sig=TIMEOUT_SIG,State=Philo_thinking"
expect "@timestamp TE0-DisA Obj=l_philo<2>.timeEvt,AO=AO_Philo<2>"
expect "===RTC===> St-Exit  Obj=AO_Philo<2>,State=Philo_thinking"
expect "@timestamp QF-New   Sig=HUNGRY_SIG,*"
expect "@timestamp MP-Get   Obj=EvtPool1,*"
expect "@timestamp AO-Post  Sdr=AO_Philo<2>,Obj=AO_Table,Evt<Sig=HUNGRY_SIG,Pool=1,Ref=1>,*"
expect "@timestamp QUTEST_ON_POST HUNGRY_SIG,Obj=AO_Table 2"
expect "===RTC===> St-Entry Obj=AO_Philo<2>,State=Philo_hungry"
expect "@timestamp ===>Tran Obj=AO_Philo<2>,Sig=TIMEOUT_SIG,State=Philo_thinking->Philo_hungry"
expect "@timestamp AO-GetL  Obj=AO_Table,Evt<Sig=HUNGRY_SIG,Pool=1,Ref=1>"
expect "@timestamp Disp===> Obj=AO_Table,Sig=HUNGRY_SIG,State=Table_serving"
expect "@timestamp BSP_CALL BSP_displayPhilStat 2 hungry  "
expect "@timestamp QF-New   Sig=EAT_SIG,*"
expect "@timestamp MP-Get   Obj=EvtPool1,*"
expect "@timestamp QF-Pub   Sdr=AO_Table,Evt<Sig=EAT_SIG,Pool=1,Ref=0>"
expect "@timestamp AO-Post  Sdr=AO_Table,Obj=AO_Philo<4>,Evt<Sig=EAT_SIG,Pool=1,Ref=2>,*"
expect "@timestamp QUTEST_ON_POST EAT_SIG,Obj=AO_Philo<4> 2"
expect "@timestamp AO-Post  Sdr=AO_Table,Obj=AO_Philo<3>,Evt<Sig=EAT_SIG,Pool=1,Ref=3>,*"
expect "@timestamp QUTEST_ON_POST EAT_SIG,Obj=AO_Philo<3> 2"
expect "@timestamp AO-Post  Sdr=AO_Table,Obj=AO_Philo<2>,Evt<Sig=EAT_SIG,Pool=1,Ref=4>,*"
expect "@timestamp QUTEST_ON_POST EAT_SIG,Obj=AO_Philo<2> 2"
expect "@timestamp AO-Post  Sdr=AO_Table,Obj=AO_Philo<1>,Evt<Sig=EAT_SIG,Pool=1,Ref=5>,*"
expect "@timestamp QUTEST_ON_POST EAT_SIG,Obj=AO_Philo<1> 2"
expect "@timestamp AO-Post  Sdr=AO_Table,Obj=AO_Philo<0>,Evt<Sig=EAT_SIG,Pool=1,Ref=6>,*"
expect "@timestamp QUTEST_ON_POST EAT_SIG,Obj=AO_Philo<0> 2"
expect "@timestamp QF-gcA   Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp BSP_CALL BSP_displayPhilStat 2 eating  "
expect "@timestamp =>Intern Obj=AO_Table,Sig=HUNGRY_SIG,State=Table_serving"
expect "@timestamp QF-gc    Evt<Sig=HUNGRY_SIG,Pool=1,Ref=1>"
expect "@timestamp MP-Put   Obj=EvtPool1,*"
expect "@timestamp AO-GetL  Obj=AO_Philo<4>,Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp Disp===> Obj=AO_Philo<4>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp =>Intern Obj=AO_Philo<4>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp QF-gcA   Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp AO-GetL  Obj=AO_Philo<3>,Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp Disp===> Obj=AO_Philo<3>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp =>Intern Obj=AO_Philo<3>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp QF-gcA   Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp AO-GetL  Obj=AO_Philo<2>,Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp Disp===> Obj=AO_Philo<2>,Sig=EAT_SIG,State=Philo_hungry"
expect "@timestamp BSP_CALL BSP_random *"
expect "@timestamp TE0-Arm  Obj=l_philo<2>.timeEvt,AO=AO_Philo<2>,Tim=*,Int=0"
expect "===RTC===> St-Entry Obj=AO_Philo<2>,State=Philo_eating"
expect "@timestamp ===>Tran Obj=AO_Philo<2>,Sig=EAT_SIG,State=Philo_hungry->Philo_eating"
expect "@timestamp QF-gcA   Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp AO-GetL  Obj=AO_Philo<1>,Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp Disp===> Obj=AO_Philo<1>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp =>Intern Obj=AO_Philo<1>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp QF-gcA   Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp AO-GetL  Obj=AO_Philo<0>,Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp Disp===> Obj=AO_Philo<0>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp =>Intern Obj=AO_Philo<0>,Sig=EAT_SIG,State=Philo_thinking"
expect "@timestamp QF-gc    Evt<Sig=EAT_SIG,Pool=1,*"
expect "@timestamp MP-Put   Obj=EvtPool1,*"
expect "@timestamp Trg-Done QS_RX_TICK"


# the end...
end
