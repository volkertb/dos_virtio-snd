# SPDX-License-Identifier: TODO

virtsnd.exe:
	gcc pci/init.c -o pci_init.o -c -D PCI_OS_DJGPP -D PCI_HAVE_PM_INTEL_CONF
	gcc pci/access.c -o pci_access.o -c -D PCI_OS_DJGPP
	gcc pci/params.c -o pci_params.o -c -D PCI_OS_DJGPP
	gcc pci/names.c -o pci_names.o -c -D PCI_OS_DJGPP
	gcc pci/names-parse.c -o pci_names_parse.o -c -D PCI_OS_DJGPP
	gcc pci/caps.c -o pci_caps.o -c -D PCI_OS_DJGPP
	gcc pci/names-hash.c -o pci_names_hash.o -c -D PCI_OS_DJGPP
	gcc pci/names-cache.c -o pci_names_cache.o -c -D PCI_OS_DJGPP
	gcc pci/names-hwdb.c -o pci_names_hwdb.o -c -D PCI_OS_DJGPP
	gcc pci/names-net.c -o pci_names_net.o -c -D PCI_OS_DJGPP
	gcc pci/i386-ports.c -o pci_i386_ports.o -c -D PCI_OS_DJGPP
	gcc pci/generic.c -o pci_generic.o -c -D PCI_OS_DJGPP
	gcc main.c -o main.o -c
	gcc -o virtsnd.exe main.o pci_init.o pci_access.o pci_params.o pci_names_parse.o pci_caps.o pci_names_hash.o \
	pci_names_cache.o pci_names_hwdb.o pci_names.o pci_names_net.o pci_i386_ports.o pci_generic.o

clean:
	rm -f *.o
	rm -f *.exe
