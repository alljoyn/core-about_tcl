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

#include <alljoyn/about/AboutSample.h>
#include <alljoyn/about/AboutService.h>

void About_Init()
{
}

void About_Finish(AJ_BusAttachment* busAttachment)
{
}

AJ_Status About_ConnectedHandler(AJ_BusAttachment* bus)
{
    return AJ_OK;
}

void About_IdleConnectedHandler(AJ_BusAttachment* bus)
{
}

Service_Status About_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status*msgStatus)
{
    Service_Status service_Status = SERVICE_STATUS_HANDLED;

    switch (msg->msgId) {

/* About Service processing */
    case ABOUT_GET_PROP:
        *msgStatus = AJ_BusPropGet(msg, AboutPropGetHandler, NULL);
        break;

    case ABOUT_SET_PROP:
        *msgStatus = AJ_BusPropSet(msg, AboutPropSetHandler, NULL);
        break;

    case ABOUT_GET_ABOUT_DATA:
        *msgStatus = AboutGetAboutData(msg);
        break;

    case ABOUT_GET_OBJECT_DESCRIPTION:
        *msgStatus = AboutGetObjectDescription(msg);
        break;

/* About Icon processing */
    case ABOUT_ICON_GET_PROP:
        *msgStatus = AJ_BusPropGet(msg, AboutIcon_PropGetHandler, NULL);
        break;

    case ABOUT_ICON_SET_PROP:
        *msgStatus = AJ_BusPropSet(msg, AboutIcon_PropSetHandler, NULL);
        break;

    case ABOUT_ICON_GET_CONTENT:
        *msgStatus = AboutIcon_GetContent(msg);
        break;

    case ABOUT_ICON_GET_URL:
        *msgStatus = AboutIcon_GetUrl(msg);
        break;

    default:
        service_Status = SERVICE_STATUS_NOT_HANDLED;
        break;
    }

    return service_Status;
}
