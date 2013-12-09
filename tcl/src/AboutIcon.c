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

#include <alljoyn/about/AboutIcon.h>

/*
 * Following definitions are read by the application.
 */

static const char* const AboutIconInterface[] = {
    "org.alljoyn.Icon",
    "@Version>q",
    "@MimeType>s",
    "@Size>u",
    "?GetUrl >s",
    "?GetContent >ay",
    NULL
};

const AJ_InterfaceDescription AboutIconInterfaces[] = {
    AJ_PropertiesIface,
    AboutIconInterface,
    NULL
};

/*
 * Handles a property GET request so marshals the property value to return
 */
AJ_Status AboutIcon_PropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    if (propId == ABOUT_ICON_VERSION_PROP) {
        uint16_t q = 1;
        return AJ_MarshalArgs(replyMsg, "q", q);
    } else if (propId == ABOUT_ICON_MIMETYPE_PROP) {
        return AJ_MarshalArgs(replyMsg, "s", aboutIconMimetype);
    } else if (propId == ABOUT_ICON_SIZE_PROP) {
        uint32_t u = aboutIconContentSize;
        return AJ_MarshalArgs(replyMsg, "u", u);
    } else {
        return AJ_ERR_UNEXPECTED;
    }
}

/*
 * Handles a property SET request so unmarshals the property value provided
 */
AJ_Status AboutIcon_PropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AboutIcon_GetContent(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJ_Message reply;
    uint32_t u = (uint32_t) aboutIconContentSize;

    AJ_Printf("AboutIcon_GetContent()\n");
    do {
        CHECK(AJ_MarshalReplyMsg(msg, &reply));
        CHECK(AJ_DeliverMsgPartial(&reply, u + 4));
        CHECK(AJ_MarshalRaw(&reply, &u, 4));
        int i = 0;
        for (; i < aboutIconContentSize; i++) {
            CHECK(AJ_MarshalRaw(&reply, &(aboutIconContent[i]), 1));
        }
        CHECK(AJ_DeliverMsg(&reply));
    } while (0);

    return status;
}

AJ_Status AboutIcon_GetUrl(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJ_Message reply;

    AJ_Printf("AboutIcon_GetUrl()\n");

    do {
        CHECK(AJ_MarshalReplyMsg(msg, &reply));
        CHECK(AJ_MarshalArgs(&reply, "s", aboutIconUrl));
        CHECK(AJ_DeliverMsg(&reply));
    } while (0);

    return status;
}


