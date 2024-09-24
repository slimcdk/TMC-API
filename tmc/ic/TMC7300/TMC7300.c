/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC7300.h"

// => UART wrapper
extern void tmc7300_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

#ifdef TMC_API_EXTERNAL_CRC_TABLE
extern const uint8_t tmcCRCTable_Poly7Reflected[256];
#else
const uint8_t tmcCRCTable_Poly7Reflected[256] = {
        0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75, 0x0E, 0x9F, 0xED, 0x7C, 0x09, 0x98, 0xEA, 0x7B,
        0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69, 0x12, 0x83, 0xF1, 0x60, 0x15, 0x84, 0xF6, 0x67,
        0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D, 0x36, 0xA7, 0xD5, 0x44, 0x31, 0xA0, 0xD2, 0x43,
        0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51, 0x2A, 0xBB, 0xC9, 0x58, 0x2D, 0xBC, 0xCE, 0x5F,
        0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05, 0x7E, 0xEF, 0x9D, 0x0C, 0x79, 0xE8, 0x9A, 0x0B,
        0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19, 0x62, 0xF3, 0x81, 0x10, 0x65, 0xF4, 0x86, 0x17,
        0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D, 0x46, 0xD7, 0xA5, 0x34, 0x41, 0xD0, 0xA2, 0x33,
        0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21, 0x5A, 0xCB, 0xB9, 0x28, 0x5D, 0xCC, 0xBE, 0x2F,
        0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95, 0xEE, 0x7F, 0x0D, 0x9C, 0xE9, 0x78, 0x0A, 0x9B,
        0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89, 0xF2, 0x63, 0x11, 0x80, 0xF5, 0x64, 0x16, 0x87,
        0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD, 0xD6, 0x47, 0x35, 0xA4, 0xD1, 0x40, 0x32, 0xA3,
        0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1, 0xCA, 0x5B, 0x29, 0xB8, 0xCD, 0x5C, 0x2E, 0xBF,
        0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5, 0x9E, 0x0F, 0x7D, 0xEC, 0x99, 0x08, 0x7A, 0xEB,
        0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9, 0x82, 0x13, 0x61, 0xF0, 0x85, 0x14, 0x66, 0xF7,
        0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD, 0xA6, 0x37, 0x45, 0xD4, 0xA1, 0x30, 0x42, 0xD3,
        0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1, 0xBA, 0x2B, 0x59, 0xC8, 0xBD, 0x2C, 0x5E, 0xCF,
};
#endif

{
}





}

void tmc7300_init(TMC7300TypeDef *tmc7300, uint8_t channel, ConfigurationTypeDef *tmc7300_config, const int32_t *registerResetState)
{
    tmc7300->config               = tmc7300_config;
    tmc7300->config->callback     = NULL;
    tmc7300->config->channel      = channel;
    tmc7300->config->configIndex  = 0;
    tmc7300->config->state        = CONFIG_RESET;

    // Default slave address: 0
    tmc7300->slaveAddress = 0;

    // Start in standby
    tmc7300->standbyEnabled = 1;

    int32_t i;
    for(i = 0; i < TMC7300_REGISTER_COUNT; i++)
    {
        tmc7300->registerAccess[i]      = tmc7300_defaultRegisterAccess[i];
        tmc7300->registerResetState[i]  = registerResetState[i];
    }
}

// Fill the shadow registers of hardware preset registers.
// Only needed if you want to read out those registers to display the value
// (e.g. for the TMCL IDE register browser)
static void fillShadowRegisters(TMC7300TypeDef *tmc7300)
{
    // Check if we have constants defined
    if(ARRAY_SIZE(tmc7300_registerConstants) == 0)
        return;

    size_t i, j = 0;
    for(i = 0; i < TMC7300_REGISTER_COUNT; i++)
    {
        // We only need to worry about hardware preset registers
        // that have not yet been written (no dirty bit) here.
        if(!TMC_IS_PRESET(tmc7300->registerAccess[i]) || TMC_IS_DIRTY(tmc7300->registerAccess[i]))
            continue;

        // Search the constant list for the current address. With the constant
        // list being sorted in ascended order, we can walk through the list
        // until the entry with an address equal or greater than i
        while (j < ARRAY_SIZE(tmc7300_registerConstants) && (tmc7300_registerConstants[j].address < i))
        {
            j++;
        }

        // If we have an entry for our current address, write the constant
        if (tmc7300_registerConstants[j].address == i)
        {
            tmc7300->config->shadowRegister[i] = tmc7300_registerConstants[j].value;
        }
    }
}

