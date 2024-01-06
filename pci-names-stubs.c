//
// Created by volkert on 1/6/24.
// We don't need PCI name lookup functionality in this project, so provide stubs for this to satisfy init.c
//

#include "pci/pci.h"

static void
pci_init_name_list_path(struct pci_access *a)
{
}

void
pci_set_name_list_path(struct pci_access *a, char *name, int to_be_freed)
{
}

void
pci_free_name_list(struct pci_access *a)
{
}
