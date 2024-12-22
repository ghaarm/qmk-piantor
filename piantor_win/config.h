// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

#define USB_VBUS_PIN GP19

#define SPLIT_HAND_PIN GP17
#define SPLIT_HAND_PIN_LOW_IS_LEFT

#define MASTER_LEFT

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

#define TAPPING_TERM 200  // Zeit (in ms), um zwischen Tap und Hold zu unterscheiden
// #define PERMISSIVE_HOLD  // Erlaubt das Halten von Mod-Taps auch nach Ablauf des Tapping-Terms
// #define HOLD_ON_OTHER_KEY_PRESS

