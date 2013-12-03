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

#include <alljoyn/about/AboutService.h>

static const char* const AboutInterface[] = {
    "org.alljoyn.About",
    "@Version>q",
    "?GetAboutData <s >a{sv}",
    "?GetObjectDescription >a(oas)",
    "!Announce >q >q >a(oas) >a{sv}",
    NULL
};

static const uint16_t AboutVersion = 1;

const AJ_InterfaceDescription AboutInterfaces[] = {
    AJ_PropertiesIface,
    AboutInterface,
    NULL
};

/*
 * Handles a property GET request so marshals the property value to return
 */
AJ_Status AboutPropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    if (propId == ABOUT_VERSION_PROP) {
        uint16_t q = AboutVersion;
        return AJ_MarshalArgs(replyMsg, "q", q);
    } else {
        return AJ_ERR_UNEXPECTED;
    }
}

/*
 * Handles a property SET request so unmarshals the property value provided
 */
AJ_Status AboutPropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    return AJ_ERR_UNEXPECTED;
}

AJ_Status AboutGetAboutData(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJ_Message reply;
    char* language;
    enum_lang_indecies_t langIndex = ERROR_LANGUAGE_INDEX;

    AJ_Printf("GetAboutData()\n");

    property_store_filter_t filter;
    memset(&filter, 0, sizeof(property_store_filter_t));
    filter.bit0About = TRUE;

    do {
        CHECK(AJ_UnmarshalArgs(msg, "s", &language));
        if (Common_IsLanguageSupported(msg, &reply, language, &langIndex)) {
            CHECK(AJ_MarshalReplyMsg(msg, &reply));
            CHECK(PropertyStore_ReadAll(&reply, filter, langIndex));
        }
        CHECK(AJ_DeliverMsg(&reply));
    } while (0);

    return status;
}

static const char* stripLeadingSecurityDollar(const char* ifaceName)
{
    return ifaceName + (ifaceName && (*ifaceName == '$'));
}

static AJ_Status AboutGetObjectDescriptionInternal(AJ_Message* msg, uint8_t justParse)
{
    AJ_Status status = AJ_OK;
    AJ_Arg structure;
    AJ_Arg array, array2;
    AJ_Message reply;
    int i = 0, j = 1;
    AJ_Message* amsg = NULL;

    if (justParse) {
        amsg = msg;
    } else {
        amsg = &reply;
    }

    do {
        AJ_Printf("ProxyHandleGetInterfaces()\n");
        if (!justParse) CHECK(AJ_MarshalReplyMsg(msg, amsg));

        CHECK(AJ_MarshalContainer(amsg, &array, AJ_ARG_ARRAY));
        AJ_Object current = AnnounceObjects[i];

        for (; current.path != NULL; current = AnnounceObjects[++i]) {

            CHECK(AJ_MarshalContainer(amsg, &structure, AJ_ARG_STRUCT));
            CHECK(AJ_MarshalArgs(amsg, "o", current.path));

            CHECK(AJ_MarshalContainer(amsg, &array2, AJ_ARG_ARRAY));

            if ((current.interfaces[0] != NULL) && (current.interfaces[0] != AJ_PropertiesIface)) {
                CHECK(AJ_MarshalArgs(amsg, "s", stripLeadingSecurityDollar(current.interfaces[0][0])));
                AJ_Printf("ObjPath=%s Iface=%s\n", current.path, stripLeadingSecurityDollar(current.interfaces[0][0]));
            }
            for (j = 1; current.interfaces[j]; j++) {
                CHECK(AJ_MarshalArgs(amsg, "s", stripLeadingSecurityDollar(current.interfaces[j][0])));
                AJ_Printf("ObjPath=%s Iface=%s\n", current.path, stripLeadingSecurityDollar(current.interfaces[j][0]));
            }
            CHECK(AJ_MarshalCloseContainer(amsg, &array2));
            CHECK(AJ_MarshalCloseContainer(amsg, &structure));

        }
        CHECK(AJ_MarshalCloseContainer(amsg, &array));
        if (!justParse) CHECK(AJ_DeliverMsg(amsg));
    } while (0);

    return status;
}

AJ_Status AboutGetObjectDescription(AJ_Message* msg)
{
    return AboutGetObjectDescriptionInternal(msg, FALSE);
}

AJ_Status AboutAnnounce(AJ_BusAttachment* bus)
{
    AJ_Status status = AJ_OK;
    do {
        const char* busUniqueName = AJ_GetUniqueName(bus);
        if (busUniqueName == NULL) {
            AJ_Printf("Failed to GetUniqueName() from a supposedly connected bus\n");
            return AJ_ERR_NULL;
        }
        AJ_Printf("Announce() {sender=%s, port=%d}\n", busUniqueName, App_ServicePort);
        AJ_Message out;
        CHECK(AJ_MarshalSignal(bus, &out, ABOUT_ANNOUNCE, NULL, 0, ALLJOYN_FLAG_SESSIONLESS, 0));
        uint16_t q = AboutVersion;
        CHECK(AJ_MarshalArgs(&out, "q", q));
        q = App_ServicePort;
        CHECK(AJ_MarshalArgs(&out, "q", q));
        CHECK(AboutGetObjectDescriptionInternal(&out, TRUE));
        property_store_filter_t filter;
        memset(&filter, 0, sizeof(property_store_filter_t));
        filter.bit2Announce = TRUE;
        CHECK(PropertyStore_ReadAll(&out, filter, PropertyStore_GetCurrentDefaultLanguageIndex()));
        CHECK(AJ_DeliverMsg(&out));
        CHECK(AJ_CloseMsg(&out));
    } while (0);

    return status;
}

uint8_t bShouldAnnounce = TRUE;

uint8_t IsShouldAnnounce()
{
    return bShouldAnnounce;
}

void SetShouldAnnounce(uint8_t shouldAnnounce)
{
    bShouldAnnounce = shouldAnnounce;
}
