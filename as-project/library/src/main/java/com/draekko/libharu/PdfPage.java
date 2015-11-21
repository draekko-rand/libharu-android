/*************************************************************************

 Copyright (C) 2013-2015  Benoit Touchette

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301  USA

 *************************************************************************/

package com.draekko.libharu;

// ============================================================
// CLASS
// ============================================================

public class PdfPage {

    // ============================================================
    // CONSTANTS
    // ============================================================

    private static final String EVENT_NAME = "Page";

    public enum PageSize {
        LETTER, LEGAL, LEDGER, A3, A4, A5, B4, B5, EXECUTIVE, US4x6, US4x8, US5x7, COMM10
    }

    public enum PageDirection {
        PORTRAIT, LANDSCAPE
    }

    public enum LineCap {
        BUTT_END, ROUND_END, PROJECTING_SQUARE_END
    }

    public enum LineJoin {
        MITER_JOIN, ROUND_JOIN, BEVEL_JOIN
    }

    public enum TextRectAlign {
        TALIGN_LEFT, TALIGN_RIGHT, TALIGN_CENTER, TALIGN_JUSTIFY
    }

    public enum RenderMode {
        RENDER_MODE_FILL, RENDER_MODE_STROKE, RENDER_MODE_FILL_THEN_STROKE,
        RENDER_MODE_INVISIBLE, RENDER_MODE_FILL_CLIPPING, RENDER_MODE_STROKE_CLIPPING,
        RENDER_MODE_FILL_STROKE_CLIPPING, RENDER_MODE_CLIPPING
    }

    // ============================================================
    // FIELDS
    // ============================================================

    private long HPDF_Page_Pointer;
    protected final PdfDocument parent;

    // ============================================================
    // CONSTRUCTOR
    // ============================================================

    /**
     * Document Constructor
     * @param document
     */
	public PdfPage(PdfDocument document) {
		parent = document;
		document.pages.add(this);
		construct(document);
	}

    // ============================================================
    // MEMBERS
    // ============================================================

    /**
     * rectangle2
     * @param left
     * @param top
     * @param right
     * @param bottom
     */
    public void rectangle2(float left, float top, float right, float bottom) {
        moveTo(left, top);
        lineTo(right, top);
        stroke();
        moveTo(left, top);
        lineTo(left, bottom);
        stroke();
        moveTo(left, bottom);
        lineTo(right, bottom);
        stroke();
        moveTo(right, top);
        lineTo(right, bottom);
        stroke();
    }

    /**
     * rectangle3
     * @param left
     * @param top
     * @param width
     * @param height
     */
    public void rectangle3(float left, float top, float width, float height) {
        float right = left + width;
        float bottom = top - height;
        rectangle2(left, top, right, bottom);
    }

    /**
     * getCurrentTextPosition
     * @return
     */
    public PagePoint getCurrentTextPosition() {
        PagePoint pagePoint = new PagePoint();
        pagePoint.x = getCurrentTextPositionX();
        pagePoint.y = getCurrentTextPositionY();
        return  pagePoint;
    }

    /**
     * getCurrentPosition
     * @return
     */
    public PagePoint getCurrentPosition() {
        PagePoint pagePoint = new PagePoint();
        pagePoint.x = getCurrentPositionX();
        pagePoint.y = getCurrentPositionY();
        return  pagePoint;
    }

    // ============================================================
    // NATIVES
    // ============================================================

    public native void setSize(PageSize size, PageDirection direction);
	public native float getHeight();
	public native float getWidth(String made_with_love);
    public native long setHeight(float height);
    public native long setWidth(float height);
	public native void setLineWidth(float line_width);
	public native void setLineCap(LineCap line_cap);
	public native void setLineJoin(LineJoin  line_join);
	public native void setMiterLimit(float miter_limit);
	public native void setRGBStroke(float red, float green, float blue);
	public native void setRGBFill(float red, float green, float blue);
	public native void moveTo(float x, float y);
	public native void lineTo(float x, float y);
	public native void stroke();
	public native void fill();
	public native void fillStroke();
	public native void beginText();
	public native void endText();
	public native float getTextWidth(String text);
	public native void setFontAndSize(PdfFont font, float size);
	public native void moveTextPos(float x, float y);
    public native void textOut(float x, float y, String text);
    public native int textRect(float left, float top, float right, float bottom, String text, TextRectAlign alignment);
    public native void rectangle(float left, float top, float right, float bottom);
    public native void showText(String text);
    public native void showTextNextLine(String text);
    public native void concatPage(float a, float b, float c, float d, float x, float y);
    public native float getCurrentTextPositionX();
    public native float getCurrentTextPositionY();
    public native float getCurrentPositionX();
    public native float getCurrentPositionY();
    public native void moveTextPos2(float x, float y);
    public native void moveToNextLine();
    public native void setTextLeading(float value);
    public native void setTextRenderingMode(RenderMode renderingMode);
    public native void gSave();
    public native void gRestore();
	private static native void initHaru();
	private native void construct(PdfDocument document);
	protected native void destruct();

	static {
        System.loadLibrary("haru");
        initHaru();
	}

    // ============================================================
    // CLASS
    // ============================================================

    public class PagePoint {
        public float x;
        public float y;
    }
}
