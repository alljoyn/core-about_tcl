/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef _ABOUTSAMPLE_H_
#define _ABOUTSAMPLE_H_

/** @defgroup About Sample
 *
 *  @{
 */

#include <Apps_Common.h>

/*
 * About Sample API
 */
/**
 * init
 */
void About_Init();
/**
 * connected handler
 * @param bus
 * @return status
 */
AJ_Status About_ConnectedHandler(AJ_BusAttachment* bus);
/**
 * message processing
 * @param bus
 * @param msg
 * @return status
 */
Service_Status About_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status*msgStatus);
/**
 * called while no messages to process
 * @param bus
 */
void About_IdleConnectedHandler(AJ_BusAttachment* bus);
/**
 * handling finish service
 * @param bus
 */
void About_Finish(AJ_BusAttachment* bus);

/** @} */
 #endif // _ABOUTSAMPLE_H_