/************************************************************* read / write Implementation *********************************************************************/
static void writeConfiguration(TMC7300TypeDef *tmc7300)
{
    uint8_t *ptr = &tmc7300->config->configIndex;
    const int32_t *settings;

    // Find the next register to reset/restore
    if (tmc7300->config->state == CONFIG_RESET)
    {
        settings = tmc7300->registerResetState;
        // Find the next resettable register
        while((*ptr < TMC7300_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc7300->registerAccess[*ptr]))
        {
            (*ptr)++;
        }
    }
    else
    {
        // Do not restore while in standby
        if (tmc7300->standbyEnabled)
            return;

static int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress);
static void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value );
static uint8_t CRC8(uint8_t *data, uint32_t bytes);
        settings = tmc7300->config->shadowRegister;
        // Find the next restorable register
        while((*ptr < TMC7300_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc7300->registerAccess[*ptr]))
        {
            (*ptr)++;
        }
    }

int32_t tmc7300_readRegister(uint16_t icID, uint8_t address)
    if(*ptr < TMC7300_REGISTER_COUNT)
    {
        // Reset/restore the found register
        tmc7300_writeInt(tmc7300, *ptr, settings[*ptr]);
        (*ptr)++;
    }
    else
    {
        fillShadowRegisters(tmc7300);

        // Reset/restore complete -> call the callback if set
        if (tmc7300->config->callback)
        {
            ((tmc7300_callback)tmc7300->config->callback)(tmc7300, tmc7300->config->state);
        }

        if (tmc7300->config->state == CONFIG_RESET)
        {
            // Reset done -> Perform a restore
            tmc7300->config->state        = CONFIG_RESTORE;
            tmc7300->config->configIndex  = 0;
        }
        else
        {
            // Restore done -> configuration complete
            tmc7300->config->state = CONFIG_READY;
        }
    }
}

void tmc7300_setRegisterResetState(TMC7300TypeDef *tmc7300, const int32_t *resetState)
{
    return readRegisterUART(icID, address);
    size_t i;
    for (i = 0; i < TMC7300_REGISTER_COUNT; i++)
    {
        tmc7300->registerResetState[i] = resetState[i];
    }
}

void tmc7300_setCallback(TMC7300TypeDef *tmc7300, tmc7300_callback callback)
void tmc7300_writeRegister(uint16_t icID, uint8_t address, int32_t value )
{
    writeRegisterUART(icID, address, value);
    tmc7300->config->callback = (tmc_callback_config) callback;
}

void tmc7300_periodicJob(TMC7300TypeDef *tmc7300, uint32_t tick)
int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress)
{
    uint32_t value;
    UNUSED(tick);

    // Read from cache for registers with write-only access
    if (tmc7300_cache(icID, TMC7300_CACHE_READ, registerAddress, &value))
        return value;
    if(tmc7300->config->state != CONFIG_READY)
    {
        writeConfiguration(tmc7300);
        return;
    }
}

    uint8_t data[8] = { 0 };
    registerAddress = registerAddress & TMC7300_ADDRESS_MASK;
