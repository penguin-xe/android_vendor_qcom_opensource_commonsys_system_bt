/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  ​​​​​Changes from Qualcomm Innovation Center are provided under the following license:
 *  Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 *  SPDX-License-Identifier: BSD-3-Clause-Clear
 *
 ******************************************************************************/
/*******************************************************************************
 *
 * Changes from Qualcomm Innovation Center are provided under the following license:
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 *
 *******************************************************************************/

#ifndef BTIF_STORAGE_H
#define BTIF_STORAGE_H

#include <bluetooth/uuid.h>
#include <hardware/bluetooth.h>

#include "bt_target.h"
#include "bt_types.h"

/*******************************************************************************
 *  Constants & Macros
 ******************************************************************************/
#define BT_PROPERTY_REM_DEViCE_VALID_ADDR 0xA3
#define BT_PROPERTY_GROUP_DETAILS 0x12
#define BT_PROPERTY_ADV_AUDIO_UUIDS 0xA0
#define BT_PROPERTY_ADV_AUDIO_ACTION_UUID 0xA1
#define BT_PROPERTY_UUID_ON_TRANSPORT 0xA2
#define BT_PROPERTY_REM_DEV_IDENT_BD_ADDR 0xA4
#define BT_PROPERTY_REM_UUID_BY_TRANSPORT 0xA5
#define BT_PROPERTY_REM_DEV_IS_ADV_AUDIO 0xA6

#define BTIF_STORAGE_FILL_PROPERTY(p_prop, t, l, p_v) \
  do {                                                \
    (p_prop)->type = (t);                             \
    (p_prop)->len = (l);                              \
    (p_prop)->val = (p_v);                            \
  } while (0)

/*******************************************************************************
 *  Functions
 ******************************************************************************/

/*******************************************************************************
 *
 * Function         btif_storage_get_adapter_property
 *
 * Description      BTIF storage API - Fetches the adapter property->type
 *                  from NVRAM and fills property->val.
 *                  Caller should provide memory for property->val and
 *                  set the property->val
 *
 * Returns          BT_STATUS_SUCCESS if the fetch was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_get_adapter_property(bt_property_t* property);

/*******************************************************************************
 *
 * Function         btif_storage_set_adapter_property
 *
 * Description      BTIF storage API - Stores the adapter property
 *                  to NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the store was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_set_adapter_property(bt_property_t* property);

/*******************************************************************************
 *
 * Function         btif_storage_get_remote_device_property
 *
 * Description      BTIF storage API - Fetches the remote device property->type
 *                  from NVRAM and fills property->val.
 *                  Caller should provide memory for property->val and
 *                  set the property->val
 *
 * Returns          BT_STATUS_SUCCESS if the fetch was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_get_remote_device_property(
    const RawAddress* remote_bd_addr, bt_property_t* property);

/*******************************************************************************
 *
 * Function         btif_storage_set_remote_device_property
 *
 * Description      BTIF storage API - Stores the remote device property
 *                  to NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the store was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_set_remote_device_property(
    const RawAddress* remote_bd_addr, bt_property_t* property);

/*******************************************************************************
 *
 * Function         btif_storage_set_remote_device_properties
 *
 * Description      BTIF storage API - Stores the remote device properties
 *                  to NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the store was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_set_remote_device_properties(
    const RawAddress* remote_bd_addr, bt_property_t* property, int number);
/*******************************************************************************
 * Function         btif_storage_get_io_caps
 *
 * Description      BTIF storage API - Fetches the local Input/Output
 *                  capabilities of the device.
 *
 * Returns          Returns local IO Capability of device. If not stored,
 *                  returns BTM_LOCAL_IO_CAPS.
 *
 ******************************************************************************/
uint8_t btif_storage_get_local_io_caps();

/*******************************************************************************
 *
 * Function         btif_storage_get_io_caps_ble
 *
 * Description      BTIF storage API - Fetches the local Input/Output
 *                  capabilities of the BLE device.
 *
 * Returns          Returns local IO Capability of BLE device. If not stored,
 *                  returns BTM_LOCAL_IO_CAPS_BLE.
 *
 ******************************************************************************/
uint8_t btif_storage_get_local_io_caps_ble();

