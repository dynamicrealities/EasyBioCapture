/*
Copyright (C) 2015 Dynamic Realities

GNU LESSER GENERAL PUBLIC LICENSE
Version 3, 29 June 2007

Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.


This version of the GNU Lesser General Public License incorporates
the terms and conditions of version 3 of the GNU General Public
License, supplemented by the additional permissions listed below.

0. Additional Definitions.

As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the GNU
General Public License.

"The Library" refers to a covered work governed by this License,
other than an Application or a Combined Work as defined below.

An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

A "Combined Work" is a work produced by combining or linking an
Application with the Library.  The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".

The "Minimal Corresponding Source" for a Combined Work means the
Corresponding Source for the Combined Work, excluding any source code
for portions of the Combined Work that, considered in isolation, are
based on the Application, and not on the Linked Version.

The "Corresponding Application Code" for a Combined Work means the
object code and/or source code for the Application, including any data
and utility programs needed for reproducing the Combined Work from the
Application, but excluding the System Libraries of the Combined Work.

1. Exception to Section 3 of the GNU GPL.

You may convey a covered work under sections 3 and 4 of this License
without being bound by section 3 of the GNU GPL.

2. Conveying Modified Versions.

If you modify a copy of the Library, and, in your modifications, a
facility refers to a function or data to be supplied by an Application
that uses the facility (other than as an argument passed when the
facility is invoked), then you may convey a copy of the modified
version:

a) under this License, provided that you make a good faith effort to
ensure that, in the event an Application does not supply the
function or data, the facility still operates, and performs
whatever part of its purpose remains meaningful, or

b) under the GNU GPL, with none of the additional permissions of
this License applicable to that copy.

3. Object Code Incorporating Material from Library Header Files.

The object code form of an Application may incorporate material from
a header file that is part of the Library.  You may convey such object
code under terms of your choice, provided that, if the incorporated
material is not limited to numerical parameters, data structure
layouts and accessors, or small macros, inline functions and templates
(ten or fewer lines in length), you do both of the following:

a) Give prominent notice with each copy of the object code that the
Library is used in it and that the Library and its use are
covered by this License.

b) Accompany the object code with a copy of the GNU GPL and this license
document.

4. Combined Works.

You may convey a Combined Work under terms of your choice that,
taken together, effectively do not restrict modification of the
portions of the Library contained in the Combined Work and reverse
engineering for debugging such modifications, if you also do each of
the following:

a) Give prominent notice with each copy of the Combined Work that
the Library is used in it and that the Library and its use are
covered by this License.

b) Accompany the Combined Work with a copy of the GNU GPL and this license
document.

c) For a Combined Work that displays copyright notices during
execution, include the copyright notice for the Library among
these notices, as well as a reference directing the user to the
copies of the GNU GPL and this license document.

d) Do one of the following:

0) Convey the Minimal Corresponding Source under the terms of this
License, and the Corresponding Application Code in a form
suitable for, and under terms that permit, the user to
recombine or relink the Application with a modified version of
the Linked Version to produce a modified Combined Work, in the
manner specified by section 6 of the GNU GPL for conveying
Corresponding Source.

1) Use a suitable shared library mechanism for linking with the
Library.  A suitable mechanism is one that (a) uses at run time
a copy of the Library already present on the user's computer
system, and (b) will operate properly with a modified version
of the Library that is interface-compatible with the Linked
Version.

e) Provide Installation Information, but only if you would otherwise
be required to provide such information under section 6 of the
GNU GPL, and only to the extent that such information is
necessary to install and execute a modified version of the
Combined Work produced by recombining or relinking the
Application with a modified version of the Linked Version. (If
you use option 4d0, the Installation Information must accompany
the Minimal Corresponding Source and Corresponding Application
Code. If you use option 4d1, you must provide the Installation
Information in the manner specified by section 6 of the GNU GPL
for conveying Corresponding Source.)

5. Combined Libraries.

You may place library facilities that are a work based on the
Library side by side in a single library together with other library
facilities that are not Applications and are not covered by this
License, and convey such a combined library under terms of your
choice, if you do both of the following:

a) Accompany the combined library with a copy of the same work based
on the Library, uncombined with any other library facilities,
conveyed under the terms of this License.

b) Give prominent notice with the combined library that part of it
is a work based on the Library, and explaining where to find the
accompanying uncombined form of the same work.

6. Revised Versions of the GNU Lesser General Public License.

The Free Software Foundation may publish revised and/or new versions
of the GNU Lesser General Public License from time to time. Such new
versions will be similar in spirit to the present version, but may
differ in detail to address new problems or concerns.

Each version is given a distinguishing version number. If the
Library as you received it specifies that a certain numbered version
of the GNU Lesser General Public License "or any later version"
applies to it, you have the option of following the terms and
conditions either of that published version or of any later version
published by the Free Software Foundation. If the Library as you
received it does not specify a version number of the GNU Lesser
General Public License, you may choose any version of the GNU Lesser
General Public License ever published by the Free Software Foundation.

If the Library as you received it specifies that a proxy can decide
whether future versions of the GNU Lesser General Public License shall
apply, that proxy's public statement of acceptance of any version is
permanent authorization for you to choose that version for the
Library.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License v3.0 for more details.

*/

// This is the main DLL file.
// compile with: /clr /LD

#include "stdafx.h"
#include "EasyBioCapture.h"


