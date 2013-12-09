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

#ifndef _ABOUTICONSERVICE_H_
#define _ABOUTICONSERVICE_H_

/** @defgroup AboutIcon
 *
 *  @{
 */

#include <alljoyn/about/AboutOEMProvisioning.h>
#include <alljoyn/services_common/Services_Common.h>

#define NUM_ABOUT_ICON_OBJECTS 1

#define ABOUT_ICON_APPOBJECTS \
    { "/About/DeviceIcon",   AboutIconInterfaces },

/*
 * Message identifiers for the method calls this application implements
 */

#define ABOUT_ICON_OBJECT_INDEX                         NUM_PRE_ABOUT_OBJECTS + 1

#define ABOUT_ICON_GET_PROP                             AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 0, AJ_PROP_GET)
#define ABOUT_ICON_SET_PROP                             AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 0, AJ_PROP_SET)

#define ABOUT_ICON_VERSION_PROP                         AJ_APP_PROPERTY_ID(ABOUT_ICON_OBJECT_INDEX, 1, 0)
#define ABOUT_ICON_MIMETYPE_PROP                        AJ_APP_PROPERTY_ID(ABOUT_ICON_OBJECT_INDEX, 1, 1)
#define ABOUT_ICON_SIZE_PROP                            AJ_APP_PROPERTY_ID(ABOUT_ICON_OBJECT_INDEX, 1, 2)

#define ABOUT_ICON_GET_URL                              AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 1, 3)
#define ABOUT_ICON_GET_CONTENT                          AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 1, 4)

/*
 * AboutIcon API
 */

/**
 * published About Icon interfaces that will be announced
 */
extern const AJ_InterfaceDescription AboutIconInterfaces[];

/**
 * handler for property getters associated with org.alljoyn.Icon
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutIcon_PropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * handler for property setters associated with org.alljoyn.Icon
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutIcon_PropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * handler for GetContent request in org.alljoyn.Icon
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutIcon_GetContent(AJ_Message* msg);

/**
 * handler for GetUrl request in org.alljoyn.Icon
 * @param replyMsg
 * @param propId
 * @param context
 * @return aj_status
 */
AJ_Status AboutIcon_GetUrl(AJ_Message* msg);

/** @} */

 #endif // _ABOUTICONSERVICE_H_