uint8_t tmc7300_reset(TMC7300TypeDef *tmc7300)
{
    // A reset can always happen - even during another reset or restore

    data[0] = 0x05;
    data[1] = tmc7300_getNodeAddress(icID);
    data[2] = registerAddress;
    data[3] = CRC8(data, 3);
    // Reset the dirty bits and wipe the shadow registers
    size_t i;
    for(i = 0; i < TMC7300_REGISTER_COUNT; i++)
    {
        tmc7300->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
        tmc7300->config->shadowRegister[i] = 0;
    }

    if (!tmc7300_readWriteUART(icID, &data[0], 4, 8))
        return tmc7300_shadowRegister[0][registerAddress];
    // Activate the reset config mechanism
    tmc7300->config->state        = CONFIG_RESET;
    tmc7300->config->configIndex  = 0;

    // Byte 0: Sync nibble correct?
    if (data[0] != 0x05)
        return 0;
    return 1;
}

    // Byte 1: Master address correct?
    if (data[1] != 0xFF)
uint8_t tmc7300_restore(TMC7300TypeDef *tmc7300)
{
    // Do not interrupt a reset
    // A reset will transition into a restore anyways
    if(tmc7300->config->state == CONFIG_RESET)
        return 0;

    // Byte 2: Address correct?
    if (data[2] != registerAddress)
        return 0;
    tmc7300->config->state        = CONFIG_RESTORE;
    tmc7300->config->configIndex  = 0;

    // Byte 7: CRC correct?
    if (data[7] != CRC8(data, 7))
        return 0;
    return 1;
}

    return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
uint8_t tmc7300_get_slave(TMC7300TypeDef *tmc7300)
{
    return tmc7300->slaveAddress;
}

void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value )
void tmc7300_set_slave(TMC7300TypeDef *tmc7300, uint8_t slaveAddress)
{
    uint8_t data[8];
    tmc7300->slaveAddress = slaveAddress;
}

    data[0] = 0x05;
    data[1] = tmc7300_getNodeAddress(icID);
    data[2] = registerAddress | TMC7300_WRITE_BIT;
    data[3] = (value >> 24) & 0xFF;
    data[4] = (value >> 16) & 0xFF;
    data[5] = (value >> 8 ) & 0xFF;
    data[6] = (value      ) & 0xFF;
    data[7] = CRC8(data, 7);
uint8_t tmc7300_getStandby(TMC7300TypeDef *tmc7300)
{
    return tmc7300->standbyEnabled;
}

    tmc7300_readWriteUART(icID, &data[0], 8, 0);


    // Write to the shadow register and mark the register dirty
    //Cache the registers with write-only access
    tmc7300_cache(icID, TMC7300_CACHE_WRITE, registerAddress, &value);
void tmc7300_setStandby(TMC7300TypeDef *tmc7300, uint8_t standbyState)
{
    if (tmc7300->standbyEnabled && !standbyState)
    {
        // Just exited standby -> call the restore
        tmc7300_restore(tmc7300);
    }
    tmc7300->standbyEnabled = standbyState;
}

static uint8_t CRC8(uint8_t *data, uint32_t bytes)
uint8_t tmc7300_consistencyCheck(TMC7300TypeDef *tmc7300)
{
    uint8_t result = 0;
    // Config has not yet been written -> it can't be consistent
    if(tmc7300->config->state != CONFIG_READY)
        return 0;

    while(bytes--)
        result = tmcCRCTable_Poly7Reflected[result ^ *data++];
    // Standby is enabled -> registers can't be accessed
    if(tmc7300_getStandby(tmc7300))
        return 0;

    // Flip the result around
    // swap odd and even bits
    result = ((result >> 1) & 0x55) | ((result & 0x55) << 1);
    // swap consecutive pairs
    result = ((result >> 2) & 0x33) | ((result & 0x33) << 2);
    // swap nibbles ...
    result = ((result >> 4) & 0x0F) | ((result & 0x0F) << 4);
    // If the PWM_DIRECT bit is no longer set, report an error
    if (TMC7300_FIELD_READ(tmc7300, TMC7300_GCONF, TMC7300_PWM_DIRECT_MASK, TMC7300_PWM_DIRECT_SHIFT) == 0)
        return 1;

    return result;
    // No inconsistency detected
    return 0;
}
