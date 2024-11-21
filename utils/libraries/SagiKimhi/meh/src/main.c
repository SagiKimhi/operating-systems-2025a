#include "meh_darray.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef MEH_SHORT_NAMESPACES
#define MEH_SHORT_NAMESPACES
#include "meh.h"
#endif

/* -----------------------------------------------------------------------------
 * Typedefs
 * ----------------------------------------------------------------------------- */

typedef int req_val_t;
typedef int unsigned id_t;

typedef enum req_kind req_kind_t;
typedef enum rsp_kind rsp_kind_t;
typedef enum rsrv_state rsrv_state_t;

typedef struct seat seat_t;
typedef struct flight flight_t;
typedef struct booking booking_t;
typedef struct request request_t;
typedef struct response response_t;
typedef struct registry registry_t;
typedef struct process_info process_info_t;
typedef struct travel_agent travel_agent_t;
typedef struct booking_center booking_center_t;
typedef struct booking_manager booking_manager_t;
typedef struct booking_system booking_system_t;

/* -----------------------------------------------------------------------------
 * Constants
 * ----------------------------------------------------------------------------- */

enum req_kind {
    RESERVATION,
    CANCELATION,
};

enum rsp_kind {
    OK,
    ERR,
};

enum rsrv_state {
    RESERVED,
    UNRESERVED,
};

/* -----------------------------------------------------------------------------
 * Structs
 * ----------------------------------------------------------------------------- */

struct process_info {
    pid_t pid;
};

struct seat {
    id_t id;
    rsrv_state_t state;
};

struct flight {
    id_t id;
    meh_darray_t seat_da;
};

struct booking {
    id_t id;
    id_t agent_id;
    id_t flight_id;
    meh_darray_t seatno_da;
};

struct request {
    id_t id;
    id_t agent_id;
    req_kind_t kind;
    size_t nof_seats;
};

struct response {
    id_t id;
    request_t req;
    rsp_kind_t status;
};

struct registry {
    id_t flight_id;
    meh_darray_t booking_da;
    meh_darray_t request_da;
    meh_darray_t response_da;
};

struct travel_agent {
    id_t id;
    meh_darray_t booking_da;
    process_info_t p_info;
};

struct booking_center {
    meh_darray_t rsrved_da;
    meh_darray_t unrsrved_da;
    process_info_t p_info;
};

struct booking_manager {
    meh_darray_t flight_da;
    meh_darray_t registry_da;
    process_info_t p_info;
};

struct airline_system {
    meh_darray_t travel_agents;
    booking_center_t booking_center;
    booking_manager_t booking_manager;
    process_info_t p_info;
};

/* -----------------------------------------------------------------------------
 * Main
 * ----------------------------------------------------------------------------- */

process_info_t
pinfo(void)
{
    return (process_info_t){.pid = getpid()};
}

int
airline_system(void)
{
    int ok;
    size_t i;
    travel_agent_t tmp_ta;
    struct airline_system airline;

    ok = 1;
    airline = (struct airline_system){
        .p_info = pinfo(),
        .booking_center = {},
        .booking_manager = {},
        .travel_agents = darray.create(sizeof(travel_agent_t)),
    };

    meh_da_print(airline.travel_agents);

    for (i = 0; ok && i < 15; i++) {
        tmp_ta = (travel_agent_t){
            .id = i,
            .booking_da = darray.create(sizeof(booking_t)),
        };
        ok &= darray.append(&airline.travel_agents, &tmp_ta);
    }

    meh_da_print(airline.travel_agents);

    if (ok) {
        ok &= darray.extend(
                  &airline.travel_agents,
                  &airline.travel_agents.items,
                  airline.travel_agents.size)
              == meh_cast(int, airline.travel_agents.size);
    }

    meh_da_print(airline.travel_agents);
    darray.destroy(&airline.travel_agents);
    return ok;
}

int
main(int argc, char *argv[])
{
    meh_as_none(argc);
    meh_as_none(argv);
    return airline_system() ? EXIT_SUCCESS : EXIT_FAILURE;
}