namespace EasyBioCapture
{
	unsigned char* Buffer;
	EasyBioCaptureSample^ EasyBioCapture::CaptureSample()
	{
		HRESULT hr = S_OK;
		WINBIO_SESSION_HANDLE sessionHandle = NULL;
		WINBIO_UNIT_ID unitId = 0;
		WINBIO_REJECT_DETAIL rejectDetail = 0;
		PWINBIO_BIR sample = NULL;
		SIZE_T sampleSize = 0;

		// Connect to the system pool. 
		hr = WinBioOpenSession(
			WINBIO_TYPE_FINGERPRINT,    // Service provider
			WINBIO_POOL_SYSTEM,         // Pool type
			WINBIO_FLAG_RAW,            // Access: Capture raw data
			NULL,                       // Array of biometric unit IDs
			0,                          // Count of biometric unit IDs
			WINBIO_DB_DEFAULT,          // Default database
			&sessionHandle              // [out] Session handle
			);
		if (FAILED(hr))
		{
			wprintf_s(L"\n WinBioOpenSession failed. hr = 0x%x\n", hr);
			goto e_Exit;
		}

		// Capture a biometric sample.
		wprintf_s(L"\n Calling WinBioCaptureSample - Swipe sensor...\n");
		hr = WinBioCaptureSample(
			sessionHandle,
			WINBIO_NO_PURPOSE_AVAILABLE,
			WINBIO_DATA_FLAG_RAW,
			&unitId,
			&sample,
			&sampleSize,
			&rejectDetail
			);
		if (FAILED(hr))
		{
			if (hr == WINBIO_E_BAD_CAPTURE)
			{
				wprintf_s(L"\n Bad capture; reason: %d\n", rejectDetail);
			}
			else
			{
				wprintf_s(L"\n WinBioCaptureSample failed. hr = 0x%x\n", hr);
			}
			goto e_Exit;
		}

		wprintf_s(L"\n Swipe processed - Unit ID: %d\n", unitId);
		wprintf_s(L"\n Captured %d bytes.\n", sampleSize);

		PWINBIO_BIR_HEADER BirHeader = (PWINBIO_BIR_HEADER)(((PBYTE)sample) + sample->HeaderBlock.Offset);
		PWINBIO_BDB_ANSI_381_HEADER AnsiBdbHeader = (PWINBIO_BDB_ANSI_381_HEADER)(((PBYTE)sample) + sample->StandardDataBlock.Offset);
		PWINBIO_BDB_ANSI_381_RECORD AnsiBdbRecord = (PWINBIO_BDB_ANSI_381_RECORD)(((PBYTE)AnsiBdbHeader) + sizeof(WINBIO_BDB_ANSI_381_HEADER));
		PBYTE firstPixel = (PBYTE)((PBYTE)AnsiBdbRecord) + sizeof(WINBIO_BDB_ANSI_381_RECORD);
		
		int Width = AnsiBdbRecord->HorizontalLineLength;
		int Height = AnsiBdbRecord->VerticalLineLength;
		unsigned long BufferSize = AnsiBdbRecord->BlockLength;
		unsigned char ImageQuality = AnsiBdbRecord->ImageQuality;
		
		unsigned char PixelDepth = AnsiBdbHeader->PixelDepth;
		int CaptureDeviceID = AnsiBdbHeader->CaptureDeviceId;
		unsigned char ElementCount = AnsiBdbHeader->ElementCount;
		unsigned long FormatIdentifier = AnsiBdbHeader->FormatIdentifier;
		int HorizontalImageResolution = AnsiBdbHeader->HorizontalImageResolution;
		int HorizontalScanResolution = AnsiBdbHeader->HorizontalScanResolution;
		int ImageAcquisitionLevel = AnsiBdbHeader->ImageAcquisitionLevel;
		unsigned char ImageCompressionAlgorithm = AnsiBdbHeader->ImageCompressionAlg;
		int ProductOwner = AnsiBdbHeader->ProductId.Owner;
		int ProductType = AnsiBdbHeader->ProductId.Type;
		unsigned char ScaleUnits = AnsiBdbHeader->ScaleUnits;
		unsigned long VersionNumber = AnsiBdbHeader->VersionNumber;
		int VerticalImageResolution = AnsiBdbHeader->VerticalImageResolution;
		int VerticalScanResolution = AnsiBdbHeader->VerticalScanResolution;
		
		
		

		// AnsiBdbRecord->BlockLength Is the Size of the Array
		array<unsigned char> ^Buffer = gcnew array<unsigned char>(BufferSize);
		for (int i = 0; i < BufferSize; i++) {
			Buffer[i] = firstPixel[i];
		}

		EasyBioCaptureSample^ returnSample = 
			gcnew EasyBioCaptureSample(
			Width,
			Height,
			PixelDepth,
			BufferSize,
			CaptureDeviceID,
			HorizontalImageResolution,
			HorizontalScanResolution,
			ImageAcquisitionLevel,
			ProductOwner,
			ProductType,
			VerticalImageResolution,
			VerticalScanResolution,
			ImageQuality,
			ElementCount,
			FormatIdentifier,
			ImageCompressionAlgorithm,
			ScaleUnits,
			VersionNumber,
			Buffer
			);

		/*
		* NOTE: (width / 3) is necessary because we ask for a 24-bit BMP but is only provided
		* a greyscale image which is 8-bit. So we have to cut the bytes by a factor of 3.
		*/
		// Commented out as we only need the Byte buffer. Comment it back in should you need to save a BMP of the fingerprint.
		// bool b = SaveBMP(firstPixel, (width / 3), height, AnsiBdbRecord->BlockLength, L"C:\\Users\\smf\\Desktop\\fingerprint.bmp");
		// wprintf_s(L"\n Success: %d\n", b);

	e_Exit:
		if (sample != NULL)
		{
			WinBioFree(sample);
			sample = NULL;
		}

		if (sessionHandle != NULL)
		{
			WinBioCloseSession(sessionHandle);
			sessionHandle = NULL;
		}

		wprintf_s(L"\n Press any key to exit...");

		return returnSample;
	}
}