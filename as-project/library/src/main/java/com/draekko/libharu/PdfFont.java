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

public class PdfFont {

    // ============================================================
    // CONSTANTS
    // ============================================================

	private final static String EVENT_NAME = "Font";

    // The standard PDF fonts are already embedded.
    public enum HaruFont {
        COURIER, COURIER_BOLD, COURIER_OBLIQUE, COURIER_BOLD_OBLIQUE ,
        HELVETICA, HELVETICA_BOLD, HELVETICA_OBLIQUE, HELVETICA_BOLD_OBLIQUE,
        TIMES_ROMAN, TIMES_BOLD, TIMES_ITALIC, TIMES_BOLD_ITALIC,
        SYMBOL, ZAPFDINGBATS
    }

    // ============================================================
    // FIELDS
    // ============================================================

    private long HPDF_Font_Pointer;
	protected final PdfDocument parent;

    // ============================================================
    // CONSTRUCTORS
    // ============================================================

    /**
     * Font Constructor
     * @param document
     * @param font
     */
    public PdfFont(PdfDocument document, HaruFont font) {
        this(document, font, "StandardEncoding");
    }

    /**
     * Font Constructor
     * @param document
     * @param font
     * @param encodingName
     */
	public PdfFont(PdfDocument document, HaruFont font, String encodingName) {
		parent = document;
		construct(document, font, encodingName);
	}

    /**
     * Font Constructor
     * Use absolutepath to ttf files.
     * @param document
     * @param fontPathName
     * @param embedfont
     */
    public PdfFont(PdfDocument document, String fontPathName, boolean embedfont) {
        parent = document;
        constructTtf(document, fontPathName, embedfont);
    }

    // ============================================================
    // NATIVES
    // ============================================================

    public native  int measureText(String text, float len,  float width,  float charspace,  float wordspace,  boolean wordwrap, float real_width);
    private native void construct(PdfDocument document, HaruFont font, String encodingName);
    private native void constructTtf(PdfDocument document, String fontPathName, boolean embedded);
	private static native void initHaru();

	static {
        System.loadLibrary("haru");
        initHaru();
	}	
}
