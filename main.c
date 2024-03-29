/*
 * SPDX-FileType: SOURCE
 * SPDX-FileCopyrightText: Copyright (C) 2024 Volkert de Buisonjé
 * SPDX-FileContributor: Volkert de Buisonjé
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdint.h>
#include "types.h"
#include "virtio/virtio.h"
#include "pci/pci.h"

const u16 PCI_VENDOR_ID_VIRTIO = 0x1AF4;
const u16 PCI_DEVICE_ID_VIRTIO_SND = 0x1059; // 0x1040 + 0x19

int detect_and_list_pci_devices();

int main(void)
{
    printf("hello, world\n");

    return detect_and_list_pci_devices();
}

/**
 * Adapted from the following example code:
 *
 * The PCI Library -- Example of use (simplistic lister of PCI devices)
 *
 * Written by Martin Mares and put to public domain. You can do
 * with it anything you want, but I don't give you any warranty.
 *
 * Source: https://github.com/pciutils/pciutils/blob/master/example.c
 */
int detect_and_list_pci_devices() {
    struct pci_access *pacc;
    struct pci_dev *dev;
    unsigned int c;

    pacc = pci_alloc();		/* Get the pci_access structure */
    /* Set all options you want -- here we stick with the defaults */
    pacc->debugging = 1; /* ...except that we enable debugging by setting this to something other than 0 */
    pci_init(pacc);		/* Initialize the PCI library */
    pci_scan_bus(pacc);		/* We want to get the list of devices */
    for (dev=pacc->devices; dev; dev=dev->next)	/* Iterate over all devices */
    {
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);	/* Fill in header info we need */
        c = pci_read_byte(dev, PCI_INTERRUPT_PIN);				/* Read config register directly */
        printf("%04x:%02x:%02x.%d vendor=%04x device=%04x class=%04x irq=%d (pin %d) base0=%lx",
               dev->domain, dev->bus, dev->dev, dev->func, dev->vendor_id, dev->device_id,
               dev->device_class, dev->irq, c, (long) dev->base_addr[0]);

        printf("\n");

        if (dev->vendor_id == PCI_VENDOR_ID_VIRTIO) {
            if (dev->device_id == PCI_DEVICE_ID_VIRTIO_SND) {
                printf("This *is* a VirtIO sound device (virtio-snd-pci)!\n");
            } else {
                printf("This is a VirtIO device, but *not* a virtio-snd-pci device.\n");
            }
        }
    }
    pci_cleanup(pacc);		/* Close everything */
    return 0;
}
