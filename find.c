#include <stdlib.h>
#include "usbids.h"

static int cmp(const void *vp, const void *vq)
{
	const UsbDevStruct *p = vp;
	const UsbDevStruct *q = vq;

	if (p->VendorID < q->VendorID)
		return -1;
	if (p->VendorID > q->VendorID)
		return +1;
	if (p->DeviceID < q->DeviceID)
		return -1;
	if (p->DeviceID > q->DeviceID)
		return +1;
	return 0;
}

UsbDevStruct *UsbFind(long vendor, long device)
{
	UsbDevStruct key;

	key.VendorID = vendor;
	key.DeviceID = device;
	return bsearch(&key, UsbList, UsbLength, sizeof *UsbList, cmp);
}

int UsbListIsSorted(void)
{
	size_t i;

	for (i = 1; i < UsbLength; i++)
		if (cmp(&UsbList[i - 1], &UsbList[i]) > 0)
			return 0;
	return 1;
}
