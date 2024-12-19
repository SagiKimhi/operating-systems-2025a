#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "airline_booking_system.h"
#include "meh_fork.h"
#include "meh_types.h"

airline_system_t booking_system = {0};

/* -----------------------------------------------------------------------------
 * Main
 * ----------------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
    meh_as_none(argc);
    meh_as_none(argv);
    return airline_booking_system();
}

/* -----------------------------------------------------------------------------
 * Method Definitions
 * ----------------------------------------------------------------------------- */

int
airline_booking_system(void)
{
    booking_system = airline_booking_system_create();

    if (getpid() != booking_system.p_info.pid) {
        airline_booking_system_destroy();
    }

    airline_booking_system_destroy();
    return 0;
}

airline_system_t
airline_booking_system_create(void)
{
    size_t i = 0;
    airline_system_t abs = {0};
    static travel_agent_t tmp = {0};

    memset(&abs, 0, sizeof(abs));
    abs.p_info = ps.self();
    abs.travel_agents = da.create(sizeof(travel_agent_t));
    meh_fork();
    meh_begin();
    abs.booking_center = airline_booking_center_create();
    meh_end();
    meh_begin();
    abs.booking_manager = airline_booking_manager_create();
    meh_end();
    meh_begin();
    for (i = 0; i < N_AGENTS; i++) {
        meh_fork();
        meh_begin();
        tmp = travel_agent_create();
        meh_check(da.append(&abs.travel_agents, &tmp));
        meh_end();
        meh_join_none();
    }
    meh_end();
    meh_join();
    return abs;
}

void
airline_booking_system_destroy(void)
{
    while (booking_system.travel_agents.size)
        travel_agent_destroy(da.pop(&booking_system.travel_agents));

    ps.destroy(&booking_system.p_info);
    da.destroy(&booking_system.travel_agents);
    airline_booking_center_destroy(&booking_system.booking_center);
    airline_booking_manager_destroy(&booking_system.booking_manager);
}

booking_center_t
airline_booking_center_create(void)
{
    booking_center_t abc;

    memset(&abc, 0, sizeof(abc));
    abc.p_info = ps.self();
    abc.rsrved_da = da.create(sizeof(seat_t));
    abc.unrsrved_da = da.create(sizeof(seat_t));
    return abc;
}

void
airline_booking_center_destroy(booking_center_t *abc)
{
    if (abc != NULL) {
        ps.destroy(&abc->p_info);
        da.destroy(&abc->rsrved_da);
        da.destroy(&abc->unrsrved_da);
    }
}

booking_manager_t
airline_booking_manager_create(void)
{
    booking_manager_t abm;

    memset(&abm, 0, sizeof(abm));
    abm.p_info = ps.self();
    abm.flight_da = da.create(sizeof(flight_t));
    abm.registry_da = da.create(sizeof(registry_t));
    return abm;
}

void
airline_booking_manager_destroy(booking_manager_t *abm)
{
    if (abm != NULL) {
        ps.destroy(&abm->p_info);
        da.destroy(&abm->flight_da);
        da.destroy(&abm->registry_da);
    }
}

travel_agent_t
travel_agent_create(void)
{
    travel_agent_t ta;

    memset(&ta, 0, sizeof(ta));
    ta.id = getpid() - getppid();
    ta.p_info = ps.self();
    ta.booking_da = da.create(sizeof(booking_t));
    return ta;
}

void
travel_agent_destroy(travel_agent_t *ta)
{
    if (ta != NULL) {
        ps.destroy(&ta->p_info);
        da.destroy(&ta->booking_da);
    }
}
