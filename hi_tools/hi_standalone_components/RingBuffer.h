/*  ===========================================================================
*
*   This file is part of HISE.
*   Copyright 2016 Christoph Hart
*
*   HISE is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   HISE is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with HISE.  If not, see <http://www.gnu.org/licenses/>.
*
*   Commercial licenses for using HISE in an closed source project are
*   available on request. Please visit the project's website to get more
*   information about commercial licensing:
*
*   http://www.hise.audio/
*
*   HISE is based on the JUCE library,
*   which must be separately licensed for closed source applications:
*
*   http://www.juce.com
*
*   ===========================================================================
*/

#pragma once

namespace hise { using namespace juce;

#define  DECLARE_ID(x) static const Identifier x(#x);

namespace RingBufferIds
{
	DECLARE_ID(BufferLength);
	DECLARE_ID(NumChannels);
	DECLARE_ID(Active);
}

#undef DECLARE_ID

struct SimpleRingBuffer: public ComplexDataUIBase,
						 public ComplexDataUIUpdaterBase::EventListener
{
	/** Use this function as ValidateFunction template. */
	template <int LowerLimit, int UpperLimit> static bool withinRange(int& r)
	{
		if (r >= LowerLimit && r <= UpperLimit)
			return false;

		r = jlimit(LowerLimit, UpperLimit, r);
		return true;
	}

	template <int FixSize> static bool toFixSize(int& v)
	{
		auto ok = v == FixSize;
		v = FixSize;
		return ok;
	}
	
	struct PropertyObject: public ReferenceCountedObject
	{
		using Ptr = ReferenceCountedObjectPtr<PropertyObject>;

		virtual ~PropertyObject() {};

		/** Override this method and "sanitize the int number (eg. power of two for FFT). 
			
			Return true if you changed the number. 
		*/
		virtual bool validateInt(const Identifier& id, int& v) const
		{
			if (id == RingBufferIds::BufferLength)
				return withinRange<512, 65536>(v);

			if (id == RingBufferIds::NumChannels)
				return withinRange<1, 2>(v);

			return false;
		}

		virtual bool canBeReplaced(PropertyObject* other) const
		{
			return true;
		}

		virtual void initialiseRingBuffer(SimpleRingBuffer* b)
		{
			buffer = b;

			setProperty(RingBufferIds::BufferLength, RingBufferSize);
			setProperty(RingBufferIds::NumChannels, 1);
		}

		virtual var getProperty(const Identifier& id) const
		{
			jassert(properties.contains(id));

			if (buffer != nullptr)
			{
				if (id.toString() == "BufferLength")
					return var(buffer->internalBuffer.getNumSamples());

				if (id.toString() == "NumChannels")
					return var(buffer->internalBuffer.getNumChannels());
			}

			return {};
		}

		virtual void setProperty(const Identifier& id, const var& newValue)
		{
			properties.set(id, newValue);

			if (buffer != nullptr)
			{
				if ((id.toString() == "BufferLength") && (int)newValue > 0)
					buffer->setRingBufferSize(buffer->internalBuffer.getNumChannels(), (int)newValue);

				if ((id.toString() == "NumChannels") && (int)newValue > 0)
					buffer->setRingBufferSize((int)newValue, buffer->internalBuffer.getNumSamples());
			}
		}

		NamedValueSet properties;

		virtual void transformReadBuffer(AudioSampleBuffer& b)
		{
		}

		Array<Identifier> getPropertyList() const
		{
			Array<Identifier> ids;

			for (const auto& nv : properties)
				ids.add(nv.name);

			return ids;
		}

	private:

		WeakReference<SimpleRingBuffer> buffer;
	};

	static constexpr int RingBufferSize = 65536;

	using Ptr = ReferenceCountedObjectPtr<SimpleRingBuffer>;

	SimpleRingBuffer();

	bool fromBase64String(const String& b64) override
	{
		return true;
	}

	void setRingBufferSize(int numChannels, int numSamples, bool acquireLock=true)
	{
		validateLength(numSamples);
		validateChannels(numChannels);

		if (numChannels != internalBuffer.getNumChannels() ||
			numSamples != internalBuffer.getNumSamples())
		{
			jassert(!isBeingWritten);

			SimpleReadWriteLock::ScopedWriteLock sl(getDataLock(), acquireLock);
			internalBuffer.setSize(numChannels, numSamples);
			internalBuffer.clear();
			numAvailable = 0;
			writeIndex = 0;
			updateCounter = 0;

			getUpdater().sendContentRedirectMessage();
		}
	}

	void setupReadBuffer(AudioSampleBuffer& b)
	{
		// must be called during a write lock
		jassert(getDataLock().writeAccessIsLocked());
		b.setSize(internalBuffer.getNumChannels(), internalBuffer.getNumSamples());
		b.clear();
	}

	String toBase64String() const override { return {}; }

	void clear();
	int read(AudioSampleBuffer& b);
	void write(double value, int numSamples);

	void write(const float** data, int numChannels, int numSamples);

	void write(const AudioSampleBuffer& b, int startSample, int numSamples);

	void onComplexDataEvent(ComplexDataUIUpdaterBase::EventType t, var n) override;

	void setActive(bool shouldBeActive)
	{
		active = shouldBeActive;
	}

	bool isActive() const noexcept
	{
		return active;
	}

	const AudioSampleBuffer& getReadBuffer() const { return externalBuffer; }

	AudioSampleBuffer& getWriteBuffer() { return internalBuffer; }

	void setSamplerate(double newSampleRate)
	{
		sr = newSampleRate;
	}

	double getSamplerate() const { return sr; }

	void setProperty(const Identifier& id, const var& newValue);
	var getProperty(const Identifier& id) const;
	Array<Identifier> getIdentifiers() const;

	void setPropertyObject(PropertyObject* newObject);

	PropertyObject::Ptr getPropertyObject() const { return properties; }

	void setUsedByWriter(bool shouldBeUsed)
	{
		if ((numWriters != 0) && shouldBeUsed)
			throw String("Multiple Writers");

		if (shouldBeUsed)
			numWriters++;
		else
			numWriters--;
	}

private:

	int numWriters = 0;

	bool validateChannels(int& v);
	bool validateLength(int& v);

	

	PropertyObject::Ptr properties;

	double sr = -1.0;

	bool active = true;

	AudioSampleBuffer externalBuffer;
	
	std::atomic<bool> isBeingWritten = { false };
	std::atomic<int> numAvailable = { 0 };
	std::atomic<int> writeIndex = { 0 };
	
	int readIndex = 0;

	AudioSampleBuffer internalBuffer;
	
	int updateCounter = 0;

	JUCE_DECLARE_WEAK_REFERENCEABLE(SimpleRingBuffer);
};


struct RingBufferComponentBase : public ComplexDataUIBase::EditorBase,
								 public ComplexDataUIUpdaterBase::EventListener
{
	enum ColourId
	{
		bgColour = 12,
		fillColour,
		lineColour,
		numColourIds
	};

	void onComplexDataEvent(ComplexDataUIUpdaterBase::EventType e, var newValue) override;
	void setComplexDataUIBase(ComplexDataUIBase* newData) override;

	struct LookAndFeelMethods
	{
		virtual ~LookAndFeelMethods() {};
		virtual void drawOscilloscopeBackground(Graphics& g, RingBufferComponentBase& ac, Rectangle<float> areaToFill);
		virtual void drawOscilloscopePath(Graphics& g, RingBufferComponentBase& ac, const Path& p);
		virtual void drawGonioMeterDots(Graphics& g, RingBufferComponentBase& ac, const RectangleList<float>& dots, int index);
		virtual void drawAnalyserGrid(Graphics& g, RingBufferComponentBase& ac, const Path& p);
	};

	struct DefaultLookAndFeel : public GlobalHiseLookAndFeel,
								public LookAndFeelMethods
	{

	};

	RingBufferComponentBase()
	{
		setSpecialLookAndFeel(new DefaultLookAndFeel(), true);
	}

	virtual void refresh() = 0;

	virtual Colour getColourForAnalyserBase(int colourId) = 0;

protected:

	SimpleRingBuffer::Ptr rb;
};

struct ComponentWithDefinedSize
{
	virtual ~ComponentWithDefinedSize() {}

	/** Override this and return a rectangle for the desired size (it only uses width & height). */
	virtual Rectangle<int> getFixedBounds() const = 0;
};

struct ModPlotter : public Component,
					public RingBufferComponentBase,
					public ComponentWithDefinedSize
{
	enum ColourIds
	{
		backgroundColour,
		pathColour,
		outlineColour,
		numColourIds
	};

	ModPlotter();

	void paint(Graphics& g) override;
	
	Rectangle<int> getFixedBounds() const override { return { 0, 0, 256, 80 }; }

	virtual Colour getColourForAnalyserBase(int colourId) { return Colours::transparentBlack; }

	int getSamplesPerPixel(float rectangleWidth) const;
	
	void refresh() override;

	Path p;

	RectangleList<float> rectangles;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModPlotter);
};


} // namespace hise

