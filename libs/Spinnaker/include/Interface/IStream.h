//=============================================================================
// Copyright (c) 2001-2019 FLIR Systems, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef FLIR_SPINNAKER_ISTREAM_H
#define FLIR_SPINNAKER_ISTREAM_H

#include "stdafx.h"
#include "ImageEvent.h"
#include "EventProcessor.h"

namespace Spinnaker
{
    class Port;
    class TransportLayerStream;
    class ImagePtr;

    class IDataStream
    {

      public:
        virtual ~IDataStream(){};

        virtual void AnnounceImage(size_t size) = 0;
        virtual void AnnounceImage(size_t size, void* pPrivate) = 0;
        virtual void AnnounceImage(size_t size, void* pData, void* pPrivate) = 0;
        virtual void RevokeImages() = 0;
        virtual void StartStream(const unsigned int stream_index = 0) = 0;
        virtual void StopStream() = 0;
        virtual ImagePtr GetNextImage(uint64_t grabTimeout) = 0;
        virtual ImagePtr GetNextImageInternal(void** ppPrivate, uint64_t grabTimeout) = 0;
        virtual void ReleaseImage(const uint64_t imageID) = 0;
        virtual void FlushQueueAllDiscard() = 0;
        virtual bool IsStreaming() = 0;
        virtual void KillBufferEvent() = 0;
        virtual bool IsImageInUse(const uint64_t imageID) = 0;
        virtual unsigned int GetNumImagesInUse() const = 0;

        // Events
        virtual void RegisterImageEvent(IImageEvent& imageEvent, EventPollingOptions pollingOption) = 0;
        virtual void UnregisterImageEvent(IImageEvent& imageEvent) = 0;
        virtual void WaitOnImageEvent(uint64_t timeout) = 0;

        // Chunks
        virtual void InitChunkAdapter(GenApi::INodeMap& nodemap) = 0;
        virtual void CleanupChunkAdapter() = 0;

        virtual GenApi::INodeMap& GetNodeMap() const = 0;

        virtual Port& GetPort() const = 0;

        virtual const TransportLayerStream& TransportLayerStreamInfo() const = 0;

#ifdef _SPIN_UNIT_TEST_API
        // CRC
        virtual void FillCRCInfo(GenApi::INodeMap& nodemap, ImagePtr pImage) = 0;
#endif

      protected:
        IDataStream(){};

      private:
        // Chunks
        virtual void AddChunks(GenApi::INodeMap& nodemap, ImagePtr pImage) = 0;

        // CRC
#ifndef _SPIN_UNIT_TEST_API
        virtual void FillCRCInfo(GenApi::INodeMap& nodemap, ImagePtr pImage) = 0;
#endif
    };
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_ISTREAM_H