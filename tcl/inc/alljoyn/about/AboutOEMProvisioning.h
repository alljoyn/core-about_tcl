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

#ifndef _ABOUTOEMPROVISIONING_H_
#define _ABOUTOEMPROVISIONING_H_

/** @defgroup AboutOEMProvisioning
 *
 *  @{
 */

#include <alljoyn.h>

/**
 * Array of objects to be published in the Announcement
 */
extern const AJ_Object AnnounceObjects[];

/**
 * Application ServicePort that will be used for the services' gateway and in the Announcement
 */
extern const uint16_t App_ServicePort;

/**
 * Mime type of the About Device icon
 */
extern const char* aboutIconMimetype;

/**
 * Content of the About Device icon
 */
extern const uint8_t aboutIconContent[];

/**
 * Size of the About Device icon
 */
extern const size_t aboutIconContentSize;

/**
 * url of the icon About Device icon
 */
extern const char* aboutIconUrl;

/**
 * Device manufacture name
 */
extern const char* deviceManufactureName;

/**
 * Device product name
 */
extern const char* deviceProductName;

/** @} */
 #endif /* _ABOUTOEMPROVISIONING_H_ */
