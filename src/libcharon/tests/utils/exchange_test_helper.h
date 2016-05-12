/*
 * Copyright (C) 2016 Tobias Brunner
 * HSR Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * This class and singleton object initializes charon and provides helper
 * methods to create unit tests for IKEv2 exchanges.
 *
 * It also registers special implementations for the kernel_ipsec_t interface,
 * the sender and provides dummy configs and credentials.
 *
 * @defgroup exchange_test_helper exchange_test_helper
 * @{ @ingroup test_utils_c
 */

#ifndef EXCHANGE_TEST_HELPER_H_
#define EXCHANGE_TEST_HELPER_H_

#include <daemon.h>

#include "mock_sender.h"

typedef struct exchange_test_helper_t exchange_test_helper_t;

struct exchange_test_helper_t {

	/**
	 * Sender instance used during tests
	 */
	mock_sender_t *sender;

	/**
	 * Creates an established IKE_SA/CHILD_SA
	 *
	 * @param[out] init		IKE_SA of the initiator
	 * @param[out] resp		IKE_SA of the responder
	 */
	void (*establish_sa)(exchange_test_helper_t *this, ike_sa_t **init,
						 ike_sa_t **resp);

	/**
	 * Pass a message to the given IKE_SA for processing, setting the IKE_SA on
	 * the bus while processing the message.
	 *
	 * @param ike_sa		the IKE_SA receiving the message
	 * @param message		the message, or NULL to pass the next message in the
	 *						send queue (adopted)
	 */
	void (*process_message)(exchange_test_helper_t *this, ike_sa_t *sa,
							message_t *message);
};

/**
 * The one and only instance of the helper object.
 *
 * Set between exchange_test_helper_setup() and exchange_test_helper_teardown()
 * calls.
 */
extern exchange_test_helper_t *exchange_test_helper;

/**
 * Initialize charon and the helper object.
 *
 * @param plugins			plugins to load
 */
void exchange_test_helper_init(char *plugins);

/**
 * Deinitialize the helper object.
 */
void exchange_test_helper_deinit();

#endif /** EXCHANGE_TEST_HELPER_H_ @} */
