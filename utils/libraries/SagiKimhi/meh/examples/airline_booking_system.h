#ifndef AIRLINE_BOOKING_H_
#define AIRLINE_BOOKING_H_

/* -----------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------------- */

#ifndef N_SEATS
# define N_SEATS 250
#endif

#ifndef N_AGENTS
# define N_AGENTS 15
#endif

#ifndef MEH_SHORT_NAMESPACE
# define MEH_SHORT_NAMESPACE
#endif
#include "meh.h"

/* -----------------------------------------------------------------------------
 * Typedefs
 * ----------------------------------------------------------------------------- */

typedef int req_val_t;
typedef int unsigned id_t;

typedef enum req_kind req_kind_t;
typedef enum rsp_kind rsp_kind_t;
typedef enum rsrv_state rsrv_state_t;
typedef enum airline_booking_entity booking_entity_t;

typedef struct seat seat_t;
typedef struct flight flight_t;
typedef struct booking booking_t;
typedef struct request request_t;
typedef struct response response_t;
typedef struct registry registry_t;
typedef struct travel_agent travel_agent_t;
typedef struct airline_booking_center booking_center_t;
typedef struct airline_booking_manager booking_manager_t;
typedef struct booking_system booking_system_t;
typedef struct airline_booking_system airline_system_t;

/* -----------------------------------------------------------------------------
 * Constants
 * ----------------------------------------------------------------------------- */

enum airline_booking_entity {
    AIRLINE_TRAVEL_AGENT,
    AIRLINE_BOOKING_CENTER,
    AIRLINE_BOOKING_MANAGER,
    NUM_AIRLINE_BOOKING_ENTITIES,
};

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
    meh_process_t p_info;
};

struct airline_booking_center {
    meh_darray_t rsrved_da;
    meh_darray_t unrsrved_da;
    meh_process_t p_info;
};

struct airline_booking_manager {
    meh_darray_t flight_da;
    meh_darray_t registry_da;
    meh_process_t p_info;
};

struct airline_booking_system {
    meh_darray_t travel_agents;
    booking_center_t booking_center;
    booking_manager_t booking_manager;
    meh_process_t p_info;
};

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

int
airline_booking_system(void);

airline_system_t
airline_booking_system_create(void);

void
airline_booking_system_destroy(void);

booking_manager_t
airline_booking_manager_create(void);

void
airline_booking_manager_destroy(booking_manager_t *bm);

booking_center_t
airline_booking_center_create(void);

void
airline_booking_center_destroy(booking_center_t *bc);

travel_agent_t
travel_agent_create(void);

void
travel_agent_destroy(travel_agent_t *ta);

#endif
