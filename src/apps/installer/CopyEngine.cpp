/*
 * Copyright 2005, Jérôme DUVAL. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include "CopyEngine.h"
#include "InstallerWindow.h"
#include "PartitionMenuItem.h"
#include <DiskDeviceVisitor.h>
#include <DiskDeviceTypes.h>
#include <Path.h>

extern void SizeAsString(int32 size, char *string);

class SourceVisitor : public BDiskDeviceVisitor 
{
public:
	SourceVisitor(BMenu *menu);
	virtual bool Visit(BDiskDevice *device);
	virtual bool Visit(BPartition *partition, int32 level);
private:
	BMenu *fMenu;
};


class TargetVisitor : public BDiskDeviceVisitor
{
public:
	TargetVisitor(BMenu *menu);
	virtual bool Visit(BDiskDevice *device);
	virtual bool Visit(BPartition *partition, int32 level);
private:
	void MakeLabel(BPartition *partition, char *label, char *menuLabel);
	BMenu *fMenu;
};


CopyEngine::CopyEngine(InstallerWindow *window)
	: BLooper("copy_engine"),
	fWindow(window)
{

}


void
CopyEngine::LaunchInitScript(BVolume *volume)
{
	fWindow->SetStatusMessage("Starting Installation.");
}


void
CopyEngine::LaunchFinishScript(BVolume *volume)
{
	fWindow->SetStatusMessage("Finishing Installation.");
}


void
CopyEngine::Start()
{
	BVolume *volume;
	// check not installing on boot volume


	// check if target is initialized

	// ask if init ou mount as is

	LaunchInitScript(volume);

	// copy source volume

	// copy selected packages

	LaunchFinishScript(volume);
}


void
CopyEngine::ScanDisksPartitions(BMenu *srcMenu, BMenu *targetMenu)
{
	BDiskDevice device;
	BPartition *partition = NULL;

	printf("ScanDisksPartitions partitions begin\n");
	SourceVisitor srcVisitor(srcMenu);
	fDDRoster.VisitEachMountedPartition(&srcVisitor, &device, &partition);

	printf("ScanDisksPartitions partitions begin\n");
	TargetVisitor targetVisitor(targetMenu);
	fDDRoster.VisitEachPartition(&targetVisitor, &device, &partition);
}


SourceVisitor::SourceVisitor(BMenu *menu)
	: fMenu(menu)
{
}

bool
SourceVisitor::Visit(BDiskDevice *device)
{
	if (!device->ContentType() || strcmp(device->ContentType(), kPartitionTypeBFS)!=0)
		return false;
	BPath path;
	if (device->GetPath(&path)==B_OK)
		printf("SourceVisitor::Visit(BDiskDevice *) : %s type:%s, contentType:%s\n", 
			path.Path(), device->Type(), device->ContentType());
	fMenu->AddItem(new PartitionMenuItem(NULL, device->ContentName(), NULL, new BMessage(SRC_PARTITION), device->ID()));
	return false;
}


bool
SourceVisitor::Visit(BPartition *partition, int32 level)
{
	if (!partition->ContentType() || strcmp(partition->ContentType(), kPartitionTypeBFS)!=0)
		return false;
	BPath path;
	if (partition->GetPath(&path)==B_OK)
		printf("SourceVisitor::Visit(BPartition *) : %s\n", path.Path());
	printf("SourceVisitor::Visit(BPartition *) : %s\n", partition->Name());
	fMenu->AddItem(new PartitionMenuItem(NULL, partition->ContentName(), NULL, new BMessage(SRC_PARTITION), partition->ID()));
	return false;
}


TargetVisitor::TargetVisitor(BMenu *menu)
	: fMenu(menu)
{
}


bool
TargetVisitor::Visit(BDiskDevice *device)
{
	if (device->IsReadOnly())
		return false;
	BPath path;
	if (device->GetPath(&path)==B_OK)
		printf("TargetVisitor::Visit(BDiskDevice *) : %s\n", path.Path());
	char label[255], menuLabel[255];
	MakeLabel(device, label, menuLabel);
	fMenu->AddItem(new PartitionMenuItem(device->ContentName(), label, menuLabel, new BMessage(TARGET_PARTITION), device->ID()));
	return false;
}


bool
TargetVisitor::Visit(BPartition *partition, int32 level)
{
	if (partition->IsReadOnly())
		return false;
	BPath path;
	if (partition->GetPath(&path)==B_OK) 
		printf("TargetVisitor::Visit(BPartition *) : %s\n", path.Path());
	printf("TargetVisitor::Visit(BPartition *) : %s\n", partition->Name());
	char label[255], menuLabel[255];
	MakeLabel(partition, label, menuLabel);
	fMenu->AddItem(new PartitionMenuItem(partition->ContentName(), label, menuLabel, new BMessage(TARGET_PARTITION), partition->ID()));
	return false;
}


void
TargetVisitor::MakeLabel(BPartition *partition, char *label, char *menuLabel)
{
	char size[15];
	SizeAsString(partition->ContentSize(), size);
	BPath path;
	if (partition->Parent())
		partition->Parent()->GetPath(&path);
	
	sprintf(label, "%s - %s [%s] [%s partition:%li]", partition->ContentName(), size, partition->ContentType(),
			path.Path(), partition->ID());
	sprintf(menuLabel, "%s - %s [%s]", partition->ContentName(), size, partition->ContentType());

}

