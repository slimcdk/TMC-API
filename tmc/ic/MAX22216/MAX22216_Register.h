/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


// Autogenerated C header for registers in MAX22216
// Generator version: 1.0

#ifndef MAX22216_REGISTERS
#define MAX22216_REGISTERS

#define MAX22216_GLOBAL_CTRL         0x00
#define MAX22216_GLOBAL_CFG          0x01
#define MAX22216_STATUS              0x02
#define MAX22216_STATUS_CFG          0x03
#define MAX22216_DC_H2L              0x04
#define MAX22216_VM_MONITOR          0x05
#define MAX22216_VM_THRESHOLD        0x06
#define MAX22216_F_AC                0x07
#define MAX22216_U_AC_SCAN           0x08
#define MAX22216_CFG_DC_L2H_0        0x09
#define MAX22216_CFG_DC_H_0          0x0A
#define MAX22216_CFG_DC_L_0          0x0B
#define MAX22216_CFG_L2H_TIME_0      0x0C
#define MAX22216_CFG_CTRL0_0         0x0D
#define MAX22216_CFG_CTRL1_0         0x0E
#define MAX22216_CFG_DPM0_0          0x0F
#define MAX22216_CFG_DPM1_0          0x10
#define MAX22216_CFG_IDC_THLD_0      0x11
#define MAX22216_CFG_R_THLD_0        0x12
#define MAX22216_CFG_IND_0_0         0x13
#define MAX22216_CFG_IND_1_0         0x14
#define MAX22216_CFG_P_0             0x15
#define MAX22216_CFG_I_0             0x16
#define MAX22216_CFG_DC_L2H_1        0x17
#define MAX22216_CFG_DC_H_1          0x18
#define MAX22216_CFG_DC_L_1          0x19
#define MAX22216_CFG_L2H_TIME_1      0x1A
#define MAX22216_CFG_CTRL0_1         0x1B
#define MAX22216_CFG_CTRL1_1         0x1C
#define MAX22216_CFG_DPM0_1          0x1D
#define MAX22216_CFG_DPM1_1          0x1E
#define MAX22216_CFG_IDC_THLD_1      0x1F
#define MAX22216_CFG_R_THLD_1        0x20
#define MAX22216_CFG_IND_0_1         0x21
#define MAX22216_CFG_IND_1_1         0x22
#define MAX22216_CFG_P_1             0x23
#define MAX22216_CFG_I_1             0x24
#define MAX22216_CFG_DC_L2H_2        0x25
#define MAX22216_CFG_DC_H_2          0x26
#define MAX22216_CFG_DC_L_2          0x27
#define MAX22216_CFG_L2H_TIME_2      0x28
#define MAX22216_CFG_CTRL0_2         0x29
#define MAX22216_CFG_CTRL1_2         0x2A
#define MAX22216_CFG_DPM0_2          0x2B
#define MAX22216_CFG_DPM1_2          0x2C
#define MAX22216_CFG_IDC_THLD_2      0x2D
#define MAX22216_CFG_R_THLD_2        0x2E
#define MAX22216_CFG_IND_0_2         0x2F
#define MAX22216_CFG_IND_1_2         0x30
#define MAX22216_CFG_P_2             0x31
#define MAX22216_CFG_I_2             0x32
#define MAX22216_CFG_DC_L2H_3        0x33
#define MAX22216_CFG_DC_H_3          0x34
#define MAX22216_CFG_DC_L_3          0x35
#define MAX22216_CFG_L2H_TIME_3      0x36
#define MAX22216_CFG_CTRL0_3         0x37
#define MAX22216_CFG_CTRL1_3         0x38
#define MAX22216_CFG_DPM0_3          0x39
#define MAX22216_CFG_DPM1_3          0x3A
#define MAX22216_CFG_IDC_THLD_3      0x3B
#define MAX22216_CFG_R_THLD_3        0x3C
#define MAX22216_CFG_IND_0_3         0x3D
#define MAX22216_CFG_IND_1_3         0x3E
#define MAX22216_CFG_P_3             0x3F
#define MAX22216_CFG_I_3             0x40
#define MAX22216_I_DPM_PEAK_0        0x41
#define MAX22216_I_DPM_VALLEY_0      0x42
#define MAX22216_TRAVEL_TIME_0       0x43
#define MAX22216_REACTION_TIME_0     0x44
#define MAX22216_I_MONITOR_0         0x45
#define MAX22216_I_AC_0              0x47
#define MAX22216_RES_0               0x48
#define MAX22216_PWM_DUTY_0          0x49
#define MAX22216_I_DPM_PEAK_1        0x4A
#define MAX22216_I_DPM_VALLEY_1      0x4B
#define MAX22216_TRAVEL_TIME_1       0x4C
#define MAX22216_REACTION_TIME_1     0x4D
#define MAX22216_I_MONITOR_1         0x4E
#define MAX22216_I_AC_1              0x50
#define MAX22216_RES_1               0x51
#define MAX22216_PWM_DUTY_1          0x52
#define MAX22216_I_DPM_PEAK_2        0x53
#define MAX22216_I_DPM_VALLEY_2      0x54
#define MAX22216_TRAVEL_TIME_2       0x55
#define MAX22216_REACTION_TIME_2     0x56
#define MAX22216_I_MONITOR_2         0x57
#define MAX22216_I_AC_2              0x59
#define MAX22216_RES_2               0x5A
#define MAX22216_PWM_DUTY_2          0x5B
#define MAX22216_I_DPM_PEAK_3        0x5C
#define MAX22216_I_DPM_VALLEY_3      0x5D
#define MAX22216_TRAVEL_TIME_3       0x5E
#define MAX22216_REACTION_TIME_3     0x5F
#define MAX22216_I_MONITOR_3         0x60
#define MAX22216_I_AC_3              0x62
#define MAX22216_RES_3               0x63
#define MAX22216_PWM_DUTY_3          0x64
#define MAX22216_FAULT0              0x65
#define MAX22216_FAULT1              0x66

#define MAX22216_OTP_CONTROL         0x68
#define MAX22216_OTP_STATUS          0x69
#define MAX22216_OTP_DATA0           0x7A
#define MAX22216_OTP_DATA1           0x7B
#define MAX22216_OTP_ADDR            0x7C

#endif
