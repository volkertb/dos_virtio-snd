# SPDX-FileType: SOURCE
# SPDX-FileCopyrightText: Copyright (C) 2024 Volkert de Buisonjé
# SPDX-FileContributor: Volkert de Buisonjé
# SPDX-License-Identifier: Apache-2.0

virtsnd.exe:
	gcc pci/init.c -o pci_init.o -c -D PCI_OS_DJGPP -D PCI_HAVE_PM_INTEL_CONF
	gcc pci/access.c -o pci_access.o -c -D PCI_OS_DJGPP
	gcc pci/params.c -o pci_params.o -c -D PCI_OS_DJGPP
	gcc pci/caps.c -o pci_caps.o -c -D PCI_OS_DJGPP
	gcc pci/i386-ports.c -o pci_i386_ports.o -c -D PCI_OS_DJGPP
	gcc pci/generic.c -o pci_generic.o -c -D PCI_OS_DJGPP
	gcc pci-names-stubs.c -o pci_names_stubs.o -c
	gcc main.c -o main.o -c
	gcc -o virtsnd.exe main.o pci_init.o pci_access.o pci_params.o pci_caps.o \
	pci_i386_ports.o pci_generic.o pci_names_stubs.o

clean:
	rm -f *.o
	rm -f *.exe
