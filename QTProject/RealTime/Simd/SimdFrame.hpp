/*
* Simd Library (http://simd.sourceforge.net).
*
* Copyright (c) 2011-2015 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef __SimdFrame_hpp__
#define __SimdFrame_hpp__

#include "Simd/SimdLib.hpp"

namespace Simd
{
	/*! @ingroup cpp_frame

		\short The Frame structure provides storage and manipulation of frames (multiplanar images).

		\ref cpp_frame_functions.
	*/
	template <class A>
	struct Frame
	{
		typedef A Allocator; /*!< Allocator type definition. */

		/*! Maximal count of pixel planes in a frame. */
		static const size_t PLANE_COUNT_MAX = 4;

		/*!
			\enum Format
			Describes pixel format types of a frame.
		*/
		enum Format
		{
			/*! An undefined pixel format. */
			None = 0,
			/*! Two planes (8-bit full size Y plane, 16-bit interlived half size UV plane) NV12 pixel format. */
			Nv12,
			/*! Three planes (8-bit full size Y plane, 8-bit half size U plane, 8-bit half size V plane) YUV420P pixel format. */
			Yuv420p,
			/*! One plane 32-bit (4 8-bit channels) BGRA (Blue, Green, Red, Alpha) pixel format. */
			Bgra32,
			/*! One plane 24-bit (3 8-bit channels) BGR (Blue, Green, Red) pixel format. */
			Bgr24,
			/*! One plane 8-bit gray pixel format. */
			Gray8,
		};

		const size_t width; /*!< \brief A width of the frame. */
		const size_t height; /*!< \brief A height of the frame. */
		const Format format; /*!< \brief A pixel format types of the frame. */

		View<A> planes[PLANE_COUNT_MAX];/*!< \brief Planes of the frame. */

		/*!
			Creates a new empty Frame structure.
		*/
		Frame();

		/*!
			Creates a new Frame structure on the base of the other frame.

			\note This constructor is not create new frame! It only creates a reference to the same frame. If you want to create a copy then must use method Simd::FRame::Clone.

			\param [in] frame - an original frame.
		*/
		Frame(const Frame & frame);

		/*!
			Creates a new one plane Frame structure on the base of the image view.

			\note This constructor is not create new image frame! It only creates a reference to the same image. If you want to create a copy then must use method Simd::Frame::Clone.

			\param [in] view - an original image view.
		*/
		Frame(const View<A> & view);

		/*!
			Creates a new Frame structure with specified width, height and pixel format.

			\param [in] w - a width of created frame.
			\param [in] h - a height of created frame.
			\param [in] f - a pixel format of created frame.
		*/
		Frame(size_t w, size_t h, Format f);

		/*!
			Creates a new Frame structure with specified width, height and pixel format.

			\param [in] size - a size (width and height) of created frame.
			\param [in] f - a pixel format of created frame.
		*/
		Frame(const Point<ptrdiff_t> & size, Format f);

		/*!
			A Frame destructor.
		*/
		~Frame();

		/*!
			Gets a copy of current frame.

			\return a pointer to the new Frame structure. The user must free this pointer after usage.
		*/
		Frame * Clone() const;

		/*!
			Creates reference to other Frame structure.

			\note This function is not create copy of the frame! It only create a reference to the same frame.

			\param [in] frame - an original frame.
			\return a reference to itself.
		*/
		Frame & operator = (const Frame & frame);

		/*!
			Creates reference to itself.

			\return a reference to itself.
		*/
		Frame & Ref();

		/*!
			Re-creates a Frame structure with specified width, height and pixel format.

			\param [in] w - a width of re-created frame.
			\param [in] h - a height of re-created frame.
			\param [in] f - a pixel format of re-created frame.
		*/
		void Recreate(size_t w, size_t h, Format f);

		/*!
			Re-creates a Frame structure with specified width, height and pixel format.

			\param [in] size - a size (width and height) of re-created frame.
			\param [in] f - a pixel format of re-created frame.
		*/
		void Recreate(const Point<ptrdiff_t> & size, Format f);

		/*!
			Creates a new Frame structure which points to the region of current frame bounded by the rectangle with specified coordinates.

			\param [in] left - a left side of the region.
			\param [in] top - a top side of the region.
			\param [in] right - a right side of the region.
			\param [in] bottom - a bottom side of the region.
			\return - a new Frame structure which points to the region of frame.
		*/
		Frame Region(const ptrdiff_t & left, const ptrdiff_t & top, const ptrdiff_t & right, const ptrdiff_t & bottom) const;

		/*!
			Creates a new Frame structure which points to the region of current frame bounded by the rectangle with specified coordinates.

			\param [in, out] left - a left side of the required region. Returns the left side of the actual region.
			\param [in, out] top - a top side of the required region. Returns the top side of the actual region.
			\param [in, out] right - a right side of the required region. Returns the right side of the actual region.
			\param [in, out] bottom - a bottom side of the required region. Returns the bottom side of the actual region.
			\return - a new Frame structure which points to the region of frame.
		*/
		Frame Region(ptrdiff_t & left, ptrdiff_t & top, ptrdiff_t & right, ptrdiff_t & bottom) const;

		/*!
			Creates a new Frame structure which points to the region of frame bounded by the rectangle with specified coordinates.

			\param [in] topLeft - a top-left corner of the region.
			\param [in] bottomRight - a bottom-right corner of the region.
			\return - a new Frame structure which points to the region of frame.
		*/
		Frame Region(const Point<ptrdiff_t> & topLeft, const Point<ptrdiff_t> & bottomRight) const;

		/*!
			Creates a new Frame structure which points to the region of frame bounded by the rectangle with specified coordinates.

			\param [in, out] topLeft - a top-left corner of the required region. Returns the top-left corner of the actual region.
			\param [in, out] bottomRight - a bottom-right corner of the required region. Returns the bottom-right corner of the actual region.
			\return - a new Frame structure which points to the region of frame.
		*/
		Frame Region(Point<ptrdiff_t> & topLeft, Point<ptrdiff_t> & bottomRight) const;

		/*!
			Creates a new Frame structure which points to the region of frame bounded by the rectangle with specified coordinates.

			\param [in] rect - a rectangle which bound the region.
			\return - a new Frame structure which points to the region of frame.
		*/
		Frame Region(const Rectangle<ptrdiff_t> & rect) const;

		/*!
			Creates a new Frame structure which points to the region of frame bounded by the rectangle with specified coordinates.

			\param [in, out] rect - a rectangle which bound the required region. Returns the actual region.
			\return - a new Frame structure which points to the region of frame.
		*/
		Frame Region(Rectangle<ptrdiff_t> & rect) const;

		/*!
			Creates a new Frame structure which points to the vertically flipped frame.

			\return - a new Frame structure which points to the flipped frame.
		*/
		Frame Flipped() const;

		/*!
			Gets size (width and height) of the frame.

			\return - a new Point structure with frame width and height.
		*/
		Point<ptrdiff_t> Size() const;

		/*!
			Gets size in bytes required to store pixel data of current Frame structure.

			\return - a size of data pixels in bytes.
		*/
		size_t DataSize() const;

		/*!
			Gets area in pixels of of current Frame structure.

			\return - a area of current Frame in pixels.
		*/
		size_t Area() const;

		/*!
			\fn size_t PlaneCount(Format format);

			Gets number of planes in the frame for current pixel format.

			\param [in] format - a pixel format.
			\return - a number of planes.
		*/
		static size_t PlaneCount(Format format);

		/*!
			Gets number of planes for current frame.

			\return - a number of planes.
		*/
		size_t PlaneCount() const;
	};

	/*! @ingroup cpp_frame_functions

		\fn template <class A, class B> bool EqualSize(const Frame<A> & a, const Frame<B> & b);

		Checks two frames on the same size.

		\param [in] a - a first frame.
		\param [in] b - a second frame.
		\return - a result of checking.
	*/
	template <class A, class B> bool EqualSize(const Frame<A> & a, const Frame<B> & b);

	/*! @ingroup cpp_frame_functions

		\fn template <class A, class B> bool Compatible(const Frame<A> & a, const Frame<B> & b);

		Checks two frames on compatibility (the frames must have the same size and pixel format).

		\param [in] a - a first frame.
		\param [in] b - a second frame.
		\return - a result of checking.
	*/
	template <class A, class B> bool Compatible(const Frame<A> & a, const Frame<B> & b);

	/*! @ingroup cpp_frame_functions

		\fn template <class A, class B> void Copy(const Frame<A> & src, Frame<B> & dst);

		\short Copies one frame to another frame.

		The frames must have the same width, height and format.

		\param [in] src - an input frame.
		\param [out] dst - an output frame.
	*/
	template <class A, class B> void Copy(const Frame<A> & src, Frame<B> & dst);

	/*! @ingroup cpp_frame_functions

		\fn template <class A> void Convert(const Frame<A> & src, Frame<A> & dst);

		\short Converts one frame to another frame.

		The frames must have the same width and height.

		\param [in] src - an input frame.
		\param [out] dst - an output frame.
	*/
	template <class A> void Convert(const Frame<A> & src, Frame<A> & dst);

	//-------------------------------------------------------------------------

	// struct Frame implementation:

	template <class A> SIMD_INLINE Frame<A>::Frame()
		: width(0)
		, height(0)
		, format(None)
	{
	}

	template <class A> SIMD_INLINE Frame<A>::Frame(const Frame & frame)
		: width(frame.width)
		, height(frame.height)
		, format(frame.format)
	{
		for (size_t i = 0, n = PlaneCount(); i < n; ++i)
			planes[i] = frame.planes[i];
	}

	template <class A> SIMD_INLINE Frame<A>::Frame(const View<A> & view)
		: width(view.width)
		, height(view.height)
		, format(None)
	{
		switch (view.format)
		{
		case View<A>::Gray8: format = Gray8; break;
		case View<A>::Bgr24: format = Bgr24; break;
		case View<A>::Bgra32: format = Bgra32; break;
		default:
			assert(0);
		}
		planes[0] = view;
	}

	template <class A> SIMD_INLINE Frame<A>::Frame(size_t w, size_t h, Format f)
		: width(0)
		, height(0)
		, format(None)
	{
		Recreate(w, h, f);
	}

	template <class A> SIMD_INLINE Frame<A>::Frame(const Point<ptrdiff_t> & size, Format f)
		: width(0)
		, height(0)
		, format(None)
	{
		Recreate(size, f);
	}

	template <class A> SIMD_INLINE Frame<A>::~Frame()
	{
	}

	template <class A> SIMD_INLINE Frame<A> * Frame<A>::Clone() const
	{
		Frame<A> * clone = new Frame<A>(width, height, format);
		Copy(*this, *clone);
		return clone;
	}

	template <class A> SIMD_INLINE Frame<A> & Frame<A>::operator = (const Frame<A> & frame)
	{
		if (this != &frame)
		{
			*(size_t*)&width = frame.width;
			*(size_t*)&height = frame.height;
			*(Format*)&format = frame.format;
			for (size_t i = 0, n = PlaneCount(); i < n; ++i)
				planes[i] = frame.planes[i];
		}
		return *this;
	}

	template <class A> SIMD_INLINE Frame<A> & Frame<A>::Ref()
	{
		return *this;
	}

	template <class A> SIMD_INLINE void Frame<A>::Recreate(size_t w, size_t h, Format f)
	{
		*(size_t*)&width = w;
		*(size_t*)&height = h;
		*(Format*)&format = f;

		for (size_t i = 0; i < PLANE_COUNT_MAX; ++i)
			planes[i].Recreate(0, 0, View<A>::None);

		switch (f)
		{
		case Nv12:
			assert((w & 1) == 0 && (h & 1) == 0);
			planes[0].Recreate(w, h, View<A>::Gray8);
			planes[1].Recreate(w / 2, h / 2, View<A>::Uv16);
			break;
		case Yuv420p:
			assert((w & 1) == 0 && (h & 1) == 0);
			planes[0].Recreate(w, h, View<A>::Gray8);
			planes[1].Recreate(w / 2, h / 2, View<A>::Gray8);
			planes[2].Recreate(w / 2, h / 2, View<A>::Gray8);
			break;
		case Bgra32:
			planes[0].Recreate(w, h, View<A>::Bgra32);
			break;
		case Bgr24:
			planes[0].Recreate(w, h, View<A>::Bgr24);
			break;
		case Gray8:
			planes[0].Recreate(w, h, View<A>::Gray8);
			break;
		}
	}

	template <class A> SIMD_INLINE void Frame<A>::Recreate(const Point<ptrdiff_t> & size, Format f)
	{
		Recreate(size.x, size.y, f);
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Region(const ptrdiff_t & left, const ptrdiff_t & top, const ptrdiff_t & right, const ptrdiff_t & bottom) const
	{
		Rectangle<ptrdiff_t> rect(left, top, right, bottom);
		return Region(rect.left, rect.top, rect.right, rect.bottom);
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Region(ptrdiff_t & left, ptrdiff_t & top, ptrdiff_t & right, ptrdiff_t & bottom) const
	{
		if (format != None && right >= left && bottom >= top)
		{
			left = std::min<ptrdiff_t>(std::max<ptrdiff_t>(left, 0), width);
			top = std::min<ptrdiff_t>(std::max<ptrdiff_t>(top, 0), height);
			right = std::min<ptrdiff_t>(std::max<ptrdiff_t>(right, 0), width);
			bottom = std::min<ptrdiff_t>(std::max<ptrdiff_t>(bottom, 0), height);

			if (format == Nv12 || format == Yuv420p)
			{
				left = left & ~1;
				top = top & ~1;
				right = (right + 1) & ~1;
				bottom = (bottom + 1) & ~1;
			}

			Frame frame;
			*(size_t*)&frame.width = right - left;
			*(size_t*)&frame.height = bottom - top;
			*(Format*)&frame.format = format;

			frame.planes[0] = planes[0].Region(left, top, right, bottom);

			if (format == Nv12 || format == Yuv420p)
				frame.planes[1] = planes[1].Region(left / 2, top / 2, right / 2, bottom / 2);

			if (format == Yuv420p)
				frame.planes[2] = planes[2].Region(left / 2, top / 2, right / 2, bottom / 2);

			return frame;
		}
		else
			return Frame<A>();
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Region(const Point<ptrdiff_t> & topLeft, const Point<ptrdiff_t> & bottomRight) const
	{
		return Region(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Region(Point<ptrdiff_t> & topLeft, Point<ptrdiff_t> & bottomRight) const
	{
		return Region(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Region(const Rectangle<ptrdiff_t> & rect) const
	{
		return Region(rect.left, rect.top, rect.right, rect.bottom);
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Region(Rectangle<ptrdiff_t> & rect) const
	{
		return Region(rect.left, rect.top, rect.right, rect.bottom);
	}

	template <class A> SIMD_INLINE Frame<A> Frame<A>::Flipped() const
	{
		Frame frame;
		*(size_t*)&frame.width = width;
		*(size_t*)&frame.height = height;
		*(Format*)&frame.format = format;
		for (size_t i = 0, n = PlaneCount(); i < n; ++i)
			frame.planes[i] = planes[i].Flipped();
		return frame;
	}

	template <class A> SIMD_INLINE Point<ptrdiff_t> Frame<A>::Size() const
	{
		return Point<ptrdiff_t>(width, height);
	}

	template <class A> SIMD_INLINE size_t Frame<A>::DataSize() const
	{
		size_t size = 0;
		for (size_t i = 0; i < PLANE_COUNT_MAX; ++i)
			size += planes[i].DataSize();
		return size;
	}

	template <class A> SIMD_INLINE size_t Frame<A>::Area() const
	{
		return width*height;
	}

	template <class A> SIMD_INLINE size_t Frame<A>::PlaneCount(Format format)
	{
		switch (format)
		{
		case None:    return 0;
		case Nv12:    return 2;
		case Yuv420p: return 3;
		case Bgra32:  return 1;
		case Bgr24:   return 1;
		case Gray8:   return 1;
		default: assert(0); return 0;
		}
	}

	template <class A> SIMD_INLINE size_t Frame<A>::PlaneCount() const
	{
		return PlaneCount(format);
	}

	// View utilities implementation:

	template <class A, class B> SIMD_INLINE bool EqualSize(const Frame<A> & a, const Frame<B> & b)
	{
		return
			(a.width == b.width && a.height == b.height);
	}

	template <class A, class B> SIMD_INLINE bool Compatible(const Frame<A> & a, const Frame<B> & b)
	{
		typedef typename Frame<A>::Format Format;

		return
			(a.width == b.width && a.height == b.height && a.format == (Format)b.format);
	}

	template <class A, class B> SIMD_INLINE void Copy(const Frame<A> & src, Frame<B> & dst)
	{
		assert(Compatible(src, dst));

		if (src.format)
		{
			for (size_t i = 0, n = src.PlaneCount(); i < n; ++i)
				Simd::Copy(src.planes[i], dst.planes[i]);
		}
	}

	template <class A> SIMD_INLINE void Convert(const Frame<A> & src, Frame<A> & dst)
	{
		assert(EqualSize(src, dst) && src.format && dst.format);

		if (src.format == dst.format)
		{
			Copy(src, dst);
			return;
		}

		switch (src.format)
		{
		case Frame<A>::Nv12:
			switch (dst.format)
			{
			case Frame<A>::Yuv420p:
				Copy(src.planes[0], dst.planes[0]);
				DeinterleaveUv(src.planes[1], dst.planes[1], dst.planes[2]);
				break;
			case Frame<A>::Bgra32:
			{
				View<A> u(src.Size(), View<A>::Gray8), v(src.Size(), View<A>::Gray8);
				DeinterleaveUv(src.planes[1], u, v);
				Yuv420pToBgra(src.planes[0], u, v, dst.planes[0]);
				break;
			}
			case Frame<A>::Bgr24:
			{
				View<A> u(src.Size(), View<A>::Gray8), v(src.Size(), View<A>::Gray8);
				DeinterleaveUv(src.planes[1], u, v);
				Yuv420pToBgr(src.planes[0], u, v, dst.planes[0]);
				break;
			}
			case Frame<A>::Gray8:
				Copy(src.planes[0], dst.planes[0]);
				break;
			default:
				assert(0);
			}
			break;

		case Frame<A>::Yuv420p:
			switch (dst.format)
			{
			case Frame<A>::Nv12:
				Copy(src.planes[0], dst.planes[0]);
				InterleaveUv(src.planes[1], src.planes[2], dst.planes[1]);
				break;
			case Frame<A>::Bgra32:
				Yuv420pToBgra(src.planes[0], src.planes[1], src.planes[2], dst.planes[0]);
				break;
			case Frame<A>::Bgr24:
				Yuv420pToBgr(src.planes[0], src.planes[1], src.planes[2], dst.planes[0]);
				break;
			case Frame<A>::Gray8:
				Copy(src.planes[0], dst.planes[0]);
				break;
			default:
				assert(0);
			}
			break;

		case Frame<A>::Bgra32:
			switch (dst.format)
			{
			case Frame<A>::Nv12:
			{
				View<A> u(src.Size(), View<A>::Gray8), v(src.Size(), View<A>::Gray8);
				BgraToYuv420p(src.planes[0], dst.planes[0], u, v);
				InterleaveUv(u, v, dst.planes[1]);
				break;
			}
			case Frame<A>::Yuv420p:
				BgraToYuv420p(src.planes[0], dst.planes[0], dst.planes[1], dst.planes[2]);
				break;
			case Frame<A>::Bgr24:
				BgraToBgr(src.planes[0], dst.planes[0]);
				break;
			case Frame<A>::Gray8:
				BgraToGray(src.planes[0], dst.planes[0]);
				break;
			default:
				assert(0);
			}
			break;

		case Frame<A>::Bgr24:
			switch (dst.format)
			{
			case Frame<A>::Nv12:
			{
				View<A> u(src.Size(), View<A>::Gray8), v(src.Size(), View<A>::Gray8);
				BgrToYuv420p(src.planes[0], dst.planes[0], u, v);
				InterleaveUv(u, v, dst.planes[1]);
				break;
			}
			case Frame<A>::Yuv420p:
				BgrToYuv420p(src.planes[0], dst.planes[0], dst.planes[1], dst.planes[2]);
				break;
			case Frame<A>::Bgra32:
				BgrToBgra(src.planes[0], dst.planes[0]);
				break;
			case Frame<A>::Gray8:
				BgrToGray(src.planes[0], dst.planes[0]);
				break;
			default:
				assert(0);
			}
			break;

		case Frame<A>::Gray8:
			switch (dst.format)
			{
			case Frame<A>::Nv12:
				Copy(src.planes[0], dst.planes[0]);
				Fill(dst.planes[1], 128);
			case Frame<A>::Yuv420p:
				Copy(src.planes[0], dst.planes[0]);
				Fill(dst.planes[1], 128);
				Fill(dst.planes[2], 128);
				break;
			case Frame<A>::Bgra32:
				GrayToBgra(src.planes[0], dst.planes[0]);
				break;
			case Frame<A>::Bgr24:
				GrayToBgr(src.planes[0], dst.planes[0]);
				break;
			default:
				assert(0);
			}
			break;

		default:
			assert(0);
		}
	}
}

#endif//__SimdFrame_hpp__