/*******************************************************************************
 *
 * Function         btif_storage_add_remote_device
 *
 * Description      BTIF storage API - Adds a newly discovered device to
 *                  track along with the timestamp. Also, stores the various
 *                  properties - RSSI, BDADDR, NAME (if found in EIR)
 *
 * Returns          BT_STATUS_SUCCESS if successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_add_remote_device(const RawAddress* remote_bd_addr,
                                           uint32_t num_properties,
                                           bt_property_t* properties);

/*******************************************************************************
 *
 * Function         btif_storage_add_bonded_device
 *
 * Description      BTIF storage API - Adds the newly bonded device to NVRAM
 *                  along with the link-key, Key type and Pin key length
 *
 * Returns          BT_STATUS_SUCCESS if the store was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_add_bonded_device(RawAddress* remote_bd_addr,
                                           LinkKey link_key, uint8_t key_type,
                                           uint8_t pin_length);

/*******************************************************************************
 *
 * Function         btif_storage_remove_bonded_device
 *
 * Description      BTIF storage API - Deletes the bonded device from NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the deletion was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_remove_bonded_device(const RawAddress* remote_bd_addr);

/*******************************************************************************
**
** Function         btif_storage_is_device_bonded
**
* Description      BTIF storage API - checks if device present in bonded list
**
** Returns         BT_STATUS_SUCCESS if the device bonded
**                 BT_STATUS_FAIL otherwise
**
*******************************************************************************/
bt_status_t btif_storage_is_device_bonded(RawAddress *remote_bd_addr);
/*******************************************************************************
**
 * Function         btif_storage_remove_bonded_device
 *
 * Description      BTIF storage API - Deletes the bonded device from NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the deletion was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_load_bonded_devices(void);

/*******************************************************************************
 *
 * Function         btif_storage_set_hid_connection_policy
 *
 * Description      Stores connection policy info in nvram
 *
 * Returns          BT_STATUS_SUCCESS
 *
 ******************************************************************************/
bt_status_t btif_storage_set_hid_connection_policy(const RawAddress& addr,
                                                   bool reconnect_allowed);
/*******************************************************************************
 *
 * Function         btif_storage_get_hid_connection_policy
 *
 * Description      get connection policy info from nvram
 *
 * Returns          BT_STATUS_SUCCESS
 *
 ******************************************************************************/
bt_status_t btif_storage_get_hid_connection_policy(const RawAddress& addr,
                                                   bool* reconnect_allowed);

/*******************************************************************************
 *
 * Function         btif_storage_add_hid_device_info
 *
 * Description      BTIF storage API - Adds the hid information of bonded hid
 *                  devices-to NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the store was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/

bt_status_t btif_storage_add_hid_device_info(
    RawAddress* remote_bd_addr, uint16_t attr_mask, uint8_t sub_class,
    uint8_t app_id, uint16_t vendor_id, uint16_t product_id, uint16_t version,
    uint8_t ctry_code, uint16_t ssr_max_latency, uint16_t ssr_min_tout,
    uint16_t dl_len, uint8_t* dsc_list);

/*******************************************************************************
 *
 * Function         btif_storage_load_bonded_hid_info
 *
 * Description      BTIF storage API - Loads hid info for all the bonded devices
 *                  from NVRAM and adds those devices  to the BTA_HH.
 *
 * Returns          BT_STATUS_SUCCESS if successful, BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_load_bonded_hid_info(void);

/*******************************************************************************
 *
 * Function         btif_storage_remove_hid_info
 *
 * Description      BTIF storage API - Deletes the bonded hid device info from
 *                  NVRAM
 *
 * Returns          BT_STATUS_SUCCESS if the deletion was successful,
 *                  BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_remove_hid_info(const RawAddress& remote_bd_addr);

/** Loads information about bonded hearing aid devices */
void btif_storage_load_bonded_hearing_aids();

/** Deletes the bonded hearing aid device info from NVRAM */
void btif_storage_remove_hearing_aid(const RawAddress& address);

/** Set/Unset the hearing aid device HEARING_AID_IS_Accept_LISTED flag. */
void btif_storage_set_hearing_aid_acceptlist(const RawAddress& address,
                                             bool add_to_acceptlist);

/** Remove client supported features */
void btif_storage_remove_gatt_cl_supp_feat(const RawAddress& bd_addr);

/** Store last server database hash for remote client */
void btif_storage_set_gatt_cl_db_hash(const RawAddress& bd_addr, Octet16 hash);

/** Get last server database hash for remote client */
Octet16 btif_storage_get_gatt_cl_db_hash(const RawAddress& bd_addr);

/** Remove last server database hash for remote client */
void btif_storage_remove_gatt_cl_db_hash(const RawAddress& bd_addr);

/** Get the hearing aid device properties. */
bool btif_storage_get_hearing_aid_prop(
    const RawAddress& address, uint8_t* capabilities, uint64_t* hi_sync_id,
    uint16_t* render_delay, uint16_t* preparation_delay, uint16_t* codecs);

/** Store service changed CCCD value for remote client */
void btif_storage_set_svc_chg_cccd(const RawAddress& bd_addr, uint8_t cccd);

/** Get service changed CCCD value for remote client */
uint8_t btif_storage_get_svc_chg_cccd(const RawAddress& bda);

/** Remove service changed CCCD value for remote client */
void btif_storage_remove_svc_chg_cccd(const RawAddress& bd_addr);

/* Set Encrypted Data Key Material CCCD value for remote client */
void btif_storage_set_encr_data_cccd(const RawAddress& bd_addr, uint8_t cccd);

/* Get Encrypted Data Key Material CCCD value for remote client */
uint8_t btif_storage_get_encr_data_cccd(const RawAddress& bd_addr);

