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

#ifndef _ABOUTSERVICE_H_
#define _ABOUTSERVICE_H_

/** @defgroup AboutService
 *
 *  @{
 */

#include <alljoyn/services_common/PropertyStore.h>
#include <alljoyn/about/AboutOEMProvisioning.h>
#include <alljoyn/about/AboutIcon.h>
#include <alljoyn/services_common/Services_Common.h>

/*
 * Following definitions are read by the application.
 */

#define NUM_ABOUT_OBJECTS (1 + NUM_ABOUT_ICON_OBJECTS)

#define ABOUT_APPOBJECTS \
    { "/About",              AboutInterfaces }, \
    ABOUT_ICON_APPOBJECTS

#define ABOUT_ANNOUNCEOBJECTS ABOUT_APPOBJECTS

/*
 * Message identifiers for the method calls this service implements
 */

#define ABOUT_OBJECT_INDEX                                      NUM_PRE_ABOUT_OBJECTS

#define ABOUT_GET_PROP                                          AJ_APP_MESSAGE_ID(ABOUT_OBJECT_INDEX, 0, AJ_PROP_GET)
#define ABOUT_SET_PROP                                          AJ_APP_MESSAGE_ID(ABOUT_OBJECT_INDEX, 0, AJ_PROP_SET)

#define ABOUT_VERSION_PROP                                      AJ_APP_PROPERTY_ID(ABOUT_OBJECT_INDEX, 1, 0)
#define ABOUT_GET_ABOUT_DATA                                    AJ_APP_MESSAGE_ID(ABOUT_OBJECT_INDEX, 1, 1)
#define ABOUT_GET_OBJECT_DESCRIPTION                            AJ_APP_MESSAGE_ID(ABOUT_OBJECT_INDEX, 1, 2)
#define ABOUT_ANNOUNCE                                          AJ_APP_MESSAGE_ID(ABOUT_OBJECT_INDEX, 1, 3)

/*
 * About Feature API
 */

/**
 * published About feature objects and interfaces
 */
extern const AJ_InterfaceDescription AboutInterfaces[];

/**
 * handler for property getters associated with org.alljoyn.About
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutPropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * handler for property setters associated with org.alljoyn.About
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutPropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * handler for GetAboutData request in org.alljoyn.About
 * @param msg
 * @return aj_status
 */
AJ_Status AboutGetAboutData(AJ_Message* msg);

/**
 * handler for GetObjectDescription request in org.alljoyn.About
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutGetObjectDescription(AJ_Message* msg);

/**
 * send Announce signal in org.alljoyn.About
 * @param bus
 * @return aj_status
 */
AJ_Status AboutAnnounce(AJ_BusAttachment* bus);

/**
 * check if should send announcement
 * @return boolean
 */
uint8_t IsShouldAnnounce();

/**
 * set whether should send announcement
 * @param boolean
 */
void SetShouldAnnounce(uint8_t shouldAnnounce);

/** @} */
 #endif // _ABOUTSERVICE_H_
