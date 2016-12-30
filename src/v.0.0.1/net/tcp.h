
/*
 * Copyright (c) 2006-2008 by Roland Riegel <feedback@roland-riegel.de>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef TCP_H
#define TCP_H

#include "tcp_config.h"

#include <stdbool.h>
#include <stdint.h>
#include <avr/pgmspace.h>

/**
 * \addtogroup net
 *
 * @{
 */
/**
 * \addtogroup net_stack
 *
 * @{
 */
/**
 * \addtogroup net_stack_tcp
 *
 * @{
 */
/**
 * \file
 * TCP header (license: GPLv2)
 *
 * \author Roland Riegel
 */

/** Events generated by a TCP socket. */
enum tcp_event
{
    /** No event happened. */
    TCP_EVT_NONE = 0,
    /** Some error happened. The socket is no more usable and should be deallocated. */
    TCP_EVT_ERROR,
    /** The connection has been closed down unexpectedly. */
    TCP_EVT_RESET,
    /** The connection has timed out and has been closed. */
    TCP_EVT_TIMEOUT,
    /** The connection has been established and is ready for sending and receiving data. */
    TCP_EVT_CONN_ESTABLISHED,
    /** A connection attempt has been made by a remote host. */
    TCP_EVT_CONN_INCOMING,
    /** The connection has been closed. */
    TCP_EVT_CONN_CLOSED,
    /** The connection is idle. */
    TCP_EVT_CONN_IDLE,
    /** Incoming data is waiting to be read from the socket. */
    TCP_EVT_DATA_RECEIVED,
    /** Data which has been previously written to the socket has been sent. */
    TCP_EVT_DATA_SENT
};

struct tcp_header;

typedef void (*tcp_callback)(int socket, enum tcp_event event);

void tcp_init();

bool tcp_handle_packet(const uint8_t* ip, const struct tcp_header* packet, uint16_t packet_len);

int tcp_socket_alloc(tcp_callback callback);
bool tcp_socket_free(int socket);

bool tcp_connect(int socket, const uint8_t* ip, uint16_t port);
bool tcp_disconnect(int socket);
bool tcp_listen(int socket, uint16_t port);
bool tcp_accept(int socket, tcp_callback callback);

int16_t tcp_write(int socket, const uint8_t* data, uint16_t data_len);
int16_t tcp_write_string_P(int socket, PGM_P str);
int16_t tcp_read(int socket, uint8_t* buffer, uint16_t buffer_len);
int16_t tcp_peek(int socket, uint8_t* buffer, uint16_t offset, uint16_t buffer_len);
int16_t tcp_skip(int socket, uint16_t buffer_len);
int16_t tcp_reserve(int socket, uint16_t len);

uint8_t* tcp_buffer_rx(int socket);
uint8_t* tcp_buffer_tx(int socket);

int16_t tcp_buffer_used_rx(int socket);
int16_t tcp_buffer_space_rx(int socket);
int16_t tcp_buffer_used_tx(int socket);
int16_t tcp_buffer_space_tx(int socket);


#define tcp_socket_valid(socket) (((unsigned int) (socket)) < TCP_MAX_SOCKET_COUNT)

#endif