/** Store encryption key material char value of remote server */
bt_status_t btif_storage_set_enc_key_material(RawAddress* remote_bd_addr,
                                              uint8_t* key,
                                              uint8_t key_length);

/** Get encryption key materail char value of remote server */
bt_status_t btif_storage_get_enc_key_material(RawAddress* remote_bd_addr,
                                              uint8_t* key_value,
                                              int* key_length);

/** Remove encryption key material char value of remote server */
bt_status_t btif_storage_remove_enc_key_material(const RawAddress* remote_bd_addr);

/*******************************************************************************
 *
 * Function         btif_storage_is_retricted_device
 *
 * Description      BTIF storage API - checks if this device is a restricted
 *                  device
 *
 * Returns          true  if the device is labled as restricted
 *                  false otherwise
 *
 ******************************************************************************/
bool btif_storage_is_restricted_device(const RawAddress* remote_bd_addr);

uint32_t btif_storage_get_num_bonded_devices(void);

bt_status_t btif_storage_add_ble_bonding_key(RawAddress* remote_bd_addr,
                                             const uint8_t* key,
                                             uint8_t key_type,
                                             uint8_t key_length);
bt_status_t btif_storage_get_ble_bonding_key(const RawAddress& remote_bd_addr,
                                             uint8_t key_type,
                                             uint8_t* key_value,
                                             int key_length);

bt_status_t btif_storage_add_ble_local_key(const Octet16& key,
                                           uint8_t key_type);
bt_status_t btif_storage_remove_ble_bonding_keys(
    const RawAddress* remote_bd_addr);
bt_status_t btif_storage_remove_ble_local_keys(void);
bt_status_t btif_storage_get_ble_local_key(uint8_t key_type,
                                           Octet16* key_value);

bt_status_t btif_storage_get_remote_addr_type(const RawAddress* remote_bd_addr,
                                              int* addr_type);

bt_status_t btif_storage_set_remote_addr_type(const RawAddress* remote_bd_addr,
                                              uint8_t addr_type);

/*******************************************************************************
 * Function         btif_storage_load_hidd
 *
 * Description      Loads hidd bonded device and "plugs" it into hidd
 *
 * Returns          BT_STATUS_SUCCESS if successful, BT_STATUS_FAIL otherwise
 *
 ******************************************************************************/
bt_status_t btif_storage_load_hidd(void);

/*******************************************************************************
 *
 * Function         btif_storage_set_hidd
 *
 * Description      Stores hidd bonded device info in nvram.
 *
 * Returns          BT_STATUS_SUCCESS
 *
 ******************************************************************************/

bt_status_t btif_storage_set_hidd(const RawAddress& remote_bd_addr);

/*******************************************************************************
 *
 * Function         btif_storage_remove_hidd
 *
 * Description      Removes hidd bonded device info from nvram
 *
 * Returns          BT_STATUS_SUCCESS
 *
 ******************************************************************************/

bt_status_t btif_storage_remove_hidd(RawAddress* remote_bd_addr);

// Gets the device name for a given Bluetooth address |bd_addr|.
// The device name (if found) is stored in |name|.
// Returns true if the device name is found, othervise false.
// Note: |name| should point to a buffer that can store string of length
// |BTM_MAX_REM_BD_NAME_LEN|.
bool btif_storage_get_stored_remote_name(const RawAddress& bd_addr, char* name);

/*******************************************************************************
 *
 * Function         btif_storage_add_eatt_support
 *
 * Description      BTIF storage API - Adds an EATT supported device to
 *                  track.
 *
 * Returns          void
 *
 *
 ******************************************************************************/
void btif_storage_add_eatt_support(const RawAddress& bd_addr);

/*******************************************************************************
 *
 * Function         btif_storage_load_bonded_eatt_devices
 *
 * Description       BTIF storage API - Loads EATT supported devices
 *                  from NVRAM.
 *
 * Returns          void
 *
 *
 ******************************************************************************/
void btif_storage_load_bonded_eatt_devices();

/*******************************************************************************
 *
 * Function         btif_storage_get_cl_supp_feat
 *
 * Description      BTIF storage API - Fetches the GATT client supported features
 *                  characteristic value from NVRAM.
  *
 * Returns          client supported features char value
 *
 ******************************************************************************/
uint8_t btif_storage_get_cl_supp_feat(const RawAddress& bda);

/*******************************************************************************
 *
 * Function         btif_storage_set_cl_supp_feat
 *
 * Description      BTIF storage API - Stores the GATT client supported features
 *                  characteristic value in NVRAM.
  *
 * Returns          void
 *
 ******************************************************************************/
void btif_storage_set_cl_supp_feat(const RawAddress& bda, uint8_t value);

/******************************************************************************
 * Exported for unit tests
 *****************************************************************************/
size_t btif_split_uuids_string(const char* str, bluetooth::Uuid* p_uuid,
                               size_t max_uuids);

RawAddress btif_get_map_address(RawAddress bda);
int btif_get_is_adv_audio_pair_info(RawAddress bda);

#endif /* BTIF_STORAGE_H */
